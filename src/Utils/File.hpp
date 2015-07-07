#ifndef FILE_HPP
#define FILE_HPP

#include "Shared.hpp"
#include <fstream>

namespace engine {
	/// \brief Read/Write file opening mode
	enum eReadWriteMode{
		RWM_Write = 1,				/// Read/Write, make a new file or overwrite an existant one
		RWM_Open = 0,				/// Read/Write, does not overwrite, file must exist
		RWM_ReadOnly = -1,			/// Read Only mode, file must exist
	};

	/// \brief Opening cursor position in file
	enum eFilePos{
		FP_Top,									
		FP_Bottom
	};


	/// \brief Class used for any file handling
	class OOXAPI File{
	public:
		/// \brief Ctor, default, do nothing
		File();

		/// \brief Ctor, open the given file in given mode
		/// \param pFilename : name of the file
		/// \param pFp		: file cursor position
		/// \param pRwm      : opening mode
		File(const std::string &pFilename, eReadWriteMode pRwm = RWM_Open, eFilePos pFp = FP_Top);

		virtual ~File();

		/// \brief Open a file (in buffer)
		/// \param pFilename : name of the file
		/// \param pFp		: file cursor position
		/// \param pRwm      : opening mode
		void Open(const std::string &pFilename, eReadWriteMode pRwm = RWM_Open, eFilePos pFp = FP_Top);

		/// \brief Close the opened file (buffer)
		void Close();

		/// \brief Flush the buffer in the file
		void Flush();

		/// \brief Returns the content of opened file in one string
		std::string Read() const;

		/// \brief Returns true if a file is opened
		bool IsOpened() const;

		/// \brief Returns the name of opened file
		std::string Filename() const;

		/// \brief Returns true if EoF is reached
		bool End() const;

		/// \brief Returns the current line in the opened file(and increments cursor afterwards)
		std::string GetLine();

		/// \brief Stream Op for in file writing
		template<class T> File& operator<< (T &pMsg);


		/// Static Methods
			/// \brief Check if a file exists on drive
			/// \param pFilename : path to the file
			static bool Exists(const std::string &pFilename);

	protected:
		std::fstream mFile;			/// File buffer
		std::string mFileName;		/// File name (with path)
	};

	template<class T>
	inline File& File::operator<< (T &pMsg){
		if(IsOpened())
			mFile << pMsg;
		return (*this);
	}
}
#endif
