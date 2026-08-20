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

#include <unistd.h>

#include "streamer.h"
#include "mp3file.h"
#include "config.h"
#include "log.h"

namespace vgmstream
{
    Streamer::Streamer(Queue<Mp3File>& input) : Thread(),
						m_input(input)
    {
	CreateThread();
    }

    void Streamer::ThreadCode()
    {
	const Config& config = Config::Instance();
	bool done = false;

    	while(!done)
	{
	    Mp3File output;

	    if (m_input.Pop(output))
	    {
		if (config.MiscOutputDirSet())
		{
		    std::string filename =
			config.MiscOutputDir() + "/" + output.Entry().Mp3Name();

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
		else
		{
		    VGMLOG("TODO: icecast output");
		}
	    }
	    else
	    {
	    	done = true;
	    }
	}
    }
};
