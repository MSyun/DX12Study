#pragma once


#include "IArchivesType.h"


namespace MSLib {
	namespace ArchivesCollection {
		class ArchivesTextureBase : public IArchivesType<std::string> {
		public:
			ArchivesTextureBase();
			virtual ~ArchivesTextureBase();

		protected:
			virtual void Create() override;
		};
	}
}