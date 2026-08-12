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
#ifndef VGMSTREAM_FILETYPE_H
#define VGMSTREAM_FILETYPE_H

#include <map>
#include <vector>
#include <string>

namespace vgmstream
{
    class SourceFile
    {
    	public:

	    enum eType
	    {
		NotExist,
		Unknown,
		AY,
		Gameboy,
	    	Genesis,
	    	PCEngine,
		MSX,
		NES,
		POKEY,
		SNES,
		MasterSystem,
		SID
	    };

	    // Construct a file type for the passed file
	    //
	    SourceFile(const std::string& path);

	    // The type of file
	    eType Type() const;

	    // The contents of the file
	    const unsigned char *Contents() const;

	private:

	    typedef std::map<std::string, eType> StringTypeMap;
	    static StringTypeMap ext_map;

	    eType			m_type;
	    std::vector<unsigned char>	m_contents;

	    void ToUpper(std::string& s);

    };
};

#endif
