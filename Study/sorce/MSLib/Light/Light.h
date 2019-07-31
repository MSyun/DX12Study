#pragma once


#include "../Math/Math.h"
#include "../Transform/Transform.h"
#include <string>


namespace MSLib {
	class Light {
	public:
		typedef enum eLight_TYPE {
			SPOT_LIGHT,
			DIRECTIONAL_LIGHT,
			POINT_LIGHT,
		} LIGHT_TYPE;

	public:
		Light();
		virtual ~Light();

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

		void SetColor(float _r, float _g, float _b, float _a);
		void SetColor(float _color);
		void SetColor(const Color& _color);
		Color GetColor() const;

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

		Color color;
		LIGHT_TYPE type;
	};
}