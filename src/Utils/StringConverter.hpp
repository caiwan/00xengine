#ifndef STRINGCONVERTER_HPP
#define STRINGCONVERTER_HPP

#include "Shared.hpp"
#include "Math/Vector2.hpp"
#include "Math/Vector3.hpp"

namespace engine {
	class String;
	class Color;

	/// \brief String Converter (types -> String & String -> types)
	class OOXAPI StringConverter{
	public:
		/// \brief STRING TO FLOAT
		static f32 ToFloat(const std::string &pVal);

		/// \brief STRING TO INT
		static s32 ToInt(const std::string &pVal);

		/// \brief STRING TO UNSIGNED
		static u32 ToUnsigned(const std::string &pVal);

		/// \brief STRING TO BOOL
		static bool ToBool(const std::string &pVal);

		/// \brief STRING to VECTOR2
		static Vector2F ToVector2(const std::string &pVal);

		/// \brief STRING to VECTOR3
		static Vector3F ToVector3(const std::string &pVal);

		/// \brief STRING to COLOR
		static Color ToColor(const std::string &pVal);

		/// \brief FLOAT to STRING
		static String ToString(f32 pVal, u16 pPrecision = 6);

		/// \brief DOUBLE to STRING
		static String ToString(f64 pVal, u16 pPrecision = 6);

		/// \brief LINT to STRING
		static String ToString(s32 pVal);

		/// \brief LUNSIGNED to STRING
		static String ToString(u32 pVal);

		/// \brief SHORT to STRING
		static String ToString(s16 pVal);

		/// \brief UNSIGNED to STRING
		static String ToString(u16 pVal);
	};

}
#endif
