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
// Playlist handling
//
#include <iostream>
#include <fstream>
#include <algorithm>
#include <random>
#include <chrono>

#include "playlist.h"
#include "config.h"
#include "log.h"

namespace vgmstream
{
    Playlist::Playlist(bool& ok)
    	: m_rnd(std::chrono::system_clock::to_time_t
			(std::chrono::system_clock::now()))
    {
    	ok = Read();
    }

    bool Playlist::Next(std::string& next)
    {
    	if (m_playlist.size() == 0)
	{
	    return false;
	}

	next = m_playlist[0];
	m_playlist.erase(m_playlist.begin());

	return true;
    }

    void Playlist::ReRead()
    {
    	Read();
    }

    bool Playlist::Read()
    {
	std::string path(Config::Instance().PlaylistFile());

    	std::ifstream file(path);

	if (!file)
	{
	    VGMLOG("Failed to open playlist file %s", path.c_str());
	    return false;
	}

	std::string line;

	while(std::getline(file, line))
	{
	    if (!line.empty() && line[0] != '#')
	    {
	    	m_playlist.push_back(line);
	    }
	}

	file.close();

	if (m_playlist.size() == 0)
	{
	    VGMLOG("Empty playlist file %s", path.c_str());
	    return false;
	}

	if (Config::Instance().PlaylistShuffle())
	{
	    std::shuffle(m_playlist.begin(),
			 m_playlist.end(),
			 m_rnd);
	}

	return true;
    }
};
