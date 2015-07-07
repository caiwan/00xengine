#include "Mathlib.hpp"
#include "Quaternion.hpp"
#include "Matrix4.hpp"
#include "Vector2.hpp"
#include "Vector3.hpp"

namespace engine {
	// Mathlib.hpp
	const float Math::Pi = 3.14159265f;
	const float Math::HalfPi = 1.570796325f;
	const float Math::Epsilon = std::numeric_limits<float>::epsilon();

	// Vector2.hpp
	template<> const Vector2I Vector2I::ZERO = Vector2I(0,0);
	template<> const Vector2F Vector2F::ZERO = Vector2F(0.f, 0.f);

	// Vector3.hpp
	template<> const Vector3I Vector3I::ZERO = Vector3I(0,0,0);
	template<> const Vector3F Vector3F::ZERO = Vector3F(0.f,0.f,0.f);

	template<> const Vector3F Vector3F::UNIT_Z = Vector3F(0.f,0.f,1.f);
	template<> const Vector3F Vector3F::UNIT_X = Vector3F(1.f,0.f,0.f);
	template<> const Vector3F Vector3F::UNIT_Y = Vector3F(0.f,1.f,0.f);
	template<> const Vector3F Vector3F::NEGUNIT_Z = Vector3F(0.f,0.f,-1.f);
	template<> const Vector3F Vector3F::NEGUNIT_X = Vector3F(-1.f,0.f,0.f);
	template<> const Vector3F Vector3F::NEGUNIT_Y = Vector3F(0.f,-1.f,0.f);

	// Matrix4.hpp
	const Matrix4 Matrix4::IDENTITY = Matrix4();

	void Matrix4::SetOrientation(const Quaternion &pQuat){
		Matrix4 tempMat = pQuat.ToMatrix();
		tempMat.SetTranslation(this->GetTranslation());
		*this = tempMat;
	}

	void Matrix4::Rotate(const Quaternion &pQuat){
		Quaternion oldOrient, newOrient;
		oldOrient.FromMatrix(*this);
		newOrient = oldOrient * pQuat;
		this->SetOrientation(newOrient);
	}
}
