#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include <map>
#include <string>
#include "Resource.hpp"
#include "Utils/Singleton.hpp"

namespace engine {
	/// \brief Singleton, Keep trace of all IResource inherited instances
	class OOXAPI ResourceManager : public Singleton<ResourceManager> {
		friend class Singleton<ResourceManager>;
	public:
		/// \brief Returns a Resource from its name
		/// \param pName : resource name
		template<class T> T* Get(const std::string &pName) const;

		/// \brief Add a resource to the manager
		/// \param pName     : resource name
		/// \param pResource : resource pointer
		void Add(const std::string &pName, IResource* pResource);

		/// \brief Remove a resource from the manager
		/// \param pName : name of the resource to be removed
		void Remove(const std::string &pName);

		/// \brief Add a resource path
		/// \param pPath     : path to reach the associated file type
		/// \param pFileType : File type associated to the path. Null means the path is for all files
		void AddPath(const std::string &pPath, const std::string &pFileType = "");

		/// \brief Returns the full name (with path) of a resource if found
		/// \param pFileName : asked resource name
		/// \param pFileType : asked resource type. Null means searching il all paths
		std::string FindFile(const std::string &pFileName, const std::string &pFileType = "");

	private:
		typedef std::map<std::string, std::string> LocationMap;
		LocationMap mLocations;									/// Map of resource type associated to their directory path
		LocationMap::iterator mLocationsIt;

		typedef std::map<std::string, IResource*> ResourceMap;
		ResourceMap mResources;									/// Map of resource associated to their name

		/// Private Ctor/Dtor, Singleton
		~ResourceManager();
		ResourceManager();
	};

	template<class T>
	inline T* ResourceManager::Get(const std::string &pName) const{
		ResourceMap::const_iterator it = mResources.find(pName);

		if(it != mResources.end()){
			it->second->AddRef();
			return static_cast<T*>(it->second);
		}else
			return NULL;
	}
}
#endif
