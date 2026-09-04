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
// Interface to libshout
//
#ifndef VGMSTREAM_SHOUTAPI_H
#define VGMSTREAM_SHOUTAPI_H

#include <string>

#include <shout/shout.h>

#include "url.h"

namespace vgmstream
{
    class ShoutApi
    {
    	public:

	    // Constructor
	    ShoutApi(const URL& url,
		     const std::string& password,
		     bool public_stream);

	    // Clean up
	    ~ShoutApi();

	    // Whether the API was initialised OK and connected
	    bool Initialised() const;

	    // Why there has been an error
	    const std::string& Error() const;

	    // Start a new track.  Returns true if successful.
	    bool StartTrack(const std::string& album,
	    		    const std::string& artist,
			    const std::string& title,
			    const std::string& year);


	    // Send a buffer to the icecast server.  Returns true if the
	    // buffer was sent.
	    bool Write(const char *buffer, std::size_t size);

	    // Wait for streaming to be available again
	    void Sync();

	private:

	    shout_t	*m_shout;
	    std::string	m_error;

	    bool	IsError(int status, const char *message);
    };
};

#endif
