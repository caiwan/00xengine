inline engine::Matrix4::Matrix4(f32 m11, f32 m12, f32 m13, f32 m14,
										f32 m21, f32 m22, f32 m23, f32 m24,
										f32 m31, f32 m32, f32 m33, f32 m34,
										f32 m41, f32 m42, f32 m43, f32 m44) : 
			a11(m11), a12(m12), a13(m13), a14(m14),
			a21(m21), a22(m22), a23(m23), a24(m24),
			a31(m31), a32(m32), a33(m33), a34(m34),
			a41(m41), a42(m42), a43(m43), a44(m44) {
};

inline void engine::Matrix4::Identity(){
	a11 = 1.0f; a12 = 0.0f; a13 = 0.0f; a14 = 0.0f;
    a21 = 0.0f; a22 = 1.0f; a23 = 0.0f; a24 = 0.0f;
    a31 = 0.0f; a32 = 0.0f; a33 = 1.0f; a34 = 0.0f;
    a41 = 0.0f; a42 = 0.0f; a43 = 0.0f; a44 = 1.0f;
}

inline void engine::Matrix4::ToFloat(f32* tab) const{
	tab[0] = a11; tab[1] = a12; tab[2] = a13; tab[3] = a14;
	tab[4] = a21; tab[5] = a22; tab[6] = a23; tab[7] = a24;
	tab[8] = a31; tab[9] = a32; tab[10] = a33; tab[11] = a34;
	tab[12] = a41; tab[13] = a42; tab[14] = a43; tab[15] = a44;
}

inline f32 engine::Matrix4::Det() const{
	f32 A = a22 * (a33 * a44 - a43 * a34) - a23 * (a32 * a44 - a34 * a42) + a24 * (a32 * a43 - a33 * a42);
    f32 B = a21 * (a33 * a44 - a43 * a34) - a23 * (a31 * a44 - a34 * a41) + a24* (a31 * a43 - a33 * a41);
    f32 C = a21 * (a32 * a44 - a34 * a42) - a22 * (a31 * a44 - a34 * a41) + a24 * (a31 * a42 - a32 * a41);
    f32 D = a21 * (a32 * a43 - a33 * a42) - a22 * (a31 * a43 - a33 * a41) + a23 * (a31 * a42 - a32 * a41);
	return a11 * A - a12 * B + a13 * C - a14 * D;		// LaPlace en prenant la premiere Colonne, en trouvant ses cofactors(A..D)
}

inline Matrix4 engine::Matrix4::Transpose() const{
	return Matrix4(a11, a21, a31, a41,
								a12, a22, a32, a42,
								a13, a23, a33, a43, 
								a14, a24, a34, a44);
}

