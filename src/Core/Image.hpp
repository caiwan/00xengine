#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <vector>
#include "Core/Resource.hpp"
#include "Math/Vector2.hpp"
#include "Utils/SPointer.hpp"

namespace engine {
	//// \brief Wrapper Class between an SFML Image and the engine
	class OOXAPI Image : public IResource{
	public:
		/// \brief Ctor with empty image
		Image(const Vector2I &pSize = Vector2I(1,1));

		/// \brief Ctor from sf::Image
		Image(const std::string &pName, const Vector2I &pSize, sf::Image &pSurface);

		~Image();

		/// \brief Returns the image dimensions
		const Vector2I& GetSize() const;

		/// \brief Returns the BPP (OpenGL Format)
		u32 GetBytesPerPixel() const;

		/// \brief Returns the image format
		u32 GetFormat() const;

		/// \brief Returns the image pixels
		const u8* GetData() const;

		/// \brief Create the image from an image file
		/// \return true if image was succesfully loaded
		bool LoadFromFile(const std::string &pFilename);

	private:
		Vector2I mSize;		/// Dimensions
		u32 mBPP;			/// Bytes per pixel
		u32 mFormat;		/// Image Format

		sf::Image mSurface;	/// SFML Image Surface
	};

	typedef SPointer<Image, ResourceTypePolicy> ImagePtr;
}
#endif
