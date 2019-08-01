#include "../Utility/SystemUtility.h"

template<class T>
void Archives::MeshCreate() {
	Safe_Delete(meshArchive);
	meshArchive = new T;
}

template<class T>
void Archives::TextureCreate() {
	Safe_Delete(textureArchive);
	textureArchive = new T;
}

template<class T>
void Archives::SoundCreate() {
	Safe_Delete(soundArchive);
	soundArchive = new T;
}

template<class T>
void Archives::ShaderCreate() {
	Safe_Delete(shaderArchive);
	shaderArchive = new T;
}