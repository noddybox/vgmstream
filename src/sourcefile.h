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
// Source file class
//
#ifndef VGMSTREAM_SOURCEFILE_H
#define VGMSTREAM_SOURCEFILE_H

#include <vector>
#include <string>
#include <cstring>

#include "util.h"

namespace vgmstream
{
    class SourceFile
    {
    	public:
	    // Construct a source file for the passed path
	    //
	    SourceFile(const std::string& path);

	    // Whether the file was read OK
	    bool ReadOk() const;

	    // The size of the file
	    std::size_t Size() const;

	    // The contents of the file
	    const unsigned char *Contents() const;

	    // The contents of the file as an allocated memory block of
	    // type T.  It is recommended that T has sizeof == 1.
	    template <typename T> T *Buffer() const
	    {
		T *buffer = new T[m_size];

		if (buffer == 0)
		{
		    Util::OSError(0);
		}

		std::memcpy(buffer, m_contents.data(), m_size);

		return buffer;
	    }

	private:
	    bool			m_readOk;
	    std::size_t			m_size;
	    std::vector<unsigned char>	m_contents;
    };
};

#endif
