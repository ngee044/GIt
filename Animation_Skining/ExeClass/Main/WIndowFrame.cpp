#include "WindowFrame.h"

CWindowFrame* CWindowFrame::m_pkThis = NULL;

//static 변수 초기화 !!!

CWindowFrame::CWindowFrame()
{ 
	m_hInst = NULL; 
	m_hWnd = NULL; 
}

CWindowFrame* CWindowFrame::Create(HINSTANCE hInst,UINT uiWidth , UINT uiHeight)
{
	if(!m_pkThis)
		m_pkThis = new CWindowFrame;

	CWindowFrame::Get()->Init(hInst,uiWidth,uiHeight);

	return	m_pkThis;
}

void CWindowFrame::Destroy(void)
{
	CWindowFrame* pkWindow = CWindowFrame::Get();

	delete pkWindow;
}

CWindowFrame* CWindowFrame::Get()
{
	return m_pkThis;
}
//윈도우 생성
void CWindowFrame::Init(HINSTANCE hInst,UINT uiWidth,UINT uiHeight)
{
	m_hInst = hInst;
	m_uiWidth = uiWidth;
	m_uiHeight = uiHeight;

	RegisterWindow(hInst);

	HWND hWnd = CreateWindow(TEXT("Game Graphic Programing"),
		TEXT("Game Graphic Programing"),
		WS_OVERLAPPEDWINDOW
		,CW_USEDEFAULT,
		CW_USEDEFAULT,
		m_uiWidth,//속성값은 멤버변수로
		m_uiHeight,
		NULL,(HMENU)NULL,hInst,NULL);

	m_hWnd = hWnd;

	ShowWindow(m_hWnd,1);
   UpdateWindow(hWnd);
}
//윈도우 클래스 설정
void CWindowFrame::RegisterWindow(HINSTANCE hInst)
{
	WNDCLASS WndClass;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(COLOR_WINDOW+1);
	WndClass.hCursor = (HCURSOR)LoadCursor(NULL,IDC_ARROW);
	WndClass.hIcon = (HICON)LoadIcon(NULL,IDI_APPLICATION);
	WndClass.hInstance = hInst;
	WndClass.lpfnWndProc = CWindowFrame::WndProc;
	WndClass.lpszClassName = TEXT("Game Graphic Programing");
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&WndClass);
}
//프록메세지
LRESULT CALLBACK CWindowFrame::WndProc(HWND hWnd,UINT Message,WPARAM wParam,LPARAM lParam)
{
	switch(Message)
	{
	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd,Message,wParam,lParam);
}
void CWindowFrame::Run(MSG* pMsg)
{
	TranslateMessage(pMsg);
	DispatchMessage(pMsg);
}