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

#include <gme/gme.h>

#include "mp3encoder.h"
#include "lameapi.h"
#include "log.h"
#include "config.h"
#include "constants.h"

namespace vgmstream
{
    MP3Encoder::MP3Encoder(Queue<Decoded>& input,
		           Queue<Mp3File>& output) : Thread(),
						     m_input(input),
						     m_output(output)
    {
	CreateThread();
	SetQueue(&m_input);
    }

    void MP3Encoder::ThreadCode()
    {
	const Config& config = Config::Instance();

    	while(!CancelRequested())
	{
	    Decoded decoded;

	    if (m_input.Pop(decoded))
	    {
		LameApi lame(decoded, config.MiscOutputDirSet());

		if (lame.Initialised())
		{
		    Mp3File mp3(lame.Data(), lame.Size(), decoded.Info());

		    m_output.Push(mp3);

		    if (m_output.Size() > Constants::MAX_QUEUE_SIZE)
		    {
		    	VGMLOG("Waiting for MP3 output queue to reduce");

			while (!CancelRequested() &&
				    m_output.Size() > Constants::MAX_QUEUE_SIZE)
			{
			    ::sleep(1);
			}

		    	VGMLOG("Resuming MP3 encoding");
		    }
		}
	    }
	}
    }
};
