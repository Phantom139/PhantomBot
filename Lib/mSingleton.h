/**
	mSingleton.h
	PhantomBot Project
	By: Robert F. (Phantom139)
**/

#ifndef _MANAGEDSINGLETON_H
#define _MANAGEDSINGLETON_H

template <typename T> class managedSingleton {
	public:
		static void createInstance() {
			if(mSingleton != NULL) {
				//ToDo: Throw an assert error here
				return;
			}
			mSingleton = new T();
		}

		static void destroyInstance() {
			if(mSingleton == NULL) {
				return;
			}
			SendToHell(mSingleton);
		}

		static const char * getInstanceName() {
			return "UNNAMED_SINGLETON_INSTACE";
		}

		static T* instance() {
			return mSingleton ? mSingleton : NULL;
		}

	private:
		static T* mSingleton;

};
template <typename T> T* managedSingleton<T>::mSingleton = NULL;

#endif //_MANAGEDSINGLETON_H
