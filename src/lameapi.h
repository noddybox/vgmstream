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
// Interface to libmp3lame
//
#ifndef VGMSTREAM_LAMEAPI_H
#define VGMSTREAM_LAMEAPI_H

#include <vector>

#include "decoded.h"

namespace vgmstream
{
    class LameApi
    {
    	public:

	    // Construct an interface and do the encoding.
	    // If it works Initialised() will return true and Data() will
	    // return the encoded data.  ID3 tags will only be inlcuded if
	    // tags is true.
	    LameApi(Decoded& pcm, bool tags);

	    // Whether the API was initialised OK
	    bool Initialised() const;

	    // The size of the encoded data
	    std::size_t Size() const;

	    // The encoded data
	    const char *Data() const;

	private:

	    bool		m_initialised;
	    std::vector<char>	m_data;
    };
};

#endif
