#pragma once


#include <map>
#include "../String/String.h"

// NOTE : �����ƃp�X�̕ϊ��@�I�Ȉ���
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