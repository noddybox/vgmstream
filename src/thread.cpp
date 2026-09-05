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
    Thread::Thread() : m_alive(false), m_cancel(false),
		       m_force_cancel(false), m_queue_cancel(0)
    {
    }

    Thread::~Thread()
    {
    	Cancel();
    }

    void Thread::Cancel(bool force)
    {
    	m_cancel.Set(true);
	m_force_cancel.Set(force);

	if (m_queue_cancel !=0)
	{
	    m_queue_cancel->Cancel();
	}
    }

    bool Thread::Alive()
    {
    	return m_alive.Get();
    }

    bool Thread::CancelRequested()
    {
    	return m_cancel.Get();
    }

    bool Thread::ForceCancelRequested()
    {
    	return m_force_cancel.Get();
    }

    void Thread::Join()
    {
	pthread_join(m_thread, 0);
    }

    void Thread::SetQueue(QueueCancel *queue)
    {
	m_queue_cancel = queue;
    }

    void Thread::CreateThread()
    {
    	if (pthread_create(&m_thread, 0, ThreadWrapper,
			   static_cast<void*>(this)) != 0)
	{
	    Util::OSError("pthread_create");
	}

	m_alive.Set(true);
    }

    void *Thread::ThreadWrapper(void *object_pointer)
    {
    	Thread *t = static_cast<Thread*>(object_pointer);

	t->ThreadCode();
	t->m_alive.Set(false);
	pthread_exit(0);

	return 0;
    }
};
