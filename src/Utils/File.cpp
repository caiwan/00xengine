#include <sstream>
#include "File.hpp"
#include "Debug/Exceptions.hpp"
#include "Debug/New.hpp"


namespace engine {
	File::File() : mFileName(""){
	}

	File::File(const std::string &pFilename, eReadWriteMode pRwm, eFilePos pFp) {
		Open(pFilename, pRwm, pFp);
	}

	File::~File(){
		Close();
	}

	void File::Open(const std::string &pFilename, eReadWriteMode pRwm, eFilePos pFp){
		std::ios_base::openmode mode;
		switch(pRwm){
			case RWM_Write: 
				mode = std::fstream::in | std::fstream::out | std::fstream::trunc; break;
			case RWM_Open : 
				mode = std::fstream::in | std::fstream::out; break;
			case RWM_ReadOnly : 
				mode = std::fstream::in; break;
			default: throw LoadingFailed(pFilename, "ReadWriteMode is invalid!");
		}

		switch(pFp){
			case FP_Top:
				break;
			case FP_Bottom:
				mode |= std::fstream::ate; break;
			default:
				throw LoadingFailed(pFilename, "File Positionment value is invalid!");
		}

		mFileName = pFilename;
		mFile.open(pFilename.c_str(), mode);
	}

	void File::Close(){
		if(IsOpened())
			mFile.close();
	}

	void File::Flush(){
		if(IsOpened())
			mFile.flush();
	}

	bool File::IsOpened() const{
		return mFile.is_open();
	}

	bool File::Exists(const std::string &pFilename){
		std::ifstream readFile(pFilename.c_str());
		return readFile.is_open();
	}

	std::string File::Filename() const{
		return mFileName;
	}

	bool File::End() const{
		return mFile.eof();
	}

	std::string File::GetLine(){
		std::string line;
		getline(mFile, line);
		return line;
	}

    std::string File::Read() const{
		if(mFile){
			std::stringstream buffer;
			buffer << mFile.rdbuf();
			std::string ret(buffer.str());
			ret.push_back('\0');
			return ret;
		}else
			throw Exception("Tried to read an inexistant file : "+mFileName);	
    }
/*

    void File::GoTo(FilePos pos){
        if(mFile.is_open())
            switch(pos){
                case BEG: mFile.seekg(0, ios::beg); break;
                case END: mFile.seekg(0, ios::end); break;
                case NEXT: JumpLine(); break;
                default:break;
            }
    }

    s

    string File::GetUntil(string s, char c){
        size_t pos = s.find_first_of(c);
        if(pos >= 10000){
            pos = 0;
            ErrLog << "File : in " << s << ", " << c << " is not present!" << eol;
        }
        return s.substr(0,pos);
    }
*/
}
