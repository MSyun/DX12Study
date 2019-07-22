#pragma once


#include <Windows.h>


namespace MSLib {

	class ApplicationBase
	{
	public:
		ApplicationBase(
			int width = 600,
			int height = 480,
			bool isWindow = true);
		virtual ~ApplicationBase();

		bool Run(HINSTANCE _hInstance);

		static LRESULT CALLBACK WndProc(
			HWND _hWnd,
			UINT _msg,
			WPARAM _wParam,
			LPARAM _lParam);

		virtual LRESULT LocalWindowProc(
			HWND _hWnd,
			UINT _msg,
			WPARAM _wParam,
			LPARAM _lParam);

		static void End();

		inline HWND GetHWND();

	private:
		bool RegistWndClass();
		bool CreateMainWnd();

	protected:
		virtual void SettingWndClass();
		virtual void SettingMainWindow();
		virtual bool Initialize();
		virtual void Loop();
		virtual void Release();

	protected:
		HINSTANCE hInstance;
		WNDCLASSEX wndClassEx;
		CREATESTRUCT createStruct;
		HWND hWnd;
	};
}