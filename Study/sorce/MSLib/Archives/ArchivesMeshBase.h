#pragma once

#include "IArchivesType.h"


namespace MSLib {
	namespace ArchivesCollection {
		class ArchivesMeshBase : public IArchivesType<std::string> {
		public:
			ArchivesMeshBase();
			virtual ~ArchivesMeshBase();

		protected:
			virtual void Create() override;
		};
	}
}