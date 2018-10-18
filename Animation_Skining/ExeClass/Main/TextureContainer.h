///////////////////////////////////////////////////////////
//3D모델링 파일의 텍스쳐를 저장하는 컨테이너 코드 입니다.//
///////////////////////////////////////////////////////////
#pragma once
#include "Common.h"

struct STextureList
{

	LPDIRECT3DTEXTURE9 m_pTexture;
	char* m_szName;
	int m_Count;

	STextureList* m_pPrev;
	STextureList* m_pNext;

	STextureList();
	~STextureList();
};
class CTextureContainer  
{
public:
	STextureList* m_pHead;            // list
	STextureList* m_pTail;

	void ReleaseAll();

	CTextureContainer();
	virtual ~CTextureContainer();

	STextureList* LoadTexture(LPDIRECT3DDEVICE9 pDevice, char* Name, bool bMipMap= true);
	STextureList* Search(LPDIRECT3DTEXTURE9 pTexture);
	STextureList* Search(char* Name);
	void Delete(LPDIRECT3DTEXTURE9 pTexture);

protected:
	bool Add(STextureList*);
};