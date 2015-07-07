#ifndef MATRIX4_HPP
#define MATRIX4_HPP

#include "Vector2.hpp"
#include "Vector3.hpp"

namespace engine {
	class Quaternion;
    class Matrix4{
    	public:
			/// \brief Ctor, Identity matrix
    		Matrix4(f32 m11 = 1.f, f32 m12 = 0.f, f32 m13 = 0.f, f32 m14 = 0.f,
						f32 m21 = 0.f, f32 m22 = 1.f, f32 m23 = 0.f, f32 m24 = 0.f,
						f32 m31 = 0.f, f32 m32 = 0.f, f32 m33 = 1.f, f32 m34 = 0.f,
						f32 m41 = 0.f, f32 m42 = 0.f, f32 m43 = 0.f, f32 m44 = 1.f);

			/// \brief Make the matrix an identity matrix
			void Identity();

			/// \brief Fill a float array with matrix data
			void ToFloat(f32* tab) const;

			/// \brief Returns the matrix determinant
			f32 Det() const;

			/// \brief Returns the matrix Inverse
			Matrix4 Inverse() const;

			/// \brief Returns the matrix Transpose
			Matrix4 Transpose() const;

			/// \brief Create a Translation matrix
			void SetTranslation(f32 x, f32 y, f32 z);
			void SetTranslation(const Vector3F &V);

			/// \brief Create a matrix from axis-dependant scale components
			void SetScale(f32 x, f32 y, f32 z);
			void SetScale(const Vector3F &V);

			/// \brief Create a matrix from scale component
			void SetScale(f32 xyz);

			/// \brief Create a Rotation matrix from angle centered on (0,0,0)
			void SetRotationX(f32 Angle);
			void SetRotationY(f32 Angle);
			void SetRotationZ(f32 Angle);

			/// \brief Create a Rotation matrix from Axis-Angle constraints
			void SetRotationX(f32 Angle, const Vector3F &Axis);
			void SetRotationY(f32 Angle, const Vector3F &Axis);
			void SetRotationZ(f32 Angle, const Vector3F &Axis);

			/// \brief Sets the rotation component of the matrix
			void SetOrientation(const Quaternion &pQuat);

			/// \brief Add a Rotation component to the matrix
			void Rotate(const Quaternion &pQuat);

			/// \brief Add a translation component to the matrix
			void Translate(const Vector3F &pVector);

			/// \brief Scales the matrix from axis dependant factors
			void Scale(const Vector3F &pVector);

			/// \brief Scales the matrix on all axis by the same factor
			void Scale(f32 pFactor);

			/// \brief Returns the Translation component
			Vector3F GetTranslation() const;

			/// \brief Returns the Scale component
			Vector3F GetScale() const;

			/// \brief Transform a Vector3 by multiplying it with the matrix
			Vector3F Transform(const Vector3F &V, f32 w = 0.f) const;

			/// \brief Construct a matrix from Translation and Rotation components
			void WorldMatrix(const Vector3F &Translation, const Vector3F &Rotation);

			/// \brief Construct a 2D Orthogonal matrix
			/// params : Boundaries of orthogonal zone. Generally the window bounds
			void OrthoOffCenter(f32 Left, f32 Top, f32 Right, f32 Bottom);

			/// \brief Construct a Perspective Projection Matrix
			/// \param FOV   : Vertical Field of view
			/// \param Ratio : Width/Height ratio
			/// \param Near  : Near plane
			/// \param Far   : Far plane
			void PerspectiveFOV(f32 FOV, f32 Ratio, f32 Near, f32 Far);

			/// \brief Construct a LookAt Matrix
			/// \param From : Position of eye
			/// \param To   : Position pointed by eye
			/// \param Up   : Up Vector, UNIT_Y in the engine
			void LookAt(const Vector3F &From, const Vector3F &To, const Vector3F &Up = Vector3F::UNIT_Y);


			/// Operations
				/// \brief Returns the negate matrix 
				Matrix4 operator -() const;

				/// \brief Matrix addition/substraction functions
				Matrix4 operator +(const Matrix4& m) const;
				Matrix4 operator -(const Matrix4& m) const;
				const Matrix4& operator +=(const Matrix4& m);
				const Matrix4& operator -=(const Matrix4& m);

				/// \brief Matrix multiplication functions
				Matrix4 operator *(const Matrix4& m) const;
				const Matrix4& operator *=(const Matrix4& m);

				/// \brief Multiplies matrix data with a float
				const Matrix4& operator *=(f32 t);

				/// \brief Divides matrix data with a float
				const Matrix4& operator /=(f32 t);

				/// \brief Comparison operators
				bool operator ==(const Matrix4& m) const;
				bool operator !=(const Matrix4& m) const;

				/// \brief Data access operators
				f32& operator ()(std::size_t i, std::size_t j);
				const f32& operator ()(std::size_t i, std::size_t j) const;

				/// \brief Returns a pointer on a11 (for floats arrays)
				operator f32*();
				operator const f32*() const;

				/// Constant Identity matrix
				static const OOXAPI Matrix4 IDENTITY;

				
        // Data
        f32 a11, a12, a13, a14;		// 1st row
        f32 a21, a22, a23, a24;		// 2nd row
        f32 a31, a32, a33, a34;		// 3rd row
        f32 a41, a42, a43, a44;		// 4th row
    };

	Matrix4 operator*(const Matrix4 &m, f32 t);
	Matrix4 operator/(const Matrix4 &m, f32 t);
	Matrix4 operator*(f32 t, const Matrix4 &m);


	std::istream& operator >>(std::istream& iss, Matrix4 &m);
	std::ostream& operator <<(std::ostream& oss, const Matrix4 &m);
	
	#include "Matrix4.inl"

}
#endif
