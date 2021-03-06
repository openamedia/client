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

#ifndef OPENAMEDIA_VIDEO_ENGINE_H
#define OPENAMEDIA_VIDEO_ENGINE_H

#include "MediaPlayer.h"
#include "io/ANativeWindowRenderer.h"
#include <pthread.h>

namespace openamedia {

	class VideoEngine : public Engine {
	public:
		VideoEngine();
		virtual ~VideoEngine();

		virtual bool setSource(Prefetcher::SubSource* src);
		bool setSink(ANativeWindow* window);
		virtual bool setTimeSync(SyncTimer* timer);
		virtual bool start();
		virtual bool stop();
		virtual bool pause();
		virtual bool resume();
		virtual bool seek(int64_t time);

	private:
		Mutex mLock;
		Condition mCond;
		pthread_t mThread;
		bool mStarted;
		bool mDone;
		bool mThreadExited;

		bool mPausing;
		bool mSeeking;
		int64_t mSeekTime;

		Prefetcher::SubSource* mSource;
		ANativeWindow* mNativeWindow;
		ANativeWindowRenderer* mRenderer;

		SyncTimer* mTimer;
		
		static void* ThreadWrapper(void* me);
		void threadEntry();

		VideoEngine(const VideoEngine&);
		VideoEngine& operator=(const VideoEngine&);
	};

}//namespace

#endif//OPENAMEDIA_VIDEO_PLAYER_H
