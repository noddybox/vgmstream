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
// Interface to libgme
//
#include <sidplayfp/builders/residfp.h>

#include "sidapi.h"
#include "config.h"
#include "log.h"
#include "util.h"

namespace vgmstream
{
    sidplayfp	SidApi::m_engine;
    SidDatabase	SidApi::m_database;
    bool	SidApi::m_static_setup = false;

    SidApi::SidApi(const std::string& path, int subtune)
    					: m_tune(new SidTune(path.c_str())),
					  m_initialised(false)
    {
	if (!m_static_setup)
	{
	    m_static_setup = true;
	    SetStaticData();
	}

	m_tune.get()->selectSong(subtune);

	if (!m_tune.get()->getStatus())
	{
	    VGMLOG("Failed to load SID tune: %s", m_tune.get()->statusString());
	    return;
	}

	m_initialised = true;
    }

    SidApi::~SidApi()
    {
    }

    bool SidApi::Initialised() const
    {
    	return m_initialised;
    }

    bool SidApi::Decode(Decoded& result)
    {
	if (m_tune.get() == 0 || !m_tune.get()->getStatus())
	{
	    return false;
	}

	std::unique_ptr<ReSIDfpBuilder> builder(new ReSIDfpBuilder("SidApi"));
	SidConfig sid_config;

	sid_config.frequency = Decoded::DesiredFrequency();
	sid_config.samplingMethod = SidConfig::INTERPOLATE;
	sid_config.sidEmulation = builder.get();

	if (!m_engine.config(sid_config))
	{
	    VGMLOG("Error configuring SID engine: %s", m_engine.error());
	}

	m_engine.initMixer(true);

	const Config& config(Config::Instance());
	const SidTuneInfo *info = m_tune->getInfo();

	int length = m_database.length(*m_tune);

	if (length < 1)
	{
	    length = config.DecoderDefaultLength();
	}

    	return false;
    }

    void SidApi::SetStaticData()
    {
	const Config& config(Config::Instance());

	if (config.SidKernalSet())
	{
	    SourceFile file(config.SidKernal());

	    if (file.ReadOk())
	    {
		uint8_t *buffer = file.Buffer<uint8_t>();
		m_engine.setKernal(buffer);
		delete[] buffer;
	    }
	    else
	    {
		VGMLOG("Failed to read kernal ROM from %s",
					config.SidKernal().c_str());
	    }
	}

	if (config.SidChargenSet())
	{
	    SourceFile file(config.SidChargen());

	    if (file.ReadOk())
	    {
		uint8_t *buffer = file.Buffer<uint8_t>();
		m_engine.setChargen(buffer);
		delete[] buffer;
	    }
	    else
	    {
		VGMLOG("Failed to read chargen ROM from %s",
					config.SidChargen().c_str());
	    }
	}

	if (config.SidBasicSet())
	{
	    SourceFile file(config.SidBasic());

	    if (file.ReadOk())
	    {
		uint8_t *buffer = file.Buffer<uint8_t>();
		m_engine.setBasic(buffer);
		delete[] buffer;
	    }
	    else
	    {
		VGMLOG("Failed to read BASIC ROM from %s",
					config.SidBasic().c_str());
	    }
	}

	if (config.SidSonglengthSet())
	{
	    if (!m_database.open(config.SidSonglength().c_str()))
	    {
	    	VGMLOG("Error opening SID length database: %s",
				m_database.error());
	    }
	}
    }
};
