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
// Thread-safe wrapper around a variable
//
#ifndef VGMSTREAM_MTVAR_H
#define VGMSTREAM_MTVAR_H

#include <queue>
#include <pthread.h>

#include "util.h"

namespace vgmstream
{
    template <typename T> class MTVar
    {
    	public:

	    // Construct a queue.
	    MTVar(T initial) : m_value(initial)
	    {
		if (pthread_mutex_init(&m_mutex, 0) != 0)
		{
		    Util::OSError("pthread_mutex_init");
		}
	    }

	    // Get the value of the variable
	    T Get()
	    {
		pthread_mutex_lock(&m_mutex);
		T result = m_value;
		pthread_mutex_unlock(&m_mutex);
		return result;
	    }

	    // Set the value of the variable
	    void Set(const T& value)
	    {
		pthread_mutex_lock(&m_mutex);
		m_value = value;
		pthread_mutex_unlock(&m_mutex);
	    }

	private:
	    T			m_value;
	    pthread_mutex_t	m_mutex;
    };

};

#endif
