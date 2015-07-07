#ifndef VBO_HPP
#define VBO_HPP

#include "Utils/Shared.hpp"
#include "Math/Vector3.hpp"
#include "Math/Vector2.hpp"

namespace engine{
	class Color;

	/// \brief Differents types of Buffer
	enum eBufferType{
		BT_VERTEX,
		BT_INDEX,
		BT_NORMALS
	};

	/// \brief Usage Flag for VBO creation
	enum eBufferUsage{
		BU_Static,
		BU_Stream,
		BU_Dynamic
	};

	/// \brief Return GL Usage Flag from eBufferUsage
	GLenum GetUsage(eBufferUsage);

	/// \brief OLD. Erase?
	struct Vertex{
		Vector3F position;
		Vector3F color;
		Vector2F texcoord;
	};

	/// \brief Just for usage
	typedef u32 Index;

	/// \brief Wrapper class for OpenGL VBO
	class OOXAPI VBO{
	public:
		VBO();
		~VBO();

		/// \brief Generate Buffer from Indices (u32)
		/// \param pIndices : Index array to place in the buffer
		/// \param pSize : Size of this array
		/// \param pUsage : Usage Flag for vbo creation
		void Generate(const Index* pIndices, u32 pSize, eBufferUsage pUsage = BU_Static);
		
		/// \brief Generate Buffer from 3D Float Vector
		/// \param pVector : Vector array to place in the buffer
		/// \param pSize : Size of this array
		/// \param pUsage : Usage Flag for vbo creation
		void Generate(const Vector3F* pVector, u32 pSize, eBufferUsage pUsage = BU_Static);
		
		/// \brief Generate Buffer from 2D Float Vector
		/// \param pVector : Vector array to place in the buffer
		/// \param pSize : Size of this array
		/// \param pUsage : Usage Flag for vbo creation
		void Generate(const Vector2F* pVector, u32 pSize, eBufferUsage pUsage = BU_Static);

		/// \brief Update an already dynamically created 3D Float Vector VBO with new Data
		/// \param pVector : Vector array to place in the buffer
		/// \param pSize : Size of this array
		void Update(const Vector3F* pVector, u32 pSize);

		/// \brief Update an already dynamically created 2D Float Vector VBO with new Data
		/// \param pVector : Vector array to place in the buffer
		/// \param pSize : Size of this array
		void Update(const Vector2F* pVector, u32 pSize);

		/// \brief Update an already dynamically created Index VBO with new Data
		/// \param pVector : Index array to place in the buffer
		/// \param pSize : Size of this array
		void Update(const Index* pVector, u32 pSize);

		/// \brief Destroy the VBO in OpenGL Memory
		void Destroy();

		/// \brief Returns the OGL Buffer
		GLuint GetBuffer() { return mVbo; }

	private:
		GLuint mVbo;			/// Buffer ID
		eBufferType mType;		/// Buffer Type
		eBufferUsage mUsage;	/// Usage Flag
	};
}
#endif
