#ifndef SPOINTER_HPP
#define SPOINTER_HPP

#include "SPointerPolicies.hpp"
#include "Debug/New.hpp"

namespace engine {
	/// \brief Smart Pointer class used to limit and ease the use of real pointers
	template <class T, template<class> class Ownership = RefCountPolicy>
	class SPointer : public Ownership<T>{
	protected:
		T* Ptr;

	public:
		/// \brief Ctor, Null init
		SPointer() : Ptr(NULL){
		}	

		/// \brief Ctor, Copy of another SPointer
		SPointer(const SPointer<T> &P) : Ownership<T>(P), 
									     Ptr(Clone(P.Ptr)){
		}	

		/// \brief Ctor, Pointer init
		SPointer( T* obj ) : Ptr(obj){
		}							

		/// \brief Dtor, release an instance of the stored pointer if it exists
		~SPointer(){ 
			Kill();
		}								

		/// \brief Release an instance of the stored pointer if it exists
		void Kill(){ 
			Release(Ptr);
		}								
		
		/// \brief Returns the content of stored pointer
		T& operator*() const { return *Ptr; }			

		/// \brief Returns the stored pointer
		T* operator->() const { return Ptr; }			

		/// \brief Returns the stored pointer
		operator T*() const { return Ptr; }						

		/// \brief Returns the stored pointer
		T* Get() { return Ptr; }

		/// \brief Internally used function to swap two pointers and their policy
		void Swap(SPointer &P){									
			Ownership<T>::Swap(P);								
			std::swap(Ptr, P.Ptr);								
		}

		/// \brief Returns a copy of this SPointer and its policy
		SPointer& Copy(){
			Ptr = Clone(Ptr);
			return *this;
		}

		/// \brief Copy operator, add a reference to policy
		SPointer& operator=(const SPointer &P){					
			SPointer<T, Ownership>(P).Swap(*this);
			return *this;
		}

		/// \brief Assign operator
		SPointer& operator=(T* obj){							
			if(Ptr != obj)
				SPointer<T, Ownership>(obj).Swap(*this);
			return *this;
		}

		/// \brief Returns true if stored pointer is null
		bool operator!() { return Ptr == NULL; }					
	};
	
	#include "Debug/NewOff.hpp"
} 
#endif
