#include "ResourceManager.hpp"
#include "Utils/File.hpp"
#include "Utils/String.hpp"
#include "Debug/Debug.hpp"

namespace engine {
	ResourceManager::ResourceManager(){
	}

	ResourceManager::~ResourceManager(){
		if(!(mResources.empty())){
			OmniLog << "Resources haven't been freed :" << eol << eol;

			for(ResourceMap::iterator it = mResources.begin(); it != mResources.end(); ++it){
				OmniLog << "- " << it->first << eol;
			}
		}
	}

	void ResourceManager::Add(const std::string &pName, IResource* pResource){
		Assert(pResource != NULL);

		if(mResources.find(pName) != mResources.end())
			OmniLog << "Resource \"" << pName << "\" already loaded!" << eol;

		mResources[pName] = pResource;
		pResource->SetName(pName);
	#ifdef _DEBUG
		BaseLog << "DEBUG : Adding " << pName << " to ResourceManager." << eol;
	#endif
	}

	void ResourceManager::Remove(const std::string &pName){
		ResourceMap::iterator it = mResources.find(pName);

		if(it != mResources.end()){
			mResources.erase(it);
		#ifdef _DEBUG
			BaseLog << "DEBUG : Removing " << pName << " from ResourceManager." << eol;
		#endif
		}
	}

	void ResourceManager::AddPath(const std::string &pPath, const std::string &pFileType){
		std::string fileType = pFileType.empty() ? "Generic" : pFileType;
		mLocations.insert(std::pair<std::string, std::string>(fileType, pPath));
		#ifdef _DEBUG
			BaseLog << "DEBUG : Path \"" << pPath << "\" added for \"" << fileType << "\" type resources." << eol;
		#endif
	}
	
	std::string ResourceManager::FindFile(const std::string &pFileName, const std::string &pFileType){
		std::string fileType = pFileType.empty() ? "Generic" : pFileType;
		String filePath;

		for(mLocationsIt = mLocations.begin(); mLocationsIt != mLocations.end(); ++mLocationsIt){
			if(mLocationsIt->first == fileType || fileType == "Generic"){
				filePath = String(mLocationsIt->second)+"/"+pFileName;
				if(File::Exists(filePath))
					return filePath;
			}
		}
		return "0";
	}
}
