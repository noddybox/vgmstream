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
// Thread base class
//
#include <gme/gme.h>

#include "decoder.h"
#include "gmeapi.h"
#include "sidapi.h"
#include "filetype.h"
#include "sourcefile.h"
#include "log.h"
#include "config.h"

namespace vgmstream
{
    Decoder::Decoder(Playlist& playlist,
		     Queue<Decoded>& output) : Thread(),
    						  m_playlist(playlist),
						  m_output(output)
    {
	CreateThread();
    }

    Decoder::~Decoder()
    {
    }

    void Decoder::ThreadCode()
    {
	bool done = false;
	const Config& config = Config::Instance();

    	while(!Cancelled() && !done)
	{
	    std::string filename;

	    if (!m_playlist.Next(filename))
	    {
	    	if (config.PlaylistRepeat() && !config.MiscOutputDirSet())
		{
		    m_playlist.ReRead();
		}
		else
		{
		    done = true;
		}
	    }

	    if (!done)
	    {
	    	FileType type(filename);
		bool is_gme = false;
		bool is_sid = false;

		switch (type.Type())
		{
		    case FileType::eType::NotExist:
			VGMLOG("Unable to open file %s", filename.c_str());
			break;

		    case FileType::eType::Unknown:
			VGMLOG("Unable to determine filetype of %s",
				    filename.c_str());
			break;

		    case FileType::eType::SID:
		    	is_sid = true;
			break;

		    default:
		    	is_gme = true;
			break;
		}

		if (is_gme)
		{
		    GmeApi gme(filename, 0);

		    if (gme.Initialised())
		    {
			Decoded decoded;

			if (gme.Decode(decoded))
			{
			    m_output.Push(decoded);
			}
		    }
		}

		if (is_sid)
		{
		    SidApi sid(filename, 0);

		    if (sid.Initialised())
		    {
			Decoded decoded;

			if (sid.Decode(decoded))
			{
			    m_output.Push(decoded);
			}
		    }
		}
	    }
	}

	Exiting();
    }
};
