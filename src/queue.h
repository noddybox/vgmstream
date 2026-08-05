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

namespace vgmstream
{
    template <typename T> class Queue
    {
    	public:

	    // Construct a queue.
	    //
	    Queue();

	    // Get the next entry from the queue.  Returns false if there
	    // is nothing on the queue, otherwise true and stores the head
	    // of the queue in head.
	    //
	    bool Pop(T& head);

	    // Push an entry onto the queue.
	    void Push(T& entry);

	private:

	    std::queue<T>	m_queue;
	    pthread_mutex_t	m_mutex;
    };

    template <typename T> Queue<T>::Queue()
    {
    	pthread_mutex_init(&m_mutex, 0);
    }

    template <typename T> bool Queue<T>::Pop(T& head)
    {
	pthread_mutex_lock(&m_mutex);

    	if (m_queue.size() == 0)
	{
	    pthread_mutex_unlock(&m_mutex);
	    return false;
	}

	head = m_queue.front();
	m_queue.pop();

	pthread_mutex_unlock(&m_mutex);
	return true;
    }

    template <typename T> void Queue<T>::Push(T& entry)
    {
	pthread_mutex_lock(&m_mutex);
	m_queue.push(entry);
	pthread_mutex_unlock(&m_mutex);
    }
};

#endif
