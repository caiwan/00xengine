#ifndef RENDERENUMS_HPP
#define RENDERENUMS_HPP

#include "Utils/Shared.hpp"

namespace engine {
	/// \brief OpenGL Primitive Types
    enum PrimitiveType {
        PT_TRIANGLELIST,  
        PT_TRIANGLESTRIP, 
        PT_TRIANGLEFAN,   
        PT_LINELIST,      
        PT_LINESTRIP,     
        PT_POINTLIST      
    };

	/// \brief Matrix Types
	enum MatrixType{
		MAT_WORLD,
		MAT_INVWORLD,
		MAT_VIEW,
		MAT_INVVIEW,
		MAT_PROJ,
		MAT_WORLDVIEW,
		MAT_WORLDVIEWPROJ,
		MAT_INVWORLDTRANSPOSE
	};

}

#endif
