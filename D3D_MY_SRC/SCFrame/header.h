#ifndef HEADER_H
#define HEADER_H
#include <d3d9.h>
#include <d3dx9.h>
#include <windows.h>
#include <stdio.h>
//STL���
#include <vector>
#include <string>

using namespace std;

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define MAPXSIZE 128
#define MAPYSIZE 128
#define MAPSCALE 20

//#define FULLSCREEN
//enum GAMESTATE {START,LOADING,ING,END};
//��ī�̹ڽ�.ť����� ���ؽ�
struct CUSTOMVERTEX
{
	D3DXVECTOR3 point;	/// ������ ��ȯ�� ��ǥ
	D3DXVECTOR3 normal;
	DWORD color;
	FLOAT tu,tv;	/// ������ ����
};

/// ����� ���� ����ü�� ���� ������ ��Ÿ���� FVF��
struct MYINDEX
{
	DWORD	_0, _1, _2;		
};
//��ŷ���� ���� ����� ���� ����ü
struct PICKINGVERTEX
{
	float dist;
	float fbary1;
	float fbary2;
	DWORD face;
};

//������ ��ũ��
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }

//��ü��
#include "CCamera.h"
#include "CFont.h"
#include "CMesh.h"
#include "CSprite.h"
#include "CGameApp.h"

//����� ���� Ŭ���� TODO:
#include "../ASEParser/CDefine.h"
#include "../ASEParser/CMesh.h"
#include "../ASEParser/CGeom.h"
#include "../ASEParser/CAseParser.h"
#include "../CGameMyApp.h"


#endif