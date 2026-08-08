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
#include <cctype>

#include "filetype.h"

namespace vgmstream
{
    FileType::StringTypeMap FileType::ext_map =
    {
	{"AY",		eType::AY},
	{"GBS",		eType::Gameboy},
	{"GYM",		eType::Genesis},
	{"HES",		eType::PCEngine},
	{"KSS",		eType::MSX},
	{"NSF",		eType::NES},
	{"NSFE",	eType::NES},
	{"SAP",		eType::POKEY},
	{"SPC",		eType::SNES},
	{"VGM",		eType::MasterSystem},
	{"VGZ",		eType::MasterSystem},
	{"SID",		eType::SID},
	{"PSID",	eType::SID}
    };

    FileType::FileType(const std::string& m_path)
    {
    	m_type = eType::Unknown;

	std::size_t pos = m_path.find_last_of(".");

	if (pos == std::string::npos)
	{
	    return;
	}

	std::string ext = m_path.substr(pos + 1);
	ToUpper(ext);

	StringTypeMap::const_iterator  iter = ext_map.find(ext);

	if (iter == ext_map.end())
	{
	    return;
	}

	m_type = iter->second;
    }

    FileType::eType FileType::Type() const
    {
    	return m_type;
    }

    void FileType::ToUpper(std::string& s)
    {
    	for(std::string::iterator i = s.begin(); i != s.end(); ++i)
	{
	    *i = std::toupper(*i);
	}
    }
};
