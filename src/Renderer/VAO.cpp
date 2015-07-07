#include "VAO.hpp"
#include "Shader.hpp"
#include "Utils/Color.hpp"
#include "Utils/String.hpp"
#include "Debug/Exceptions.hpp"

namespace engine {
	VAO::VAO() : mVao(0), mVCount(0), mICount(0), mHasIndices(false){
	}

	VAO::~VAO(){
		if(mIbo.GetBuffer())
			mIbo.Destroy();
		if(mVbo.GetBuffer())
			mVbo.Destroy();
		if(mVao)
			Destroy();
	}
	
	void VAO::CopyVAO(const VAOPtr& pVao){
		mHasIndices = pVao->HasIndices();
		mVao = pVao->GetVAO();
		mVbo = pVao->GetVertices();
		mIbo = pVao->GetIndices();
		mICount = pVao->GetIndexCount();
		mVCount = pVao->GetVertexCount();
	}

	void VAO::Destroy(){
		glDeleteVertexArrays(1, &mVao);
	}

	void VAO::Bind() const{
		glBindVertexArray(mVao);
	}

	void VAO::UnBind() const{
		glBindVertexArray(0);
	}

	void VAO::Generate(Shader* pShader, const Vector3F* pVertices, u32 pVerticeSize, const Index* pIndices, u32 pIndiceSize, eBufferUsage bu){
		// On s'assure que le tableau est remplit
		//Assert(pVertices != NULL);

		// On regarde s'il existe deja un VAO ici
		if(mVao)
			Destroy();

		// On génère le VAO
		glGenVertexArrays(1, &mVao);

		// On génère le VBO
		mVbo.Generate(pVertices, pVerticeSize, bu);
		mVCount = pVerticeSize / sizeof(Vector3F);

		// On fait de même avec l'IBO s'il existe
	//	if(pIndices){
			mIbo.Generate(pIndices, pIndiceSize, bu);
			mICount = pIndiceSize / sizeof(Index);
			mHasIndices = true;
	//	}
		
		// On bascule notre VAO comme VAO courant
		glBindVertexArray(mVao);

		// De meme avec le VertexBuffer
		glBindBuffer(GL_ARRAY_BUFFER, mVbo.GetBuffer());

		// On met le tableau de vertices dans le VAO
			GLint loc = glGetAttribLocation(pShader->GetProgram(), "inVertex");
			glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, 0);
#ifdef _DEBUG
			GLenum error = GL_NO_ERROR;
			if((error = glGetError()) != GL_NO_ERROR){
				throw Exception(String("OpenGL Error: \"")+GetGLErrorStr(error)+"\" in function \"VAO::Generate\"\n\tDoes \"inVertex\" exists or is used?");
			}
#endif
			glEnableVertexAttribArray(loc);

		// Si on a des indices, on active notre IBO
		if(mHasIndices)
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIbo.GetBuffer());

		// On dé-lie notre VAO
		glBindVertexArray(0);
	}
	
	void VAO::Update(const Vector3F* pVertices, u32 pVerticeSize, const Index* pIndices, u32 pIndiceSize){
		mVCount = pVerticeSize / sizeof(Vector3F);
		mICount = pIndiceSize / sizeof(Index);

		mVbo.Update(pVertices, pVerticeSize);
		mIbo.Update(pIndices, pIndiceSize);
	}
	
	// ################################################################### //
	//					COLORMESH

	void ColorMesh::GenerateNormals(const Vector3F* pNormals, u32 pSize, Shader* shader, eBufferUsage bu){
		glBindVertexArray(mVao);
			mNormals.Generate(pNormals, pSize, bu);
			glBindBuffer(GL_ARRAY_BUFFER, mNormals.GetBuffer());
			GLint loc = glGetAttribLocation(shader->GetProgram(), "inNormal");
			glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, 0);
#ifdef _DEBUG
			GLenum error = GL_NO_ERROR;
			if((error = glGetError()) != GL_NO_ERROR){
				throw Exception(String("OpenGL Error: \"")+GetGLErrorStr(error)+"\" in function \"ColorMesh::GenerateNormals\"\n\tDoes \"inNormal\" exists or is used?");
			}
#endif
			glEnableVertexAttribArray(loc);
		glBindVertexArray(0);
	}

	void ColorMesh::UpdateNormals(const Vector3F* pNormals, u32 pSize){
		mNormals.Update(pNormals, pSize);
	}
	
	// ################################################################### //
	//					COLORVAO

	void ColorVAO::GenerateTexCoords(const Vector2F* pTexCoords, u32 pSize, Shader* shader, eBufferUsage bu){
		glBindVertexArray(mVao);
			mTexCoords.Generate(pTexCoords, pSize, bu);
			glBindBuffer(GL_ARRAY_BUFFER, mTexCoords.GetBuffer());
			GLint loc = glGetAttribLocation(shader->GetProgram(), "inTexcoord");
			glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 0, 0);
#ifdef _DEBUG
			GLenum error = GL_NO_ERROR;
			if((error = glGetError()) != GL_NO_ERROR){
				throw Exception(String("OpenGL Error: \"")+GetGLErrorStr(error)+"\" in function \"ColorVAO::GenerateNormals\"\n\tDoes \"inTexcoord\" exists or is used?");
			}
#endif
			glEnableVertexAttribArray(loc);
		glBindVertexArray(0);
	}

	void ColorVAO::UpdateTexCoords(const Vector2F* pTexCoords, u32 pSize){
		mTexCoords.Update(pTexCoords, pSize);
	}
	
	// ################################################################### //
	//					TEXMESH

	void TextureMesh::GenerateTexCoords(const Vector2F* pTexCoords, u32 pSize, Shader* shader, eBufferUsage bu){
		glBindVertexArray(mVao);
			mTexCoords.Generate(pTexCoords, pSize, bu);
			glBindBuffer(GL_ARRAY_BUFFER, mTexCoords.GetBuffer());
			GLint loc = glGetAttribLocation(shader->GetProgram(), "inTexcoord");
			glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 0, 0);
#ifdef _DEBUG
			GLenum error = GL_NO_ERROR;
			if((error = glGetError()) != GL_NO_ERROR){
				throw Exception(String("OpenGL Error: \"")+GetGLErrorStr(error)+"\" in function \"TexMesh::GenerateNormals\"\n\tDoes \"inTexcoord\" exists or is used?");
			}
#endif
			glEnableVertexAttribArray(loc);
		glBindVertexArray(0);
	}

	void TextureMesh::UpdateTexCoords(const Vector2F* pTexCoords, u32 pSize){
		mTexCoords.Update(pTexCoords, pSize);
	}

	void TextureMesh::GenerateNormals(const Vector3F* pNormals, u32 pSize, Shader* shader, eBufferUsage bu){
		glBindVertexArray(mVao);
			mNormals.Generate(pNormals, pSize, bu);
			glBindBuffer(GL_ARRAY_BUFFER, mNormals.GetBuffer());
			GLint loc = glGetAttribLocation(shader->GetProgram(), "inNormal");
			glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, 0);
#ifdef _DEBUG
			GLenum error = GL_NO_ERROR;
			if((error = glGetError()) != GL_NO_ERROR){
				throw Exception(String("OpenGL Error: \"")+GetGLErrorStr(error)+"\" in function \"TexMesh::GenerateNormals\"\n\tDoes \"inNormal\" exists or is used?");
			}
#endif
			glEnableVertexAttribArray(loc);
		glBindVertexArray(0);
	}

	void TextureMesh::UpdateNormals(const Vector3F* pNormals, u32 pSize){
		mNormals.Update(pNormals, pSize);
	}
}
