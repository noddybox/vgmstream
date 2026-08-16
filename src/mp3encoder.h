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
#ifndef VGMSTREAM_MP3ENCODER_H
#define VGMSTREAM_MP3ENCODER_H

#include <vector>
#include <string>

#include "thread.h"
#include "decoded.h"
#include "mp3file.h"
#include "queue.h"

namespace vgmstream
{
    class MP3Encoder : public Thread
    {
    	public:

	    // Constructor
	    MP3Encoder(Queue<Decoded>& input,
		       Queue<Mp3File>& output);

	protected:

	    void ThreadCode();

	private:

	    Queue<Decoded>& 	m_input;
	    Queue<Mp3File>&	m_output;

    };
};

#endif
