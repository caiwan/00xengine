
	template<class T>
	inline engine::Vector2<T>::Vector2(T X, T Y) : x(X), y(Y){
	}

	template<class T>
	inline void engine::Vector2<T>::Set(T X, T Y){
		x = X;
		y = Y;
	}

	template<class T>
	inline void engine::Vector2<T>::XY(T pTab[]) const{
		pTab[0] = x;
		pTab[1] = y;
	}

	template<class T>
	inline T engine::Vector2<T>::Norme() const{
		return Math::Sqrt(NormeSq());
	}

	template<class T>
	inline T engine::Vector2<T>::NormeSq() const{
		return x * x + y * y;
	}

	template<class T>
	inline void engine::Vector2<T>::Normalize(){
		T Norme = Norme();

		if(Math::Abs(Norme) > Math::Epsilon){	
			x /= Norme;
			y /= Norme;
		}
	}
	
	template<class T>
	inline Vector2<T> engine::Vector2<T>::operator-() const{
		return Vector2<T>(-x, -y);
	}

	template<class T>
	inline Vector2<T> engine::Vector2<T>::operator+(const Vector2<T> &V) const{
		return Vector2<T>(x + V.x, y + V.y);
	}

	template<class T>
	inline Vector2<T> engine::Vector2<T>::operator-(const Vector2<T> &V) const{
		return Vector2<T>(x - V.x, y - V.y);
	}

	template<class T>
	inline Vector2<T>& engine::Vector2<T>::operator+=(const Vector2<T> &V) const{
		x += V.x;
		y += V.y;

		return *this;
	}

	template<class T>
	inline Vector2<T>& engine::Vector2<T>::operator-=(const Vector2<T> &V) const{
		x -= V.x;
		y -= V.y;

		return *this;
	}

	template<class T>
	inline Vector2<T> engine::Vector2<T>::operator*(T t) const{
		return Vector2<T>(x*t, y*t);
	}

		template<class T>
	inline Vector2<T> engine::Vector2<T>::operator/(T t) const{
		return Vector2<T>(x/t, y/t);
	}

	template<class T>
	inline Vector2<T>& engine::Vector2<T>::operator*=(T t) const{
		x *= t;
		y *= t;

		return *this;
	}

	template<class T>
	inline Vector2<T>& engine::Vector2<T>::operator/=(T t) const{
		x /= t;
		y /= t;

		return *this;
	}

	template<class T>
	inline bool engine::Vector2<T>::operator==(const Vector2<T> &V) const{
		return ( (Math::Abs(float(x - V.x)) <= Math::Epsilon) &&
						(Math::Abs(float(y - V.y)) <= Math::Epsilon)      );
	}

	template<class T>
	inline bool engine::Vector2<T>::operator!=(const Vector2<T> &V) const{
		return !(*this == V);
	}

	template<class T>
	inline engine::Vector2<T>::operator T*(){
		return &x;
	}


	template<class T> 
	Vector2<T> operator* (const Vector2<T> &V, T t){
		return Vector2<T>(V.x * t, V.y * t);
	}

	template<class T> 
	Vector2<T> operator/ (const Vector2<T> &V, T t){
		return Vector2<T>(V.x / t, V.y / t);
	}

	template<class T> 
	Vector2<T> operator* (T t, const Vector2<T> &V){
		return V * t;
	}

	template<class T> 
	T Dot(const Vector2<T> &U, const Vector2<T> &V){
		return U.x * V.x + U.y * V.y;
	}

	template<class T> 
	std::istream& operator >>(std::istream& iss, Vector2<T> &V){
		return iss >> V.x >> V.y;
	}

	template<class T> 
	std::ostream& operator <<(std::ostream& oss, const Vector2<T> &V){
		return oss <<  V.x << " " << V.y;
	}

	template<class T>
	Vector2F To00xVector2F(const sf::Vector2<T> &pVec){
		return Vector2F(static_cast<f32>(pVec.x), static_cast<f32>(pVec.y));
	}

	template<class T>
	Vector2I To00xVector2I(const sf::Vector2<T> &pVec){
		return Vector2I(static_cast<s32>(pVec.x), static_cast<s32>(pVec.y));
	}
	
	template<class T> 
	sf::Vector2f ToSFMLVector2f(const Vector2<T> &pVec){
		return sf::Vector2f(static_cast<f32>(pVec.x), static_cast<f32>(pVec.y));
	}

	template<class T> 
	sf::Vector2i ToSFMLVector2i(const Vector2<T> &pVec){
		return sf::Vector2f(static_cast<s32>(pVec.x), static_cast<s32>(pVec.y));
	}
