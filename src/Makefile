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

# The location of the LAME library
#
CFLAGS_LAME	:=	$(shell pkgconf --cflags lame)
LIBS_LAME	:=	$(shell pkgconf --libs lame)

# The location of the libsidplayfp library
#
CFLAGS_SIDPLAY	:=	$(shell pkgconf --cflags libsidplayfp)
LIBS_SIDPLAY	:=	$(shell pkgconf --libs libsidplayfp)

# The location of the libgme library
#
CFLAGS_GME	:=	$(shell pkgconf --cflags libgme)
LIBS_GME	:=	$(shell pkgconf --libs libgme)

# Combines the flags
CFLAGS_VGM	:=	$(CFLAGS_LAME) $(CFLAGS_SIDPLAY) $(CFLAGS_GME)
LIBS_VGM	:=	$(LIBS_LAME) $(LIBS_SIDPLAY) $(LIBS_GME)

# The target
#
TARGET		=	vgmstream

# The sources
#
SOURCES		=	main.cpp		\
			log.cpp			\
			util.cpp

# Objects
#
OBJECTS		=	$(SOURCES:.cpp=.o)

# Rules
#
$(TARGET): $(OBJECTS)
	$(CXX) -o $(TARGET) $(OBJECTS) $(LIBS_VGM)

clean:
	rm -f $(TARGET) core $(OBJECTS)

%.o: %.cpp
	$(CXX) $(CFLAGS_VGM) -c -o $@ $<

main.o: main.cpp log.h
log.o: log.cpp log.h
util.o: util.cpp util.h
