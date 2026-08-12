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
// WAV file representation
//
#include <cstring>

#include "decoded.h"

namespace vgmstream
{

    Decoded::Decoded() : m_name(""),
			 m_composer(""),
			 m_album(""),
			 m_year(1980),
			 m_freq(DesiredFrequency()),
			 m_buff()
    {
    }

    const std::string& Decoded::Name() const
    {
    	return m_name;
    }

    const void Decoded::Name(const std::string& value)
    {
    	m_name = value;
    }

    const std::string& Decoded::Composer() const
    {
    	return m_composer;
    }

    const void Decoded::Composer(const std::string& value)
    {
    	m_composer = value;
    }

    const std::string& Decoded::Album() const
    {
    	return m_album;
    }

    const void Decoded::Album(const std::string& value)
    {
    	m_album = value;
    }

    unsigned int Decoded::Year() const
    {
    	return m_year;
    }

    const void Decoded::Year(unsigned int value)
    {
    	m_year = value;
    }

    unsigned int Decoded::Frequency() const
    {
    	return m_freq;
    }

    const void Decoded::Frequency(unsigned int value)
    {
    	m_freq = value;
    }

    std::size_t Decoded::Size() const
    {
    	return m_buff.size();
    }

    std::size_t Decoded::ByteSize() const
    {
    	return m_buff.size() * sizeof(short);
    }

    const short *Decoded::Buffer() const
    {
    	return m_buff.data();
    }

    const void Decoded::AddToBuffer(const short *mem, std::size_t len)
    {
    	while(len--)
	{
	    m_buff.push_back(*mem++);
	}
    }

    unsigned int Decoded::DesiredFrequency()
    {
    	return 44100u;
    }
};
