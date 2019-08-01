#pragma once


#include "ArchivesMeshBase.h"
#include "ArchivesTextureBase.h"
#include "ArchivesSoundBase.h"
#include "ArchivesShaderBase.h"
#include "../String/String.h"

namespace MSLib {
	class Archives {
	public:
		Archives();
		virtual ~Archives();

		template<class T>static void MeshCreate();

		template<class T>static void TextureCreate();
		template<class T>static void SoundCreate();
		template<class T>static void ShaderCreate();

		static string Mesh(const string Name);
		static string Texture(const string Name);
		static string Sound(const string Name);
		static string Shader(const string Name);

	private:
		static ArchivesCollection::ArchivesMeshBase* meshArchive;
		static ArchivesCollection::ArchivesTextureBase* textureArchive;
		static ArchivesCollection::ArchivesSoundBase* soundArchive;
		static ArchivesCollection::ArchivesShaderBase* shaderArchive;
	};

#include "Archives.inl"
}