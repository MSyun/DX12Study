#include "Archives.h"
#include "../Utility/SystemUtility.h"


namespace MSLib {
	ArchivesCollection::ArchivesMeshBase* Archives::meshArchive = nullptr;
	ArchivesCollection::ArchivesTextureBase* Archives::textureArchive = nullptr;
	ArchivesCollection::ArchivesSoundBase* Archives::soundArchive = nullptr;
	ArchivesCollection::ArchivesShaderBase* Archives::shaderArchive = nullptr;

	Archives::Archives() {

	}

	Archives::~Archives() {
		Safe_Delete(meshArchive);
		Safe_Delete(textureArchive);
		Safe_Delete(soundArchive);
		Safe_Delete(shaderArchive);
	}

	string Archives::Mesh(const string Name) {
		if (!meshArchive)	return "";

		return meshArchive->Get(Name);
	}
	string Archives::Texture(const string Name) {
		if (!textureArchive)	return "";

		return textureArchive->Get(Name);
	}
	string Archives::Sound(const string Name) {
		if (!soundArchive)	return "";

		return soundArchive->Get(Name);
	}
	string Archives::Shader(const string Name) {
		if (!shaderArchive)	return "";

		return shaderArchive->Get(Name);
	}
}