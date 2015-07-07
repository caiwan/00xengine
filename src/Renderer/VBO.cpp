#include "VBO.hpp"
#include "Utils/Color.hpp"
#include "Utils/String.hpp"
#include "Debug/Exceptions.hpp"
#include "Debug/New.hpp"

namespace engine {
	GLenum GetUsage(eBufferUsage usage){
		GLenum ret;
		switch(usage){
		case BU_Static: ret = GL_STATIC_DRAW; break;
		case BU_Stream: ret = GL_STREAM_DRAW; break;
		case BU_Dynamic: ret = GL_DYNAMIC_DRAW; break;
		}
		return ret;
	}

	VBO::VBO() : mVbo(0), mType(BT_VERTEX), mUsage(BU_Static){
	}

	VBO::~VBO(){
		if(mVbo)
			Destroy();
	}

	void VBO::Destroy(){
		glDeleteBuffers(1, &mVbo);
	}

	void VBO::Generate(const Index* pIndices, u32 pSize, eBufferUsage usage){
		// On élimine les buffers contenus précédement
		if(mVbo)
			Destroy();

		// On génère le bufer
		glGenBuffers(1, &mVbo);

		// On Lock le Buffer en mémoire et on le remplit
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mVbo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, pSize, pIndices, GetUsage(usage));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		// On change le type en IBO et l'usage
		mType = BT_INDEX;
		mUsage = usage;
	}

	void VBO::Generate(const Vector3F* pVector, u32 pSize, eBufferUsage usage){
		// On élimine les buffers contenus précédement
		if(mVbo)
			Destroy();

		// On génère le bufer
		glGenBuffers(1, &mVbo);

		// On Lock le Buffer en mémoire et on le remplit
		glBindBuffer(GL_ARRAY_BUFFER, mVbo);
		glBufferData(GL_ARRAY_BUFFER, pSize, pVector, GetUsage(usage));
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		
		// changement possible de l'usage
		mUsage = usage;
	}

	void VBO::Generate(const Vector2F* pVector, u32 pSize, eBufferUsage usage){
		// On élimine les buffers contenus précédement
		if(mVbo)
			Destroy();

		// On génère le bufer
		glGenBuffers(1, &mVbo);

		// On Lock le Buffer en mémoire et on le remplit
		glBindBuffer(GL_ARRAY_BUFFER, mVbo);
		glBufferData(GL_ARRAY_BUFFER, pSize, pVector, GetUsage(usage));
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		
		// changement possible de l'usage
		mUsage = usage;
	}
	
	void VBO::Update(const Vector3F* pVector, u32 pSize){
		// Check si le buffer est dynamic
		//if(mUsage != BU_Dynamic)
		//	throw Exception("VBO : Tried to Update a static buffer.");

		glBindBuffer(GL_ARRAY_BUFFER, mVbo);
		glBufferData(GL_ARRAY_BUFFER, 0, NULL, GetUsage(mUsage));
		glBufferData(GL_ARRAY_BUFFER, pSize, pVector, GetUsage(mUsage));
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void VBO::Update(const Vector2F* pVector, u32 pSize){
		// Check si le buffer est dynamic
		//if(mUsage != BU_Dynamic)
		//	throw Exception("VBO : Tried to Update a static buffer.");

		glBindBuffer(GL_ARRAY_BUFFER, mVbo);
		glBufferData(GL_ARRAY_BUFFER, 0, NULL, GetUsage(mUsage));
		glBufferData(GL_ARRAY_BUFFER, pSize, pVector, GetUsage(mUsage));
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void VBO::Update(const Index* pVector, u32 pSize){
		// Check si le buffer est dynamic
		//if(mUsage != BU_Dynamic)
		//	throw Exception("VBO : Tried to Update a static buffer.");

		glBindBuffer(GL_ARRAY_BUFFER, mVbo);
		glBufferData(GL_ARRAY_BUFFER, 0, NULL, GetUsage(mUsage));
		glBufferData(GL_ARRAY_BUFFER, pSize, pVector, GetUsage(mUsage));
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

}
