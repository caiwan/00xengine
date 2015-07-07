#ifndef SHARED
#define SHARED

	#define ENGINE_MAJOR 0
	#define ENGINE_MINOR 3
	#define ENGINE_PATCH 0

    /// SFML
	#include "SFML/Graphics.hpp"

	/// Platform
	#if defined(_WIN32) || defined(WIN32)
	#	define OOXWIN32
	#	include <time.h>
	#else
	#	define OOXLINUX
	#	include <sys/time.h>
	#endif

	/// DLL managment under WIN32
	#ifdef OOXWIN32
	#	ifdef OOXEXPORTS
	#		define OOXAPI __declspec(dllexport)
	#	else
	#		define OOXAPI __declspec(dllimport)
	#	endif
	#	ifdef _MSC_VER
    #		pragma warning(disable : 4251)
    #		pragma warning(disable : 4661)
	#	endif
	#else
	#	define OOXAPI
	#endif

	/// Open GL 3
	#ifdef OOXWIN32
	#	define GLEW_STATIC 1
	#	include "GL/glew.h"
	#else
    #	define GL3_PROTOTYPES 1
    #	include <GL3/gl3.h>
	#endif

	/// Anisotropic extension definition
	#define GL_TEXTURE_MAX_ANISOTROPY_EXT 0x84FE
	#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF


	/// String (always used anyway)
	#include <string>


	/// End Of Line
	#define eol "\n"

	/// Types declaration
	typedef char s8;
	typedef unsigned char u8;
	typedef short s16;
	typedef unsigned short u16;
	typedef int s32;
	typedef unsigned int u32;
	typedef long long s64;
	typedef unsigned long long u64;

	typedef float f32;
	typedef double f64;

	/// \brief Returns time in "HH:MM:SS" format
	inline std::string GetTime(){
		time_t tps = time(NULL);
		tm* temps = localtime(&tps);
		char ret[9];
		strftime(ret, 9, "%H:%M:%S", temps);
		return ret;
	}

	/// \brief Returns date in "Day DD MMM YYYY" format
	inline std::string GetDate(){
		time_t tps = time(NULL);
		tm* temps = localtime(&tps);
		char ret[16];
		strftime(ret, 16, "%a %d %b %Y", temps);
		return ret;
	}
#endif
