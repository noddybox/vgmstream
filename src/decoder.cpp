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
// Decoder thread class
//
#include <gme/gme.h>

#include <unistd.h>

#include "decoder.h"
#include "filedecoder.h"
#include "filetype.h"
#include "sourcefile.h"
#include "log.h"
#include "config.h"
#include "constants.h"

namespace vgmstream
{
    Decoder::Decoder(Playlist& playlist,
		     Queue<Decoded>& output) : Thread(),
    						  m_playlist(playlist),
						  m_output(output)
    {
	CreateThread();
    }

    void Decoder::ThreadCode()
    {
	bool done = false;
	const Config& config = Config::Instance();

    	while(!done && !CancelRequested())
	{
	    PlaylistEntry *entry = m_playlist.Next();

	    if (entry == 0)
	    {
	    	if (config.PlaylistRepeat() && !config.MiscOutputDirSet())
		{
		    m_playlist.ReRead();

		    entry = m_playlist.Next();

		    if (entry == 0)
		    {
		    	VGMLOG("Failed to read next item from playlist");
			done = true;
		    }
		}
		else
		{
		    done = true;
		}
	    }

	    if (!done)
	    {

		FileType file_type(entry->Filename());

		FileDecoder *decoder = file_type.Decoder();

		if (decoder == 0)
		{
		    VGMLOG("Error fetching decoder: %s",
		    			file_type.Error().c_str());
		}
		else
		{
		    if (decoder->Initialise(*entry))
		    {
		    	Decoded decoded;

			if (decoder->Decode(decoded))
			{
			    decoded.Info().System(file_type.System());
			    m_output.Push(decoded);
			}
			else
			{
			    VGMLOG("Failed to decode %s: %s",
						    entry->Filename().c_str(),
						    decoder->Error().c_str());
			}
		    }
		    else
		    {
			VGMLOG("Failed to initialise decoder: %s",
						decoder->Error().c_str());
		    }

		    delete decoder;
		}

		if (m_output.Size() > Constants::MAX_QUEUE_SIZE)
		{
		    VGMLOG("Waiting for decoded output queue to reduce");

		    while (!CancelRequested() &&
		    		m_output.Size() > Constants::MAX_QUEUE_SIZE)
		    {
			::sleep(1);
		    }

		    VGMLOG("Resuming file decoding");
		}
	    }
	    
	    if (entry != 0)
	    {
	    	delete entry;
		entry = 0;
	    }
	}
    }
};
