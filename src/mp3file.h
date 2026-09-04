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
// MP3 encoded file
//
#ifndef VGMSTREAM_MP3FILE_H
#define VGMSTREAM_MP3FILE_H

#include <vector>

#include "trackinfo.h"

namespace vgmstream
{
    class Mp3File
    {
    	public:

	    // Construct an empty MP3 file based on the passed filename if the
	    // file was written to disk and passed memory
	    Mp3File(const char *memory,
		    std::size_t size,
		    const TrackInfo& info);

	    // Construct an empty object
	    Mp3File();

	    // The track info
	    const TrackInfo& Info() const;

	    // Get the size of the MP3 data
	    std::size_t Size() const;

	    // Get a pointer to the MP3 data
	    const char *Data() const;

	private:

	    std::vector<char>	m_data;
	    TrackInfo		m_info;
    };
};

#endif