inline Matrix4 engine::Matrix4::Inverse() const{
	f32 det = Det();
	Matrix4 inverse;

	if(Math::Abs(det) > Math::Epsilon){
		inverse.a11 =  (a22 * (a33 * a44 - a43 * a34) - a23 * (a32 * a44 - a34 * a42) + a24 * (a32 * a43 - a33 * a42)) / det;
        inverse.a21 = -(a21 * (a33 * a44 - a43 * a34) - a23 * (a31 * a44 - a34 * a41) + a24* (a31 * a43 - a33 * a41)) / det;
        inverse.a31 =  (a21 * (a32 * a44 - a34 * a42) - a22 * (a31 * a44 - a34 * a41) + a24 * (a31 * a42 - a32 * a41)) / det;
        inverse.a41 = -(a21 * (a32 * a43 - a33 * a42) - a22 * (a31 * a43 - a33 * a41) + a23 * (a31 * a42 - a32 * a41)) / det;

        inverse.a12 = -(a12 * (a33 * a44 - a34 * a43) - a13 * (a32 * a44 - a34 * a42) + a14 * (a32 * a43 - a33 *  a42)) / det;
        inverse.a22 =  (a11 * (a33 * a44 - a34 * a43) - a13 * (a31 * a44 - a34 * a41) + a14 * (a31 * a43 - a33 *  a41)) / det;
        inverse.a32 = -(a11 * (a32 * a44 - a34 * a42) - a12 * (a31 * a44 - a34 * a41) + a14 * (a31 * a42 - a32 *  a41)) / det;
        inverse.a42 =  (a11 * (a32 * a43 - a33 * a42) - a12 * (a31 * a43 - a33 * a41) + a13 * (a31 * a42 - a32 *  a41)) / det;

        inverse.a13 =  (a12 * (a23 * a44 - a24 * a43) - a13 * (a22 * a44 - a24 * a42) + a14 * (a22 * a43 - a23 *  a42)) / det;
        inverse.a23 = -(a11 * (a23 * a44 - a24 * a43) - a13 * (a21 * a44 - a24 * a41) + a14 * (a21 * a43 - a23 *  a41)) / det;
        inverse.a33 =  (a11 * (a22 * a44 - a24 * a42) - a12 * (a21 * a44 - a24 * a41) + a14 * (a21 * a42 - a22 *  a41)) / det;
        inverse.a43 = -(a11 * (a22 * a43 - a23 * a42) - a12 * (a21 * a43 - a23 * a41) + a13 * (a21 * a42 - a22 *  a41)) / det;

        inverse.a14 = -(a12 * (a23 * a34 - a24 * a33) - a13 * (a22 * a34 - a24 * a32) + a14 * (a22 * a33 - a23 *  a32)) / det;
        inverse.a24 =  (a11 * (a23 * a34 - a24 * a33) - a13 * (a21 * a34 - a24 * a31) + a14 * (a21 * a33 - a23 *  a31)) / det;
        inverse.a34 = -(a11 * (a22 * a34 - a24 * a32) - a12 * (a21 * a34 - a24 * a31) + a14 * (a21 * a32 - a22 *  a31)) / det;
        inverse.a44 =  (a11 * (a22 * a33 - a23 * a32) - a12 * (a21 * a33 - a23 * a31) + a13 * (a21 * a32 - a22 *  a31)) / det;
	}
	return inverse;
}

inline void engine::Matrix4::SetTranslation(f32 x, f32 y, f32 z){
	a41 = x; 
	a42 = y; 
	a43 = z;
}

inline void engine::Matrix4::SetTranslation(const Vector3F &V){
	a41 = V.x; 
	a42 = V.y; 
	a43 = V.z;
}

inline void engine::Matrix4::SetScale(f32 x, f32 y, f32 z){
	a11 = x; 
	a22 = y; 
	a33 = z;
}

inline void engine::Matrix4::SetScale(const Vector3F &V){
	a11 = V.x; 
	a22 = V.y; 
	a33 = V.z;
}

inline void engine::Matrix4::SetScale(f32 xyz){
	SetScale(xyz, xyz, xyz);
}

inline void engine::Matrix4::SetRotationX(f32 Angle){
	f32 Sin = std::sin(Angle);
	f32 Cos = std::cos(Angle);

	a11= 1.f;a12= 0.f; a13= 0.f; 
	a21= 0.f;a22= Cos; a23= -Sin; 
	a31= 0.f;a32= Sin; a33= Cos; 
}

inline void engine::Matrix4::SetRotationY(f32 Angle){
	f32 Sin =std::sin(Angle);
	f32 Cos = std::cos(Angle);

	a11= Cos;a12= 0.f; a13= Sin; 
	a21= 0.f;a22= 1.f; a23= 0.f; 
	a31= -Sin;a32= 0.f; a33= Cos; 
}

inline void engine::Matrix4::SetRotationZ(f32 Angle){
	f32 Sin = std::sin(Angle);
	f32 Cos = std::cos(Angle);

	a11= Cos;a12= -Sin; a13= 0.f; 
	a21= Sin;a22= Cos; a23= 0.f; 
	a31= 0.f;a32= 0.f; a33= 1.f; 
}

inline void engine::Matrix4::SetRotationX(f32 Angle, const Vector3F &Axis){
	Matrix4 Tr1, Tr2, Rot;

	Tr1.SetTranslation(Axis.x, Axis.y, Axis.z);
	Tr2.SetTranslation(-Axis.x, -Axis.y, -Axis.z);
	Rot.SetRotationX(Angle);

	*this = Tr1 * Rot * Tr2;
}

inline void engine::Matrix4::SetRotationY(f32 Angle, const Vector3F &Axis){
	Matrix4 Tr1, Tr2, Rot;

	Tr1.SetTranslation(Axis.x, Axis.y, Axis.z);
	Tr2.SetTranslation(-Axis.x, -Axis.y, -Axis.z);
	Rot.SetRotationY(Angle);

	*this = Tr1 * Rot * Tr2;
}

