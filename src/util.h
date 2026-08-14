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
// Utilities
//
#ifndef VGMSTREAM_UTIL_H
#define VGMSTREAM_UTIL_H

#include <iostream>
#include <string>

namespace vgmstream
{
    class Util
    {
    	public:

	    // Return the basename of the passed C string.  Returns a pointer
	    // into the passed pointer.
	    static const char *Basename(const char *path);

	    // Report an error for an OS call.  This function exits.
	    static void OSError(const char *function);

	    // Make the process a daemon.
	    static void MakeDaemon();

	    // Convert the passed string into a number.  Returns false if the
	    // number cannot be parsed.
	    static bool ParseInt(const std::string& str, int& value);

	    // Convert the passed string into a boolean.  Returns false if the
	    // flag cannot be parsed. 
	    static bool ParseBool(const std::string& str, bool& value);

	private:
	    Util();
    };
};

#endif
