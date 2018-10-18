#include <windows.h>
#include "ManagerHeader.h"

INT WINAPI WinMain(HINSTANCE _hInstance, HINSTANCE _h, LPSTR _lpstr, INT _int)//½ÃÀÛÁ¡
{
	WinMgr *pWinMgr = WinMgr::Instance();

	pWinMgr->CreatWindows_Main(_hInstance, _h, _lpstr, _int);

	delete pWinMgr;
}

