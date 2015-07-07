#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "Renderer/VAO.hpp"
#include "Math/AABB.hpp"
#include "Math/Matrix4.hpp"
#include "Utils/Color.hpp"
#include "Debug/Exceptions.hpp"

namespace engine {
	/// \brief Different types of entities (look below for desc)
	enum eEntityType{
		ET_NONE,
		ET_OBJECT,
		ET_MESH,
		ET_DEBUGOBJECT
	};

	/// \brief Material d'une entity
	class OOXAPI Material{
	public:
		Material() : mAmbient(0.1f,0.1f,0.1f),
					 mDiffuse(1.f,1.f,1.f),
					 mSpecular(0.5f,0.5f,0.5f),
					 mShininess(1.f){}

		Color mAmbient, mDiffuse, mSpecular;
		f32 mShininess;
	};

	class Shader;
	class Texture;

	class OOXAPI Entity{
	public:
		/// \brief Returns Entity ID
		u32 GetID() const { return mID; }
		

		// Custom Shapes  (Definition in 
			/// \brief Cube 1x1x1
			void MakeCube(const std::string &pMeshname, Shader &pShader);

			/// \brief Sphere radius 1
			/// \param pMeshName : entity name for resourceManager
			/// \param pShader   : Shader used for rendering
			/// \param pSlices   : number of subdivisions of the sphere
			void MakeSphere(const std::string &pMeshName, Shader &pShader, s32 pSlices);



		/// \brief Create a new mesh from vertices/indices
		/// \param pMeshName : entity name for resourceManager
		/// \param pShader   : Shader used for rendering
		/// \param pVertices : Vertices array
		/// \param pVSize    : Vertices array size
		/// \param pIndices  : Indices array
		/// \param pISize    : Indices array size
		void CreateVAO(const std::string &pMeshName, Shader &pShader, Vector3F* pVertices, u32 pVSize, Index* pIndices = NULL, u32 pISize = 0);
		
		/// \brief Function overloaded in Mesh
		virtual void Make(Vector3F* pNormals, Vector2F* pTexCoords){
			throw Exception("Entity : Tried to use the \"Make(normal, texcoords)\" function on a non-Mesh Entity Type.");
		}
		
		/// \brief Function overloaded in Object
		virtual void Make(Vector3F* pNormals){
			throw Exception("Entity : Tried to use the \"Make(normal)\" function on a non-Object Entity Type.");
		}
		
		/// \brief Function overloaded in DebugObject
		virtual void Make(Vector2F* pTexCoords){
			throw Exception("Entity : Tried to use the \"Make(normal, texcoords)\" function on a non-DebugObject Entity Type.");
		}

		/// \brief Copy a VAO from another Entity
		void CopyVAO(Entity &pCopy);

		/// \brief Returns the VAO
		VAOPtr& GetVAO() { return mVao; }

		/// \brief Texture Functions
		void SetTexture(Texture &pTexture) { mTexture = &pTexture; mUseTexture = true; }
		const Texture& GetTexture() const { return *mTexture; }
		
		/// \brief Return true if entity use texture
		bool UseTexture() const { return mUseTexture; }

		/// \brief Set the used shader
		void SetShader(Shader &pShader) { mShader = &pShader; }

		/// \brief Returns the Shader
		Shader* GetShader() const { return mShader; }
		
		/// Matrix operations
			/// \brief Set the modelMatrix
			void SetModelMatrix(const Matrix4 &pMat) { mModelMatrix = pMat; }

			/// \brief Returns the ModelMatrix
			const Matrix4& GetModelMatrix() const { return mModelMatrix; }

		/// \brief Returns the entity AABB
		const AABB& GetAABB() const { return mAABB; }

		/// \brief Returns the entity used material
		Material& GetMaterial() { return mMaterial; }

		/// Movement and Orientation
			/// \brief Change the entity position
			void SetPosition(const Vector3F &pVec);

			/// \brief Change the entity orientation
			void SetOrientation(const Quaternion &pQuat);

			/// \brief Scale the entity
			void Scale(f32 x, f32 y, f32 z);

			/// \brief Move the entity
			void Translate(const Vector3F& pVector);
			void Translate(f32 x, f32 y, f32 z);

			/// \brief Rotate the entity
			void Rotate(const Vector3F &pAxis, f32 angle);

		/// \brief Add the entity to the renderer drawlist
		virtual void Draw() = 0;

		/// \brief Returns the entity type
		eEntityType GetType() const { return mType; }



	protected:
		Entity();
		Entity(const Entity &pCopy);
		~Entity(){}

		static u32 EntityIDs;	/// Auto incremented Entities IDs
		u32 mID;				/// This Entity ID
		std::string mName;		/// Entity Name

		VAOPtr mVao;			/// Position/Indice VAO
		Shader* mShader;		/// Shader used during rendering
		Texture* mTexture;		/// Used texture (if any)
		bool mUseTexture;		/// True if a texture is used
		
		Matrix4 mModelMatrix;	/// Model Matrix
		AABB mAABB;				/// Axis Aligned Bounding Box

		eEntityType mType;		/// Entity Type

		Material mMaterial;		/// Entity Material
	};
	


	/// \brief MESH : Entity with Texture Coordinates and Normals
	class OOXAPI Mesh : public Entity{
	public:
		Mesh() : Entity() {
			mType = ET_MESH;
		}

		/// \brief Generate the Normals and TexCoords VBO
		/// \param pNormals : normals array
		/// \param pTexCoords : texcoords array
		void Make(Vector3F* pNormals, Vector2F* pTexCoords);

		/// \brief Copy an existing Mesh (Pos/Indices/Normals/TexCoords)
		void CopyMesh(Mesh &pMesh);

		/// \brief Add the Mesh to the renderer DrawList
		void Draw();
		
		/// \brief Returns the VAO
		TexMeshPtr& GetMesh() { return mMesh; }

	private:
		TexMeshPtr mMesh;		/// VAO used in spite of the mVAO
	};

	/// \brief OBJECT : Entite avec couleurs et normales
	class OOXAPI Object : public Entity{
	public:
		Object() : Entity() {
			mType = ET_OBJECT;
		}
		
		/// \brief Generate the Normals VBO
		/// \param pNormals : normals array
		void Make(Vector3F* pNormals);

		/// \brief Copy an existing Object (Pos/Indices/Normals)
		void CopyObject(Object &pObject);

		/// \brief Add the Object to the renderer DrawList
		void Draw();
		
		/// \brief Returns the VAO
		ColorMeshPtr& GetMesh() { return mMesh; }

	private:
		ColorMeshPtr mMesh;		/// VAO used in spite of the mVAO
	};

	/// \brief DEBUGOBJECT : objet avec couleur et texture
	class OOXAPI DebugObject : public Entity{
	public:
		DebugObject() : Entity() {
			mType = ET_DEBUGOBJECT;
		}
		
		/// \brief Generate the TexCoords VBO
		/// \param pTexCoords : texcoords array
		void Make(Vector2F* pTexCoords);

		/// \brief Copy an existing DebugObject (Pos/Indices/TexCoords)
		void CopyDebugObject(DebugObject &pObject);

		/// \brief Add the DebugObject to the renderer DrawList
		void Draw();
		
		/// \brief Returns the VAO
		ColorVAOPtr& GetMesh() { return mMesh; }

	private:
		ColorVAOPtr mMesh;		/// VAO used in spite of the mVAO
	};
}
#endif
