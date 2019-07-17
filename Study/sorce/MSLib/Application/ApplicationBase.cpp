#include "ApplicationBase.h"
#include "../Screen/Screen.h"
#include <tchar.h>


namespace MSLib {

	ApplicationBase* pApp = nullptr;

	constexpr LPCTSTR ClassName = _T("ClassName");

	HWND ApplicationBase::hWnd = NULL;


	ApplicationBase::ApplicationBase(
		int width,
		int height,
		bool isWindow)
	{
		pApp = this;
		Screen::SetSize(width, height);
		Screen::SetFullScreen(!isWindow);
	}

	ApplicationBase::~ApplicationBase() {

	}

	LRESULT CALLBACK ApplicationBase::WndProc(
		HWND _hWnd,
		UINT _msg,
		WPARAM _wParam,
		LPARAM _lParam)
	{
		return pApp->LocalWindowProc(_hWnd, _msg, _wParam, _lParam);
	}

	LRESULT ApplicationBase::LocalWindowProc(
		HWND _hWnd,
		UINT _msg,
		WPARAM _wParam,
		LPARAM _lParam)
	{
		switch (_msg) {
		case WM_CLOSE:
			DestroyWindow(_hWnd);
			break;

		default:
			return DefWindowProc(_hWnd, _msg, _wParam, _lParam);
		}
		
		return 0;
	}

	bool ApplicationBase::Run(HINSTANCE _hInstance) {
		if (!_hInstance)
			return false;

		this->hInstance = _hInstance;

		if (!this->RegistWndClass())
			return false;

		if (!this->CreateMainWnd())
			return false;

		if (!this->Initialize())
			return false;

		this->Loop();
		this->Release();

		return true;
	}

	bool ApplicationBase::RegistWndClass() {
		this->SettingWndClass();

		if (!RegisterClassEx(&this->wndClassEx)) {
			MessageBox(
				NULL,
				_T("Call to RegisterClassEx failed!"),
				_T("Failed Create WindowClass"),
				NULL);
			return false;
		}

		return true;
	}

	void ApplicationBase::SettingWndClass() {
		this->wndClassEx.cbSize = sizeof(WNDCLASSEX);
		this->wndClassEx.style = CS_HREDRAW | CS_VREDRAW;
		this->wndClassEx.lpfnWndProc = pApp->WndProc;
		this->wndClassEx.cbClsExtra = 0;
		this->wndClassEx.cbWndExtra = 0;
		this->wndClassEx.hInstance = this->hInstance;
		this->wndClassEx.hIcon = NULL;
		this->wndClassEx.hCursor = LoadCursor(NULL, IDC_ARROW);
		this->wndClassEx.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		this->wndClassEx.lpszMenuName = NULL;
		this->wndClassEx.lpszClassName = ClassName;
		this->wndClassEx.hIconSm = NULL;
	}

	bool ApplicationBase::CreateMainWnd() {
		this->createStruct.hInstance = this->hInstance;
		this->createStruct.lpszClass = ClassName;

		this->SettingMainWindow();

		this->hWnd = CreateWindowEx(
			this->createStruct.dwExStyle,
			this->createStruct.lpszClass,
			this->createStruct.lpszName,
			this->createStruct.style,
			this->createStruct.x,
			this->createStruct.y,
			this->createStruct.cx,
			this->createStruct.cy,
			this->createStruct.hwndParent,
			this->createStruct.hMenu,
			this->createStruct.hInstance,
			this->createStruct.lpCreateParams);

		if (!this->hWnd) {
			MessageBox(
				NULL,
				_T("Call to CreateWindow failed!"),
				_T("Failed Create WindowHundle"),
				NULL);
			return false;
		}

		return true;
	}

	void ApplicationBase::SettingMainWindow() {
		RECT rect;

		HWND hWnd = GetDesktopWindow();
		GetWindowRect(hWnd, &rect);

		int width = Screen::GetWidth();
		int height = Screen::GetHeight();
		int systemMatrics = GetSystemMetrics(SM_CXDLGFRAME);

		this->createStruct.dwExStyle = 0;
		this->createStruct.lpszName = _T("Base");
		this->createStruct.style = WS_OVERLAPPEDWINDOW;
		this->createStruct.x = (int)(rect.right * 0.5 - width * 0.5);
		this->createStruct.y = (int)(rect.bottom * 0.5 - height * 0.5);
		this->createStruct.cx = (width + systemMatrics * 2);
		this->createStruct.cy = (height + systemMatrics * 2 + GetSystemMetrics(SM_CYCAPTION));
		this->createStruct.hwndParent = NULL;
		this->createStruct.hMenu = NULL;
		this->createStruct.lpCreateParams = NULL;
	}

	bool ApplicationBase::Initialize() {
		if (!ShowWindow(this->hWnd, SW_SHOWNORMAL))
			return false;

		if (!UpdateWindow(this->hWnd))
			return false;

		return true;
	}

	void ApplicationBase::Loop() {
		MSG msg;

		while (GetMessage(&msg, NULL, 0, 0)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	void ApplicationBase::Release() {
		UnregisterClass(ClassName, this->wndClassEx.hInstance);
	}

	void ApplicationBase::End() {
		DestroyWindow(hWnd);
	}
}