inline void engine::Matrix4::SetRotationZ(f32 Angle, const Vector3F &Axis){
	Matrix4 Tr1, Tr2, Rot;

	Tr1.SetTranslation(Axis.x, Axis.y, Axis.z);
	Tr2.SetTranslation(-Axis.x, -Axis.y, -Axis.z);
	Rot.SetRotationZ(Angle);

	*this = Tr1 * Rot * Tr2;
}

inline void engine::Matrix4::Translate(const Vector3F &pVector){
	a41 += pVector.x;
	a42 += pVector.y;
	a43 += pVector.z;
}

inline void engine::Matrix4::Scale(const Vector3F &pVector){
	a11 *= pVector.x;
	a22 *= pVector.y;
	a33 *= pVector.z;
}

inline void engine::Matrix4::Scale(f32 pFactor){
	a11 *= pFactor;
	a22 *= pFactor;
	a33 *= pFactor;
}

inline Vector3F engine::Matrix4::GetTranslation()const{
	return Vector3F(a14, a24, a34);
}

inline Vector3F engine::Matrix4::GetScale() const{
	return Vector3F(Math::Sqrt(a11*a11+a12*a12+a13*a13), Math::Sqrt(a21*a21+a22*a22+a23*a23), Math::Sqrt(a31*a31+a32*a32+a33*a33));
}

inline Vector3F engine::Matrix4::Transform(const Vector3F &V, f32 w) const{
	return Vector3F(a11 * V.x + a12 * V.y + a13 * V.z + a14 * w,
								  a21 * V.x + a22 * V.y + a23 * V.z + a24 * w,
								  a31 * V.x + a31 * V.y + a33 * V.z + a34 * w);
}

inline void engine::Matrix4::WorldMatrix(const Vector3F &Translation, const Vector3F &Rotation){
	Matrix4 Temp;
	Matrix4 Rot;

	SetTranslation(Translation);

	if(Rotation.x || Rotation.y ||Rotation.z){
		Temp.SetRotationX(Rotation.x);
		Rot *= Temp;
		Temp.SetRotationY(Rotation.y);
		Rot *= Temp;
		Temp.SetRotationZ(Rotation.z);
		Rot *= Temp;

		(*this) = Rot * (*this);
	}
}


inline Matrix4 engine::Matrix4::operator -() const
{
    return Matrix4(-a11, -a12, -a13, -a14,
                    -a21, -a22, -a23, -a24,
                    -a31, -a32, -a33, -a34,
                    -a41, -a42, -a43, -a44);
}

inline Matrix4 engine::Matrix4::operator +(const Matrix4& m) const
{
    return Matrix4(a11 + m.a11, a12 + m.a12, a13 + m.a13, a14 + m.a14,
                    a21 + m.a21, a22 + m.a22, a23 + m.a23, a24 + m.a24,
                    a31 + m.a31, a32 + m.a32, a33 + m.a33, a34 + m.a34,
                    a41 + m.a41, a42 + m.a42, a43 + m.a43, a44 + m.a44);
}

inline Matrix4 engine::Matrix4::operator -(const Matrix4& m) const
{
    return Matrix4(a11 - m.a11, a12 - m.a12, a13 - m.a13, a14 - m.a14,
                    a21 - m.a21, a22 - m.a22, a23 - m.a23, a24 - m.a24,
                    a31 - m.a31, a32 - m.a32, a33 - m.a33, a34 - m.a34,
                    a41 - m.a41, a42 - m.a42, a43 - m.a43, a44 - m.a44);
}

inline const Matrix4& engine::Matrix4::operator +=(const Matrix4& m)
{
    a11 += m.a11; a12 += m.a12; a13 += m.a13; a14 += m.a14;
    a21 += m.a21; a22 += m.a22; a23 += m.a23; a24 += m.a24;
    a31 += m.a31; a32 += m.a32; a33 += m.a33; a34 += m.a34;
    a41 += m.a41; a42 += m.a42; a43 += m.a43; a44 += m.a44;

    return *this;
}

