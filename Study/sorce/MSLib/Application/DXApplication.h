#pragma once


#include "ApplicationBase.h"
#include "../DirectX/DXBase.h"


namespace MSLib {
	class DXApplication : public ApplicationBase {
	public:
		DXApplication(
			int width = 600,
			int height = 480,
			bool isWindow = true);
		virtual ~DXApplication();

		void SetDXObj(IDXBase* _obj);

		virtual LRESULT LocalWindowProc(
			HWND _hWnd,
			UINT _msg,
			WPARAM _wParam,
			LPARAM _lParam) override;

	protected:
		virtual void SettingMainWindow() override;
		virtual bool Initialize() override;
		virtual void Loop() override;
		virtual void Release() override;

	protected:
		IDXBase* pDxObj;
	};
}