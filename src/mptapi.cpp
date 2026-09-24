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
// Interface to libopenmpt
//
#include <exception>
#include <fstream>

#include "mptapi.h"
#include "constants.h"

namespace vgmstream
{
    MptApi::MptApi() : FileDecoder()
    {
    }

    MptApi::~MptApi()
    {
    }

    bool MptApi::DecodeImpl(Decoded& result)
    {
	try
	{
	    result.Info().Title(m_mod->get_metadata("title"));
	    result.Info().Artist(m_mod->get_metadata("artist"));
	    result.Info().Year(m_mod->get_metadata("date"));

	    const std::size_t samples = 4096;
	    short buffer[samples * 2];
	    std::size_t count;

	    while((count = m_mod->read_interleaved_stereo
	    			(Constants::DEFAULT_WAV_FREQUENCY,
				 samples,
				 buffer)) > 0)
	    {
	    	result.AddToData(buffer, count * 2);
	    }

	    return true;
	}
	catch (const std::exception& ex)
	{
	    SetErrorMessage(ex.what());
	    return false;
	}
    }

    bool MptApi::InitialiseImpl(const PlaylistEntry& entry)
    {
	try
	{
	    std::ifstream file(entry.Filename());

	    m_mod = std::make_unique<openmpt::module>(file);

	    return true;
	}
	catch (const std::exception& ex)
	{
	    SetErrorMessage(ex.what());
	    return false;
	}
    }
};
