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

#include "gmeapi.h"
#include "log.h"

namespace vgmstream
{
    GmeApi::GmeApi(const std::string& path, int track, bool& ok)
    {
    	ok = false;

	if (Error(gme_open_file(path.c_str(),
				&m_emu,
				Decoded::DesiredFrequency())))
	{
	    return;
	}

	m_track_count = gme_track_count(m_emu);

	track = std::max(track, m_track_count - 1);

	if (Error(gme_track_info(m_emu, &m_info, 0)))
	{
	    return;
	}

	ok = true;
    }

    GmeApi::~GmeApi()
    {
    	if (m_info)
	{
	    gme_free_info(m_info);
	    m_info = 0;
	}

    	if (m_emu)
	{
	    gme_delete(m_emu);
	    m_emu = 0;
	}
    }

    int GmeApi::TrackCount() const
    {
    	return m_track_count;
    }

    bool GmeApi::Decode(Decoded& result)
    {
    	return false;
    }

    bool GmeApi::Error(const gme_err_t message) const
    {
    	if (message == 0)
	{
	    return false;
	}

	VGMLOG("Error returned by libgme: %s", message);
	return true;
    }
};
