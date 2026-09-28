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
#include <vector>
#include <cstdint>
#include <cstdio>

#include <sidplayfp/sidplayfp.h>
#include <sidplayfp/SidTune.h>
#include <sidplayfp/SidTuneInfo.h>
#include <sidplayfp/SidInfo.h>
#include <sidplayfp/SidDatabase.h>

namespace
{
    std::string name;
    SidDatabase database;

    class UTF8
    {
    	public:

	    // Return the passed Latin-1 string as UTF-8.  If the string is
	    // already valid UTF-8 or ASCII, it is returned unchanged.
	    static std::string Convert(const std::string& from);

	private:
	    UTF8();

	    static bool IsValid(const std::string& str);
	    static void Append(std::string& to, unsigned char code);
    };

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

    void ProcessFile(const char *path, int trim)
    {
	// Using stdio rather than ifstream as it's a pain to use explicitly
	// unsigned type
	std::FILE *fp = fopen(path, "rb");

	if (fp == 0)
	{
	    std::cerr << name << ": Failed to open " << path << std::endl;
	    return;
	}

	std::vector<std::uint8_t> data;
	uint8_t buffer[1024];
	std::size_t count;

	while((count = std::fread(buffer, 1, sizeof buffer, fp)) > 0)
	{
	    data.insert(data.end(), buffer, buffer + count);
	}

	std::fclose(fp);

	if (data.size() < 0x77 ||
	    data[1] != 'S'||
	    data[2] != 'I' ||
	    data[3] != 'D')
	{
	    std::cerr << name << ": " << path
		      << " does not appear to be a SID file" << std::endl;
	    return;
	}

	unsigned int num_sub_tunes = 
		((unsigned int)data[0x0e]) << 8 | data[0x0f];

    	SidTune sid(path);

	if (!sid.getStatus())
	{
	    std::cerr << name << ": " << sid.statusString() << std::endl;
	    return;
	}

	if (trim == 0)
	{
	    std::cout << "File: " << path << std::endl;
	    std::cout << "Number of subtunes: " << num_sub_tunes << std::endl;

	    const SidTuneInfo *info = sid.getInfo();

	    if (info != 0 && info->numberOfInfoStrings() > 2)
	    {
		std::cout << "Title: " << UTF8::Convert((info->infoString(0)))
			  << std::endl;
		std::cout << "Artist: " << UTF8::Convert((info->infoString(1))) 
			  << std::endl;
		std::cout << "Year: " << UTF8::Convert((info->infoString(2))) 
			  << std::endl;
	    }
	}

	for(unsigned int f = 1; f <= num_sub_tunes; f++)
	{
	    sid.selectSong(f);

	    int length = database.lengthMs(sid);

	    if (trim == 0)
	    {
		std::cout << "Subtune #" << f << ": "
			  << length << " msec" << std::endl;
	    }
	    else
	    {
	    	if (length > trim)
		{
		    std::cout << path << ":" << (f - 1) << std::endl;
		}
	    }
	}
    }

    void Usage()
    {
    	std::cerr << name << ": usage " << name << " [-p max_msec] "
		  << "HVSC_song_md5 file [...file]" << std::endl;
    	std::exit(EXIT_FAILURE);
    }
};


int main(int argc, char *argv[])
{
    std::size_t last;
    int base = 1;
    int trim = 0;

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

    while(base < argc && argv[base][0] == '-')
    {
    	switch(argv[base][1])
	{
	    case 'p':
		if (++base < argc)
		{
		    trim = std::atoi(argv[base++]);
		}
		else
		{
		    Usage();
		}
		break;

	    default:
	    	Usage();
		break;
	}
    }

    if (argc - base < 2)
    {
    	Usage();
    }

    if (!database.open(argv[base]))
    {
	std::cerr << name << ": error opening database "
		  << argv[base] << std::endl;

	return EXIT_FAILURE;
    }

    for(int f = base + 1; f < argc; f++)
    {
    	ProcessFile(argv[f], trim);
    }

    return EXIT_SUCCESS;
}
