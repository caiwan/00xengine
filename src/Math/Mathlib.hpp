#ifndef MATHLIB_HPP
#define MATHLIB_HPP

#include <cmath>
#include <iostream>
#include <limits>
#include "Utils/Shared.hpp"

namespace engine {	
	class OOXAPI Math{
	public:

		/// Fonctions
		static f32 ToDeg(f32 radian);
		static f32 ToRad(f32 degree);

		static f32 Cos(f32 value);
		static f32 Sin(f32 value);
		static f32 Tan(f32 value);
		static f32 ACos(f32 value);
		static f32 ASin(f32 value);
		static f32 ATan(f32 value);
		static f32 ATan2(f32 Y, f32 X);
		
		static f32 Sqrt(f32 value);
		static f32 InvSqrt(f32 value);
		
		static f32 Ceil(f32 value);
		static f32 Floor(f32 value);
		
		static f32 Abs(f32 value);
		
		static f32 Pow(f32 value, u32 exp);
		static f32 Exp(f32 value);
		
		static int Sign(int value);
		static int Sign(f32 value);

		template<typename T> static T Max(T a, T b);
		template<typename T> static T Min(T a, T b);
		
		/// \brief Random between min and max
		static f32 Rand(u32 min = 0, u32 max = 1, u32 seed = 0);

		/// \brief Not a Number check
		static bool IsNaN(double x);

		/// \brief Quasi-equality between to floats
		static bool IsEqual(f32 x, f32 y);

		/// \brief Power of 2
		static bool IsPowOf2(u32 value);

		/// \brief Clamp a value between to other
		/// \param val : value to clamp
		/// \param min : lower bound
		/// \param max : upper bound
		static f32 Clamp(f32 val, f32 min, f32 max);

		/// Constants
		static const f32 Epsilon;		/// Constant used to compare two floats
		static const f32 Pi;
		static const f32 HalfPi;
	};
	
	#include "Mathlib.inl"
}

#endif
