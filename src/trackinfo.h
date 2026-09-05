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
#ifndef VGMSTREAM_TRACKINFO_H
#define VGMSTREAM_TRACKINFO_H

#include <string>

namespace vgmstream
{
    class TrackInfo
    {
    	public:

	    // Construct
	    TrackInfo();

	    // Get and set properties

	    const std::string& Title() const; 
	    void Title(const std::string& value); 

	    const std::string& Artist() const; 
	    void Artist(const std::string& value); 

	    const std::string& Album() const; 
	    void Album(const std::string& value); 

	    const std::string& Year() const; 
	    void Year(const std::string& value); 

	    const std::string& System() const; 
	    void System(const std::string& value); 

	    const std::string& Mp3Name() const; 
	    void Mp3Name(const std::string& value); 

	private:

	    std::string		m_title;
	    std::string		m_artist;
	    std::string		m_album;
	    std::string		m_year;
	    std::string		m_system;
	    std::string		m_mp3_name;
    };
};

#endif
