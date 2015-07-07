#include "Shader.hpp"
#include "Core/ResourceManager.hpp"
//#include "Core/DataManager.hpp"
#include "Math/Matrix4.hpp"
#include "Utils/Color.hpp"
#include "Utils/File.hpp"
#include "Utils/String.hpp"
#include "Debug/Exceptions.hpp"
#include "Debug/New.hpp"
#include <iostream>

namespace engine {
	Shader::Shader() : mProgram(0), mVShader(0), mFShader(0), mGShader(0){
	}

	Shader::~Shader(){
		Destroy();
	}

	void Shader::Destroy(){
		if(mProgram)
			glDeleteProgram(mProgram);
	}


	void Shader::LoadVertexShader(const std::string &pFilename){
		// Creation des shaders
		mVShader = glCreateShader(GL_VERTEX_SHADER);

		// Récupération de la source
		std::string filePath = ResourceManager::Call().FindFile(pFilename, "Shader");
		if(filePath == "0")
			throw Exception(String("Vertex Shader file \"")+pFilename+"\" does not exist. Double check file path!");
		File vFile(filePath);
		std::string vSourceStr = vFile.Read();
		const char* vSource = vSourceStr.c_str();
		glShaderSource(mVShader, 1, &vSource, NULL);

		// Compilation
		glCompileShader(mVShader);
		
		// Vérification
		GLint error;
		glGetShaderiv(mVShader, GL_COMPILE_STATUS, &error);
		if(error != GL_TRUE){
			char log[1024];
			glGetShaderInfoLog(mVShader, 1024, NULL, log);
			glDeleteShader(mVShader);
			if(mFShader) 
				glDeleteShader(mFShader);
			if(mGShader)
				glDeleteShader(mGShader);
			throw Exception(String("Vertex Shader Compilation Error (\"")+pFilename+"\") :\n"+log);
		}
	}

	void Shader::LoadFragmentShader(const std::string &pFilename){
		// Creation des shaders
		mFShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Récupération de la source
		std::string filePath = ResourceManager::Call().FindFile(pFilename, "Shader");
		if(filePath == "0")
			throw Exception(String("Fragment Shader file \"")+pFilename+"\" does not exist. Double check file path!");
		File fFile(filePath);
		std::string fSourceStr = fFile.Read();
		const char* fSource = fSourceStr.c_str();
		glShaderSource(mFShader, 1, &fSource, NULL);

		// Compilation
		glCompileShader(mFShader);

		// Vérification
		GLint error;
		glGetShaderiv(mFShader, GL_COMPILE_STATUS, &error);
		if(error != GL_TRUE){
			char log[1024];
			glGetShaderInfoLog(mFShader, 1024, NULL, log);
			if(mVShader)
				glDeleteShader(mVShader);
			glDeleteShader(mFShader);
			if(mGShader)
				glDeleteShader(mGShader);
			throw Exception(String("Fragment Shader Compilation Error (\"")+pFilename+"\") :\n"+log);
		}
	}

	void Shader::LoadGeometryShader(const std::string &pFilename){
		// Creation des shaders
		mGShader = glCreateShader(GL_GEOMETRY_SHADER);

		// Récupération de la source
		std::string filePath = ResourceManager::Call().FindFile(pFilename, "Shader");
		if(filePath == "0")
			throw Exception(String("Geometry Shader file \"")+pFilename+"\" does not exist. Double check file path!");
		File gFile(filePath);
		std::string gSourceStr = gFile.Read();
		const char* gSource = gSourceStr.c_str();
		glShaderSource(mGShader, 1, &gSource, NULL);

		// Compilation
		glCompileShader(mGShader);

		// Vérification
		GLint error;
		glGetShaderiv(mGShader, GL_COMPILE_STATUS, &error);
		if(error != GL_TRUE){
			char log[1024];
			glGetShaderInfoLog(mGShader, 1024, NULL, log);
			if(mVShader)
				glDeleteShader(mVShader);
			if(mFShader) 
				glDeleteShader(mFShader);
			glDeleteShader(mGShader);
			throw Exception(String("Geometry Shader Compilation Error (\"")+pFilename+"\") :\n"+log);
		}
	}

