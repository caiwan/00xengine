#ifndef VECTOR3_HPP
#define VECTOR3_HPP

#include "Mathlib.hpp"

namespace engine {
	class Matrix4;
	template<class T>
    class Vector3{
    public:
		Vector3(T x = 0, T y = 0, T z =0);
			
		// Sets vector components
		void Set(T x, T y, T z);

		// Returns the vector components in an array
		void XYZ(T pTab[]) const;

		// Returns the vector length
		T Norme() const;

		// Returns the squared length (used internally for Norme())
		T NormeSq() const;

		// Normalize the vector
		void Normalize();

		// Scale the vector from an Origin point and a scalle Factor
		void ScaleFrom(const Vector3<T> &pCenter, f32 pScaleFactor);

		// Returns the negate of the vector
		Vector3<T> operator- () const;

		// Binary operators
		Vector3<T> operator+ (const Vector3<T> &V) const;
		Vector3<T> operator- (const Vector3<T> &V) const;

		Vector3<T>& operator+= (const Vector3<T> &V) ;
		Vector3<T>& operator -= (const Vector3<T> &V) ;
		
		Vector3<T> operator*(T t) const;
		Vector3<T> operator/(T t) const;

		Vector3<T>& operator*= (T t);
		Vector3<T>& operator /= (T t);

		// Comparison operators
		bool operator==(const Vector3<T> &V) const;
		bool operator!=(const Vector3<T> &V) const;

		// Returns a pointer on x
		operator T*();

		// Static constant 
			// Zeroed Vector
			static const OOXAPI Vector3 ZERO;

			// Normal Vectors
			static const OOXAPI Vector3 UNIT_Z;	// +Z
			static const OOXAPI Vector3 NEGUNIT_Z;	// -Z
			
			static const OOXAPI Vector3 UNIT_X;	// +X
			static const OOXAPI Vector3 NEGUNIT_X;	// -X
			
			static const OOXAPI Vector3 UNIT_Y;	// +Y
			static const OOXAPI Vector3 NEGUNIT_Y;	// -Y

		// Data
		T x;
		T y;
		T z;
	};
	
	// Result of multiplication between a vector and a T
	template<class T> Vector3<T> operator* (const Vector3<T> &V, T t);
	
	// Result of division between a vector and a T
	template<class T> Vector3<T> operator/ (const Vector3<T> &V, T t);
	
	// Result of multiplication between a T and a vector
	template<class T> Vector3<T> operator* (T t, const Vector3<T> &V);
	
	// Dot product between two vector3
	template<class T> T Dot(const Vector3<T> &U, const Vector3<T> &V);
	
	// Cross product between two vector3
	template<class T> Vector3<T> Cross(const Vector3<T> &U, const Vector3<T> &V);

	// Stream Ops
	template<class T> std::istream& operator >>(std::istream& iss, Vector3<T> &V);
	template<class T> std::ostream& operator <<(std::ostream& oss, const Vector3<T> &V);

	#include "Vector3.inl"
	typedef Vector3<s32> Vector3I;
	typedef Vector3<f32> Vector3F;
}
#endif
