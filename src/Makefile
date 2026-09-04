# vgmstream - an Icecast 2 source for video games music trancoded to MP3
# Copyright (C) 2026  Ian Cowburn <deathstation9000@gmail.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.
#
# Makefile
#

# Switches for the LAME library
#
CFLAGS_LAME	:=	$(shell pkgconf --cflags lame)
LIBS_LAME	:=	$(shell pkgconf --libs lame)

# Switches for the libsidplayfp library
#
CFLAGS_SIDPLAY	:=	$(shell pkgconf --cflags libsidplayfp)
LIBS_SIDPLAY	:=	$(shell pkgconf --libs libsidplayfp)

# Switches for the libgme library
#
CFLAGS_GME	:=	$(shell pkgconf --cflags libgme)
LIBS_GME	:=	$(shell pkgconf --libs libgme)

# Switches for the libshout library
#
CFLAGS_SHOUT	:=	$(shell pkgconf --cflags shout)
LIBS_SHOUT	:=	$(shell pkgconf --libs shout)

# Switches for pthreads
#
CFLAGS_PTHREAD	:=	-pthread
LIBS_PTHREAD	:=	-pthread

# General switches
#
CFLAGS_GENERAL	:=	-std=c++17
LIBS_GENERAL	:=	

# Combines the flags
CFLAGS_VGM	:=	$(CFLAGS_LAME) $(CFLAGS_SIDPLAY) $(CFLAGS_GME) \
			$(CFLAGS_SHOUT) $(CFLAGS_PTHREAD) $(CFLAGS_GENERAL)
LIBS_VGM	:=	$(LIBS_LAME) $(LIBS_SIDPLAY) $(LIBS_GME) \
			$(LIBS_SHOUT) $(LIBS_PTHREAD) $(LIBS_GENERAL)

# The target
#
TARGET		=	vgmstream

# The sources
#
SOURCES		=	main.cpp		\
			log.cpp			\
			config.cpp		\
			playlist.cpp		\
			playlistentry.cpp	\
			decoded.cpp		\
			thread.cpp		\
			sourcefile.cpp		\
			filetype.cpp		\
			decoder.cpp		\
			gmeapi.cpp		\
			sidapi.cpp		\
			mp3encoder.cpp		\
			streamer.cpp		\
			lameapi.cpp		\
			mp3file.cpp		\
			url.cpp			\
			shoutapi.cpp		\
			trackinfo.cpp		\
			util.cpp

HEADERS		=	log.h			\
			config.h		\
			playlist.h		\
			playlistentry.h		\
			decoded.h		\
			thread.h		\
			sourcefile.h		\
			filetype.h		\
			decoder.h		\
			gmeapi.h		\
			sidapi.h		\
			mp3encoder.h		\
			streamer.h		\
			lameapi.h		\
			mp3file.h		\
			mtvar.h			\
			queue.h			\
			queuecancel.h		\
			url.h			\
			shoutapi.h		\
			trackinfo.h		\
			util.h

# Objects
#
OBJECTS		=	$(SOURCES:.cpp=.o)

# Rules
#
$(TARGET): $(OBJECTS)
	$(CXX) -o $(TARGET) $(OBJECTS) $(LIBS_VGM)

depend.mak: $(SOURCES) $(HEADERS) Makefile
	$(CXX) -MM $(SOURCES) > depend.mak

clean:
	rm -f $(TARGET) core $(OBJECTS) depend.mak

%.o: %.cpp
	$(CXX) $(CFLAGS_VGM) -g -c -o $@ $<

include depend.mak
