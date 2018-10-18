#include "MainFrame.h"

CMainFrame* CMainFrame::m_pkThis = NULL;
CMainFrame::CMainFrame()
{
	ZeroMemory(&msg,sizeof(msg));
}
CMainFrame::~CMainFrame()
{
}
//생성
CMainFrame* CMainFrame::Create(HINSTANCE hInstance)
{
	if(!m_pkThis)
		m_pkThis = new CMainFrame;
	//윈도우 생성
	CWindowFrame::Create(hInstance);
	//d3d 생성
	CD3DFrame::Get()->Create();

	return	m_pkThis;
}
//생성의 역순으로 삭제
void CMainFrame::Destroy()
{
	//d3d 삭제
	CD3DFrame::Destroy();
	//윈도우 삭제
	CWindowFrame::Destroy();
	//포인트로 자기자신의 주소를 넘겨준 후 삭제
	CMainFrame* pFrame = CMainFrame::Get();

	delete pFrame;
}
//메인프레임주소리턴
CMainFrame* CMainFrame::Get()
{
	return m_pkThis;
}
//메세지전달함수
int CMainFrame::Run()
{
	while(1)
	{
		 // 메시지가 있다면 처리한다.
        if( PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) )
        {
            // WM_QUIT 메시지 발생시, 루프를 벗어난다.
            if( msg.message == WM_QUIT)
                break;

            // 메시지 처리.
            TranslateMessage(&msg); // 메시지 번역.
            DispatchMessage(&msg);  // 번역된 메시지 전달.
        }
		else
		{
			CD3DFrame::Get()->Run();
		}
	}
	return (int)msg.wParam;
}

