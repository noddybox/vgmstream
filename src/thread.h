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
#ifndef VGMSTREAM_THREAD_H
#define VGMSTREAM_THREAD_H

#include <pthread.h>

#include "mtvar.h"

namespace vgmstream
{
    class Thread
    {
    	public:

	    // Implementors should call this from their constructor.
	    Thread();

	    // Destructor.
	    virtual ~Thread();

	    // Cancel the thread; waits for the thread to exit
	    void Cancel();

	    // Is the thread alive
	    bool Alive();

	protected:

	    // Implementors should call this to create the thread once
	    // initialisation is complete.
	    void CreateThread();

	    // Implementors must implement this with their thread code.
	    virtual void ThreadCode() = 0;

	private:

	    MTVar<bool>	m_alive;
	    pthread_t	m_thread;

	    static void *ThreadWrapper(void *object_pointer);
    };
};

#endif
