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
// Logging
//
#include <iostream>
#include <fstream>
#include <sstream>

#include <cctype>

#include "config.h"
#include "log.h"

namespace vgmstream
{
    Config *Config::m_instance = 0;

    const Config& Config::Instance()
    {
    	return *m_instance;
    }

    bool Config::Open(const std::string& path)
    {
	bool ok;

    	m_instance = new Config(path, ok);

	return ok;
    }

    const std::string Config::IcecastUrl() const
    {
    	return m_icecast_url;
    }

    const std::string Config::IcecastPassword() const
    {
    	return m_icecast_password;
    }

    bool Config::IcecastPublic() const
    {
    	return m_icecast_public;
    }

    const std::string Config::PlaylistFile() const
    {
    	return m_playlist_file;
    }

    bool Config::PlaylistShuffle() const
    {
    	return m_playlist_shuffle;
    }

    bool Config::PlaylistRepeat() const
    {
    	return m_playlist_repeat;
    }

    bool Config::Mp3IsVBR() const
    {
    	return m_mp3_is_VBR;
    }

    int Config::Mp3Bitrate() const
    {
    	return m_mp3_bitrate;
    }

    Config::Config(const std::string& path, bool& open_ok)
    {
	open_ok = false;

    	std::ifstream file(path);

	if (!file)
	{
	    VGMLOG("Failed to open %s", path.c_str());
	    return;
	}

	std::string line;

	while(std::getline(file, line))
	{
	    if (!line.empty() && line[0] != '#')
	    {
	    	std::string setting;
		std::string value;
		std::string::size_type i = 0;

		while(i < line.length() && !std::isblank(line[i]))
		{
		    setting += line[i++];
		}

		while(i < line.length() && std::isblank(line[i]))
		{
		    i++;
		}

		if (i < line.length())
		{
		    value = line.substr(i);
		}

		if (!setting.empty() && !value.empty())
		{
		    if (setting == "icecast.url")
		    {
		    	m_icecast_url = value;
		    }
		    else if (setting == "icecast.password")
		    {
		    	m_icecast_password = value;
		    }
		    else if (setting == "icecast.public")
		    {
		    	if (!ParseFlag(value, m_icecast_public))
			{
			    return;
			}
		    }
		    else if (setting == "playlist.file")
		    {
		    	m_playlist_file = value;
		    }
		    else if (setting == "playlist.shuffle")
		    {
		    	if (!ParseFlag(value, m_playlist_shuffle))
			{
			    return;
			}
		    }
		    else if (setting == "playlist.repeat")
		    {
		    	if (!ParseFlag(value, m_playlist_repeat))
			{
			    return;
			}
		    }
		    else if (setting == "mp3.bitrate")
		    {
		    	if (value == "vbr")
			{
			    m_mp3_is_VBR = true;
			    m_mp3_bitrate = 0;
			}
			else
			{
			    m_mp3_is_VBR = false;

			    try
			    {
				m_mp3_bitrate = std::stoi(value);
			    }
			    catch (...)
			    {
				VGMLOG("Illegal number `%s`", value.c_str());
				return;
			    }
			}
		    }
		    else
		    {
		    	VGMLOG("Unknown setting `%s`", setting.c_str());
			return;
		    }
		}
	    }
	}

	file.close();

	if (m_icecast_url.empty())
	{
	    VGMLOG("Missing config for icecast.url");
	    return;
	}

	if (m_icecast_password.empty())
	{
	    VGMLOG("Missing config for icecast.password");
	    return;
	}

	if (m_playlist_file.empty())
	{
	    VGMLOG("Missing config for playlist.file");
	    return;
	}

	VGMLOG("Successfully read configuration from %s", path.c_str());
	open_ok = true;
    }

    bool Config::ParseFlag(const std::string& flag_text, bool& flag)
    {
	if (flag_text == "yes" || flag_text == "1" ||
		flag_text == "on" || flag_text == "true")
	{
	    flag = true;
	    return true;
	}

	if (flag_text == "no" || flag_text == "0" ||
		flag_text == "off" || flag_text == "false")
	{
	    flag = false;
	    return true;
	}

	VGMLOG("Failed to parse flag `%s`", flag_text.c_str());

    	return false;
    }
};
