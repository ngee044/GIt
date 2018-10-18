#pragma once

#include "D3DFrame.h"

//d3d 전체관리 클래스 및 윈도우 클래스를 관리하여 최종적으로 출력

class CMainFrame
{
protected:
	MSG msg;
	CMainFrame();
	//메인프레임주소리턴
	static CMainFrame* m_pkThis;

public:
	static CMainFrame* Create(HINSTANCE);
	//생성의 역순으로 삭제
	static void Destroy();
	//자기자신의 주소값 리턴
	static CMainFrame* Get();
	// 프레임 관리 
	float frame;
public:
	~CMainFrame();
	//메세지전달함수
	int Run();
};