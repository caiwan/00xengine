#include "Frustum.hpp"
#include "Utils/String.hpp"
#include "Debug/Debug.hpp"

namespace engine {
	void Plane::Normalize(){
		static f32 length = 0;
		length = 1.f / Math::Sqrt(A * A + B * B + C * C);

		A *= length;
		B *= length;
		C *= length;
		D *= length;
	}

	const Plane& Frustum::operator()(s32 pIndex) const{
		switch(pIndex){
			case 0: return mTop;
			case 1: return mBottom;
			case 2: return mLeft;
			case 3: return mRight;
			case 4: return mNear;
			case 5: return mFar;
			default: throw Exception(String("Frustum Plane No \"")+pIndex+"\" doesn't exist");
		}
	}

	void Frustum::SetFrustum(const Matrix4 &pViewProj){
		static s32 debug = 1;

		mLeft.A = pViewProj(0,3) + pViewProj(0,0);
		mLeft.B = pViewProj(1,3) + pViewProj(1,0);
		mLeft.C = pViewProj(2,3) + pViewProj(2,0);
		mLeft.D = pViewProj(3,3) + pViewProj(3,0);

		mLeft.Normalize();

		if(!debug){
			std::cout << "//////////////////////////////////////////////" << std::endl;
			std::cout << mLeft.A << "    "
					   << mLeft.B << "    "
					   << mLeft.C << "    "
					   << mLeft.D << eol;
		}
		mRight.A = pViewProj(0,3) - pViewProj(0,0);
		mRight.B = pViewProj(1,3) - pViewProj(1,0);
		mRight.C = pViewProj(2,3) - pViewProj(2,0);
		mRight.D = pViewProj(3,3) - pViewProj(3,0);

		mRight.Normalize();


		if(!debug)
			std::cout << mRight.A << "    "
					   << mRight.B << "    "
					   << mRight.C << "    "
					   << mRight.D << eol;
		mBottom.A = pViewProj(0,3) + pViewProj(0,1);
		mBottom.B = pViewProj(1,3) + pViewProj(1,1);
		mBottom.C = pViewProj(2,3) + pViewProj(2,1);
		mBottom.D = pViewProj(3,3) + pViewProj(3,1);

		mBottom.Normalize();

		if(!debug)
			std::cout << mBottom.A << "    "
					   << mBottom.B << "    "
					   << mBottom.C << "    "
					   << mBottom.D << eol;
		mTop.A = pViewProj(0,3) - pViewProj(0,1);
		mTop.B = pViewProj(1,3) - pViewProj(1,1);
		mTop.C = pViewProj(2,3) - pViewProj(2,1);
		mTop.D = pViewProj(3,3) - pViewProj(3,1);

		mTop.Normalize();

		if(!debug)
			std::cout << mTop.A << "    "
					   << mTop.B << "    "
					   << mTop.C << "    "
					   << mTop.D << eol;
		mFar.A = pViewProj(0,3) - pViewProj(0,2);
		mFar.B = pViewProj(1,3) - pViewProj(1,2);
		mFar.C = pViewProj(2,3) - pViewProj(2,2);
		mFar.D = pViewProj(3,3) - pViewProj(3,2);

		mFar.Normalize();

		if(!debug)
			std::cout << mFar.A << "    "
					   << mFar.B << "    "
					   << mFar.C << "    "
					   << mFar.D << eol;
		mNear.A = pViewProj(0,3) + pViewProj(0,2);
		mNear.B = pViewProj(1,3) + pViewProj(1,2);
		mNear.C = pViewProj(2,3) + pViewProj(2,2);
		mNear.D = pViewProj(3,3) + pViewProj(3,2);

		mNear.Normalize();

		if(!debug){
			std::cout << mNear.A << "    "
					   << mNear.B << "    "
					   << mNear.C << "    "
					   << mNear.D << eol;
			std::cout << "//////////////////////////////////////////////" << std::endl;
		}
	}

	bool Frustum::CubeInFrustum(const AABB &pCube) const {
		// Recuperation des vertices du cube AABB
		Vector3F corners[8];
		pCube.GetVertices(corners);
		
		int inCount; // comptage des vertices a l'interieur du frustum pour
					 // chaque plan

		for(int p = 0; p < 6; ++p){
			inCount = 8;

			// Check du plan pour tous les vertices du cube
			for(int i = 0; i < 8; ++i){
				if((Dot((*this)(p).GetNormal(), corners[i]) + (*this)(p).D) < 0){
					--inCount;
				}
			}
			
			// Si le cube est completement en dehors d'un plan
			// L'objet n'est pas affiche
			if(inCount == 0)
				return false;
		}

		// Si au moins un point est dedans, on affiche
		return true;
	}

}
