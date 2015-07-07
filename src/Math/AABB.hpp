#ifndef AABB_HPP
#define AABB_HPP

#include "Vector3.hpp"

namespace engine {
	struct Vertex;
	class Quaternion;

	/// \brief Axis-Aligned Bounding Box Class
	class OOXAPI AABB{
		/// For BSphere computation
		friend class BSphere;
	public:
		/// \brief Ctor from already known bounding box
		AABB(Vector3F pOrigin = Vector3F::ZERO, Vector3F pEnd = Vector3F::ZERO);

		/// \brief Initialize the AABB from a vertices array
		/// \param pVertices : vertice array
		/// \param pSize : element number in above array
		void Init(Vector3F* pVertices, u32 pSize);

		/// \brief Sets the AABB origin position
		void SetOrigin(const Vector3F &pOrigin) { mOrigin = pOrigin; }

		/// \brief Sets the AABB end position
		void SetEnd(const Vector3F &pEnd) { mEnd = pEnd; }

		/// \brief Scales the AABB with factors depending on axis
		void Scale(const Vector3F &pScaleFactor);

		/// \brief Moves the AABB with a Vector
		void Translate(const Vector3F &pTrans);

		/// \brief Rotate the AABB with a Quaternion
		void Rotate(const Quaternion &pOrient);

		/// \brief Returns the 8 positions of the AABB
		void GetVertices(Vector3F pTab[8]) const;
		
	protected:
		Vector3F mOrigin;
		Vector3F mEnd;
	};

	/// \brief Bounding Sphere class
	class BSphere{
	public:
		/// \brief Ctor from an Origin point and a Radius
		BSphere(Vector3F pOrigin = Vector3F::ZERO, f32 mRadius = 1.f);

		/// \brief Initialize the BSphere from a vertices array
		/// \param pVertices : vertices array
		/// \param pSize : element number in above array
		void Init(Vertex* pVertices, u32 pSize);

		/// \brief Initialize the BSphere from an AABB
		void Init(const AABB &pAABB);

		/// \brief Sets the BSphere radius
		void SetRadius(f32 pValue) { mRadius = pValue; }

		/// \brief Sets the BSphere Origin point
		void SetOrigin(const Vector3F &pOrigin) { mOrigin = pOrigin; }

		/// \brief Moves the BSphere with a Vector3
		void Translate(const Vector3F &pTrans){ mOrigin += pTrans; }

		/// \brief Scales the BSPhere
		void Scale(f32 pScaleFactor) { mRadius *= pScaleFactor; }

		/// \brief Returns the BSphere radius
		f32 GetRadius() const { return mRadius; }

		/// \brief Returns the BSphere origin point
		const Vector3F& GetOrigin() const { return mOrigin; }

	private:
		f32 mRadius;
		Vector3F mOrigin;
	};
}
#endif
