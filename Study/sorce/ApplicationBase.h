#pragma once


#include <Windows.h>


LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

class ApplicationBase
{
//public:
//	ApplicationBase();
//	virtual ~ApplicationBase();
//
//	int Run(HINSTANCE _hInstance);
//	virtual LRESULT LocalWindowProc(
//		HWND _hWnd,
//		UINT _msg,
//		WPARAM _wParam,
//		LPARAM _lParam);
//
//private:
//	virtual bool RegistWndClass();
//	virtual bool CreateMainWnd();
//
//protected:
//	virtual void PreWndClass();
//	virtual void PreCreate();
//	virtual bool Initialize();
//	virtual void Loop();
//	virtual void ReleaseApp();
//
//protected:
//	HINSTANCE hInstance;
//	WNDCLASSEX wndClassEx;
//	CREATESTRUCT createStruct;
//	HWND hWnd;
//	bool isWindow;
//	int windowWidth;
//	int windowHeight;
};