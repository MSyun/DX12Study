#pragma once


#include "../Math/Math.h"
#include "../Transform/Transform.h"
#include <string>


namespace MSLib {
	class Camera {
	public:
		Camera();
		virtual ~Camera();

		void SetName(const std::string _name);
		std::string GetName();

		void Set();

		void SetLookLength(float _len);
		void AddLookLength(float _len);

		Matrix GetView() const;
		Matrix GetProjection() const;
		void SetFovy(float _fovy);
		void SetAspect(float _aspect);
		void SetNear(float _near);
		void SetFar(float _far);

		Transform* GetTransform() { return &transform; }

	private:
		std::string name;
		Transform transform;

		// View
		Matrix viewMatrix;
		float lookLength; // íçéãì_Ç‹Ç≈ÇÃãóó£

		// Projection
		Matrix projectionMatrix;
		float fovy;
		float aspect;
		float nearPlane;
		float farPlane;
	};
}