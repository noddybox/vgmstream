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
// Main
//
#include <iostream>
#include <cstdlib>

#include "log.h"
#include "util.h"

int main(int argc, char *argv[])
{
    std::string name(vgmstream::Util::Basename(argv[0]));
    bool make_daemon = false;
    std::string config_file("/etc/vgmstreamrc");

    int arg = 1;

    while (arg < argc && argv[arg][0] == '-')
    {
	bool display_usage = false;

    	switch(argv[arg][1])
	{
	    case 'c':
		if (++arg < argc)
		{
		    config_file = argv[arg];
		}
		else
		{
		    display_usage = true;
		}
	    	break;

	    case 'd':
		make_daemon = true;
	    	break;

	    default:
	    	display_usage = true;
		break;
	}

	if (display_usage)
	{
	    std::cerr << name
		      << ": usage "
		      << name
		      << " [-c file] [-d]"
		      << std::endl;

	    std::exit(1);
	}

	arg++;
    }

    if (make_daemon)
    {
	vgmstream::Util::MakeDaemon();
    }

    vgmstream::Log::SetLog(name, make_daemon);

    vgmstream::Log::Write("Reading config from %s", config_file.c_str());

    return 0;
}
