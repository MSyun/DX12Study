#include "LightManager.h"


namespace MSLib {
	LightManager::LightManager() {
		lights.resize(10);
		lights.clear();
	}

	LightManager::~LightManager() {
		lights.clear();
	}

	void LightManager::Regist(Light* _light) {
		if (_light == nullptr)
			return;

		lights.push_back(_light);
	}

	void LightManager::Remove(Light* _light) {
		for (auto it = lights.begin(); it != lights.end(); ++it) {
			if ((*it) == _light) {
				lights.erase(it);
				return;
			}
		}
	}

	Light* LightManager::Get(const std::string& _name) {
		if (_name.empty())
			return nullptr;

		for (auto it = lights.begin(); it != lights.end(); ++it) {
			if ((*it)->GetName() == _name)
				return (*it);
		}

		return nullptr;
	}

	bool LightManager::Set(const std::string& _name) {
		Light* light = Get(_name);
		if (light == nullptr)
			return false;

		light->Set();
		return true;
	}

	LightManager* GetLightManager() {
		return LightManager::Instance();
	}
}