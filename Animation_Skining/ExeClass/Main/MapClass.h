///////////////////////////////////////////////////////
//ASE 포멧의 맵 파일을 불러오고 출력하는 코드 입니다.//
///////////////////////////////////////////////////////
#pragma once
#include "Common.h"

class cBaseAse;

class MapClass
{
public:
	LPDIRECT3DDEVICE9	m_pDevice;
////////////////////////////////////////////
	cBaseAse*	m_pAse;
//	cMapObject* m_pObj;
////////////////////////////////////////////
	char	m_Name[128];

	D3DXMATRIX m_Scale;

	D3DXMATRIX m_Rot;

	D3DXMATRIX m_Pos;

	MapClass()
	{
		m_pDevice=NULL;
		m_pAse=NULL;
		::D3DXMatrixIdentity(&m_Scale);
		::D3DXMatrixIdentity(&m_Rot);
		::D3DXMatrixIdentity(&m_Pos);
	};
	~MapClass(){};

	void InitMap(LPDIRECT3DDEVICE9	pDevice,char* MapName,char* AseFileName);

	void InitObject();


	void Render();

	void SetDevice(LPDIRECT3DDEVICE9 pDevice){m_pDevice=pDevice;};
	LPDIRECT3DDEVICE9 GetDevice(){return m_pDevice;};
};
