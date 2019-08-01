#pragma once


#include "IArchivesType.h"

namespace MSLib {
	namespace ArchivesCollection {
		class ArchivesSoundBase : public IArchivesType<std::string> {
		public:
			ArchivesSoundBase();
			virtual ~ArchivesSoundBase();

		protected:
			virtual void Create() override;
		};
	}
}