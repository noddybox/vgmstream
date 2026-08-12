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
#ifndef VGMSTREAM_DECODED_H
#define VGMSTREAM_DECODED_H

#include <string>
#include <vector>
#include <cstdlib>

namespace vgmstream
{
    // A decoded file is a stero WAV file with signed 16-bit samples
    class Decoded
    {
    	public:

	    // Construct
	    Decoded();

	    // Get and set properties

	    const std::string& Name() const; 
	    const void Name(const std::string& value); 

	    const std::string& Composer() const; 
	    const void Composer(const std::string& value); 

	    const std::string& Album() const; 
	    const void Album(const std::string& value); 

	    unsigned int Year() const; 
	    const void Year(unsigned int value); 

	    unsigned int Frequency() const; 
	    const void Frequency(unsigned int value); 

	    // Note this is the number of samples, not bytes
	    std::size_t Size() const; 

	    // Note this is the number of bytes, not samples
	    std::size_t ByteSize() const; 

	    const short *Buffer() const; 
	    const void AddToBuffer(const short *mem, std::size_t len); 

	    // The desired default frequency
	    static unsigned int DesiredFrequency();

	private:

	    std::string		m_name;
	    std::string		m_composer;
	    std::string		m_album;
	    unsigned int	m_year;
	    unsigned int	m_freq;
	    std::vector<short>	m_buff;
    };
};

#endif