inline const Matrix4& engine::Matrix4::operator -=(const Matrix4& m)
{
    a11 -= m.a11; a12 -= m.a12; a13 -= m.a13; a14 -= m.a14;
    a21 -= m.a21; a22 -= m.a22; a23 -= m.a23; a24 -= m.a24;
    a31 -= m.a31; a32 -= m.a32; a33 -= m.a33; a34 -= m.a34;
    a41 -= m.a41; a42 -= m.a42; a43 -= m.a43; a44 -= m.a44;

    return *this;
}

inline Matrix4 engine::Matrix4::operator*(const Matrix4 &m) const{
	return Matrix4(a11 * m.a11 + a12 * m.a21 + a13 * m.a31 + a14 * m.a41,
								a11 * m.a12 + a12 * m.a22 + a13 * m.a32 + a14 * m.a42,
								a11 * m.a13 + a12 * m.a23 + a13 * m.a33 + a14 * m.a43,
								a11 * m.a14 + a12 * m.a24 + a13 * m.a34 + a14 * m.a44,

								a21 * m.a11 + a22 * m.a21 + a23 * m.a31 + a24 * m.a41,
								a21 * m.a12 + a22 * m.a22 + a23 * m.a32 + a24 * m.a42,
								a21 * m.a13 + a22 * m.a23 + a23 * m.a33 + a24 * m.a43,
								a21 * m.a14 + a22 * m.a24 + a23 * m.a34 + a24 * m.a44,

								a31 * m.a11 + a32 * m.a21 + a33 * m.a31 + a34 * m.a41,
								a31 * m.a12 + a32 * m.a22 + a33 * m.a32 + a34 * m.a42,
								a31 * m.a13 + a32 * m.a23 + a33 * m.a33 + a34 * m.a43,
								a31 * m.a14 + a32 * m.a24 + a33 * m.a34 + a34 * m.a44,

								a41 * m.a11 + a42 * m.a21 + a43 * m.a31 + a44 * m.a41,
								a41 * m.a12 + a42 * m.a22 + a43 * m.a32 + a44 * m.a42,
								a41 * m.a13 + a42 * m.a23 + a43 * m.a33 + a44 * m.a43,
								a41 * m.a14 + a42 * m.a24 + a43 * m.a34 + a44 * m.a44);
}

inline const Matrix4& engine::Matrix4::operator *=(const Matrix4& m)
{
    *this = *this * m;

    return *this;
}

inline const Matrix4& engine::Matrix4::operator *=(f32 t)
{
    a11 *= t; a12 *= t; a13 *= t; a14 *= t;
    a21 *= t; a22 *= t; a23 *= t; a24 *= t;
    a31 *= t; a32 *= t; a33 *= t; a34 *= t;
    a41 *= t; a42 *= t; a43 *= t; a44 *= t;

    return *this;
}

inline const Matrix4& engine::Matrix4::operator /=(f32 t)
{
    a11 /= t; a12 /= t; a13 /= t; a14 /= t;
    a21 /= t; a22 /= t; a23 /= t; a24 /= t;
    a31 /= t; a32 /= t; a33 /= t; a34 /= t;
    a41 /= t; a42 /= t; a43 /= t; a44 /= t;

    return *this;
}

inline bool engine::Matrix4::operator ==(const Matrix4& m) const
{
    return (Math::IsEqual(a11, m.a11) && Math::IsEqual(a12, m.a12) &&
            Math::IsEqual(a13, m.a13) && Math::IsEqual(a14, m.a14) &&
            Math::IsEqual(a21, m.a21) && Math::IsEqual(a22, m.a22) &&
            Math::IsEqual(a23, m.a23) && Math::IsEqual(a24, m.a24) &&
            Math::IsEqual(a31, m.a31) && Math::IsEqual(a32, m.a32) &&
            Math::IsEqual(a33, m.a33) && Math::IsEqual(a34, m.a34) &&
            Math::IsEqual(a41, m.a41) && Math::IsEqual(a42, m.a42) &&
            Math::IsEqual(a43, m.a43) && Math::IsEqual(a44, m.a44));
}

inline bool engine::Matrix4::operator !=(const Matrix4& m) const
{
    return !(*this == m);
}

inline f32& engine::Matrix4::operator ()(std::size_t i, std::size_t j)
{
    return operator f32*()[i * 4 + j];
}

inline const f32& engine::Matrix4::operator ()(std::size_t i, std::size_t j) const
{
	return operator const f32*()[i * 4 + j];
}

