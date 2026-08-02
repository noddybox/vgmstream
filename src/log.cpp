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
#include <sstream>
#include <cstdio>
#include <cstring>
#include <cstdarg>

#include <unistd.h>
#include <syslog.h>

#include "log.h"

namespace vgmstream
{
    std::string Log::m_name;

    bool Log::m_is_daemon = false;

    void Log::SetLog(const std::string& name, bool is_daemon)
    {
	m_name = name;
    	m_is_daemon = is_daemon;

	if (is_daemon)
	{
	    openlog(name.c_str(), LOG_CONS|LOG_PID, LOG_USER);
	}
    }


    void Log::Write(const char *format, ...)
    {
	va_list ap;

	va_start(ap, format);

    	if (m_is_daemon)
	{
	    vsyslog(LOG_INFO, format, ap);
	}
	else
	{
	    std::cout << m_name << ": ";
	    vprintf(format, ap);
	    std::cout << std::endl;
	}
    }
};
