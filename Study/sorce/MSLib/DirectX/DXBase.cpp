#include "../DirectX/DXBase.h"



namespace MSLib {
	IDXBase::IDXBase(ApplicationBase* app) :
		pApp(app)
	{

	}

	IDXBase::~IDXBase() {

	}

	HRESULT IDXBase::Initialize() {
		return S_OK;
	}

	HRESULT IDXBase::Step() {
		return S_OK;
	}

	HRESULT IDXBase::Release() {
		return S_OK;
	}

	HRESULT IDXBase::ChangeWindow() {
		return S_OK;
	}

	void IDXBase::ChangeDisplayMode() {

	}

	HRESULT IDXBase::InvalidateDeviceObjects() {
		return S_OK;
	}

	HRESULT IDXBase::RestoreDeviceObjects() {
		return S_OK;
	}
}