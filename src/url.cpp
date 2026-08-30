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
#include "url.h"
#include "util.h"

namespace vgmstream
{
    URL::URL(const std::string url) : m_valid(false),
				      m_error(),
				      m_protocol(),
				      m_hostname(),
				      m_path(),
				      m_port(0)
    {
	std::string workurl(url);
	std::size_t pos = workurl.find_first_of(':');

	if (pos == std::string::npos)
	{
	    m_error = "Missing protocol";
	    return;
	}

	m_protocol = workurl.substr(0, pos);

	if (m_protocol == "http")
	{
	    m_port = 80;
	}
	else
	{
	    m_error = "Unsupported protocol " + m_protocol;
	    return;
	}

	workurl = workurl.substr(pos + 1);

	while(!workurl.empty() && workurl[0] == '/')
	{
	    workurl = workurl.substr(1);
	}

	pos = workurl.find_first_of('/');

	if (pos == std::string::npos)
	{
	    m_hostname = workurl;
	}
	else
	{
	    m_hostname = workurl.substr(0, pos);
	    m_path = workurl.substr(pos);
	}

	if (m_hostname.length() == 0)
	{
	    m_error = "Missing hostname";
	    return;
	}

	pos = m_hostname.find_first_of(':');

	if (pos != std::string::npos)
	{
	    std::string port(m_hostname.substr(pos + 1));

	    if (!Util::ParseInt(port, m_port))
	    {
	    	m_error = "Invalid port number " + port;
		return;
	    }

	    m_hostname = m_hostname.substr(0, pos);
	}

	m_valid = true;
    }

    bool URL::Valid() const
    {
    	return m_valid;
    }

    const std::string& URL::Error() const
    {
    	return m_error;
    }

    const std::string& URL::Protocol() const
    {
    	return m_protocol;
    }

    const std::string& URL::Hostname() const
    {
    	return m_hostname;
    }

    int URL::Port() const
    {
    	return m_port;
    }

    const std::string& URL::Path() const
    {
    	return m_path;
    }
};
