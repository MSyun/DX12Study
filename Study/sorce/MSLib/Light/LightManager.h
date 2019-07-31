#pragma once


#include "Light.h"
#include "../Singleton/Singleton.h"
#include <vector>


namespace MSLib {
	class LightManager : public Singleton<LightManager> {
	public:
		LightManager();
		virtual ~LightManager();

		void Regist(Light* _light);
		void Remove(Light* _light);
		Light* Get(const std::string& _name);
		bool Set(const std::string& _name);

	protected:
		std::vector<Light*> lights;
	};

	LightManager* GetLightManager();
}