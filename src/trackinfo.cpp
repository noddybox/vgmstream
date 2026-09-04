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
// Track info
//
#include "trackinfo.h"

namespace vgmstream
{

    TrackInfo::TrackInfo() : m_title(""),
		   m_artist(""),
		   m_album(""),
		   m_year(""),
		   m_mp3_name("")
    {
    }

    const std::string& TrackInfo::Title() const
    {
    	return m_title;
    }

    void TrackInfo::Title(const std::string& value)
    {
    	m_title = value;
    }

    const std::string& TrackInfo::Artist() const
    {
    	return m_artist;
    }

    void TrackInfo::Artist(const std::string& value)
    {
    	m_artist = value;
    }

    const std::string& TrackInfo::Album() const
    {
    	return m_album;
    }

    void TrackInfo::Album(const std::string& value)
    {
    	m_album = value;
    }

    const std::string& TrackInfo::Year() const
    {
    	return m_year;
    }

    void TrackInfo::Year(const std::string& value)
    {
    	m_year = value;
    }

    const std::string& TrackInfo::Mp3Name() const
    {
    	return m_mp3_name;
    }

    void TrackInfo::Mp3Name(const std::string& value)
    {
    	m_mp3_name = value;
    }
};
