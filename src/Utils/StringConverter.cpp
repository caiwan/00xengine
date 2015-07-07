#include "StringConverter.hpp"
#include "String.hpp"
#include "Color.hpp"
#include "Debug/New.hpp"

namespace engine {
		// STRING TO FLOAT
		f32 StringConverter::ToFloat(const std::string &pVal){
			std::istringstream str(pVal);
			f32 ret = 0;
			str >> ret;
			return ret;
		}

		// STRING TO INT
		s32 StringConverter::ToInt(const std::string &pVal){
			std::istringstream str(pVal);
			s32 ret = 0;
			str >> ret;
			return ret;
		}

		// STRING TO UNSIGNED
		u32 StringConverter::ToUnsigned(const std::string &pVal){
			std::istringstream str(pVal);
			u32 ret = 0;
			str >> ret;
			return ret;
		}

		// STRING TO BOOL
		bool StringConverter::ToBool(const std::string &pVal){
			return StringUtils::StartsWith(pVal, "true") || StringUtils::StartsWith(pVal, "1") || StringUtils::StartsWith(pVal, "yes");
		}

		// STRING StringConverter::to VECTOR2
		Vector2F StringConverter::ToVector2(const std::string &pVal){
			Vector2F ret;
			StringVector vec = StringUtils::SplitString(pVal);
			if(vec.size() != 2)
				ret = Vector2F::ZERO;
			else
				ret = Vector2F(ToFloat(vec[0]), ToFloat(vec[1]));
			return ret;
		}

		// STRING StringConverter::to VECTOR3
		Vector3F StringConverter::ToVector3(const std::string &pVal){
			Vector3F ret;
			StringVector vec = StringUtils::SplitString(pVal);
			if(vec.size() != 3)
				ret = Vector3F::ZERO;
			else
				ret = Vector3F(ToFloat(vec[0]), ToFloat(vec[1]), ToFloat(vec[2]));
			return ret;
		}

		// STRING StringConverter::to COLOR
		Color StringConverter::ToColor(const std::string &pVal){
			Color ret;
			StringVector vec = StringUtils::SplitString(pVal, ",");
			if(vec[0].find_first_of(".")){
				// Float Color
				if(vec.size() == 4)
					ret = Color(ToFloat(vec[0]),ToFloat(vec[1]),ToFloat(vec[2]),ToFloat(vec[3]));
				else if(vec.size() == 3)
					ret = Color(ToFloat(vec[0]),ToFloat(vec[1]),ToFloat(vec[2]), 1.f);
				else
					ret = Color::Black;
			}else{
				// Unsigned Color
				if(vec.size() == 4)
					ret = Color(ToFloat(vec[0]) / 255.f,ToFloat(vec[1]) / 255.f,ToFloat(vec[2]) / 255.f,ToFloat(vec[3]) / 255.f);
				else if(vec.size() == 3)
					ret = Color(ToFloat(vec[0]) / 255.f,ToFloat(vec[1]) / 255.f,ToFloat(vec[2]) / 255.f, 1.f);
				else
					ret = Color::Black;
			}
			return ret;
		}

		// FLOAT StringConverter::to STRING
		String StringConverter::ToString(f32 pVal, u16 pPrecision){
			std::ostringstream oss;
			oss.precision(pPrecision);
			oss << pVal;
			return oss.str();
		}

		// DOUBLE StringConverter::to STRING
		String StringConverter::ToString(f64 pVal, u16 pPrecision){
			std::ostringstream oss;
			oss.precision(pPrecision);
			oss << pVal;
			return oss.str();
		}

		// LINT StringConverter::to STRING
		String StringConverter::ToString(s32 pVal){
			std::ostringstream oss;
			oss << pVal;
			return oss.str();
		}

		// LUNSIGNED StringConverter::to STRING
		String StringConverter::ToString(u32 pVal){
			std::ostringstream oss;
			oss << pVal;
			return oss.str();
		}

		// SHORT StringConverter::to STRING
		String StringConverter::ToString(s16 pVal){
			std::ostringstream oss;
			oss << pVal;
			return oss.str();
		}

		// UNSIGNED StringConverter::to STRING
		String StringConverter::ToString(u16 pVal){
			std::ostringstream oss;
			oss << pVal;
			return oss.str();
		}
}
