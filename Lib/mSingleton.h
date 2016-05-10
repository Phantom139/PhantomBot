/*
 managedSingleton is a class based on the design of the boost library singleton class (boost::singleton). This class allows you to define a single "instance" class that is specific to the entire engine, IE: only one instance of this class can everbe defined. To define a managedSingleton, the syntax is: managedSingleton<Class>::createInstance(); It is also recommended to define a static UTF16 getInstanceName() method in managedSingleton classes for organization and identification by name.
*/

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
