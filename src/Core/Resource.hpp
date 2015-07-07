#ifndef RESOURCE_HPP
#define RESOURCE_HPP

#include <string>
#include "Utils/Shared.hpp"

namespace engine {
	/// \brief Interface for any resource type
	class OOXAPI IResource{
	public:
		IResource();

		/// \brief Can't instantiate class
		virtual ~IResource() = 0;

		/// \brief Returns the resource name
		const std::string &GetName() const;

		/// \brief Set the resource name
		void SetName(const std::string &pName);

		/// \brief Add a reference
		void AddRef();

		/// \brief Release a reference
		s32 Release();

	protected:

		std::string mName;	/// Resource Name
		s32 mRefCount;		/// References number on this resource
	};
}
#endif			
