	template<typename T>
	inline engine::String::String(const T &ppValue){
		mString << ppValue;
	}

	template<typename T>
	inline String& engine::String::operator +(const T &pValue){
		mString << pValue;

		return *this;
	}

	template<typename T>
	inline String& engine::String::operator+=(const T &pValue){
		return (*this + pValue);
	}

	inline std::ostream& operator<<(std::ostream& oss, const String &pStr){
		return oss << pStr.str();
	}
	
	inline void engine::String::operator=(const std::string &pStr){
		mString.str(pStr);
	}
	
	inline void engine::String::operator=(const String &pStr){
		mString.str(pStr);
	}

	inline engine::String::operator std::string() const{
		return mString.str();
	}

	inline bool engine::String::operator ==(const std::string &pStr) const{
		return this->str() == pStr;
	}

	inline bool engine::String::operator !=(const std::string &pStr) const{
		return !(*this == pStr);
	}

	inline std::string engine::String::str() const{
		return mString.str();
	}

	inline std::ostringstream& engine::String::ostr(){
		return mString;
	}

	inline size_t engine::String::size() const{
		return mString.str().size();
	}

	inline bool engine::String::Empty() const{
		return str().empty();
	}

	inline bool engine::String::IsCommentary() const{
		return str().substr(0,2) == "//";
	}

	inline StringVector engine::StringUtils::SplitString(const std::string &pIn, const std::string &pSep, u32 pMaxSplit){
		StringVector v;
		// pre allocation pour performance
		v.reserve(pMaxSplit ? pMaxSplit + 1 : 5); // 5 nbr max de mot le plus souvent
		u32 splitNbr = 0;
			
		// Parcourt de la chaine 
		size_t p1 = 0, p2;
		do{
			p2 = pIn.find_first_of(pSep, p1);
			if(p2 == p1)
				p1 = p2 + 1;
			else if( p2 == std::string::npos || (pMaxSplit && splitNbr == pMaxSplit)){
				v.push_back(pIn.substr(p1));
				break;
			}else{
				v.push_back(pIn.substr(p1, p2 - p1));
				p1 = p2 + 1;
			}

			p1 = pIn.find_first_not_of(pSep, p1);
			++splitNbr;
		} while(p2 != std::string::npos);
		
		return v;
	}

	inline std::string engine::StringUtils::ToLower(const std::string &pStr){
		std::string retStr(pStr.size(), ' ');
		s32 (*pf)(s32) = std::tolower;
		std::transform(pStr.begin(), pStr.end(), retStr.begin(), pf);
		return retStr;
	}

	inline std::string engine::StringUtils::ToUpper(const std::string &pStr){
		std::string retStr(pStr.size(), ' ');
		s32 (*pf)(s32) = std::toupper;
		std::transform(pStr.begin(), pStr.end(), retStr.begin(), pf);
		return retStr;
	}

	inline std::string engine::StringUtils::GetExtension(const std::string &pFileName){
		std::string::size_type Pos = pFileName.find_first_of(".");
		if( Pos != std::string::npos)
			return pFileName.substr( Pos+1, std::string::npos);
		return "";
	}

	inline std::string engine::StringUtils::GetFileName(const std::string &pFileName){
		std::string::size_type pos = pFileName.find_first_of(".");
		if(pos != std::string::npos)
			return pFileName.substr(0, pos);
		return "";
	}

	inline bool engine::StringUtils::StartsWith(const std::string &pStr, const std::string &pStart, bool pLowerCase){
		size_t strlen = pStr.length(), startlen = pStart.length();
		if(strlen < startlen || startlen == 0)
			return false;

		std::string strstart = pStr.substr(0, startlen);
		std::string str = pStr;
		if(pLowerCase){
			strstart = ToLower(strstart);
			str = ToLower(str);
		}
		return strstart == str;
	}