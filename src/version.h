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
// Vesion number
//
#ifndef VGMSTREAM_VERSION_H
#define VGMSTREAM_VERSION_H

namespace vgmstream
{
    class Version
    {
    	public:

	    // The string version of the version number
	    static constexpr const char *STRING = "V1.0-dev";

	    // The major version of the version
	    static constexpr int MAJOR = 1;

	    // The minor version of the version
	    static constexpr int MINOR = 0;

	    // Whether it's a development version
	    static constexpr bool IS_DEVELOPMENT = true;

	private:

	    // Doesn't make sense to create this object
	    Version()
	    {
	    }
    };
};

#endif
