#ifndef SINGLETON_HPP
#define SINGLETON_HPP

#include "Debug/New.hpp"

namespace engine{
	/// \brief Classic Singleton class to store an object pointer in its only instance
    template<class T>
	class Singleton{
        private:
            /// \brief Pointer on object stored by singleton
            static T *mSingleton;

            /// \brief Copy Ctor, forbidden
            Singleton(Singleton &){}

            /// \brief Copy Op, forbidden
            void operator=(Singleton &){}

        protected:
			/// \brief Default Ctor/Dtor, forbidden
            Singleton(){}
            ~Singleton(){}

        public:
            /// \brief Returns a pointer on stored object
            static T* Get(){
                if(mSingleton == 0)
                    mSingleton = new T;
                return (static_cast<T*> (mSingleton));
            }

            /// \brief Returns the reference of stored object
            static T& Call(){
                if(mSingleton == 0)
                    mSingleton = new T;
                return *mSingleton;
            }

            /// \brief Destroy the stored object
            static void Kill(){
                if(mSingleton != 0){
                    delete mSingleton;
                    mSingleton = 0;
                }
            }
	};

    /// Initialisation
    template<class T> T *Singleton<T>::mSingleton = 0;

}
#include "Debug/NewOff.hpp"
#endif
