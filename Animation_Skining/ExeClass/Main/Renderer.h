#pragma once
#include "Ase.h"
#include "WindowFrame.h"
class CRenderer
{
protected:
	static CRenderer* m_pkThis;
	LPDIRECT3D9 m_pd3d; //객체
	LPDIRECT3DDEVICE9 m_pd3dDevice; //디바이스
	D3DPRESENT_PARAMETERS m_d3dpp; //d3d구조체
	CRenderer();
public:
	static CRenderer* Create(); //생성자 CreateDevice 함수를 호출
	static void Destroy(); //삭제
	static CRenderer* Get();
	~CRenderer();
protected:
	bool CreateDevice();
public:
	LPDIRECT3DDEVICE9 GetDevice(); //디바이스 반환
	void Run();//실제 랜더링
	void Clear(); //디바이스 지우고
	void BeginScene();//그리고
	void EndScene();//종료
	void Present();//화면보이기
};