#ifndef STRING_HPP
#define STRING_HPP

#include <sstream>
#include <vector>
#include <algorithm>
#include <cctype>
#include "StringConverter.hpp"

namespace engine {

	/// \brief Ease of use class for string managment, allowing String creation from multiple types
	class OOXAPI String{
	public:
		/// \brief Default Ctor
		String(){ mString << "";}
		
		/// \brief Copy Ctor
		String(const String &s){ mString << s.str(); }

		/// \brief Ctor from any data type
		template<typename T> String(const T& ppValue);

		/// \brief Operators allowing concatenation of different data types
		template<typename T> String& operator+(const T &ppValue);
		template<typename T> String& operator+=(const T &ppValue);

		/// \brief Stream operator (maybe useless with above one)
		friend std::ostream& operator<<(std::ostream& oss, const String &pStr);

		/// \brief Cast operator in std::string
		operator std::string() const;
		
		/// \brief Explicit Cast operator in std::string
		std::string str() const;

		/// \brief Comparison operators
		bool operator==(const std::string &pStr) const;
		bool operator !=(const std::string &pStr) const;

		/// \brief Affectation operators
		void operator=(const std::string &pStr);
		void operator=(const String &pStr);

		/// \brief Returns the oss for string operations
		std::ostringstream& ostr();

		/// \brief Returns the String length
		size_t size() const;

		/// \brief Returns true if the String is empty
		bool Empty() const;

		/// \brief Returns true if the String is a commentary (begins with "//")
		bool IsCommentary() const;

	protected:
		std::ostringstream mString;
	};

	/// \brief Vector of strings
	typedef std::vector<std::string> StringVector;

	
	
	/// \brief String utility functions
	class OOXAPI StringUtils{
	public:
		/// \brief Splits a string according to different separators
		/// \param pIn       : input string to be splitted
		/// \param pSep      : different char separators
		/// \param pMaxSplit : max splits operation. 0 means infinite
		static StringVector SplitString(const std::string &pIn, const std::string &pSep = "\t\n ", u32 pMaxSplit = 0);

		/// \brief Returns the lower case input string
		static std::string ToLower(const std::string &pStr);

		/// \brief Returns the upper case input string
		static std::string ToUpper(const std::string &pStr);

		/// \brief Returns only the extension of a complete file name
		static std::string GetExtension(const std::string &pFileName);

		/// \brief Returns only the file name without its extension
		static std::string GetFileName(const std::string &pFileName);

		/// \brief Check if a string begins by another
		/// \param pStr : string to check
		/// \param pStart : substring used for comparison
		/// \param pLowerCase : true for a case insensitive comparison
		static bool StartsWith(const std::string &pStr, const std::string &pStart, bool pLowerCase = true);
	};

	#include "String.inl"
}
#endif 
