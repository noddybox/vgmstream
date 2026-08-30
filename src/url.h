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
// URL parser
//
#ifndef VGMSTREAM_URL_H
#define VGMSTREAM_URL_H

#include <string>

namespace vgmstream
{
    class URL
    {
    	public:

	    // Construct a URL.
	    URL(const std::string url);

	    // Is the URL parsed?
	    bool Valid() const;

	    // Get a reason the URL is invalid
	    const std::string& Error() const;

	    // Get the protocol
	    const std::string& Protocol() const;

	    // Get the hostname
	    const std::string& Hostname() const;

	    // Get the port number
	    int Port() const;

	    // Get the path
	    const std::string& Path() const;

	private:

	    bool		m_valid;
	    std::string		m_error;
	    std::string		m_protocol;
	    std::string		m_hostname;
	    std::string		m_path;
	    int			m_port;
    };

};

#endif
