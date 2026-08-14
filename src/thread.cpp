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
// Thread base class
//
#include "thread.h"
#include "util.h"

namespace vgmstream
{
    Thread::Thread() : m_cancelled(false), m_alive(false)
    {
    }

    Thread::~Thread()
    {
    	Cancel();
    }

    void Thread::Cancel()
    {
    	pthread_cancel(m_thread);
	m_cancelled = true;
	m_alive = false;
    }

    void Thread::CreateThread()
    {
    	if (pthread_create(&m_thread, 0, ThreadWrapper,
			   static_cast<void*>(this)) != 0)
	{
	    Util::OSError("pthread_create");
	}

	m_alive = true;
    }

    void *Thread::ThreadWrapper(void *object_pointer)
    {
    	Thread *t = static_cast<Thread*>(object_pointer);

	t->ThreadCode();
	t->m_alive = false;
	pthread_exit(0);

	return 0;
    }

    bool Thread::Cancelled() const
    {
    	return m_cancelled;
    }

    bool Thread::Alive() const
    {
    	return m_alive;
    }
};
