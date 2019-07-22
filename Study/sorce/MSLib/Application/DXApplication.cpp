#include "DXApplication.h"
#include "../Screen/Screen.h"
#include <tchar.h>


namespace MSLib {
	DXApplication::DXApplication(
		int width,
		int height,
		bool isWindow) :
		pDxObj(nullptr),
		ApplicationBase(width, height, isWindow)
	{

	}

	DXApplication::~DXApplication() {

	}

	void DXApplication::SetDXObj(IDXBase* _obj) {
		pDxObj = _obj;
	}

	LRESULT DXApplication::LocalWindowProc(
		HWND _hWnd,
		UINT _msg,
		WPARAM _wParam,
		LPARAM _lParam)
	{
		switch (_msg) {
		case WM_KEYDOWN:
			switch (_wParam) {
			case VK_ESCAPE:
				DestroyWindow(_hWnd);
				break;
			}
			break;

			//----- Alt + 特殊キー
		case WM_SYSKEYDOWN:
			switch (_wParam) {
			case VK_RETURN:	// Alt + Enterを押すと切り替え
	//			m_pDXObj->ChangeDisplayMode();
				break;

			case VK_SHIFT:
				//			m_pSnap->Snap( "Snap.png", m_bWindow );

			default:
				break;
			}

			//----- サイズ変更
		case WM_SIZE:
			//if (m_D3Dpp.Windowed != TRUE)
			//	break;

			//if (!m_pD3DDevice || wParam == SIZE_MINIMIZED)
			//	break;
			//m_D3Dpp.BackBufferWidth  = LOWORD(lParam);
			//m_D3Dpp.BackBufferHeight = HIWORD(lParam);
			//if(m_bDeviceLost)
			//	break;
			//if (wParam == SIZE_MAXIMIZED || wParam == SIZE_RESTORED)
			//	ChangeWindowSize();
			break;

			//----- デストロ～イ
		case WM_DESTROY:
			// DirectX Graphicsの終了処理
			PostQuitMessage(0);
			hWnd = NULL;
			break;


		case WM_ACTIVATE:
			//		m_bActive = (LOWORD(wParam) != 0 );
			break;

		default:
			return ApplicationBase::LocalWindowProc(_hWnd, _msg, _wParam, _lParam);
			break;
		}
		return 0;
	}

	void DXApplication::SettingMainWindow() {
		RECT rect;

		HWND hWnd = GetDesktopWindow();
		GetWindowRect(hWnd, &rect);

		int width = Screen::GetWidth();
		int height = Screen::GetHeight();
		int systemMatrics = GetSystemMetrics(SM_CXDLGFRAME);

		this->createStruct.dwExStyle = 0;
		this->createStruct.lpszName = _T("DirectX12Application");
		this->createStruct.style = !Screen::GetIsFullScreen() ? WS_OVERLAPPEDWINDOW | WS_VISIBLE : WS_POPUP | WS_VISIBLE;
		this->createStruct.x = (int)(rect.right * 0.5 - width * 0.5);
		this->createStruct.y = (int)(rect.bottom * 0.5 - height * 0.5);
		this->createStruct.cx = (width + systemMatrics * 2);
		this->createStruct.cy = (height + systemMatrics * 2 + GetSystemMetrics(SM_CYCAPTION));
		this->createStruct.hwndParent = nullptr;
		this->createStruct.hMenu = nullptr;
		this->createStruct.lpCreateParams = nullptr;
	}

	bool DXApplication::Initialize() {
		if (pDxObj) {
			if (FAILED(pDxObj->Initialize()))
				return false;
		}

		if (!ApplicationBase::Initialize())
			return false;

		return true;
	}

	void DXApplication::Loop() {
		MSG msg;
		ZeroMemory(&msg, sizeof(msg));

		if (!pDxObj)
			return;

		while (msg.message != WM_QUIT) {
			if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else {
				if (FAILED(pDxObj->Step()))
					break;
			}
		}
	}

	void DXApplication::Release() {
		if (pDxObj) {
			delete pDxObj;
			pDxObj = nullptr;
		}

		ApplicationBase::Release();
	}
}