	void Shader::Compile(const std::string &pVSName, const std::string &pFSName, const std::string &pGSName){
		std::string all = String(pVSName)+pFSName+pGSName;

		Shader* tmp = ResourceManager::Call().Get<Shader>(all);
		if(tmp != 0){
			//Shader existe deja, on copie ses identifiants dans celui ci
			mProgram = tmp->mProgram;
		}else{
			//Shader n'existe pas, on le cree

			// Ajout du shader au ResourceManager
			ResourceManager::Call().Add(all, this);

			// Chargement des fichiers shaders
			LoadVertexShader(pVSName);
			LoadFragmentShader(pFSName);
			if(!pGSName.empty())
				LoadGeometryShader(pGSName);

			// Creation du shader mProgram
			mProgram = glCreateProgram();

			// Linkage des deux shaders précédemment créés
			glAttachShader(mProgram, mVShader);
			glAttachShader(mProgram, mFShader);
			if(mGShader)
				glAttachShader(mProgram, mGShader);

			// Linkage du mProgramme a OGL
			glLinkProgram(mProgram);

			GLint error;
			glGetProgramiv(mProgram, GL_LINK_STATUS, &error);
			if(!error){
				char log[1024];
				glGetProgramInfoLog(mProgram, 1024, NULL, log);
				if(mVShader)
					glDeleteShader(mVShader);
				if(mFShader)
					glDeleteShader(mFShader);
				if(mGShader)
					glDeleteShader(mGShader);
				throw Exception(String("Shader Link Error :\n")+log);
			}
		
			// Destruction des Shaders. ils sont maintenant dans le program
			glDeleteShader(mVShader);
			glDeleteShader(mFShader);
			if(mGShader)
				glDeleteShader(mGShader);

			// Attribution des texCoords
			glUseProgram(mProgram);
			glUniform1i(glGetUniformLocation(mProgram, "tex"), 0);
			glBindFragDataLocation(mProgram, 0, "finalColor");
			glUseProgram(0);
		}
	}

	void Shader::Bind() const{
		glUseProgram(mProgram);
	}

	void Shader::UnBind() const{
		glUseProgram(0);
	}

	void Shader::SendMatrix4(const std::string &pVarName, const Matrix4 &pMatrix){
		glUniformMatrix4fv(glGetUniformLocation(mProgram, pVarName.c_str()), 1, GL_FALSE, pMatrix);
#ifdef _DEBUG
		GLenum error = GL_NO_ERROR;
		if((error = glGetError()) != GL_NO_ERROR){
			throw Exception(String("OpenGL Error: \"")+GetGLErrorStr(error)+"\" in function \"SendMatrix4\"\n\tDoes \""+pVarName+"\" exists or has the right type?");
		}
#endif
	}

	void Shader::SendVector3(const std::string &pVarName, const Vector3F &pVector){
		float toSend[3];
		pVector.XYZ(toSend);
		glUniform3fv(glGetUniformLocation(mProgram, pVarName.c_str()), 1, toSend);
#ifdef _DEBUG
		GLenum error = GL_NO_ERROR;
		if((error = glGetError()) != GL_NO_ERROR){
			throw Exception(String("OpenGL Error: \"")+GetGLErrorStr(error)+"\" in function \"SendVector3\"\n\tDoes \""+pVarName+"\" exists or has the right type?");
		}
#endif
	}

	void Shader::SendVector2(const std::string &pVarName, const Vector2F &pVector){
		float toSend[2];
		pVector.XY(toSend);
		glUniform2fv(glGetUniformLocation(mProgram, pVarName.c_str()), 1, toSend);
#ifdef _DEBUG
		GLenum error = GL_NO_ERROR;
		if((error = glGetError()) != GL_NO_ERROR){
			throw Exception(String("OpenGL Error: \"")+GetGLErrorStr(error)+"\" in function \"SendVector2\"\n\tDoes \""+pVarName+"\" exists or has the right type?");
		}
#endif
	}

	void Shader::SendColor(const std::string &pVarName, const Color &pColor){
		float toSend[4];
		pColor.RGBA(toSend);
		glUniform4fv(glGetUniformLocation(mProgram, pVarName.c_str()), 1, toSend);
#ifdef _DEBUG
		GLenum error = GL_NO_ERROR;
		if((error = glGetError()) != GL_NO_ERROR){
			throw Exception(String("OpenGL Error: \"")+GetGLErrorStr(error)+"\" in function \"SendColor\"\n\tDoes \""+pVarName+"\" exists or has the right type?");
		}
#endif
	}

	void Shader::SendFloat(const std::string &pVarName, f32 pVar){
		glUniform1f(glGetUniformLocation(mProgram, pVarName.c_str()), pVar);
#ifdef _DEBUG
		GLenum error = GL_NO_ERROR;
		if((error = glGetError()) != GL_NO_ERROR){
			throw Exception(String("OpenGL Error: \"")+GetGLErrorStr(error)+"\" in function \"SendFloat\"\n\tDoes \""+pVarName+"\" exists or has the right type?");
		}
#endif
	}
}
