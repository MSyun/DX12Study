#pragma once


#include <vector>
#include "Camera.h"
#include "../Singleton/Singleton.h"


namespace MSLib {
	class CameraManager : public Singleton<CameraManager> {
	public:
		CameraManager();
		virtual ~CameraManager();

		void Regist(Camera* camera);
		void Remove(Camera* camera);
		Camera* Get(const std::string& name);
		bool Set(const std::string& name);
		Camera* CurrentCamera();

	protected:
		std::vector<Camera*> cameras;
		std::string currentCameraName;
	};

	CameraManager* GetCameraManager();
}