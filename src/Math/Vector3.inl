
template<class T>
	inline engine::Vector3<T>::Vector3(T X, T Y, T Z) : x(X), y(Y), z(Z){
	}

	template<class T>
	inline void engine::Vector3<T>::Set(T X, T Y, T Z){
		x = X;
		y = Y;
		z = Z;
	}

	template<class T>
	inline void engine::Vector3<T>::XYZ(T pTab[]) const{
		pTab[0] = x;
		pTab[1] = y;
		pTab[2] = z;
	}

	template<class T>
	inline T engine::Vector3<T>::Norme() const{
		return Math::Sqrt(NormeSq());
	}

	template<class T>
	inline T engine::Vector3<T>::NormeSq() const{
		return x * x + y * y + z * z;
	}

	template<class T>
	inline void engine::Vector3<T>::Normalize(){
		T norme = Norme();

		// on s'assure que norme != 0
		if(Math::Abs(norme) > Math::Epsilon){		// Eviter le == non precis des floating points
			x /= norme;
			y /= norme;
			z /= norme;
		}
	}

	template<class T>
	inline void engine::Vector3<T>::ScaleFrom(const Vector3<T> &pCenter, f32 pScaleFactor){
		Vector3<T> axis = (*this) - pCenter;

		(*this) += axis * pScaleFactor;
	}
	
	template<class T>
	inline Vector3<T> engine::Vector3<T>::operator-() const{
		return Vector3<T>(-x, -y, -z);
	}

	template<class T>
	inline Vector3<T> engine::Vector3<T>::operator+(const Vector3<T> &V) const{
		return Vector3<T>(x + V.x, y + V.y, z + V.z);
	}

	template<class T>
	inline Vector3<T> engine::Vector3<T>::operator-(const Vector3<T> &V) const{
		return Vector3<T>(x - V.x, y - V.y, z - V.z);
	}

	template<class T>
	inline Vector3<T>& engine::Vector3<T>::operator+=(const Vector3<T> &V) {
		x += V.x;
		y += V.y;
		z += V.z;

		return *this;
	}

	template<class T>
	inline Vector3<T>& engine::Vector3<T>::operator-=(const Vector3<T> &V) {
		x -= V.x;
		y -= V.y;
		z -= V.z;

		return *this;
	}

	template<class T>
	inline Vector3<T> engine::Vector3<T>::operator*(T t) const{
		return Vector3<T>(x * t, y * t, z * t);
	}

		template<class T>
	inline Vector3<T> engine::Vector3<T>::operator/(T t) const{
		return Vector3<T>(x/t, y/t, z/t);
	}

	template<class T>
	inline Vector3<T>& engine::Vector3<T>::operator*=(T t){
		x *= t;
		y *= t;
		z *= t;

		return *this;
	}

	template<class T>
	inline Vector3<T>& engine::Vector3<T>::operator/=(T t){
		x /= t;
		y /= t;
		z /= t;

		return *this;
	}

	template<class T>
	inline bool engine::Vector3<T>::operator==(const Vector3<T> &V) const{
		return ( (Math::Abs(x - V.x) <= Math::Epsilon) &&
					    (Math::Abs(y - V.y) <= Math::Epsilon) &&
						(Math::Abs(z - V.z) <= Math::Epsilon)		 );
	}

	template<class T>
	inline bool engine::Vector3<T>::operator!=(const Vector3<T> &V) const{
		return !(*this == V);
	}

	template<class T>
	inline engine::Vector3<T>::operator T*(){
		return &x;
	}


	template<class T> 
	Vector3<T> operator* (const Vector3<T> &V, T t){
		return Vector3<T>(V.x * t, V.y * t, V.z * t);
	}

	template<class T> 
	Vector3<T> operator/ (const Vector3<T> &V, T t){
		return Vector3<T>(V.x / t, V.y / t, V.z / t);
	}

	template<class T> 
	Vector3<T> operator* (T t, const Vector3<T> &V){
		return V * t;
	}

	template<class T> 
	T Dot(const Vector3<T> &U, const Vector3<T> &V){
		return U.x * V.x + U.y * V.y + U.z * V.z;
	}

	template<class T>
	Vector3<T> Cross(const Vector3<T> &U, const Vector3<T> &V){
		return Vector3<T>( (U.y * V.z) - (V.y * U.z), (U.z * V.x) - (V.z * U.x), (U.x * V.y) - (V.x * U.y) );
	}

	template<class T> 
	std::istream& operator >>(std::istream& iss, Vector3<T> &V){
		return iss >> V.x >> V.y >> V.z;
	}

	template<class T> 
	std::ostream& operator <<(std::ostream& oss, const Vector3<T> &V){
		return oss <<  V.x << " " << V.y << " " << V.z;
	}
