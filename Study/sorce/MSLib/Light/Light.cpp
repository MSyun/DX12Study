#include "Light.h"
#include "../Screen/Screen.h"
#include "LightManager.h"

namespace MSLib {
	Light::Light() :
		lookLength(10.0f),
		fovy(60.0f),
		aspect((float)Screen::GetWidth() / (float)Screen::GetHeight()),
		nearPlane(1.0f),
		farPlane(10.0f),
		color(1.0f, 1.0f, 1.0f, 1.0f),
		type(DIRECTIONAL_LIGHT)
	{
		GetLightManager()->Regist(this);

		MatrixIdentity(&viewMatrix);
		MatrixIdentity(&projectionMatrix);

		SetName("Light");
		Transform* trans = GetTransform();
		trans->SetPos(0.0f, 10.0f, 0.0f);
		trans->Rotate(0.0f, -90.0f, 0.0f);
	}

	Light::~Light() {
		GetLightManager()->Remove(this);
	}

	void Light::SetName(const std::string _name) {
		name = _name;
	}

	std::string Light::GetName() {
		return name;
	}

	void Light::Set() {
		Point3 pos = transform.GetPos();
		MatrixLookAtLH(
			&viewMatrix,
			&pos,
			&(pos + transform.GetForward() * lookLength),
			&transform.GetUp());

		MatrixPerspectiveFovLH(
			&projectionMatrix,
			ToRadian(fovy),
			aspect,
			nearPlane,
			farPlane);
	}

	void Light::SetLookLength(float _len) {
		lookLength = _len;
	}

	void Light::AddLookLength(float _len) {
		lookLength += _len;
	}

	Matrix Light::GetView() const {
		return viewMatrix;
	}

	Matrix Light::GetProjection() const {
		return projectionMatrix;
	}

	void Light::SetFovy(float _fovy) {
		fovy = _fovy;
	}

	void Light::SetAspect(float _aspect) {
		aspect = _aspect;
	}

	void Light::SetNear(float _near) {
		nearPlane = _near;
	}

	void Light::SetFar(float _far) {
		farPlane = _far;
	}

	void Light::SetColor(float _r, float _g, float _b, float _a) {
		color.r = _r;
		color.g = _g;
		color.b = _b;
		color.a = _a;
	}

	void Light::SetColor(float _color) {
		color.r = color.g = color.b = _color;
	}

	void Light::SetColor(const Color& _color) {
		color = _color;
	}

	Color Light::GetColor() const {
		return color;
	}
}