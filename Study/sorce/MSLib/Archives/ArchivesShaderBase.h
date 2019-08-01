#pragma once


#include "IArchivesType.h"

namespace MSLib {
	namespace ArchivesCollection {
		class ArchivesShaderBase : public IArchivesType<std::string> {
		public:
			ArchivesShaderBase();
			virtual ~ArchivesShaderBase();

		protected:
			virtual void Create() override;
		};
	}
}