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
#include "sidapi.h"
#include "config.h"
#include "log.h"
#include "util.h"

namespace vgmstream
{
    SidDatabase	SidApi::m_database;
    uint8_t	*SidApi::m_kernal = 0;
    uint8_t	*SidApi::m_chargen = 0;
    uint8_t	*SidApi::m_basic = 0;
    bool	SidApi::m_static_setup = false;

    SidApi::SidApi(const std::string& path, int subtune)
    					: m_engine(),
					  m_builder("vgmstream"),
					  m_tune(path.c_str()),
					  m_initialised(false)
    {
	if (!m_static_setup)
	{
	    m_static_setup = true;
	    SetStaticData();
	}

	if (!m_tune.getStatus())
	{
	    VGMLOG("Failed to load SID tune: %s", m_tune.statusString());
	    return;
	}

	m_engine.setRoms(m_kernal, m_basic, m_chargen);

	m_tune.selectSong(subtune);

	SidConfig sid_config;

	sid_config.frequency = Decoded::DesiredFrequency();
	sid_config.samplingMethod = SidConfig::INTERPOLATE;
	sid_config.sidEmulation = &m_builder;

	if (!m_engine.config(sid_config))
	{
	    VGMLOG("Error configuring SID engine: %s", m_engine.error());
	    return;
	}

	if (!m_engine.load(&m_tune))
	{
	    VGMLOG("Error loading SID tune into engine: %s", m_engine.error());
	    return;
	}

	m_engine.initMixer(true);

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
	if (!m_initialised)
	{
	    return false;
	}

	const Config& config(Config::Instance());
	const SidTuneInfo *info = m_tune.getInfo();

	int length = m_database.length(m_tune);

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
		m_kernal = file.Buffer<uint8_t>();
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
		m_chargen = file.Buffer<uint8_t>();
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
		m_basic = file.Buffer<uint8_t>();
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
