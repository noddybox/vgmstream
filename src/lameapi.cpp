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
// Interface to libmp3lame
//
#include <algorithm>
#include <cstring>

#include <lame/lame.h>

#include "lameapi.h"
#include "config.h"
#include "log.h"

namespace vgmstream
{
    LameApi::LameApi(Decoded& pcm, bool tags) : m_initialised(false), m_data()
    {
	const Config& config(Config::Instance());

	lame_global_flags *lame = lame_init();

	lame_set_in_samplerate(lame, pcm.Frequency());
	lame_set_num_channels(lame, 2);
	lame_set_out_samplerate(lame, 44100);

	if (config.Mp3IsVBR())
	{
	    lame_set_VBR(lame, vbr_default);
	    lame_set_VBR_quality(lame, 0);
	    lame_set_bWriteVbrTag(lame, 1);
	}
	else
	{
	    lame_set_brate(lame, config.Mp3Bitrate());
	}

	if (tags)
	{
	    id3tag_init(lame);
	    id3tag_add_v2(lame);
	    id3tag_set_title(lame, pcm.Name().c_str());
	    id3tag_set_artist(lame, pcm.Composer().c_str());
	    id3tag_set_year(lame, pcm.Year().c_str());
	}

	lame_init_params(lame);

	const std::size_t BUFFER_SIZE = 8192;

	short pcm_buffer[BUFFER_SIZE];
	unsigned char buffer[BUFFER_SIZE];

	std::size_t read_offset = 0;
	int write = 0;

	while(read_offset < pcm.Size())
	{
	    std::size_t len = std::min(BUFFER_SIZE, pcm.Size() - read_offset);

	    std::memcpy(pcm_buffer,
	    		pcm.Data() + read_offset,
			len * sizeof(short));

	    write = lame_encode_buffer_interleaved
			    (lame,
			     pcm_buffer,
			     len / 2,
			     buffer,
			     BUFFER_SIZE);

	    m_data.insert(m_data.end(), buffer, buffer + write);

	    read_offset += len;
	}

	write = lame_encode_flush(lame, buffer, sizeof buffer);

	if (write > 0)
	{
	    m_data.insert(m_data.end(), buffer, buffer + write);
	}

	lame_close(lame);

	m_initialised = true;
    }

    bool LameApi::Initialised() const
    {
    	return m_initialised;
    }

    std::size_t LameApi::Size() const
    {
    	return m_data.size();
    }

    const char *LameApi::Data() const
    {
    	return m_data.data();
    }
};
