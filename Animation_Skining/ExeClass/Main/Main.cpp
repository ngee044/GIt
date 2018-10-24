#include "MainFrame.h"

INT WINAPI WinMain(HINSTANCE hInstance,HINSTANCE,LPSTR,int)
{
	int iExitCode = 0;

	//생성
	CMainFrame::Create(hInstance);

	CMainFrame::Get()->CreateDxShow();
	//에러코드리턴
	iExitCode = CMainFrame::Get()->Run();

	//삭제
	CMainFrame::Destroy();

	return iExitCode;
}

//LRESULT CALLBACK WndProc(HWND hWnd,UINT Message,WPARAM wParam,LPARAM lParam);
//싱글턴 클래스는 어디서든 접근가능
//하나의 클래스를 한곳에서 생성만 하면 다른곳에서도 접근하게됨.
//정보를 공유 시킬수 있는 방법의 하나
//컨트롤 정보에 대해 공유시킬수 있지않을까...?