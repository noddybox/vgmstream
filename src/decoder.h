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
#ifndef VGMSTREAM_DECODER_H
#define VGMSTREAM_DECODER_H

#include <string>

#include "thread.h"
#include "playlist.h"
#include "decoded.h"
#include "queue.h"

namespace vgmstream
{
    class Decoder : public Thread
    {
    	public:

	    // Constructor
	    Decoder(Playlist& playlist, Queue<Decoded>& output);

	protected:

	    void ThreadCode();

	private:

	    Playlist		m_playlist;
	    Queue<Decoded>&	m_output;

    };
};

#endif
