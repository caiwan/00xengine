#include "Resource.hpp"
#include "ResourceManager.hpp"
#include "Debug/New.hpp"

namespace engine {
	IResource::IResource() : mName(""), mRefCount(1){
	}

	IResource::~IResource(){
		ResourceManager::Call().Remove(mName);
	}

	const std::string &IResource::GetName() const{
		return mName;
	}

	void IResource::SetName(const std::string &pName){
		mName = pName;
	}

	void IResource::AddRef(){
		++mRefCount;
	}

	s32 IResource::Release(){
		s32 RefCount = --mRefCount;
		if(!RefCount)
			delete this;

		return RefCount;
	}
}
