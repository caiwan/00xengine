#ifndef SPOINTERPOLICIES_HPP
#define SPOINTERPOLICIES_HPP

#include <cstdlib>
#include "Debug/New.hpp"

namespace engine {
	/// \brief Reference counting policy
	template<class T>
	class RefCountPolicy{
	public:
		RefCountPolicy() : mCounter(new int(1)) {}

		/// \brief Add a reference
		T* Clone(T* pPtr){
			++*mCounter;
			return pPtr;
		}

		/// \brief Substract a reference, and delete pointer if needed
		void Release(T* pPtr){
			if(--*mCounter == 0){
				delete mCounter;
				delete pPtr;
			}
		}

		/// \brief Swap two Refcount policies
		void Swap(RefCountPolicy &pRefCount){
			std::swap(pRefCount.mCounter, mCounter);
		}

	private:
		int* mCounter;
	};

	/// \brief Resource-Type counting policy
	template<class T>
	class ResourceTypePolicy{
	public:
		/// \brief Add a reference to resource
		T* Clone(T* pPtr){
			if(pPtr)
				pPtr->AddRef();
			return pPtr;
		}

		/// \brief Release a reference to resource
		static void Release(T* pPtr){
			if(pPtr)
				pPtr->Release();
		}

		/// \brief Swap. Do nothing
		void Swap(ResourceTypePolicy &p){
		}
	};
	#include "Debug/NewOff.hpp"
}
#endif
