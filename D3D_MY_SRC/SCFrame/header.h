#ifndef HEADER_H
#define HEADER_H
#include <d3d9.h>
#include <d3dx9.h>
#include <windows.h>
#include <stdio.h>
//STL사용
#include <vector>
#include <string>

using namespace std;

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define MAPXSIZE 128
#define MAPYSIZE 128
#define MAPSCALE 20

//#define FULLSCREEN
//enum GAMESTATE {START,LOADING,ING,END};
//스카이박스.큐브등의 버텍스
struct CUSTOMVERTEX
{
	D3DXVECTOR3 point;	/// 정점의 변환된 좌표
	D3DXVECTOR3 normal;
	DWORD color;
	FLOAT tu,tv;	/// 정점의 색깔
};

/// 사용자 정점 구조체에 관한 정보를 나타내는 FVF값
struct MYINDEX
{
	DWORD	_0, _1, _2;		
};
//피킹에서 나온 결과를 담을 구조체
struct PICKINGVERTEX
{
	float dist;
	float fbary1;
	float fbary2;
	DWORD face;
};

//간단한 메크로
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }

//객체들
#include "CCamera.h"
#include "CFont.h"
#include "CMesh.h"
#include "CSprite.h"
#include "CGameApp.h"

//사용자 정의 클래스 TODO:
#include "../ASEParser/CDefine.h"
#include "../ASEParser/CMesh.h"
#include "../ASEParser/CGeom.h"
#include "../ASEParser/CAseParser.h"
#include "../CGameMyApp.h"


#endif