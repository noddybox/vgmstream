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
#include <unistd.h>

#include "streamer.h"
#include "config.h"

namespace vgmstream
{
    Streamer::Streamer(Queue<std::vector<unsigned char>>& input)
			   	: Thread(),
				  m_input(input),
				  m_stop(false)
    {
	CreateThread();
    }

    void Streamer::ThreadCode()
    {
	const Config& config = Config::Instance();

    	while(!Cancelled())
	{
	    std::vector<unsigned char> output;

	    while (!m_input.Pop(output))
	    {
		if (m_stop)
		{
		    return;
		}

	    	::sleep(1);
	    }
	}
    }

    void Streamer::RequestStop()
    {
    	m_stop = true;
    }
};
