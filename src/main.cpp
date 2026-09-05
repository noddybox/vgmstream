// vgmstream - an Icecast 2 source for video games music trancoded to MP3
// Copyright (C) 2026  Ian Cowburn <deathstation9000@gmail.com>
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//
// Main
//
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <csignal>

#include <unistd.h>

#include "log.h"
#include "config.h"
#include "playlist.h"
#include "decoder.h"
#include "decoded.h"
#include "queue.h"
#include "sourcefile.h"
#include "mp3encoder.h"
#include "streamer.h"
#include "mp3file.h"
#include "util.h"
#include "constants.h"

namespace
{
    volatile std::sig_atomic_t terminate_signal = 0;
    volatile std::sig_atomic_t skip_signal = 0;

    extern "C" void HandleTermination(int sig)
    {
    	terminate_signal = 1;
    }

    extern "C" void HandleSkip(int sig)
    {
    	skip_signal = 1;
    }
};

int main(int argc, char *argv[])
{
    std::string name(vgmstream::Util::Basename(argv[0]));
    bool make_daemon = false;
    std::string config_file("/etc/vgmstreamrc");

    int arg = 1;

    while (arg < argc && argv[arg][0] == '-')
    {
	bool display_usage = false;

    	switch(argv[arg][1])
	{
	    case 'c':
		if (++arg < argc)
		{
		    config_file = argv[arg];
		}
		else
		{
		    display_usage = true;
		}
	    	break;

	    case 'd':
		make_daemon = true;
	    	break;

	    default:
	    	display_usage = true;
		break;
	}

	if (display_usage)
	{
	    std::cerr << name
		      << ": usage "
		      << name
		      << " [-c file] [-d]"
		      << std::endl;

	    return 1;
	}

	arg++;
    }

    if (make_daemon)
    {
	vgmstream::Util::MakeDaemon();
    }

    vgmstream::Log::SetLog(name, make_daemon);

    if (!vgmstream::Config::Open(config_file))
    {
    	return 1;
    }

    const vgmstream::Config config = vgmstream::Config::Instance();

    bool playlist_ok;

    vgmstream::Playlist playlist(playlist_ok);

    if (!playlist_ok)
    {
	VGMLOG("%s", playlist.Error().c_str());
    	return 1;
    }

    // As SIGPIPE can be caused if we've not streamed for a bit, ignore it
    // so that we can degrade properly
    std::signal(SIGPIPE, SIG_DFL);

    // Handle termination and skip signals
    std::signal(SIGINT, HandleTermination);
    std::signal(SIGTERM, HandleTermination);
    std::signal(SIGUSR1, HandleSkip);

    // From here on in, we're entering the main processing loop
    vgmstream::Queue<vgmstream::Decoded> decoded_queue;
    vgmstream::Queue<vgmstream::Mp3File> stream_queue;

    vgmstream::Decoder decoder(playlist, decoded_queue);
    vgmstream::MP3Encoder encoder(decoded_queue, stream_queue);

    // If we're streaming, wait for a couple of MP3 files before starting
    // the streamer.  Otherwise we get the chance of a SIGPIPE from the
    // streamer as it connects to the server, but doesn't send for a while.
    if (!config.MiscOutputDirSet())
    {
    	VGMLOG("Waiting for MP3 streaming queue to seed");

	std::size_t seed = vgmstream::Constants::SEED_MP3;

	if (!config.PlaylistRepeat())
	{
	    seed = std::min(playlist.Size(), seed);
	}

	while(decoder.Alive() &&
	      encoder.Alive() &&
	      terminate_signal == 0 &&
	      stream_queue.Size() < seed)
	{
	    ::sleep(1);
	}
    }

    VGMLOG("Starting streamer");

    vgmstream::Streamer streamer(stream_queue);

    VGMLOG("Entering main loop");

    while(decoder.Alive() &&
    	  encoder.Alive() &&
	  streamer.Alive() &&
	  terminate_signal == 0)
    {
    	::sleep(1);

	if (skip_signal == 1)
	{
	    streamer.Skip();
	    skip_signal = 0;
	}
    }

    if (terminate_signal == 1)
    {
	VGMLOG("Termination requested -- exiting");
    }
    else
    {
	VGMLOG("One or more threads dead -- exiting");
    }

    // If one of the other threads died, cancel the decoder thread
    if (decoder.Alive())
    {
	VGMLOG("Waiting for decoder to die");
	decoder.Cancel(terminate_signal == 1);
	decoder.Join();
    }

    // Wait for outputs once decoder has exited and we're not terminating
    if (terminate_signal == 0)
    {
	VGMLOG("Waiting for decoded queue to empty");

	while(encoder.Alive() && decoded_queue.Size() > 0)
	{
	    ::sleep(1);
	}
    }

    VGMLOG("Waiting for MP3 encoder to die");
    encoder.Cancel(terminate_signal == 1);
    encoder.Join();

    if (terminate_signal == 0)
    {
	VGMLOG("Waiting for streaming queue to empty");

	while(streamer.Alive() && stream_queue.Size() > 0)
	{
	    ::sleep(1);
	}
    }

    VGMLOG("Waiting for streamer to die");
    streamer.Cancel(terminate_signal == 1);
    streamer.Join();

    VGMLOG("Exiting");
    return 0;
}
