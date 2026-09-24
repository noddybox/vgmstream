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
// File decoder base class
//
#ifndef VGMSTREAM_FILEDECODER_H
#define VGMSTREAM_FILEDECODER_H

#include "playlistentry.h"
#include "decoded.h"
#include "trackinfo.h"

namespace vgmstream
{
    class FileDecoder
    {
    	public:

	    // Implementors should call this from their constructor.
	    FileDecoder();

	    // Destructor.
	    virtual ~FileDecoder();

	    // Initialiser.  Returns true if initialised ok.  If false,
	    // Error() will return the reason.
	    bool Initialise(const PlaylistEntry& entry);

	    // Decode the file into the result WAV file.  Returns true if
	    // decoded ok.  If false, Error() will return the reason.
	    bool Decode(Decoded &result);

	    // The reason for the last error
	    const std::string& Error() const;

	protected:

	    // Implementors should call this to set error message
	    void SetErrorMessage(const std::string& error);

	    // Implementers must implement this to initialise the decoder
	    virtual bool InitialiseImpl(const PlaylistEntry& entry) = 0;

	    // Implementors must implement this to do the actual decoding
	    // to a PCM.  It should return true if the file is decoded,
	    // filling in result and info with the contents of the decoded file.
	    // If false is returned the error message should be filled in with
	    // the reason.  The MP3 name in the result will be set for the
	    // decoder.
	    virtual bool DecodeImpl(Decoded& result) = 0;

	private:

	    std::string			m_error;
	    std::string			m_mp3_name;
    };
};

#endif
