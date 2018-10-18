#include "MainFrame.h"

CMainFrame* CMainFrame::m_pkThis = NULL;
CMainFrame::CMainFrame()
{
	ZeroMemory(&msg,sizeof(msg));
}
CMainFrame::~CMainFrame()
{
}
//����
CMainFrame* CMainFrame::Create(HINSTANCE hInstance)
{
	if(!m_pkThis)
		m_pkThis = new CMainFrame;
	//������ ����
	CWindowFrame::Create(hInstance);
	//d3d ����
	CD3DFrame::Get()->Create();

	return	m_pkThis;
}
//������ �������� ����
void CMainFrame::Destroy()
{
	//d3d ����
	CD3DFrame::Destroy();
	//������ ����
	CWindowFrame::Destroy();
	//����Ʈ�� �ڱ��ڽ��� �ּҸ� �Ѱ��� �� ����
	CMainFrame* pFrame = CMainFrame::Get();

	delete pFrame;
}
//�����������ּҸ���
CMainFrame* CMainFrame::Get()
{
	return m_pkThis;
}
//�޼��������Լ�
int CMainFrame::Run()
{
	while(1)
	{
		 // �޽����� �ִٸ� ó���Ѵ�.
        if( PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) )
        {
            // WM_QUIT �޽��� �߻���, ������ �����.
            if( msg.message == WM_QUIT)
                break;

            // �޽��� ó��.
            TranslateMessage(&msg); // �޽��� ����.
            DispatchMessage(&msg);  // ������ �޽��� ����.
        }
		else
		{
			CD3DFrame::Get()->Run();
		}
	}
	return (int)msg.wParam;
}

