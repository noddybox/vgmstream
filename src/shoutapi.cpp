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
// Interface to libshot
//
#include "shoutapi.h"
#include "url.h"

namespace vgmstream
{
    ShoutApi::ShoutApi(const URL& url,
		       const std::string& password,
		       bool public_stream) : m_shout(0), m_error()
    {
	if (!url.Valid())
	{
	    m_error = "Invalid URL: " + url.Error();
	    return;
	}

    	shout_init();

	if ((m_shout = shout_new()) == 0)
	{
	    m_error = "Failed to allocate libshout instance";
	    return;
	}

	if (IsError(shout_set_host(m_shout, url.Hostname().c_str()),
		    "Failed to set hostname")) return;

	if (IsError(shout_set_port(m_shout, url.Port()),
		    "Failed to set port number")) return;

	if (IsError(shout_set_password(m_shout, password.c_str()),
		    "Failed to set password")) return;

	if (IsError(shout_set_mount(m_shout, url.Path().c_str()),
		    "Failed to set mount")) return;

	if (IsError(shout_set_content_format(m_shout,
					     SHOUT_FORMAT_MP3,
					     SHOUT_USAGE_AUDIO,
					     0),
		    "Failed to set format")) return;

	if (IsError(shout_set_protocol(m_shout, SHOUT_PROTOCOL_HTTP),
		    "Failed to set protocol")) return;

	if (IsError(shout_set_public(m_shout, public_stream ? 1 : 0),
		    "Failed to set public flag")) return;

	if (IsError(shout_open(m_shout), "Failed to connect to server"))
	    return;
    }

    ShoutApi::~ShoutApi()
    {
    	if (m_shout != 0)
	{
	    shout_close(m_shout);
	    shout_free(m_shout);
	    m_shout = 0;
	}

	shout_shutdown();
    }

    bool ShoutApi::Initialised() const
    {
    	return m_shout != 0;
    }

    const std::string& ShoutApi::Error() const
    {
    	return m_error;
    }

    bool ShoutApi::StartTrack(const std::string& album,
	    		      const std::string& artist,
			      const std::string& title,
			      const std::string& year)
    {
	shout_metadata_t *data = shout_metadata_new();

	if (data == 0)
	{
	    m_error = "Failed to allocate metadata";
	    return false;
	}

	bool status = true;
	std::string info = title;

	if (!artist.empty())
	{
	    info += " - " + artist;
	}

	if (!year.empty())
	{
	    info += " (" + year + ")";
	}

	if (shout_metadata_add(data, "song", info.c_str()))
	{
	    status = false;
	    m_error = "Failed to set song title metadata";
	}

	shout_metadata_free(data);

    	return status;
    }

    bool ShoutApi::Write(const char *buffer, std::size_t size)
    {
	switch(shout_send(m_shout,
			  reinterpret_cast<const unsigned char*>(buffer),
			  size))
	{
	    case SHOUTERR_SUCCESS:
	    	return true;

	    case SHOUTERR_INSANE:
	    	m_error = "Problem with shout object";
		break;

	    case SHOUTERR_UNCONNECTED:
	    	m_error = "Not connected to server";
		break;

	    case SHOUTERR_MALLOC:
	    	m_error = "Unable to allocate memory";
		break;

	    case SHOUTERR_SOCKET:
	    	m_error = "Error talking to server";
		break;

	    default:
	    	m_error = "Unknown error";
		break;
	}

    	return false;
    }

    void ShoutApi::Sync()
    {
    	shout_sync(m_shout);
    }

    bool ShoutApi::IsError(int code, const char *message)
    {
    	if (code != SHOUTERR_SUCCESS)
	{
	    m_error = message;
	    shout_close(m_shout);
	    shout_free(m_shout);
	    m_shout = 0;
	    return true;
	}

	return false;
    }
};
