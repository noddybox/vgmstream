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
// File type class
//
#include <fstream>
#include <iostream>

#include "sourcefile.h"

namespace vgmstream
{
    SourceFile::SourceFile(const std::string& m_path)
    {
	m_readOk = false;
	m_size = 0;

	std::ifstream in(m_path, std::ios_base::in | std::ios_base::binary);

	if (!in)
	{
	    return;
	}

	unsigned char byte;

	while(in >> byte)
	{
	    m_size++;
	    m_contents.push_back(byte);
	}

	in.close();

	m_readOk = true;
    }

    std::size_t SourceFile::Size() const
    {
    	return m_size;
    }

    bool SourceFile::ReadOk() const
    {
    	return m_readOk;
    }

    const unsigned char *SourceFile::Contents() const
    {
    	return m_contents.data();
    }
};
