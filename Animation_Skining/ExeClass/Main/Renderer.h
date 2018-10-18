#pragma once
#include "Ase.h"
#include "WindowFrame.h"
class CRenderer
{
protected:
	static CRenderer* m_pkThis;
	LPDIRECT3D9 m_pd3d; //��ü
	LPDIRECT3DDEVICE9 m_pd3dDevice; //����̽�
	D3DPRESENT_PARAMETERS m_d3dpp; //d3d����ü
	CRenderer();
public:
	static CRenderer* Create(); //������ CreateDevice �Լ��� ȣ��
	static void Destroy(); //����
	static CRenderer* Get();
	~CRenderer();
protected:
	bool CreateDevice();
public:
	LPDIRECT3DDEVICE9 GetDevice(); //����̽� ��ȯ
	void Run();//���� ������
	void Clear(); //����̽� �����
	void BeginScene();//�׸���
	void EndScene();//����
	void Present();//ȭ�麸�̱�
};