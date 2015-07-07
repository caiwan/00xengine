#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Frustum.hpp"
#include "Utils/Shared.hpp"
#include "Math/Quaternion.hpp"

namespace engine {
	class Renderer;

	enum eCamDir{
		CD_Forward, 
		CD_Right,
		CD_Up
	};

	enum eCamRot{
		CR_Pitch,
		CR_Roll,
		CR_Yaw
	};

	/// \brief Camera Class, Freefly only for now
	class OOXAPI Camera{
	public:
		Camera();
		Camera(const Vector3F &Pos);
		~Camera();

		/// \brief Initialise Camera with default values
		void Init();

		/// \brief Set the Camera position
		/// \param Pos : new Position
		void SetPosition(const Vector3F &Pos);

		/// \brief Set the Camera orientation
		/// \param Quat : new Orientation
		void SetOrientation(const Quaternion &Quat);

		/// \brief Returns the X Normal Axis of the camera
		const Vector3F GetAxisX() const;
		
		/// \brief Returns the Y Normal Axis of the camera
		const Vector3F GetAxisY() const;
		
		/// \brief Returns the Z Normal Axis of the camera
		const Vector3F GetAxisZ() const;
		
		/// \brief Move the camera on the Right (X) Axis
		void MoveRight(f32 dist) { ApplyTranslation(dist, CD_Right); }
		
		/// \brief Move the camera on the Up (Y) Axis
		void MoveUp(f32 dist) { ApplyTranslation(dist, CD_Up); }

		/// \brief Move the camera on the Forward (Z) Axis
		void MoveForward(f32 dist) { ApplyTranslation(dist, CD_Forward); }

		/// \brief Rotate around the Right (X) Axis
		void Pitch(f32 angle) { ApplyRotation(angle, CR_Pitch); }

		/// \brief Rotate around the Up (Y) Axis
		void Yaw(f32 angle) { ApplyRotation(angle, CR_Yaw); }
		
		/// \brief Rotate around the Forward (Z) Axis
		void Roll(f32 angle) { ApplyRotation(angle, CR_Roll); }

		/// \brief Look At Function
		/// \param To : Position pointed by the camera
		/// \param From : Position of the camera
		void LookAt(const Vector3F &To, const Vector3F &From);
		
		/// \brief Change the rotation speed of the camera
		void SetRPM(f32 r)			{ mRpm = r; }
		
		/// \brief Change the movement speed of the camera
		void SetSpeed(f32 s)		{ mSpeed = s; }
		
		/// \brief Change the mouse sensitivity of the camera
		void SetSensivity(f32 s)	{ mSensivity = s; }
		
		/// \brief Change the name of the camera
		void SetName(const std::string &n) { mName = n; }

		/// Getters

			f32 GetSpeed()				const { return mSpeed; }
			f32 GetSensivity()			const { return mSensivity; }
			f32 GetRPM()				const { return mRpm; }

			Vector3F GetPosition()		const { return mPosition; }
			Quaternion GetOrientation() const { return mOrientation; }
			const std::string& GetName()const { return mName; }


		/// \brief Returns the ViewMatrix computed from the camera movement
		const Matrix4& GetViewMatrix();

		/// \brief Returns the camera Frustum
		const Frustum& GetFrustum() const { return mFrustum; }

	private:
		std::string mName;

		Renderer* mCurrRenderer;

		void Update();

		void ApplyRotation(f32 angle, eCamRot rot);
		void ApplyTranslation(f32 dist, eCamDir dir);

		void RotateXAxis(f32 angle);
		void RotateYAxis(f32 angle);
		void RotateZAxis(f32 angle);

		Matrix4 ViewMatrix;
		Frustum mFrustum;

		Vector3F mPosition;
		Quaternion mOrientation;	
		
		f32 mSpeed;		
		f32 mSensivity;		
		f32 mRpm;			

		bool mNeedUpdate;	/// True if changes happened to camera position or orientation
	};
}
#endif
