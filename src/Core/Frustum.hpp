#ifndef FRUSTUM_HPP
#define FRUSTUM_HPP

#include "Math/AABB.hpp"
#include "Math/Matrix4.hpp"

namespace engine {
	/// \brief 3D Plane
	class Plane{
	public:
		/// \brief Normalize the plane components
		void Normalize();

		/// \brief Returns the plane normal
		Vector3F GetNormal() const { return Vector3F(A,B,C); }

		/// Components
		f32 A,			/// N.x
			B,			/// N.y
			C,			/// N.z
			D;			/// Distance
	};



	/// \brief Camera Frustum used for Frustum Culling
	class OOXAPI Frustum{
	public:
		/// \brief Sets the Frustum Planes from ViewProj Matrix
		void SetFrustum(const Matrix4 &pViewProj);

		/// \brief Check if a cube is in the Frustum
		bool CubeInFrustum(const AABB &pCube) const;

		const Plane& operator()(s32 pIndex) const;

		/// \brief The frustum's six planes
		Plane mTop, mBottom, mLeft, mRight, mNear, mFar;
	};
}
#endif
