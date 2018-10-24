#pragma once

//d3dŬ������ �����ϴ� Ŭ����
#include "Common.h"
#include "Renderer.h"
#include "Camera.h"
#include "CharacterClass.h"
#include "KeyMgr.h"
#include <vector>
#include "MapClass.h"

class CD3DFrame
{
protected:
	static CD3DFrame*				 m_pkThis;

	CameraClass* m_pCamera; //ī�޶�

	DWORD	m_dwMouseX; //���콺 X��
	DWORD	m_dwMouseY; //���콺 Y��

	sKeyInfo*			m_pKeyInfo;
	CharacterClass* m_pCharacter;
	std::vector<CharacterClass*> m_vChart;
	std::map<const int ,CharacterClass*> m_mChart;

	MapClass*	m_pMap;

	D3DXMATRIX m_Scale;
	D3DXMATRIX m_Rot;
	D3DXMATRIX m_Pos;
	float frame;

	LPDIRECT3DDEVICE9 m_pd3dDevice; //����̽�
	float   m_XPos, m_YPos, m_ZPos;			// location coord

	int i,j; //����

	CD3DFrame();
public:
	static CD3DFrame* Create();
	static void Destroy();	
	static CD3DFrame* Get(); //�ڱ��ڽ��� ����

	~CD3DFrame();

	//�����Լ��� �ҷ��� ������
	void Run();
	void Init();	//�ʱⰪ ����
	void Update(); //���� ����
	void ProcessInput(); //�Է°� ó��
	int ProcessMouse(void); //���콺��
	int Processkey(void); //Ű���尪

	//�Ÿ����ϱ�
	float Norm(D3DXVECTOR3 vector)
	{
		return(sqrtf(vector.x*vector.x + vector.y*vector.y + vector.z*vector.z));
	}
};