#include "AABB.hpp"
#include "Quaternion.hpp"
#include "Renderer/VBO.hpp"

namespace engine {
	AABB::AABB(Vector3F pOrigin, Vector3F pEnd) : mOrigin(pOrigin), mEnd(pEnd){
	}

	void AABB::Init(Vector3F* pVertices, u32 pSize){
		for(u32 i = 0; i < pSize; ++i){
			mOrigin.x = Math::Min(pVertices[i].x, mOrigin.x);
			mOrigin.y = Math::Min(pVertices[i].y, mOrigin.y);
			mOrigin.z = Math::Min(pVertices[i].z, mOrigin.z);

			mEnd.x = Math::Max(pVertices[i].x, mEnd.x);
			mEnd.y = Math::Max(pVertices[i].y, mEnd.y);
			mEnd.z = Math::Max(pVertices[i].z, mEnd.z);
		}
	}

	void AABB::Scale(const Vector3F &pScaleFactor){
		mOrigin.x *= pScaleFactor.x;
		mOrigin.y *= pScaleFactor.y;
		mOrigin.z *= pScaleFactor.z;
		mEnd.x *= pScaleFactor.x;
		mEnd.y *= pScaleFactor.y;
		mEnd.z *= pScaleFactor.z;
	}

	void AABB::Translate(const Vector3F &pTrans){
		mOrigin += pTrans;
		mEnd += pTrans;
	}

	void AABB::GetVertices(Vector3F pTab[8]) const{
		pTab[0] = mOrigin;
		pTab[1] = Vector3F(mEnd.x, mOrigin.y, mOrigin.z);
		pTab[2] = Vector3F(mOrigin.x, mEnd.y, mOrigin.z);
		pTab[3] = Vector3F(mOrigin.x, mOrigin.y, mEnd.z);
		pTab[4] = Vector3F(mOrigin.x, mEnd.y, mEnd.z);
		pTab[5] = Vector3F(mEnd.x, mOrigin.y, mEnd.z);
		pTab[6] = Vector3F(mEnd.x, mEnd.y, mOrigin.z);
		pTab[7] = mEnd;
	} 

	void BSphere::Init(const AABB &pAABB){
		mOrigin.x = (pAABB.mOrigin.x + pAABB.mEnd.x) / 2;
		mOrigin.y = (pAABB.mOrigin.y + pAABB.mEnd.y) / 2;
		mOrigin.z = (pAABB.mOrigin.z + pAABB.mEnd.z) / 2;

		mRadius = (pAABB.mEnd - pAABB.mOrigin).Norme();
	}
}
