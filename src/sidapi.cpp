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
#include <cstdint>
#include <sstream>
#include <sidplayfp/SidTuneInfo.h>

#include "sidapi.h"
#include "config.h"
#include "util.h"
#include "utf8.h"
#include "log.h"
#include "constants.h"

namespace vgmstream
{
    SidDatabase	SidApi::m_database;
    SourceFile	*SidApi::m_kernal = 0;
    SourceFile	*SidApi::m_chargen = 0;
    SourceFile	*SidApi::m_basic = 0;
    bool	SidApi::m_static_setup = false;

    SidApi::SidApi() : FileDecoder(),
		       m_engine(),
		       m_builder("vgmstream"),
		       m_tune(0)
    {
	if (!m_static_setup)
	{
	    m_static_setup = true;
	    SetStaticData();
	}
    }

    SidApi::~SidApi()
    {
    	if (m_tune != 0)
	{
	    delete m_tune;
	    m_tune = 0;
	}
    }

    bool SidApi::InitialiseImpl(const PlaylistEntry& entry)
    {
	m_tune = new SidTune(entry.Filename().c_str());

	if (m_tune == 0)
	{
	    SetErrorMessage("Failed to allocate SID tune");
	    return false;
	}

	if (!m_tune->getStatus())
	{
	    std::ostringstream str;

	    str << "Failed to load SID tune: " <<  m_tune->statusString();
	    SetErrorMessage(str.str());

	    return false;
	}

	if (m_kernal != 0)
	{
	    m_engine.setKernal(m_kernal->Contents<std::uint8_t>());
	}

	if (m_basic != 0)
	{
	    m_engine.setBasic(m_basic->Contents<std::uint8_t>());
	}

	if (m_chargen != 0)
	{
	    m_engine.setChargen(m_chargen->Contents<std::uint8_t>());
	}

	m_tune->selectSong(entry.HasTrack() ? entry.Track() + 1 : 0);

	SidConfig sid_config;

	sid_config.frequency = Constants::DEFAULT_WAV_FREQUENCY;
	sid_config.samplingMethod = SidConfig::INTERPOLATE;
	sid_config.sidEmulation = &m_builder;

	if (!m_engine.config(sid_config))
	{
	    std::ostringstream str;

	    str << "Error configuring SID engine: " << m_engine.error();
	    SetErrorMessage(str.str());

	    return false;
	}

	if (!m_engine.load(m_tune))
	{
	    std::ostringstream str;

	    str << "Error loading SID tune into engine: " << m_engine.error();
	    SetErrorMessage(str.str());

	    return false;
	}

	m_engine.initMixer(true);

	return true;
    }

    bool SidApi::Decode(Decoded& result)
    {
	const Config& config(Config::Instance());
	const SidTuneInfo *info = m_tune->getInfo();

	if (info != 0 && info->numberOfInfoStrings() > 2)
	{
	    result.Info().Title(UTF8::Convert(info->infoString(0)));
	    result.Info().Artist(UTF8::Convert(info->infoString(1)));
	    result.Info().Year(UTF8::Convert(info->infoString(2)));
	    result.Info().Album(UTF8::Convert(info->infoString(0)));
	}

	int length = m_database.lengthMs(*m_tune);

	if (length < 1)
	{
	    length = config.DecoderDefaultLength() * 1000;
	}

	// PAL cycles per 100 msec
	int cycles = 98525;

	if (info->songSpeed() == SidTuneInfo::CLOCK_NTSC)
	{
	    // NTSC cycles per 100 msec
	    cycles = 102273;
	}

	int buffsize = m_engine.getBufSize(cycles);
	std::vector<short> buffer(buffsize);

	while(m_engine.timeMs() < length)
	{
	    int played = m_engine.play(cycles);

	    if (played < 0)
	    {
	    	VGMLOG("Error playing SID: %s", m_engine.error());
		return false;
	    }

	    int samples = m_engine.mix(buffer.data(), played);
	    result.AddToData(buffer.data(), samples);
	}

    	return true;
    }

    void SidApi::SetStaticData()
    {
	const Config& config(Config::Instance());

	if (config.SidKernalSet())
	{
	    m_kernal = new SourceFile(config.SidKernal());

	    if (m_kernal == 0)
	    {
	    	Util::OSError("new SourceFile");
	    }

	    if (!m_kernal->ReadOk())
	    {
		VGMLOG("Failed to read kernal ROM from %s",
					config.SidKernal().c_str());
		delete m_kernal;
		m_kernal = 0;
	    }
	}

	if (config.SidChargenSet())
	{
	    m_chargen = new SourceFile(config.SidChargen());

	    if (m_chargen == 0)
	    {
	    	Util::OSError("new SourceFile");
	    }

	    if (!m_chargen->ReadOk())
	    {
		VGMLOG("Failed to read chargen ROM from %s",
					config.SidChargen().c_str());
		delete m_chargen;
		m_chargen = 0;
	    }
	}

	if (config.SidBasicSet())
	{
	    m_basic = new SourceFile(config.SidBasic());

	    if (m_basic == 0)
	    {
	    	Util::OSError("new SourceFile");
	    }

	    if (!m_basic->ReadOk())
	    {
		VGMLOG("Failed to read BASIC ROM from %s",
					config.SidBasic().c_str());
		delete m_basic;
		m_basic = 0;
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
