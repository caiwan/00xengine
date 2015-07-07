#ifndef CLOCK_HPP
#define CLOCK_HPP

#include "Shared.hpp"

namespace engine {
	/// \brief Returns system time, depending on platform
    /// \return the UTC time, seconds only
	f64 GetSystemTime();

	/// \brief Make the current thread sleep
	/// \param pTime : sleep time in seconds
	void Sleep(f32 pTime);


	/// \brief Clock is a small class used to manage time like with a timer
	class OOXAPI Clock{
	public:
		/// \brief Ctor, zeroed clock
		Clock();

		/// \brief Reset the clock to zero
		void Reset();

		/// \brief Pause the clock
		void Pause();

		/// \brief Resume the clock if it has been paused
		void Resume();

		/// \brief Returns time elapsed since last Reset
		f32 GetElapsedTime();

	private:
		f64 mLastFrameTime;	/// Global seconds elapsed the previons frame
		f64 mClockTime;		/// Seconds since last clock reset
		f64 mTempTime;		/// Variable used in mClockTime calculation

		bool mPaused;		/// True if the clock is paused
	};
}
#endif
