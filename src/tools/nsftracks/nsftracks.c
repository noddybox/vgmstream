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
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

static const char *name;

static void Error(const char *p)
{
    perror(p);
    exit(EXIT_FAILURE);
}

static char *ReadChunk(FILE *fp, const char *name)
{
    while(TRUE)
    {
	long dword_buff[4];

	for (int f = 0; f < 4; f++)
	{
	    dword_buff[f] = fgetc(fp);

	    if (dword_buff[f] == EOF)
	    {
		return NULL;
	    }
	}

	long length = dword_buff[0] |
		      dword_buff[1] << 8 |
		      dword_buff[2] << 16 |
		      dword_buff[3] << 24;

	char id_buff[5] = {0};

	if (fread(id_buff, 1, 4, fp) != 4)
	{
	    return NULL;
	}

	if (strcmp(id_buff, name) == 0)
	{
	    unsigned char *buff = malloc(length);

	    if (!buff)
	    {
		fclose(fp);
	    	Error("malloc");
	    }

	    if (fread(buff, 1, length, fp) != length)
	    {
	    	free(buff);
		return NULL;
	    }

	    return buff;
	}
	else
	{
	    while(length--)
	    {
	    	if (fgetc(fp) == EOF)
		{
		    return NULL;
		}
	    }
	}
    }
}

static void ProcessFile(const char *path)
{
    FILE *fp = fopen(path, "rb");

    if (!fp)
    {
	fprintf(stderr, "%s: can't open %s\n", name, path);
    	return;
    }

    char magic[5] = {0};

    if (fread(magic, 1, 4, fp) != 4)
    {
    	fprintf(stderr, "%s: failed to read magic bytes from %s\n", name, path);
	fclose(fp);
	return;
    }

    int tracks = 0;

    if (strcmp("NESM", magic) == 0)
    {
	int error = FALSE;

	if (fgetc(fp) != 0x1a)
	{
	    error = TRUE;
	}

	if (!error)
	{
	    error = (fgetc(fp) == EOF);
	}

	if (!error)
	{
	    tracks = fgetc(fp);
	    error = (tracks == EOF);
	}

	fclose(fp);

	if (error)
	{
	    fprintf(stderr, "%s: %s not an NES audio file\n", name, path);
	    return;
	}
    }
    else if (strcmp("NSFE", magic) == 0)
    {
	unsigned char *info = ReadChunk(fp, "INFO");

	fclose(fp);

	if (!info)
	{
	    fprintf(stderr, "%s: Failed to read INFO chunk from %s\n",
	    				name, path);
	    return;
	}

	tracks = info[8];
	free(info);
    }
    else
    {
    	fprintf(stderr, "%s: %s not an NES audio file\n", name, path);
	fclose(fp);
	return;
    }

    for(int f = 0; f < tracks; f++)
    {
    	printf("%s:%d\n", path, f);
    }
}

int main(int argc, char *argv[])
{
    name = strstr(argv[0], "/");

    if (name)
    {
    	name++;
    }
    else
    {
    	name = argv[0];
    }

    if (argc < 2)
    {
    	fprintf(stderr, "%s: usage %s file [...file]\n", name, name);
	return EXIT_FAILURE;
    }

    for(int f = 1; f < argc; f++)
    {
    	ProcessFile(argv[f]);
    }

    return EXIT_SUCCESS;
}
