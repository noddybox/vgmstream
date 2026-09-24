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
// File decoder base class
//
#include "filedecoder.h"

namespace vgmstream
{
    FileDecoder::FileDecoder() : m_error()
    {
    }

    FileDecoder::~FileDecoder()
    {
    }

    bool FileDecoder::Initialise(const PlaylistEntry& entry)
    {
	m_mp3_name = entry.Mp3Name();
    	return InitialiseImpl(entry);
    }

    bool FileDecoder::Decode(Decoded& result)
    {
    	result.Info().Mp3Name(m_mp3_name);
	return DecodeImpl(result);
    }
    const std::string& FileDecoder::Error() const
    {
    	return m_error;
    }

    void FileDecoder::SetErrorMessage(const std::string& error)
    {
    	m_error = error;
    }
};
