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
// Thread-safe queue
//
#ifndef VGMSTREAM_QUEUE_H
#define VGMSTREAM_QUEUE_H

#include <queue>
#include <pthread.h>

#include "util.h"

namespace vgmstream
{
    template <typename T> class Queue
    {
    	public:

	    // Construct a queue.
	    Queue()
	    {
		if (pthread_mutex_init(&m_mutex, 0) != 0)
		{
		    Util::OSError("pthread_mutex_init");
		}

		if (pthread_cond_init(&m_event, 0) != 0)
		{
		    Util::OSError("pthread_cond_init");
		}
	    }

	    // Get the next entry from the queue.  Returns false if there
	    // is nothing on the queue but we need to return anyway.
	    bool Pop(T& head)
	    {
		pthread_mutex_lock(&m_mutex);

		if (m_queue.size() == 0)
		{
		    pthread_cond_wait(&m_event, &m_mutex);
		}

		bool result = false;

		if (m_queue.size() > 0)
		{
		    head = m_queue.front();
		    m_queue.pop();
		    result = true;
		}

		pthread_mutex_unlock(&m_mutex);
		return result;
	    }

	    // Push an entry onto the queue.
	    void Push(const T& entry)
	    {
		pthread_mutex_lock(&m_mutex);
		m_queue.push(entry);
		pthread_cond_signal(&m_event);
		pthread_mutex_unlock(&m_mutex);
	    }

	    // The size of the queue
	    std::size_t Size()
	    {
		pthread_mutex_lock(&m_mutex);
		std::size_t size = m_queue.size();
		pthread_mutex_unlock(&m_mutex);
		return size;
	    }

	private:

	    std::queue<T>	m_queue;
	    pthread_mutex_t	m_mutex;
	    pthread_cond_t	m_event;
    };

};

#endif
