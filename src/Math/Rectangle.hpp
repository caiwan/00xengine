#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "Vector2.hpp"

namespace engine {
	// Three possible results of an Intersection
	enum IntersectionResult{
		INTR_In,		
		INTR_Out,		
		INTR_Intersect
	};

	class OOXAPI Rectangle{
	public:
		// Ctor from 4 boundaries
		Rectangle(s32 top, s32 left, s32 width, s32 height);

		// Ctor from Top-Left and Bottom-Right Vectors
		Rectangle(const Vector2I &topLeft = Vector2I(0,0), const Vector2I &size = Vector2I(0,0));

		// Initialize the rectangle from 4 boundaries
		void Set(s32 top, s32 left, s32 width, s32 height);

		// Getters

			s32 Left() const;
			s32 Top() const;
			s32 Right() const;
			s32 Bottom() const;

			s32 Width() const;
			s32 Height() const;

		// Returns the rectangle size (End - Origin)
		Vector2I Size() const;

		// Returns the intersection type between a point and this rectangle
		IntersectionResult Intersects(const Vector2I &Point) const;
		
		// Returns the intersection type between another and this rectangle
		IntersectionResult Intersects(const Rectangle &Rect) const;

		bool operator==(const Rectangle &Rect) const;
		bool operator!=(const Rectangle &Rect) const;
		
		friend std::istream& operator>> (std::istream &iss, Rectangle &Rect);
		friend std::ostream& operator<< (std::ostream &oss, const Rectangle &Rect);

		// Data
		Vector2I Origin;
		Vector2I End;
	};
}
#endif
