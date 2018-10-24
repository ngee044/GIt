#pragma once

//d3d클래스를 관리하는 클래스
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

	CameraClass* m_pCamera; //카메라

	DWORD	m_dwMouseX; //마우스 X값
	DWORD	m_dwMouseY; //마우스 Y값

	sKeyInfo*			m_pKeyInfo;
	CharacterClass* m_pCharacter;
	std::vector<CharacterClass*> m_vChart;
	std::map<const int ,CharacterClass*> m_mChart;

	MapClass*	m_pMap;

	D3DXMATRIX m_Scale;
	D3DXMATRIX m_Rot;
	D3DXMATRIX m_Pos;
	float frame;

	LPDIRECT3DDEVICE9 m_pd3dDevice; //디바이스
	float   m_XPos, m_YPos, m_ZPos;			// location coord

	int i,j; //루프

	CD3DFrame();
public:
	static CD3DFrame* Create();
	static void Destroy();	
	static CD3DFrame* Get(); //자기자신을 리턴

	~CD3DFrame();

	//랜더함수를 불러와 랜더링
	void Run();
	void Init();	//초기값 셋팅
	void Update(); //업뎃 셋팅
	void ProcessInput(); //입력값 처리
	int ProcessMouse(void); //마우스값
	int Processkey(void); //키보드값

	//거리구하기
	float Norm(D3DXVECTOR3 vector)
	{
		return(sqrtf(vector.x*vector.x + vector.y*vector.y + vector.z*vector.z));
	}
};