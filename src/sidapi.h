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
// Interface to libsidplyfp
//
#ifndef VGMSTREAM_SIDAPI_H
#define VGMSTREAM_SIDAPI_H

#include <string>

#include "sourcefile.h"
#include "decoded.h"

namespace vgmstream
{
    class SidApi
    {
    	public:

	    // Construct an interface to libsidplyfp using the supplied file
	    // and the picked subtune.  The default subtune will be used
	    // if track is -1 if there is one, else the first is chosen.
	    SidApi(const std::string& path, int track);

	    // Clean up
	    ~SidApi();

	    // Whether the API was initialised OK
	    bool Initialised() const;

	    // Get the default track for the file
	    int DefaultTrack() const;

	    // Get the number of tracks in the file
	    int TrackCount() const;

	    // Get the result of decoding.  Returns true if decoding worked.
	    bool Decode(Decoded& result);

	private:

	    bool		m_initialised;
	    int			m_default_track;
	    int			m_track_count;

	    static SourceFile	*m_kernal;
	    static SourceFile	*m_chargen;
	    static SourceFile	*m_basic;

    };
};

#endif
