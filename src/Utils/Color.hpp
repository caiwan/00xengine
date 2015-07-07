#ifndef COLOR_HPP
#define COLOR_HPP

#include "Shared.hpp"

namespace engine {
	/// \brief Color class with RGBA Components
	class OOXAPI Color{
	public:
		/// \brief Ctor, color from RGBA
		Color(f32 R = 0.f, f32 G = 0.f, f32 B = 0.f, f32 A = 1.f);
			
		/// \brief Returns the RGB color components in a float array
		void RGB(float pTab[]) const;
		
		/// \brief Returns the RGBA color components in a float array
		void RGBA(float pTab[]) const;

		f32 R() const{ return r; }
		f32 G() const{ return g; }
		f32 B() const{ return b; }
		f32 A() const{ return a; }

		/// \brief Returns a pointer on r
		operator f32*() { return &r; }

		/// \brief Sets the RGB color components
		void RGB(f32 pR, f32 pG, f32 pB);

		/// \brief Sets the RGBA color components
		void RGBA(f32 pR, f32 pG, f32 pB, f32 pA);

		void R(f32 pR) { r = pR; }
		void G(f32 pG) { g = pG; }
		void B(f32 pB) { b = pB; }
		void A(f32 pA) { a = pA; }

		/// \brief Common Colors
			static const Color Black;	
			static const Color White;	
			static const Color Red;	
			static const Color Green;	
			static const Color Blue;	
			static const Color Magenta;	
			static const Color Cyan;	
			static const Color Yellow;	
			static const Color Orange;	
			static const Color Grey;	
		
	private:
		f32 r, g, b, a;
	};

	/// \brief SFML to 00xEngine conversion
	Color To00xColor(const sf::Color &pColor);
	
	/// \brief 00xEngine to SFML conversion
	sf::Color ToSFMLColor(const Color &pColor);
}
#endif
