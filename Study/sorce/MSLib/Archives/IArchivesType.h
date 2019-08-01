#pragma once


#include <map>
#include "../String/String.h"

// NOTE : 命名とパスの変換機的な扱い
namespace MSLib {
	namespace ArchivesCollection {
		template<typename T>
		class IArchivesType {
		public:
			IArchivesType();
			virtual ~IArchivesType();

			T Get(const string& _name);

		protected:
			virtual void Create() = 0 {}

			void Add(const string& key, T regist);

		protected:
			std::map<string, T> archives;
		};

#include "IArchivesType.inl"
	}
}