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
// Interface to libgme
//
#ifndef VGMSTREAM_GMEAPI_H
#define VGMSTREAM_GMEAPI_H

#include <string>

#include <gme/gme.h>

#include "decoded.h"
#include "filetype.h"

namespace vgmstream
{
    class GmeApi
    {
    	public:

	    // Construct an interface to libgme using the supplied file.
	    //
	    GmeApi(const std::string& path, int track,
		   const std::string& system);

	    // Clean up
	    ~GmeApi();

	    // Whether the decoder initialised OK
	    bool Initialised() const;

	    // The reason for the last error
	    const std::string& Error() const;

	    // Get the number of tracks in the file
	    int TrackCount() const;

	    // Get the result of decoding.  Returns true if decoding worked.
	    bool Decode(Decoded& result);

	private:

	    bool		m_initialised;
	    std::string		m_system;
	    Music_Emu		*m_emu;
	    gme_info_t		*m_info;
	    int			m_track_count;
	    std::string		m_error;

	    bool Error(const gme_err_t message);

    };
};

#endif
