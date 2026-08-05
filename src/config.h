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
// COnfiguration file handling
//
#ifndef VGMSTREAM_CONFIG_H
#define VGMSTREAM_CONFIG_H

#include <string>

namespace vgmstream
{
    class Config
    {
    	public:

	    // Get the single instance
	    //
	    static const Config& Instance();

	    // Open the passed configuration creating the instance.  Returns
	    // true if the file is OK, otherwise false on error.  The error
	    // has already been logged, so a simple exit can be done.
	    //
	    static bool Open(const std::string& path);

	    // Config items

	    const std::string	IcecastUrl() const;
	    const std::string	IcecastPassword() const;
	    bool		IcecastPublic() const;
	    const std::string	PlaylistFile() const;
	    bool		PlaylistShuffle() const;
	    bool		PlaylistRepeat() const;
	    bool		Mp3IsVBR() const;
	    int			Mp3Bitrate() const;
	    const std::string	MiscOutputDir() const;

	    bool		MiscOutputDirSet() const;

	private:

	    static Config *m_instance;

	    Config(const std::string& path, bool& open_ok);

	    std::string	m_icecast_url;
	    std::string	m_icecast_password;
	    bool	m_icecast_public;
	    std::string	m_playlist_file;
	    bool	m_playlist_shuffle;
	    bool	m_playlist_repeat;
	    bool	m_mp3_is_VBR;
	    int		m_mp3_bitrate;
	    std::string	m_output_dir;

	    bool ParseFlag(const std::string& flag_text, bool& flag);
    };
};

#endif