inline engine::Matrix4::operator const f32*() const
{
    return &a11;
}

inline engine::Matrix4::operator f32*()
{
    return &a11;
}

inline engine::Matrix4 operator *(const Matrix4& m, f32 t)
{
    return Matrix4(m.a11 * t, m.a12 * t, m.a13 * t, m.a14 * t,
								m.a21 * t, m.a22 * t, m.a23 * t, m.a24 * t,
								m.a31 * t, m.a32 * t, m.a33 * t, m.a34 * t,
								m.a41 * t, m.a42 * t, m.a43 * t, m.a44 * t);
}

inline engine::Matrix4 operator *(f32 t, const Matrix4& m)
{
    return m * t;
}

inline engine::Matrix4 operator /(const Matrix4& m, f32 t)
{
    return Matrix4(m.a11 / t, m.a12 / t, m.a13 / t, m.a14 / t,
								m.a21 / t, m.a22 / t, m.a23 / t, m.a24 / t,
								m.a31 / t, m.a32 / t, m.a33 / t, m.a34 / t,
								m.a41 / t, m.a42 / t, m.a43 / t, m.a44 / t);
}


inline std::istream& operator >>(std::istream& iss, Matrix4 &m){
	iss >> m.a11 >> m.a12 >> m.a13 >> m.a14;
	iss >> m.a21 >> m.a22 >> m.a23 >> m.a24;
	iss >> m.a31 >> m.a32 >> m.a33 >> m.a34;
	iss >> m.a41 >> m.a42 >> m.a43 >> m.a44;
	return iss;
}

inline std::ostream& operator <<(std::ostream& oss, const Matrix4 &m){
	oss << m.a11 << " " << m.a12 << " " << m.a13 << " " << m.a14 << std::endl;
	oss << m.a21 << " " << m.a22 << " " << m.a23 << " " << m.a24 << std::endl;
	oss << m.a31 << " " << m.a32 << " " << m.a33 << " " << m.a34 << std::endl;
	oss << m.a41 << " " << m.a42 << " " << m.a43 << " " << m.a44 << std::endl;
	return oss;
}

inline void engine::Matrix4::OrthoOffCenter(f32 Left, f32 Top, f32 Right, f32 Bottom){
	a11 = 2 / (Right - Left);					a12 = 0.f;														a13 = 0.f;		a14 = 0.f;
	a21 = 0.f;											a22 = 2 / (Top - Bottom);							a23 = 0.f;		a24 = 0.f;
	a31 = 0.f;											a32 = 0.f;														a33 = 1.f;		a34 = 0.f;
	a41 = (1+Right)/(1-Right);				a42 = (Top + Bottom) / (Bottom - Top);	a43 = 0.f;		a44 = 1.f;
}

inline void engine::Matrix4::PerspectiveFOV(f32 FOV, f32 Ratio, f32 Near, f32 Far){
	f32 height = 1.f / Math::Tan(FOV/ 2.f);
	f32 width = height / Ratio;
	f32 NearFarCoeff = Far / (Near - Far);

	a11 = width;  a12 = 0.f;		 a13 = 0.f;									a14 = 0.f;
	a21 = 0.f;		a22 = height;  a23 = 0.f;									a24 = 0.f;
	a31 = 0.f;		a32 = 0.f;		 a33 = NearFarCoeff;				a34 = -1.f;
	a41 = 0.f;		a42 = 0.f;		 a43 = Near * NearFarCoeff;	 a44 = 0.f;
}

inline void engine::Matrix4::LookAt(const Vector3F &From, const Vector3F &To, const Vector3F &Up){
	Vector3F zaxis = From - To;
	zaxis.Normalize();
	Vector3F xaxis = Cross(Up, zaxis);
	xaxis.Normalize();
	Vector3F yaxis = Cross(zaxis, xaxis);

	a11 = xaxis.x;								a12 = yaxis.x;						  a13 = zaxis.x;							a14 = 0.f;
    a21 = xaxis.y;								a22 = yaxis.y;						  a23 = zaxis.y;							a24 = 0.f;
    a31 = xaxis.z;								a32 = yaxis.z;						  a33 = zaxis.z;							a34 = 0.f;
    a41 =  -Dot(xaxis, From);			a42 = -Dot(yaxis, From);    a43 = -Dot(zaxis, From);			a44 = 1.0f;
}

