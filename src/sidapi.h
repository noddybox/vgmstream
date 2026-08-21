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
// Interface to libsidplyfp
//
#ifndef VGMSTREAM_SIDAPI_H
#define VGMSTREAM_SIDAPI_H

#include <string>
#include <memory>

#include <sidplayfp/sidplayfp.h>
#include <sidplayfp/SidTune.h>
#include <sidplayfp/SidInfo.h>
#include <sidplayfp/SidDatabase.h>

#include "sourcefile.h"
#include "decoded.h"

namespace vgmstream
{
    class SidApi
    {
    	public:

	    // Construct an interface to libsidplyfp using the supplied file
	    // and subtune.  The subtune numbering starts from one, and zero
	    // means the default subtune.
	    SidApi(const std::string& path, int subtune);

	    // Clean up
	    ~SidApi();

	    // Whether the API was initialised OK
	    bool Initialised() const;

	    // Get the result of decoding.  Returns true if decoding worked.
	    bool Decode(Decoded& result);

	private:

	    std::unique_ptr<SidTune>		m_tune;

	    bool				m_initialised;

	    static sidplayfp			m_engine;
	    static SidDatabase			m_database;
	    static bool				m_static_setup;

	    void				SetStaticData();

    };
};

#endif
