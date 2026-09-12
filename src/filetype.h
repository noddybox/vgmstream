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
// Guess the file type from the extension
//
#ifndef VGMSTREAM_FILETYPE_H
#define VGMSTREAM_FILETYPE_H

#include <map>
#include <string>

#include "filedecoder.h"

namespace vgmstream
{
    class FileType
    {
    	public:

	    // Construct a file type for the passed file
	    //
	    FileType(const std::string& path);

	    // The reason for failure
	    const std::string& Error() const;

	    // The system as a string
	    const std::string& System() const;

	    // The file decoder for this file.  If not applicable, null is
	    // returned and Error() will return the reason why.
	    FileDecoder *Decoder() const;

	private:

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
		Commodore64
	    };

	    typedef std::map<std::string, eType> StringTypeMap;
	    static StringTypeMap	m_ext_map;

	    typedef std::map<eType, std::string> StringSystemMap;
	    static StringSystemMap	m_system_map;

	    eType			m_type;
	    std::string			m_error;
	    std::string			m_system;

	    void ToUpper(std::string& s);
    };
};

#endif
