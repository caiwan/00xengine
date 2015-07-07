#include "Texture.hpp"
#include "Renderer.hpp"
#include "Debug/Debug.hpp"

namespace engine {
	Texture::Texture() : mTexture(0){
	}

	Texture::~Texture(){
		Destroy();
	}

	void Texture::Destroy(){
		if(mTexture)
			glDeleteTextures(1, &mTexture);
	}		

	void Texture::LoadFromImage(const Image &pImage, const Rectangle &pSubRect){

		// Generation de Binding de la texture a OGL
		glGenTextures(1, &mTexture);
		glBindTexture(GL_TEXTURE_2D, mTexture);

		// Utilisation de linear interpolation pour les min/mag filters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, (f32)Renderer::Call().GetSpecifications().mWantedAnisotropy);

		// creation depuis l'image
		// Reconnaissance du rectangle envoye et creation de la texture OGL
		if(pSubRect.Width() == 0 && pSubRect.Height() == 0)
			glTexImage2D(GL_TEXTURE_2D, 0, pImage.GetBytesPerPixel(), pImage.GetSize().x, pImage.GetSize().y, 0, pImage.GetFormat(), GL_UNSIGNED_BYTE, pImage.GetData());
		else
			glTexSubImage2D(GL_TEXTURE_2D, 0, pSubRect.Origin.x, pSubRect.Origin.y, pSubRect.Width(), pSubRect.Height(), pImage.GetFormat(), GL_UNSIGNED_BYTE, pImage.GetData());

	//	glHint(GL_GENERATE_MIPMAP_HINT, GL_NICEST);
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);

		#ifdef _DEBUG
			BaseLog << "DEBUG : Texture created from image \"" << pImage.GetName() << "\"."/* RAJOUTER LE RECTANGLE UTILISED*/ << eol;
		#endif
	}

	void Texture::Bind() const{
		glBindTexture(GL_TEXTURE_2D, mTexture);
	}

	void Texture::UnBind() const{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}
