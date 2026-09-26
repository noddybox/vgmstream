/* vgmstream - an Icecast 2 source for video games music trancoded to MP3
   Copyright (C) 2026  Ian Cowburn <deathstation9000@gmail.com>
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.
  
   nfstracks

   This utility dumps the track numbers in an NES audio file in a form
   suitable for the playlist.
*/
#include <iostream>
#include <string>

#include <sidplayfp/sidplayfp.h>
#include <sidplayfp/SidTune.h>
#include <sidplayfp/SidInfo.h>
#include <sidplayfp/SidDatabase.h>

namespace
{
    std::string name;
    SidDatabase database;

    unsigned int NumSubTunes(const char *path)
    {
    	return 1;
    }

    void ProcessFile(const char *path)
    {
    	SidTune sid(path);

	if (!sid.getStatus())
	{
	    std::cerr << name << ": " << sid.statusString() << std::endl;
	    return;
	}

	unsigned int num_subtunes = NumSubTunes(path);
    }

    void Usage()
    {
    	std::cerr << name << ": usage " << name << " "
		  << "HVSC_song_md5 file [...file]" << std::endl;
    	std::exit(EXIT_FAILURE);
    }
};


int main(int argc, char *argv[])
{
    std::size_t last;
    int base = 1;

    name = argv[0];

    last = name.find_last_of('/');

    if (last == std::string::npos)
    {
	last = name.find_last_of('\\');
    }

    if (last != std::string::npos)
    {
    	name = name.substr(last + 1);
    }

    if (argc < 3)
    {
    	Usage();
    }

    if (!database.open(argv[base]))
    {
	std::cerr << name << ": error opening database "
		  << argv[base] << std::endl;

	return EXIT_FAILURE;
    }

    for(int f = 2; f < argc; f++)
    {
    	ProcessFile(argv[f]);
    }

    return EXIT_SUCCESS;
}
