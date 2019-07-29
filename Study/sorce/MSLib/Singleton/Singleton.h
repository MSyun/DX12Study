#pragma once


//Ql:GameProgrammingGems

namespace MSLib {
	template<typename T> class Singleton {
	protected:
		static T* ms_pInstance;

	public:
		Singleton() {
			//		assert( !ms_pInstance );
			int offset = (int)(T*)1 - (int)(Singleton<T>*)(T*)1;
			ms_pInstance = (T*)(((int)this) + offset);
		}

		~Singleton() {
			//		assert( ms_pInstance );
			ms_pInstance = 0;
		}

		static T* Instance(void) {
			return ms_pInstance;
		}
	};

	// ‰Šú‰»
	template<typename T> T* Singleton<T>::ms_pInstance = 0;

}