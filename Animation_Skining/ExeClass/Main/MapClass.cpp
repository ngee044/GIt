///////////////////////////////////////////////////////
//ASE 포멧의 맵 파일을 불러오고 출력하는 코드 입니다.//
///////////////////////////////////////////////////////

#include "MapClass.h"
#include "ASE.h"

void MapClass::InitMap(LPDIRECT3DDEVICE9	pDevice,char* MapName,char* AseFileName)
{
	SetDevice(pDevice);
	::strcpy(m_Name,MapName);
	m_pAse=new cBaseAse();
	m_pAse->SetDevice(GetDevice());

	m_pAse->LoadAse(AseFileName);
	m_pAse->m_pTextureContainer=new CTextureContainer;
	m_pAse->LoadAseTexture();

	InitObject();

}

void MapClass::Render()
{
	m_pAse->RenderAse(m_Scale,m_Rot,m_Pos);
}

void MapClass::InitObject()
{
/*
	D3DXVECTOR3 v_0=D3DXVECTOR3(-424.612f,158.483f,827.113f);
	D3DXVECTOR3 v_1=D3DXVECTOR3(424.612f,158.483f,827.113f);
	D3DXVECTOR3 v_2=D3DXVECTOR3(-424.612f,-47.67f,827.113f);
	D3DXVECTOR3 v_3=D3DXVECTOR3(424.612f,-47.67f,827.113f);
	D3DXVECTOR3 v_4=D3DXVECTOR3(-424.612f,-47.67f,-827.113f);
	D3DXVECTOR3 v_5=D3DXVECTOR3(424.612f,-47.67f,-827.113f);
	D3DXVECTOR3 v_6=D3DXVECTOR3(-424.612f,158.483f,-827.113f);
	D3DXVECTOR3 v_7=D3DXVECTOR3(424.612f,158.483f,-827.113f);

	m_pObj= new cMapObject[4];

	m_pObj[0].SetPlane4v(v_0,v_1,v_2,v_3,::D3DXVECTOR3(0.0f,0.0f,-1.0f));
	m_pObj[1].SetPlane4v(v_4,v_5,v_6,v_7,D3DXVECTOR3(0.0f,0.0f,1.0f));
	m_pObj[2].SetPlane4v(v_0,v_2,v_4,v_6,D3DXVECTOR3(1.0f,0.0f,0.0f));
	m_pObj[3].SetPlane4v(v_1,v_3,v_5,v_7,D3DXVECTOR3(-1.0f,0.0f,0.0f));
*/
}