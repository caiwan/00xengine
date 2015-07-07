#include "Image.hpp"
#include "Core/ResourceManager.hpp"
#include "Debug/Debug.hpp"

namespace engine {
	Image::Image(const Vector2I &pSize) : mSize(pSize), mBPP(GL_RGBA8), mFormat(GL_RGBA){

	}

	Image::Image(const std::string &pName, const Vector2I &pSize, sf::Image &pSurface) : 	
								mSize(pSize),
				 				mBPP(GL_RGBA8),
								mFormat(GL_RGBA),
				 				mSurface(pSurface){
		SetName(pName);
	}
 
	Image::~Image(){
	}

	const Vector2I& Image::GetSize() const{
		return mSize;
	}

	u32 Image::GetBytesPerPixel() const{
		return mBPP;
	}

	u32 Image::GetFormat() const{
		return mFormat;
	}

	const u8* Image::GetData() const{
		return const_cast<u8*>(mSurface.GetPixelsPtr());
	}

	bool Image::LoadFromFile(const std::string &pFileName){
		bool ret = true;

		// Try to find Image in ResourceManager first, so we don't load it twice
		Image* temp = ResourceManager::Call().Get<Image>(pFileName);

		// If image does not exist yet
		if(!temp){
			// Try to find it in Image Resources Path
			std::string filePath = ResourceManager::Call().FindFile(pFileName, "Image");

			// If it doesn't exist, Error and bad return.
			if(filePath == "0"){
				ret = false;
				OmniLog << "File \"" << pFileName << "\" does not exist in Image directory." << eol;		
			}else{
				// If it exists but fail to load, Error and bad return
				if(!mSurface.LoadFromFile(filePath)){
					ret = false;
					OmniLog << "File \"" << filePath << "\" is not a valid Image File." << eol;	
				}else{
					mSize = Vector2I(mSurface.GetWidth(), mSurface.GetHeight());

					#ifdef _DEBUG
						BaseLog << "DEBUG : \"" << pFileName << "\" image loaded." << eol;
					#endif

					// Add it To the ResourceManager
					ResourceManager::Call().Add(pFileName, this);
				}
			}
		}else{
			// If it exists already, send error message and bad return
			ret = false;
			OmniLog << "Image : \"" << pFileName << "\" has already been loaded" << eol;
		}

		return ret;
	}
} 
