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
// Interface to libgme
//
#include <algorithm>

#include "sidapi.h"
#include "log.h"

namespace vgmstream
{
    SidApi::SidApi(const std::string& path, int track)
    {
    	m_initialised = false;
	m_track_count = 0;
	m_default_track = 0;
    }

    SidApi::~SidApi()
    {
    }

    bool SidApi::Initialised() const
    {
    	return m_initialised;
    }

    int SidApi::DefaultTrack() const
    {
    	return m_default_track;
    }

    int SidApi::TrackCount() const
    {
    	return m_track_count;
    }

    bool SidApi::Decode(Decoded& result)
    {
    	return false;
    }
};
