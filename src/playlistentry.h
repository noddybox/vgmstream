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
#ifndef VGMSTREAM_PLAYLISTENTRY_H
#define VGMSTREAM_PLAYLISTENTRY_H

#include <string>

#include "filetype.h"

namespace vgmstream
{
    class PlaylistEntry
    {
    	public:

	    // Construct an entry.  If the filename ends in ":number" then
	    // number will be used to set the track number.  If the file name
	    // can't be parsed, or it's type can't be determined Initialised()
	    // will return false.
	    PlaylistEntry(const std::string& filename);

	    // Destructor
	    ~PlaylistEntry();

	    // Whether the entry is initialised
	    bool Initialised() const;

	    // The reason for failure
	    const std::string& Error() const;

	    // Get the filename component of the playlist entry.
	    const std::string& Filename() const;

	    // Is a track defined
	    bool HasTrack() const;

	    // Track number.  -1 if no track was defined.
	    int Track() const;

	    // Convert the filename to an MP3 filename.  If a track is set
	    // then the result will be
	    // "<filename without extension>-<track>.mp3" otherwise it
	    // will be "<filename without extension>.mp3"
	    const std::string& Mp3Name() const;

	    // The filetype
	    const FileType *Type() const;

	private:

	    // Prevent object copy due to pointer
	    PlaylistEntry(const PlaylistEntry& x) {}
	    void operator=(const PlaylistEntry& x) {}

	    bool		m_initialised;
	    std::string		m_error;
	    std::string		m_filename;
	    bool		m_track_set;
	    int			m_track;
	    std::string		m_mp3_name;
	    FileType		*m_file_type;
    };
};

#endif
