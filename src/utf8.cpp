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
// UTF8 conversion
//
#include "utf8.h"

namespace vgmstream
{
    std::string UTF8::Convert(const std::string& from)
    {
	if (IsValid(from))
	{
	    return from;
	}

    	std::string result;

	for(std::string::const_iterator i = from.begin(); i != from.end(); ++i)
	{
	    // C-style cast as we want just the bits as is, so just in case
	    // reinterpret_cast, well, reinterprets
	    Append(result, (unsigned char)*i);
	}

	return result;
    }

    bool UTF8::IsValid(const std::string& str)
    {
	int len = 0;

    	for(std::string::const_iterator i = str.begin(); i != str.end(); ++i)
	{
	    // C-style cast as we want just the bits as is, so just in case
	    // reinterpret_cast, well, reinterprets
	    unsigned char c = (unsigned char)*i;

	    if (len)
	    {
	    	if ((c & 0xc0) != 0x80)
		{
		    return false;
		}

		len--;
	    }
	    else
	    {
		if (c > 0x7f)
		{
		    if ((c & 0xe0) == 0xc0)
		    {
		    	len = 1;
		    }
		    else if ((c & 0xf0) == 0xe0)
		    {
		    	len = 2;
		    }
		    else if ((c & 0xf8) == 0xf0)
		    {
		    	len = 3;
		    }
		    else
		    {
		    	return false;
		    }
		}
	    }
	}

	return true;
    }

    void UTF8::Append(std::string& to, unsigned char code)
    {
    	if (code < 0x80)
	{
	    to.push_back(code);
	    return;
	}

	to.push_back(0xc0 | code >> 6);
	to.push_back(0x80 | (code & 0x3f));
    }
};
