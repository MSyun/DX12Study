#include <Windows.h>
#include <tchar.h>
#include "MSLib/Application/ApplicationBase.h"

MSLib::ApplicationBase* pApp = nullptr;

int WINAPI WinMain(HINSTANCE hIns, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nShowCmd) {

	pApp = new MSLib::ApplicationBase(1280, 720, true);
	pApp->Run(hIns);
	delete pApp;

	return 0;
}