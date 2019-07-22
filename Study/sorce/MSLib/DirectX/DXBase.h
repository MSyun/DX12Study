#pragma once

#include <Windows.h>
#include "../Application/ApplicationBase.h"


namespace MSLib {
	class IDXBase {
	public:
		explicit IDXBase(ApplicationBase* app);
		virtual ~IDXBase();

		virtual HRESULT Initialize();
		virtual HRESULT Step() = 0;
		virtual HRESULT Release();

		virtual HRESULT ChangeWindow();
		virtual void ChangeDisplayMode();

	protected:
		virtual HRESULT InvalidateDeviceObjects();
		virtual HRESULT RestoreDeviceObjects();

		inline ApplicationBase* GetApplication() { return pApp; }

	private:
		ApplicationBase* pApp;
	};
};