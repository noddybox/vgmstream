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
// Logging
//
#ifndef VGMSTREAM_LOG_H
#define VGMSTREAM_LOG_H

#include <iostream>
#include <string>

namespace vgmstream
{
    class Log
    {
    	public:

	    // Setup logging.  name is the name of the program as passed in
	    // argv[].  If is_daemon, log to syslog, otherwise stdout.
	    //
	    static void SetLog(const std::string& name, bool is_daemon);

	    // Write to the log.  Done using C-style printf arguments as it
	    // uses syslog().
	    //
	    static void Write(const char *format, ...);

	private:
	    static std::string	m_name;
	    static bool		m_is_daemon;

	    Log();
    };
};

#endif
