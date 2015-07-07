#ifndef QUATERNION_HPP
#define QUATERNION_HPP

#include "Mathlib.hpp"
#include "Matrix4.hpp"

namespace engine {
	class Quaternion{
	public:
		/// \brief Ctor from 4 floats
		Quaternion(f32 X = 0, f32 Y = 0, f32 Z = 0, f32 W = 0);

		/// \brief Ctor from matrix
		Quaternion(const Matrix4 &mat);

		/// \brief Ctor from Axis-Angle
		Quaternion(const Vector3F &Axis, f32 Angle);

		/// \brief Returns the quaternion conjugate
		Quaternion Conjugate() const;

		/// \brief Make the quaternion an Identity quaternion
		void Identity();

		/// \brief Normalize the quaternion
		void Normalize();


		/// \brief Returns a Rotation matrix containing the quaternion orientation
		Matrix4 ToMatrix() const;

		/// \brief Create the quaternion from Matrix4
		void FromMatrix(const Matrix4 &mat);

		/// \brief Create the quaternion from Axis-Angle
		void FromAxisAngle(const Vector3F &Axis, f32 Angle);

		/// \brief Create the quaternion from three Euler Angles
		void FromEulerAngle(f32 X, f32 Y, f32 Z);

		/// \brief Returns the Axis-Angle form of the quaternion
		/// \param Axis : Vector that'll contain the axis of the quaternion
		/// \param Angle : float that'll contain the angle of the quaternion
		void ToAxisAngle(Vector3F &Axis, f32 &Angle) const;

		/// \brief Multiply functions
		Quaternion operator*(const Quaternion &quat) const;
		const Quaternion& operator*=(const Quaternion& quat);
		
		/// \brief Returns the result of the multiplication with a vector
		Vector3F operator*(const Vector3F &pVec) const;

		/// \brief Returns the negate of the quaternion
		Quaternion operator-() const;

		f32 x;
		f32 y;
		f32 z;
		f32 w;
	};

	/// \brief Stream Ops
	std::istream& operator >> (std::istream& iss, Quaternion &quat);
	std::ostream& operator << (std::ostream& oss, const Quaternion &quat);

	#include "Quaternion.inl"
}
#endif
