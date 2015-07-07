#include "Clock.hpp"

#ifdef OOXWIN32
#	include <Windows.h>
#endif

namespace engine {
// ==============================  //
	f64 GetSystemTime(){
		#if defined(OOXWIN32)
			static LARGE_INTEGER Frequency;
			static BOOL          UseHighPerformanceTimer = QueryPerformanceFrequency(&Frequency);

			if (UseHighPerformanceTimer)
			{
				// High performance counter available : use it
				LARGE_INTEGER CurrentTime;
				QueryPerformanceCounter(&CurrentTime);

				return static_cast<double>(CurrentTime.QuadPart) / Frequency.QuadPart;
			}
			else
			{
				// High performance counter not available : use GetTickCount (less accurate)
				return GetTickCount() * 0.001;
			}
		#else
			timeval Time = {0, 0};
			gettimeofday(&Time, NULL);

			return Time.tv_sec + Time.tv_usec / 1000000.;
		#endif
	}

	void Sleep(f32 pTime){
		#if defined(OOXWIN32)
			::Sleep(static_cast<DWORD>(pTime * 1000));
		#else
			usleep(static_cast<u32>(pTime * 1000000));
		#endif
	}

// ==============================  //

	Clock::Clock() : mPaused(false), mClockTime(0.0){
		mLastFrameTime = GetSystemTime();
	}

	void Clock::Reset(){
		mLastFrameTime = GetSystemTime();
		mClockTime = 0.0;
	}

	void Clock::Pause(){
		mPaused = true;
	}

	void Clock::Resume(){
		mLastFrameTime = GetSystemTime();
		mPaused = false;
	}

	f32 Clock::GetElapsedTime(){
		if(!mPaused) {
			mTempTime = GetSystemTime();
			mClockTime += mTempTime - mLastFrameTime;
			mLastFrameTime = mTempTime;
		}
		return static_cast<f32>(mClockTime);
	}
}
