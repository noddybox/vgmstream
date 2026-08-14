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

#include <cctype>

#include "config.h"
#include "util.h"
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

    int Config::DecoderDefaultLength() const
    {
    	return m_decoder_default_length;
    }

    int Config::DecoderLoop() const
    {
    	return m_decoder_loop;
    }

    bool Config::Mp3IsVBR() const
    {
    	return m_mp3_is_VBR;
    }

    int Config::Mp3Bitrate() const
    {
    	return m_mp3_bitrate;
    }

    const std::string Config::MiscOutputDir() const
    {
    	return m_output_dir;
    }

    bool Config::IcecastUrlSet() const
    {
    	return !m_icecast_url.empty();
    }

    bool Config::IcecastPasswordSet() const
    {
    	return !m_icecast_password.empty();
    }

    bool Config::MiscOutputDirSet() const
    {
    	return !m_output_dir.empty();
    }

    Config::Config(const std::string& path, bool& open_ok) :
			m_icecast_url(""),
			m_icecast_password(""),
			m_icecast_public(false),
			m_playlist_file(""),
			m_playlist_shuffle(true),
			m_playlist_repeat(true),
			m_decoder_default_length(120),
			m_decoder_loop(2),
			m_mp3_is_VBR(true),
			m_mp3_bitrate(0),
			m_output_dir("")
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
		    	if (!Util::ParseBool(value, m_icecast_public))
			{
			    VGMLOG("Bad flag '%s' on setting '%s'",
			    		value.c_str(), setting.c_str());
			    return;
			}
		    }
		    else if (setting == "playlist.file")
		    {
		    	m_playlist_file = value;
		    }
		    else if (setting == "playlist.shuffle")
		    {
		    	if (!Util::ParseBool(value, m_playlist_shuffle))
			{
			    VGMLOG("Bad flag '%s' on setting '%s'",
			    		value.c_str(), setting.c_str());
			    return;
			}
		    }
		    else if (setting == "playlist.repeat")
		    {
		    	if (!Util::ParseBool(value, m_playlist_repeat))
			{
			    VGMLOG("Bad flag '%s' on setting '%s'",
			    		value.c_str(), setting.c_str());
			    return;
			}
		    }
		    else if (setting == "decoder.default_length")
		    {
			if (!Util::ParseInt(value, m_decoder_default_length))
			{
			    VGMLOG("Bad number '%s' on setting '%s'",
			    		value.c_str(), setting.c_str());
			    return;
			}
		    }
		    else if (setting == "decoder.loop")
		    {
			if (!Util::ParseInt(value, m_decoder_loop))
			{
			    VGMLOG("Bad number '%s' on setting '%s'",
			    		value.c_str(), setting.c_str());
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

			    if (!Util::ParseInt(value, m_mp3_bitrate))
			    {
				VGMLOG("Bad number '%s' on setting '%s'",
					    value.c_str(), setting.c_str());
				return;
			    }
			}
		    }
		    else if (setting == "misc.outputdir")
		    {
			m_output_dir = value;
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

	if (m_icecast_url.empty() && m_output_dir.empty())
	{
	    VGMLOG("Missing config for icecast.url");
	    return;
	}

	if (m_icecast_password.empty() && m_output_dir.empty())
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
};
