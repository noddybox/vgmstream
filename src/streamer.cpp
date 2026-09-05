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
// MP3 encoding thread
//
#include <fstream>
#include <iostream>
#include <algorithm>

#include <unistd.h>

#include "streamer.h"
#include "mp3file.h"
#include "shoutapi.h"
#include "config.h"
#include "log.h"

namespace vgmstream
{
    Streamer::Streamer(Queue<Mp3File>& input) : Thread(),
						m_input(input)
    {
	CreateThread();
	SetQueue(&m_input);
    }

    void Streamer::ThreadCode()
    {
	const Config& config = Config::Instance();

	if (config.MiscOutputDirSet())
	{
	    FileOutputMode();
	}
	else
	{
	    StreamOutputMode();
	}
    }

    void Streamer::FileOutputMode()
    {
	const Config& config = Config::Instance();

    	while(!CancelRequested())
	{
	    Mp3File output;

	    if (m_input.Pop(output))
	    {
		std::string filename =
		    config.MiscOutputDir() + "/" + output.Info().Mp3Name();

		VGMLOG("Saving MP3 to %s", filename.c_str());

		std::ofstream file (filename, std::ios::out |
					      std::ios::binary);

		if (file)
		{
		    file.write(output.Data(), output.Size());
		    file.close();
		}
		else
		{
		    VGMLOG("Failed to create %s", filename.c_str());
		}
	    }
	}
    }

    void Streamer::StreamOutputMode()
    {
	const std::size_t BUFFER_SIZE = 4096;
	const Config& config = Config::Instance();

	ShoutApi shoutcast(URL(config.IcecastUrl()),
			   config.IcecastPassword(),
			   config.IcecastPublic());

	if (!shoutcast.Initialised())
	{
	    VGMLOG("Failed to connect to server: %s",
	    		shoutcast.Error().c_str());
	    return;
	}

    	while(!CancelRequested())
	{
	    Mp3File output;

	    if (m_input.Pop(output))
	    {
		if (!shoutcast.StartTrack(output.Info().Album(),
					  output.Info().Artist(),
					  output.Info().Title(),
					  output.Info().Year()))
		{
		    VGMLOG("Failed to set stream metadata: %s",
		    			shoutcast.Error().c_str());
		    return;
		}

		std::size_t written = 0;

		while (written < output.Size() && !ForceCancelRequested())
		{
		    std::size_t size = std::min(BUFFER_SIZE,
		    				output.Size() - written);

		    if (!shoutcast.Write(output.Data() + written, size))
		    {
			VGMLOG("Failed to stream output: %s",
					    shoutcast.Error().c_str());
			return;
		    }

		    shoutcast.Sync();

		    written += size;
		}
	    }
	}
    }
};
