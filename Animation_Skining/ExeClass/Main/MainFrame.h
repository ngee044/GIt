#pragma once

#include "D3DFrame.h"

//d3d ��ü���� Ŭ���� �� ������ Ŭ������ �����Ͽ� ���������� ���

class CMainFrame
{
protected:
	MSG msg;
	CMainFrame();
	//�����������ּҸ���
	static CMainFrame* m_pkThis;

public:
	static CMainFrame* Create(HINSTANCE);
	//������ �������� ����
	static void Destroy();
	//�ڱ��ڽ��� �ּҰ� ����
	static CMainFrame* Get();
	// ������ ���� 
	float frame;
public:
	~CMainFrame();
	//�޼��������Լ�
	int Run();
};