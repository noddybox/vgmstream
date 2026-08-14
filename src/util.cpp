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
#include <cstdlib>
#include <cstring>
#include <cerrno>

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "util.h"

namespace vgmstream
{
    const char *Util::Basename(const char *path)
    {
	const char *basename = std::strrchr(path, '/');

	if (basename)
	{
	    return basename + 1;
	}
	
	return path;
    }

    void Util::OSError(const char *function)
    {
    	std::perror(function);
	std::exit(1);
    }

    void Util::MakeDaemon()
    {
	// First fork
	//
    	switch(fork())
	{
	    case 0:
	    	break;

	    case -1:
	    	OSError("fork");
		break;

	    default:
	    	std::exit(0);
		break;
	}

	// New session
	//
	setsid();

	// Second fork
	//
    	switch(fork())
	{
	    case 0:
	    	break;

	    case -1:
	    	OSError("fork");
		break;

	    default:
	    	std::exit(0);
		break;
	}

	// Environment
	//
	if (chdir("/") == -1)
	{
	    OSError("chdir");
	}

	umask(0770);

	// Close and redirect standard streams
	//
	int read_fd = open("/dev/null", O_RDONLY);
	int write_fd = open("/dev/null", O_WRONLY);

	if (read_fd == -1 || write_fd == -1)
	{
	    OSError("open");
	}

	if (dup2(read_fd, STDIN_FILENO) == -1)
	{
	    OSError("dup2");
	}

	if (dup2(write_fd, STDOUT_FILENO) == -1)
	{
	    OSError("dup2");
	}

	if (dup2(write_fd, STDERR_FILENO) == -1)
	{
	    OSError("dup2");
	}
    }

    bool Util::ParseInt(const std::string& str, int& value)
    {
	try
	{
	    value = std::stoi(str);
	    return true;
	}
	catch (...)
	{
	    return false;
	}
    }


    bool Util::ParseBool(const std::string& str, bool& flag)
    {
	if (str == "yes" || str == "1" || str == "on" || str == "true")
	{
	    flag = true;
	    return true;
	}

	if (str == "no" || str == "0" || str == "off" || str == "false")
	{
	    flag = false;
	    return true;
	}

    	return false;
    }
};
