/*
 * Copyright (c) 2014 Jim Qian
 *
 * This file is part of OpenaMedia-C(client).
 *
 * OpenaMedia-C is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * FFmpeg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with OpenaMedia-C; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifndef OPENAMEDIA_SYNC_TIMER_H
#define OPENAMEDIA_SYNC_TIMER_H

#include "android/Mutex.h"

namespace openamedia {

	class SyncTimer {
	public:
		SyncTimer(){
			mTime = 0;
		}
		~SyncTimer(){
		}

		void setTime(int64_t timeUS){
			Mutex::Autolock ao(mLock);
			
			mTime = timeUS;
		}
		
		int64_t getTime(){
			Mutex::Autolock ao(mLock);
			
			return mTime;
		}

	private:
		Mutex mLock;
		int64_t mTime;
	};

}//namespace


#endif//OPENAMEDIA_SYNC_TIMER_H
