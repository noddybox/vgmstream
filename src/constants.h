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
// Global constants
//
#ifndef VGMSTREAM_CONSTANTS_H
#define VGMSTREAM_CONSTANTS_H

namespace vgmstream
{
    class Constants
    {
    	public:

	    // The number if MP£ files to seed before starting the streamer
	    static const int SEED_MP3;

	    // The number of queue items to have before generation waits
	    // for something to be consumed
	    static const int MAX_QUEUE_SIZE;

	    // The default frequency for WAV files
	    static const int DEFAULT_WAV_FREQUENCY;

	private:

	    // Doesn't make sense to create this object
	    Constants()
	    {
	    }
    };
};

#endif
