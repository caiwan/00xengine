#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "Utils/Color.hpp"
#include "Math/Vector3.hpp"

namespace engine{
	/// \brief Light type. Used with shaders
	enum LightType{
		LTPoint,
		LTDirectionnal,
		LTSpot
	};

	/// \brief Light class containing only informations used by shaders
	class Light{
	public:
		/// \brief Empty Ctor, initialize with default Light
		Light() :	mType(LTPoint),
						mAmbient(Color::Black),
						mDiffuse(Color::White),
						mSpecular(Color::Black),
						mPosition(Vector3F::ZERO),
						mDirection(Vector3F::NEGUNIT_Y),
						mRange(5),
						mFalloff(0),
						mAttenuation0(0.f),
						mAttenuation1(1.f),
						mAttenuation2(0.5f),
						mTheta(0),
						mPhi(0)
		{
		}

		/// \brief Light Update
		void Update();

		/// \brief Enable or Disable the Light
		void Enable(bool pVal) { mIsOn = pVal; }

		/// \brief Setters

		void SetPosition(const Vector3F &pPos) { mPosition = pPos; }
		void SetDirection(const Vector3F &pDir) { mDirection = pDir; }

		void SetRange(f32 pRange) { mRange = pRange; }
		void SetFalloff(f32 pFalloff) { mFalloff = pFalloff; }
		void SetAttenuationConstant(f32 pAtt) { mAttenuation0 = pAtt; }
		void SetAttenuationLinear(f32 pAtt) { mAttenuation1 = pAtt; }
		void SetAttenuationQuadratic(f32 pAtt) { mAttenuation2 = pAtt; }
		void SetTheta(f32 pTheta) { mTheta = pTheta; }
		void SetPhi(f32 pPhi) { mPhi = pPhi; }

		void SetAmbient(Color pColor) { mAmbient = pColor; }
		void SetDiffuse(Color pColor) { mDiffuse = pColor; }
		void SetSpecular(Color pColor) { mSpecular = pColor; }

		void SetType(LightType pType) { mType = pType; }

		/// \brief Getters

		f32 GetRange() const{ return mRange; }
		f32 GetFalloff() const{ return mFalloff; }
		f32 GetAttenuationConstant() const{ return mAttenuation0; }
		f32 GetAttenuationLinear() const{ return mAttenuation1; }
		f32 GetAttenuationQuadratic() const{ return mAttenuation2; }
		f32 GetTheta() const{ return mTheta; }
		f32 GetPhi() const{ return mPhi; }

		LightType GetType() const{ return mType; }

		Color GetAmbient() const{ return mAmbient; }
		Color GetDiffuse() const{ return mDiffuse; }
		Color GetSpecular() const{ return mSpecular; }

		Vector3F GetPosition() const{ return mPosition; }
		Vector3F GetDirection() const{ return mDirection; }

	private:
		bool mIsOn;

		LightType mType;

		Color mAmbient, mDiffuse, mSpecular;
		Vector3F mPosition, mDirection;
		f32 mRange, mFalloff;
		f32 mAttenuation0, mAttenuation1, mAttenuation2;
		f32 mTheta, mPhi;
	};
}
#endif