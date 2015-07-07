#include "Rectangle.hpp"

namespace engine {
	Rectangle::Rectangle(s32 top, s32 left, s32 width, s32 height) : Origin(Vector2I(left, top)), End(Vector2I(left + width, top + height)){
	}

	Rectangle::Rectangle(const Vector2I &topLeft, const Vector2I &size) : Origin(topLeft), End(topLeft + size){
	}

	void Rectangle::Set(s32 top, s32 left, s32 width, s32 height){
		Origin = Vector2I(left, top);
		End = Vector2I(left + width, top + height);
	}

	s32 Rectangle::Left() const{
		return Origin.x;
	}

	s32 Rectangle::Top() const{
		return Origin.y;
	}

	s32 Rectangle::Right() const{
		return End.x;
	}

	s32 Rectangle::Bottom() const{
		return End.y;
	}

	s32 Rectangle::Width() const{
		return End.x - Origin.x;
	}

	s32 Rectangle::Height() const{
		return End.y - Origin.y;
	}

	Vector2I Rectangle::Size() const{
		return End - Origin;
	}

	IntersectionResult Rectangle::Intersects(const Vector2I &Point) const{
		if(Point.x >= Origin.x && Point.x <= End.x && Point.y >= Origin.y && Point.y <= End.y)
			return INTR_In;
		else
			return INTR_Out;
	}

	IntersectionResult Rectangle::Intersects(const Rectangle &Rect) const{
		// Creation du rectangle d'Intersection
		Vector2I newRectOrigin(Math::Max(Origin.x, Rect.Origin.x), Math::Max(Origin.y, Rect.Origin.y));
		Vector2I newRectEnd(Math::Min(End.x, Rect.End.x), Math::Min(End.y, Rect.End.y));
		Rectangle newRect(newRectOrigin, newRectEnd);

		if(newRectOrigin.x > newRectEnd.x || newRectOrigin.y > newRectEnd.y)	// Si le rectangle d'Intersection est a l'exterieur d'un des deux rectangles
			return INTR_Out;
		else if(newRect == *this || newRect == Rect)							// Si le rectangle d'Intersection est contenu dans un des deux rectangles
			return INTR_In;
		else																	// Sinon, une partie seulement est contenue, Intersection simple
			return INTR_Intersect;
	}

	bool Rectangle::operator== (const Rectangle &Rect) const{
		return ( Origin == Rect.Origin ) && ( End == Rect.End );
	}

	bool Rectangle::operator!= (const Rectangle &Rect) const{
		return !(*this == Rect);
	}

	std::istream& operator>>(std::istream& iss, Rectangle& Rect){
		return iss >> Rect.Origin >> Rect.End;
	}

	std::ostream& operator<<(std::ostream& oss, const Rectangle& Rect){
		return oss << Rect.Origin << " " << Rect.End;
	}
}
