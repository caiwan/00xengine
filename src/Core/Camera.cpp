#include "Camera.hpp"
#include "Renderer/Renderer.hpp"

namespace engine{
	Camera::Camera() : mName("Camera1"), mPosition(Vector3F::ZERO) {
		Init();
	}

	Camera::Camera(const Vector3F &Pos) : mPosition(Pos) {
		Init();
	}

	Camera::~Camera(){
	}
	
	void Camera::Init(){
		mSpeed = 10.f;
		mSensivity =  0.1f;
		mRpm = 10.f;
		mCurrRenderer = Renderer::Get();
	}

	void Camera::SetPosition(const Vector3F &Pos){
		mPosition = Pos;
		Update();
	}
	
	void Camera::SetOrientation(const Quaternion &Quat){
		mOrientation = Quat;
		Update();
	}
	
	const Vector3F Camera::GetAxisX() const{
		Vector3F ret;
		ret.x = ViewMatrix.a11;
		ret.y = ViewMatrix.a21;
		ret.z = ViewMatrix.a31;

		return ret;
	}

	const Vector3F Camera::GetAxisY() const{
		Vector3F ret;
		ret.x = ViewMatrix.a12;
		ret.y = ViewMatrix.a22;
		ret.z = ViewMatrix.a32;

		return ret;
	}

	const Vector3F Camera::GetAxisZ() const{
		Vector3F ret;
		ret.x = ViewMatrix.a13;
		ret.y = ViewMatrix.a23;
		ret.z = ViewMatrix.a33;

		return ret;
	}

	const Matrix4& Camera::GetViewMatrix(){
		if(mNeedUpdate)
			Update();

		return ViewMatrix;
	}

	void Camera::Update(){
		Matrix4 matTranslation, matRotation;

		// Calcul de la nouvelle matrice de vue
		matTranslation.SetTranslation(-mPosition.x, -mPosition.y, -mPosition.z); 
		matRotation = mOrientation.ToMatrix();

		ViewMatrix = matTranslation * matRotation;

		// Envoi de la matrice au renderer pour calcul de la ViewProjMatrix
		mCurrRenderer->Set3DViewMatrix(ViewMatrix);

		// Recuperation de la ViewProjMatrix pour calculer le nouveau Frustum
		mFrustum.SetFrustum(mCurrRenderer->Get3DViewProjMatrix());

		mNeedUpdate = false;
	}

	void Camera::LookAt(const Vector3F &To, const Vector3F &From){
		Matrix4 temp;
		temp.LookAt(From, To, Vector3F::UNIT_Y);

		mPosition = From;
		mOrientation.FromMatrix(temp);

		Update();
	}

	void Camera::ApplyTranslation(f32 dist, eCamDir dir){
		Vector3F direction;

		switch(dir){
			case CD_Forward	: direction = -GetAxisZ(); break;
			case CD_Up		: direction = GetAxisY(); break;
			case CD_Right	: direction = GetAxisX(); break;
		}

		mPosition += direction * mSpeed * dist;
		Update();
	}

	void Camera::ApplyRotation(f32 angle, eCamRot rot){
		angle *= (-mRpm / 60.f);		// multiplie par la vitesse de rotation

		switch(rot){
			case CR_Yaw 	: RotateYAxis(angle); break;
			case CR_Pitch 	: RotateXAxis(angle); break;
			case CR_Roll 	: RotateZAxis(angle); break;
		}

		mOrientation.Normalize();
		Update();
	}

	void Camera::RotateXAxis(f32 angle){
		Quaternion temp;
		temp.FromAxisAngle(Vector3F::UNIT_X, angle);

		mOrientation *= temp;
	}

	void Camera::RotateYAxis(f32 angle){
		Quaternion temp;
		temp.FromAxisAngle(Vector3F::UNIT_Y, angle);

		mOrientation = temp * mOrientation;		// (Autour de UNIT_Y Global et non local)
	}

	void Camera::RotateZAxis(f32 angle){
		Quaternion temp;
		temp.FromAxisAngle(Vector3F::UNIT_Z, angle);

		mOrientation *= temp;
	}

}
