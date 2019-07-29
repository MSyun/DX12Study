#include "Camera.h"
#include "../Screen/Screen.h"
#include "CameraManager.h"

namespace MSLib {
	Camera::Camera() :
		fovy(60.0f),
		aspect((float)Screen::GetWidth() / (float)Screen::GetHeight()),
		nearPlane(1.0f),
		farPlane(100.0f),
		lookLength(5.0f)
	{
		GetCameraManager()->Regist(this);

		transform.SetPos(0.0f, 0.0f, -5.0f);
		SetName("Camera");
	}

	Camera::~Camera() {
		GetCameraManager()->Remove(this);
	}

	void Camera::SetName(const std::string _name) {
		name = _name;
	}

	std::string Camera::GetName() {
		return name;
	}

	void Camera::Set() {
		MatrixLookAtLH(
			&viewMatrix,
			&transform.GetPos(),
			&(transform.GetPos() + transform.GetForward() * lookLength),
			&transform.GetUp());

		MatrixPerspectiveFovLH(
			&projectionMatrix,
			ToRadian(fovy),
			aspect,
			nearPlane,
			farPlane);
	}

	void Camera::SetLookLength(float _len) {
		lookLength = _len;
	}

	void Camera::AddLookLength(float _len) {
		lookLength += _len;
	}

	Matrix Camera::GetView() const {
		return viewMatrix;
	}

	Matrix Camera::GetProjection() const {
		return projectionMatrix;
	}

	void Camera::SetFovy(float _fovy) {
		fovy = _fovy;
	}

	void Camera::SetAspect(float _aspect) {
		aspect = _aspect;
	}

	void Camera::SetNear(float _near) {
		nearPlane = _near;
	}

	void Camera::SetFar(float _far) {
		farPlane = _far;
	}
}