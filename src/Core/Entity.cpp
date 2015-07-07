#include "Entity.hpp"
#include "ResourceManager.hpp"
#include "Math/Quaternion.hpp"
#include "Utils/String.hpp"
#include "Renderer/Renderer.hpp"
#include "Renderer/Shader.hpp"
#include "Debug/Debug.hpp"

namespace engine {
	u32 Entity::EntityIDs = 0;
	
	Entity::Entity() : mID(EntityIDs++), mType(ET_NONE), mUseTexture(false), mShader(0){
	}

	Entity::Entity(const Entity &pCopy){
		mType = pCopy.mType;
		mUseTexture = pCopy.mUseTexture;
		mTexture = pCopy.mTexture;
		mModelMatrix = pCopy.mModelMatrix;
		mAABB = pCopy.mAABB;
		if(!pCopy.mVao)
			OmniLog << "Entity \"" << mID << "\" has been created from copy but with no VAO." << eol;
		else
			mVao = pCopy.mVao;
	}

	void Entity::CreateVAO(const std::string &pMeshName, Shader &pShader, Vector3F* pVertices, u32 pVSize, Index* pIndices, u32 pISize){

		if(ResourceManager::Call().Get<VAO>(pMeshName))
			throw Exception(String("Entity \"")+mID+"\" was told to create mesh \"" + pMeshName + "\" but this is an already existing mesh");
		else{
			mShader = &pShader;

			mVao = new VAO();
			mVao->Generate(mShader, pVertices, pVSize, pIndices, pISize);

			mAABB.Init(pVertices, pVSize / sizeof(Vertex));
			mName = pMeshName;
		}
	}

	void Entity::CopyVAO(Entity &pCopy){
		if(pCopy.mVao){
			mVao = pCopy.mVao.Copy();
			mUseTexture = pCopy.mUseTexture;
			mTexture = pCopy.mTexture;
			mAABB = pCopy.mAABB;
			mShader = pCopy.mShader;
		}else{
			throw Exception(String("Entity \"")+mID+"\" was told to get its mesh from an empty mesh of entity \""+pCopy.mID+"\".");
		}
	}

	void Entity::SetPosition(const Vector3F &pVec){
		mAABB.Translate(pVec - mModelMatrix.GetTranslation());
		mModelMatrix.SetTranslation(pVec);
	}

	void Entity::Translate(const Vector3F &pVector){
		mAABB.Translate(pVector);
		mModelMatrix.Translate(pVector);
	}

	void Entity::Translate(f32 x, f32 y, f32 z){
		Translate(Vector3F(x,y,z));
	}

	void Entity::SetOrientation(const Quaternion &pQuat){
		mModelMatrix.SetOrientation(pQuat);
	}

	void Entity::Rotate(const Vector3F &pAxis, f32 angle){
		Matrix4 rotation;
		Quaternion quat;
		quat.FromAxisAngle(pAxis, angle);
		rotation.SetOrientation(quat);
		mModelMatrix = rotation * mModelMatrix;
	}
	
	void Entity::Scale(f32 x, f32 y, f32 z){
		mAABB.Scale(Vector3F(x,y,z));
		mModelMatrix.SetScale(x,y,z);
	}

	
	// ######################################################## //
	//				MESH

	void Mesh::Make(Vector3F* pNormals, Vector2F* pTexCoords){
		if(!mVao)
			throw Exception("Entity : Generate the Entity vertices before making a Mesh.");

		if(!mShader)
			throw Exception("Entity : Entity needs a Shader before making a Mesh.");

		mMesh = new TextureMesh();
		mMesh->CopyVAO(mVao);

		mType = ET_MESH;
		mUseTexture = true;

		mMesh->GenerateNormals(pNormals, mVao->GetVertexCount() * sizeof(Vector3F), mShader);
		mMesh->GenerateTexCoords(pTexCoords, mVao->GetVertexCount() * sizeof(Vector2F), mShader);

		ResourceManager::Call().Add(mName, mMesh);
	}

	void Mesh::CopyMesh(Mesh &pMesh){
		if(pMesh.mVao){
			mVao = pMesh.mVao.Copy();
			mUseTexture = pMesh.mUseTexture;
			mTexture = pMesh.mTexture;
			mAABB = pMesh.mAABB;
			mShader = pMesh.mShader;
			if(pMesh.mMesh)
				mMesh = pMesh.mMesh.Copy();
		}else{
			throw Exception(String("Entity \"")+mID+"\" was told to get its mesh from an empty mesh of entity \""+pMesh.mID+"\".");
		}
	}

	void Mesh::Draw(){
		Renderer::Call().DrawMesh(this);
	}

	
	// ######################################################## //
	//				OBJECT
	
	void Object::Make(Vector3F* pNormals){
		if(!mVao)
			throw Exception("Entity : Generate the Entity vertices before making an Object.");

		if(!mShader)
			throw Exception("Entity : Entity needs a Shader before making an Object.");

		mMesh = new ColorMesh();
		mMesh->CopyVAO(mVao);
		
		mType = ET_OBJECT;
		mUseTexture = false;
		
		mMesh->GenerateNormals(pNormals, mVao->GetVertexCount() * sizeof(Vector3F), mShader);
		
		ResourceManager::Call().Add(mName, mMesh);
	}

	void Object::CopyObject(Object &pObject){
		if(pObject.mVao){
			mVao = pObject.mVao.Copy();
			mUseTexture = pObject.mUseTexture;
			mTexture = pObject.mTexture;
			mAABB = pObject.mAABB;
			mShader = pObject.mShader;
			if(pObject.mMesh)
				mMesh = pObject.mMesh.Copy();
		}else{
			throw Exception(String("Entity \"")+mID+"\" was told to get its mesh from an empty mesh of entity \""+pObject.mID+"\".");
		}
	}

	void Object::Draw(){
		Renderer::Call().DrawObject(this);
	}
	
	// ######################################################## //
	//				DEBUGOBJECT

	void DebugObject::Make(Vector2F* pTexCoords){
		if(!mVao)
			throw Exception("Entity : Generate the Entity vertices before making a DebugObject.");

		if(!mShader)
			throw Exception("Entity : Entity needs a Shader before making a DebugObject.");

		mMesh = new ColorVAO();
		mMesh->CopyVAO(mVao);
		
		mType = ET_DEBUGOBJECT;
		mUseTexture = true;
		
		mMesh->GenerateTexCoords(pTexCoords, mVao->GetVertexCount() * sizeof(Vector2F), mShader);

		ResourceManager::Call().Add(mName, mMesh);
	}

	void DebugObject::CopyDebugObject(DebugObject &pObject){
		if(pObject.mVao){
			mVao = pObject.mVao.Copy();
			mUseTexture = pObject.mUseTexture;
			mTexture = pObject.mTexture;
			mAABB = pObject.mAABB;
			mShader = pObject.mShader;
			if(pObject.mMesh)
				mMesh = pObject.mMesh.Copy();
		}else{
			throw Exception(String("Entity \"")+mID+"\" was told to get its mesh from an empty mesh of entity \""+pObject.mID+"\".");
		}
	}

	void DebugObject::Draw(){
		Renderer::Call().DrawDebugObject(this);
	}
}
