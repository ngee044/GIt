#include "MainFrame.h"

INT WINAPI WinMain(HINSTANCE hInstance,HINSTANCE,LPSTR,int)
{
	int iExitCode = 0;

	//����
	CMainFrame::Create(hInstance);

	CMainFrame::Get()->CreateDxShow();
	//�����ڵ帮��
	iExitCode = CMainFrame::Get()->Run();

	//����
	CMainFrame::Destroy();

	return iExitCode;
}

//LRESULT CALLBACK WndProc(HWND hWnd,UINT Message,WPARAM wParam,LPARAM lParam);
//�̱��� Ŭ������ ��𼭵� ���ٰ���
//�ϳ��� Ŭ������ �Ѱ����� ������ �ϸ� �ٸ��������� �����ϰԵ�.
//������ ���� ��ų�� �ִ� ����� �ϳ�
//��Ʈ�� ������ ���� ������ų�� ����������...?