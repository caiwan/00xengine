#ifndef SHADER_HPP
#define SHADER_HPP

#include "Core/Resource.hpp"
#include "Utils/SPointer.hpp"
#include "Utils/Shared.hpp"
#include "Math/Vector2.hpp"
#include "Math/Vector3.hpp"

namespace engine {
	class Color;
	class Matrix4;

	/// \brief Wrapper class for GLSL Shader Program, with Vertex/Fragment/Geometry shader loading and compilation
	class OOXAPI Shader : public IResource{
	public:
		Shader();
		~Shader();

		/// \brief Destroy the program
		void Destroy();

		/// \brief Compile the shader from sources
		/// \param pVSName : Vertex Shader source file name
		/// \param pFSName : Fragment Shader source file name
		/// \param pGSName : Geometry Shader source file name
		void Compile(const std::string &pVSName, const std::string &pFSName, const std::string &pGSName = "");

		/// \brief Bind the shader to the OpenGL State
		void Bind() const;

		/// \brief Unbind the Shader
		void UnBind() const;

		/// \brief Returns the Shader ID
		GLuint GetProgram() { return mProgram; }


		/// Send/Access functions for sending uniform variables
			/// \brief Matrix 4x4
			/// \param pVarName : Variable name in shader source
			/// \param pMatrix : matrix to send
			void SendMatrix4(const std::string &pVarName, const Matrix4 &pMatrix);

			/// \brief Vector 3
			/// \param pVarName : Variable name in shader source
			/// \param pVector : vector to send
			void SendVector3(const std::string &pVarName, const Vector3F &pVector);
			
			/// \brief Vector 2
			/// \param pVarName : Variable name in shader source
			/// \param pVector : vector to send
			void SendVector2(const std::string &pVarName, const Vector2F &pVector);
			
			/// \brief Color
			/// \param pVarName : Variable name in shader source
			/// \param pColor : color to send
			void SendColor(const std::string &pVarName, const Color &pColor);
			
			/// \brief Float
			/// \param pVarName : Variable name in shader source
			/// \param pVar : float to send
			void SendFloat(const std::string &pVarName, f32 pVar);

	private:		
		/// \brief Private method used by Compile to load a Vertex Shader from source
		void LoadVertexShader(const std::string &pFilename);

		/// \brief Private method used by Compile to load a Fragment Shader from source
		void LoadFragmentShader(const std::string &pFilename);

		/// \brief Private method used by Compile to load a Geometry Shader from source
		void LoadGeometryShader(const std::string &pFilename);

		GLuint mProgram;	/// Program ID
		GLuint mVShader;	/// Vertex Shader ID
		GLuint mFShader;	/// Fragment Shader ID
		GLuint mGShader;	/// Geometry Shader ID
	};

	typedef SPointer<Shader, ResourceTypePolicy> ShaderPtr;
}
#endif
