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
// Playlist entry
//
#include "playlistentry.h"
#include "util.h"
#include "log.h"

namespace vgmstream
{
    PlaylistEntry::PlaylistEntry()
    {
    	m_track_set = false;
	m_track = -1;
    }

    void PlaylistEntry::Filename(const std::string& filename)
    {
	std::size_t pos = filename.find_last_of(':');

	if (pos != std::string::npos)
	{
	    std::string track_no(filename.substr(pos + 1));

	    if (!Util::ParseInt(track_no, m_track))
	    {
	    	VGMLOG("Bad track number on playlist entry '%s'",
				filename.c_str());
		m_track = -1;
	    }

	    m_filename = filename.substr(0, pos);
	    m_track_set = true;
	}
	else
	{
	    m_filename = filename;
	}

	std::string basename = Util::Basename(m_filename);

	pos = basename.find_last_of('.');

	if (pos != std::string::npos)
	{
	    basename = basename.substr(0, pos);
	}

	if (m_track_set)
	{
	    basename += "-" + std::to_string(m_track);
	}

	m_mp3_name = basename + ".mp3";
    }

    const std::string& PlaylistEntry::Filename() const
    {
    	return m_filename;
    }

    bool PlaylistEntry::HasTrack() const
    {
    	return m_track_set;
    }

    int PlaylistEntry::Track() const
    {
    	return m_track;
    }

    const std::string& PlaylistEntry::Mp3Name() const
    {
    	return m_mp3_name;
    }
};
