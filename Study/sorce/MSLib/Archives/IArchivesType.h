#pragma once


#include <map>
#include <string>


namespace MSLib {
	namespace ArchivesCollection {
		template<typename T>
		class IArchivesType {
		public:
			IArchivesType();
			virtual ~IArchivesType();

			T Get(const std::string& _name);

		protected:
			virtual void Create() = 0 {}

			void Add(const std::string& key, T regist);

		protected:
			std::map<std::string, T> archives;
		};

#include "IArchivesType.inl"
	}
}