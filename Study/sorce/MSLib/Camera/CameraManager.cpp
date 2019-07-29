#include "CameraManager.h"


namespace MSLib {
	CameraManager::CameraManager() :
		currentCameraName("")
	{
		cameras.resize(4);
		cameras.clear();
	}

	CameraManager::~CameraManager() {
		cameras.clear();
		currentCameraName.clear();
	}

	void CameraManager::Regist(Camera* camera) {
		if (camera == nullptr) {
			return;
		}

		cameras.push_back(camera);
	}

	void CameraManager::Remove(Camera* camera) {
		for (auto it = cameras.begin(); it != cameras.end(); ++it) {
			if ((*it) == camera) {
				cameras.erase(it);
				return;
			}
		}
	}

	Camera* CameraManager::Get(const std::string& name) {
		if (name.empty()) {
			return nullptr;
		}

		for (auto it = cameras.begin(); it != cameras.end(); ++it) {
			if ((*it)->GetName() == name)
				return (*it);
		}

		return nullptr;
	}

	bool CameraManager::Set(const std::string& name) {
		Camera* camera = Get(name);
		if (camera == nullptr) {
			return false;
		}

		camera->Set();
		currentCameraName = name;
		return true;
	}

	Camera* CameraManager::CurrentCamera() {
		return Get(currentCameraName);
	}

	CameraManager* GetCameraManager() {
		return CameraManager::Instance();
	}
}