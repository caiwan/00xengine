#ifndef VAO_HPP
#define VAO_HPP

#include "VBO.hpp"
#include "Core/Resource.hpp"
#include "Utils/SPointer.hpp"

namespace engine {
	class Shader;
	class Color;
	class VAO;

	typedef SPointer<VAO, ResourceTypePolicy> VAOPtr;

	/// \brief Interface Wrapper Class for OpenGL VAO
	/// - Use it as it is for only Vertice Position/Indices
	/// - Use one of the inherited class (ColorVAO, ColorMesh, TexMesh) for advanced uses
	class OOXAPI VAO : public IResource{
	public:
		VAO();
		~VAO();
		

		/// \brief Generate the VAO and its included VBO from Vertices/Indices arrays
		/// \param pShader : pointer on the Shader used to draw the VAO
		/// \param pVertices : Array of Positions (Vector3F)
		/// \param pVerticeSize : Size of associated arrays
		/// \param pIndices : Array of Indices (Index)
		/// \param pIndiceSize : Size of associated arrays
		/// \param pBu : VBO Usage
		void Generate(Shader* pShader, const Vector3F* pVertices, u32 pVerticeSize, const Index* pIndices, u32 pIndiceSize, eBufferUsage pBu = BU_Static);

		/// \brief Update an already dynamically created VAO with new vertices/indices data
		/// \param pVertices : Array of Positions (Vector3F)
		/// \param pVerticeSize : Size of associated arrays
		/// \param pIndices : Array of Indices (Index)
		/// \param pIndiceSize : Size of associated arrays
		void Update(const Vector3F* pVertices, u32 pVerticeSize, const Index* pIndices, u32 pIndiceSize);

		/// \brief Copy a VAO
		void CopyVAO(const VAOPtr& pVao);

		/// \brief Destroy the VAO and associated VBO
		void Destroy();

		/// \brief Bind the VAO to OpenGL Render State
		void Bind() const;

		/// \brief Unbind the VAO
		void UnBind() const;

		/// Getters

			const GLuint GetVAO() const { return mVao; }
			const VBO GetVertices() const { return mVbo; }
			const VBO GetIndices() const { return mIbo; }
			const u32 GetVertexCount() const { return mVCount; }
			const u32 GetIndexCount() const { return mICount; }

		/// Setters

			void SetVAO(GLuint pVao) { mVao = pVao; }
			void SetVertices(VBO pVbo) { mVbo = pVbo; }
			void SetIndices(VBO pIbo) { mIbo = pIbo; }
			void SetVertexCount(u32 pVc) { mVCount = pVc; }
			void SetIndexCount(u32 pIc) { mICount = pIc; }

		/// \brief Returns if the VAO possesses indices
		bool HasIndices() const { return mHasIndices; }

	protected:
		GLuint mVao;		/// VAO ID
		VBO mVbo;			/// Vertice Position VBO
		VBO mIbo;			/// Indice VBO

		u32 mVCount;		/// Vertices number
		u32 mICount;		/// Indices number

		bool mHasIndices;	/// True if VAO possesses indices
	};

	/// \brief VAO with additionnals VBOs used for Texture Coordinates and Normals
	class OOXAPI TextureMesh : public VAO{
	public:
		/// \brief Generate the Normal VBO with given data
		/// \param pNormals : Vector3F Array for normal coordinates
		/// \param pSize : size of the above array
		/// \param pShader : shader used for VAO rendering
		/// \param pBu : VBO Usage Flag
		void GenerateNormals(const Vector3F* pNormals, u32 pSize, Shader* pShader, eBufferUsage pBu = BU_Static);
		
		/// \brief Generate the TexCoords VBO with given data
		/// \param pTexCoords : Vector2F Array for texture coordinates
		/// \param pSize : size of the above array
		/// \param pShader : shader used for VAO rendering
		/// \param pBu : VBO Usage Flag
		void GenerateTexCoords(const Vector2F* pTexCoords, u32 pSize, Shader* pShader, eBufferUsage pBu = BU_Static);

		/// \brief Update an already dynamically created Normal VBO with new data
		/// \param pNormals : Array of Vector3F for normal coordinates
		/// \param pSize : Size of above array
		void UpdateNormals(const Vector3F* pNormals, u32 pSize);

		/// \brief Update an already dynamically created Texcoords VBO with new data
		/// \param pTexCoords : Array of Vector2F for texture coordinates
		/// \param pSize : Size of above array
		void UpdateTexCoords(const Vector2F* pTexCoords, u32 pSize);
	private:
		VBO mNormals;
		VBO mTexCoords;
	};

	typedef SPointer<TextureMesh, ResourceTypePolicy> TexMeshPtr;

	/// \brief VAO with an additionnal VBO used for Normals
	class OOXAPI ColorMesh : public VAO{
	public:
		/// \brief Generate the Normal VBO with given data
		/// \param pNormals : Vector3F Array for normal coordinates
		/// \param pSize : size of the above array
		/// \param pShader : shader used for VAO rendering
		/// \param pBu : VBO Usage Flag
		void GenerateNormals(const Vector3F* pNormals, u32 pSize, Shader* pShader, eBufferUsage pBu = BU_Static);

		/// \brief Update an already dynamically created Normal VBO with new data
		/// \param pNormals : Array of Vector3F for normal coordinates
		/// \param pSize : Size of above array
		void UpdateNormals(const Vector3F* pNormals, u32 pSize);
	private:
		VBO mNormals;
	};
	
	typedef SPointer<ColorMesh, ResourceTypePolicy> ColorMeshPtr;

	/// \brief VAO with an additionnal VBO used for Texture Coordinates
	class OOXAPI ColorVAO : public VAO{
	public:
		/// \brief Generate the TexCoords VBO with given data
		/// \param pTexCoords : Vector2F Array for texture coordinates
		/// \param pSize : size of the above array
		/// \param pShader : shader used for VAO rendering
		/// \param pBu : VBO Usage Flag
		void GenerateTexCoords(const Vector2F* pTexCoords, u32 pSize, Shader* pShader, eBufferUsage pBu = BU_Static);

		/// \brief Update an already dynamically created Texcoords VBO with new data
		/// \param pTexCoords : Array of Vector2F for texture coordinates
		/// \param pSize : Size of above array
		void UpdateTexCoords(const Vector2F* pTexCoords, u32 pSize);
	private:
		VBO mTexCoords;
	};
	
	typedef SPointer<ColorVAO, ResourceTypePolicy> ColorVAOPtr;
}
#endif
