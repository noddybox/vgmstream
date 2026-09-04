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
// MP3 encoded file
//
#include "mp3file.h"

namespace vgmstream
{
    Mp3File::Mp3File()
    {
    }

    Mp3File::Mp3File(const char *memory,
		     std::size_t size,
		     const TrackInfo& info)
		     	: m_data(),
			  m_info(info)
    {
    	m_data.insert(m_data.end(), memory, memory + size);
    }

    const TrackInfo& Mp3File::Info() const
    {
    	return m_info;
    }

    std::size_t Mp3File::Size() const
    {
    	return m_data.size();
    }

    const char *Mp3File::Data() const
    {
    	return m_data.data();
    }
};
