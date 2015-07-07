inline engine::Quaternion::Quaternion(f32 X, f32 Y, f32 Z, f32 W) : x(X), y(Y), z(Z), w(W){
}

inline engine::Quaternion::Quaternion(const Matrix4 &mat){
	FromMatrix(mat);
}

inline engine::Quaternion::Quaternion(const Vector3F &Axis, f32 Angle){
	FromAxisAngle(Axis, Angle);
}

inline Quaternion engine::Quaternion::Conjugate() const{
	return Quaternion(-x, -y, -z, w);
}

inline void engine::Quaternion::Identity(){
	x = y = z = 0.f;
	w = 1.f;
}

inline void engine::Quaternion::Normalize(){
	f32 norme = x * x + y * y + z * z + w * w;

	if(norme != 0.f && (Math::Abs(norme) - 1.f) > Math::Epsilon){
		norme = Math::Sqrt(norme);
		x /= norme;
		y /= norme;
		z /= norme;
		w /= norme;
	}
}

inline void engine::Quaternion::FromEulerAngle(f32 X, f32 Y, f32 Z){
	Quaternion Qx(Math::Cos(X/2), Math::Sin(X/2), 0, 0);
    Quaternion Qy(Math::Cos(Y/2), 0, Math::Sin(Y/2), 0);
    Quaternion Qz(Math::Cos(Z/2), 0, 0, Math::Sin(Z/2));

	*this = Qx * Qy * Qz;
}

inline void engine::Quaternion::FromMatrix(const Matrix4 &mat){
	f32 trace = mat(0, 0) + mat(1, 1) + mat(2, 2) + 1;

	if(trace > 0){
		f32 s = 0.5f / Math::Sqrt(trace);
		x = (mat(2,1) - mat(1,2)) * s;
		y = (mat(0,2) - mat(2,0)) * s;
		z = (mat(1,0) - mat(0,1)) * s;
		w = 0.25f / s;
	}else{
		if (mat(0, 0) > mat(1, 1) && (mat(0, 0) > mat(2, 2))){
            f32 s = Math::Sqrt(1 + mat(0, 0) - mat(1, 1) - mat(2, 2)) * 2;
            x = 0.5f / s;
            y = (mat(0, 1) + mat(1, 0)) / s;
            z = (mat(0, 2) + mat(2, 0)) / s;
            w = (mat(1, 2) + mat(2, 1)) / s;
        } else if (mat(1, 1) > mat(2, 2)){
            f32 s = Math::Sqrt(1 - mat(0, 0) + mat(1, 1) - mat(2, 2)) * 2;
            x = (mat(0, 1) + mat(1, 0)) / s;
            y = 0.5f / s;
            z = (mat(1, 2) + mat(2, 1)) / s;
            w = (mat(0, 2) + mat(2, 0)) / s;
        } else{
            f32 s = Math::Sqrt(1 - mat(0, 0) - mat(1, 1) + mat(2, 2)) * 2;
            x = (mat(0, 2) + mat(2, 0)) / s;
            y = (mat(1, 2) + mat(2, 1)) / s;
            z = 0.5f / s;
            w = (mat(0, 1) + mat(1, 0)) / s;
        }
	}
}

inline Matrix4 engine::Quaternion::ToMatrix() const{
	f32 x2 = x * x;
	f32 y2 = y * y;
	f32 z2 = z * z;
	f32 xy = x * y;
	f32 wz = w * z;
	f32 xz = x * z;
	f32 wy = w * y;
	f32 yz = y * z;
	f32 wx = w * x;

	return Matrix4(	1 - 2*(y2+z2)	, 2 * (xy - wz)		, 2 * (xz + wy)		, 0,
					2 * (xy + wz)	, 1 - 2*(x2 + z2)	, 2*(yz - wx)		, 0,
					2 * (xz - wy)	, 2 * (yz + wx)		, 1 - 2*(x2 + y2)	, 0,
					0				, 0					, 0					, 1 );	
}

inline void engine::Quaternion::FromAxisAngle(const Vector3F &Axis, f32 Angle){
	f32 Cos = Math::Cos(Angle / 2);
	f32 Sin = Math::Sin(Angle / 2);

	x = Axis.x * Sin;
	y = Axis.y * Sin;
	z = Axis.z * Sin;
	w = Cos;

	Normalize();
}

inline void engine::Quaternion::ToAxisAngle(Vector3F &Axis, f32 &Angle) const{
	if(w == 1){
		Angle = 0;
		Axis.Set(0,1,0);		// Axis arbitraire (pas de rotation anyway)
	}else{
		Angle = Math::ACos(w) * 2;

		f32 norme = Math::Sqrt(1 - w * w);

		Axis.Set(x,y,z);
		Axis /= norme;
	}
}

inline Quaternion engine::Quaternion::operator*(const Quaternion &quat) const{
	return Quaternion(	w * quat.x + x * quat.w + y * quat.z - z * quat.y,
						w * quat.y + y * quat.w + z * quat.x - x * quat.z,
						w * quat.z + z * quat.w + x * quat.y - y * quat.x, 
						w * quat.w - x * quat.x - y * quat.y - z * quat.z);
}

inline const Quaternion& engine::Quaternion::operator*=(const Quaternion &quat){
	*this = *this * quat;

	return *this;
}

inline Vector3F engine::Quaternion::operator*(const Vector3F &pVec) const{
	Vector3F vec(pVec);
	vec.Normalize();

	Quaternion vectorQuat(vec.x, vec.y, vec.z, 0.f), resultQuat;

	resultQuat = vectorQuat * Conjugate();
	resultQuat = *this * resultQuat;

	return Vector3F(resultQuat.x, resultQuat.y, resultQuat.z);
}

inline Quaternion engine::Quaternion::operator-() const{
	Quaternion neg;
	neg.x = -x;
	neg.y = -y;
	neg.z = -z;
	neg.w = -w;
	return neg;
}

inline std::istream & operator>> (std::istream &iss, Quaternion &quat){
	return iss >> quat.x >> quat.y >> quat.z >> quat.w;
}

inline std::ostream & operator<< (std::ostream &oss, const Quaternion &quat){
	return oss << quat.x << " " << quat.y << " " << quat.z << " " << quat.w;
}