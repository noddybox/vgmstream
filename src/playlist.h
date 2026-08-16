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
// Playlist file handling
//
#ifndef VGMSTREAM_PLAYLIST_H
#define VGMSTREAM_PLAYLIST_H

#include <vector>
#include <string>
#include <random>

#include "playlistentry.h"

namespace vgmstream
{
    class Playlist
    {
    	public:

	    // Construct a list from the configured file path.  Sets ok to true
	    // if the file is read OK.
	    Playlist(bool& ok);

	    // Get the next entry from the playlist if there is one.  Returns
	    // true if there is next one, false if we've reached the end of
	    // the list.
	    bool Next(PlaylistEntry& entry);

	    // Re-read the playlist
	    void ReRead();

	private:

	    std::default_random_engine m_rnd;
	    std::vector<std::string> m_playlist;

	    bool Read();
    };
};

#endif
