#include "MSLib/Application/DXApplication.h"
#include "MSLib/DirectX/Ver12/DX12Base.h"
#include	<crtdbg.h>


MSLib::DXApplication* pApp = nullptr;

int WINAPI WinMain(
	HINSTANCE hIns,
	HINSTANCE hPrevInst,
	LPSTR lpCmdLine,
	int nShowCmd)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	pApp = new MSLib::DXApplication(1280, 720, true);
	pApp->SetDXObj(new MSLib::DX12Base(pApp));
	pApp->Run(hIns);
	delete pApp;

	return 0;
}