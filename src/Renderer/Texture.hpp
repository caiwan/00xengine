#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "Core/Image.hpp"
#include "Math/Rectangle.hpp"

namespace engine {
	/// \brief Wrapper class for OpenGL Texture, load from Image only
	class OOXAPI Texture{
	public:
		Texture();
		~Texture();

		/// \brief Load the OpenGL Texture from an Image
		/// \param pImage : Image to use
		/// \param pSubRect : SubRect optionnel (partie d'une image)
		void LoadFromImage(const Image &pImage, const Rectangle &pSubRect = Rectangle(0,0,0,0));

		/// \brief Bind the texture to OpenGL Render State
		void Bind() const;

		/// \brief Unbind the texture
		void UnBind() const;

		/// \brief Destroy the OpenGL Texture
		void Destroy();

	private:
		GLuint mTexture;	/// Texture ID
	};
}
#endif
