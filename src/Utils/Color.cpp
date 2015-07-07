#include "Color.hpp"

namespace engine {
	const Color Color::Black(0.f,0.f,0.f,1.f);
	const Color Color::White(1.f,1.f,1.f,1.f);
	const Color Color::Red(1.f,0.f,0.f,1.f);
	const Color Color::Green(0.f,1.f,0.f,1.f);
	const Color Color::Blue(0.f,0.f,1.f,1.f);
	const Color Color::Magenta(1.f,0.f,1.f,1.f);
	const Color Color::Cyan(0.f,1.f,1.f,1.f);
	const Color Color::Yellow(1.f,1.f,0.f,1.f);
	const Color Color::Orange(1.f,0.5f,0.f,1.f); 
	const Color Color::Grey(0.5f,0.5f,0.5f,1.f);

	Color::Color(f32 R, f32 G, f32 B, f32 A) : r(R), g(G), b(B), a(A){
	}

	void Color::RGB(float pTab[]) const{
		pTab[0] = r;
		pTab[1] = g;
		pTab[2] = b;
	}

	void Color::RGBA(float pTab[]) const{
		pTab[0] = r;
		pTab[1] = g;
		pTab[2] = b;
		pTab[3] = a;
	}

	void Color::RGB(f32 pR, f32 pG, f32 pB){
		r = pR;
		g = pG;
		b = pB;
	}

	void Color::RGBA(f32 pR, f32 pG, f32 pB, f32 pA){
		r = pR;
		g = pG;
		b = pB;
		a = pA;
	}

	Color To00xColor(const sf::Color &pColor){
		return Color(pColor.r / 255.f, pColor.g / 255.f, pColor.b / 255.f, pColor.a / 255.f);
	}
	
	sf::Color ToSFMLColor(const Color &pColor){
		return sf::Color(static_cast<u8>(pColor.R() * 255), 
						 static_cast<u8>(pColor.G() * 255), 
						 static_cast<u8>(pColor.B() * 255), 
						 static_cast<u8>(pColor.A() * 255));
	}
}
