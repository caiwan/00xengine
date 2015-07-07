#ifndef VECTOR2_HPP
#define VECTOR2_HPP

#include "Mathlib.hpp"

namespace engine {
	template<typename T>
	class Vector2{
	public:
		Vector2(T x = 0, T y = 0);

		// Sets vector components
		void Set(T x, T y);

		// Returns the vector components in an array
		void XY(T pTab[]) const;

		// Returns the vector length
		T Norme() const;

		// Returns the Squared Length (intern use for Norme())
		T NormeSq() const;

		// Normalize the vector
		void Normalize();

		// Returns the negate of the vector
		Vector2<T> operator- () const;

		// Binary operators
		Vector2<T> operator+ (const Vector2<T> &V) const;
		Vector2<T> operator- (const Vector2<T> &V) const;

		Vector2<T>& operator+= (const Vector2<T> &V) const;
		Vector2<T>& operator -= (const Vector2<T> &V) const;

		Vector2<T> operator*(T t) const;
		Vector2<T> operator/(T t) const;

		Vector2<T>& operator*= (T t) const;
		Vector2<T>& operator /= (T t) const;

		// Comparison operators
		bool operator==(const Vector2<T> &V) const;
		bool operator!=(const Vector2<T> &V) const;

		// Returns a pointer on x
		operator T*();

		// Common Zero Vector
		static const OOXAPI Vector2 ZERO;

		// Donnees
		T x;
		T y;
	};

	// Result of multiplication between a vector and a T
	template<class T> Vector2<T> operator* (const Vector2<T> &V, T t);

	// Result of division between a vector and a T
	template<class T> Vector2<T> operator/ (const Vector2<T> &V, T t);

	// Result of multiplication between a T and a vector
	template<class T> Vector2<T> operator* (T t, const Vector2<T> &V);

	// Dot product between two vector2
	template<class T> T Dot(const Vector2<T> &U, const Vector2<T> &V);

	// Stream ops
	template<class T> std::istream& operator >>(std::istream& iss, Vector2<T> &V);
	template<class T> std::ostream& operator <<(std::ostream& oss, const Vector2<T> &V);

	typedef Vector2<s32> Vector2I;
	typedef Vector2<f32> Vector2F;

	// Conversion between SFML and 00xEngine
	template<class T> Vector2F To00xVector2F(const sf::Vector2<T> &pVec);
	template<class T> Vector2I To00xVector2I(const sf::Vector2<T> &pVec);
	template<class T> sf::Vector2f ToSFMLVector2f(const Vector2<T> &pVec);
	template<class T> sf::Vector2i ToSFMLVector2i(const Vector2<T> &pVec);
	
	#include "Vector2.inl"
}
#endif
