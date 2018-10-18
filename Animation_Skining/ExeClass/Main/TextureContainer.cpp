///////////////////////////////////////////////////////////
//3D모델링 파일의 텍스쳐를 저장하는 컨테이너 코드 입니다.//
///////////////////////////////////////////////////////////
#include "TextureContainer.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
STextureList::STextureList()
{
	m_pTexture = NULL;
	m_szName = NULL;
	m_pPrev = NULL;
	m_pNext = NULL;
	m_Count = 0;
}
STextureList::~STextureList()
{
	if(m_pNext)
		m_pNext->m_pPrev = m_pPrev;
	if(m_pPrev)
		m_pPrev->m_pNext = m_pNext;

	if(m_szName)delete[] m_szName;

	SAFE_RELEASE(m_pTexture);

}
CTextureContainer::CTextureContainer()
{
	m_pHead = NULL;
	m_pTail = NULL;
}
CTextureContainer::~CTextureContainer()
{
	STextureList* Temp = m_pHead;
	STextureList* Temp2;
	while(Temp)
	{
		Temp2 = Temp->m_pNext;
		delete Temp;
		Temp = Temp2;
	}
}
STextureList* CTextureContainer::LoadTexture(LPDIRECT3DDEVICE9 pDevice,
							 char* Name, bool bMipMap)
{
	HRESULT hr;

	STextureList* Temp = Search(Name);

	if(Temp)
	{
		Temp->m_Count++;
		return Temp;
	}
	else
	{
        
		Temp = new STextureList;

		Temp->m_szName = new char[strlen(Name)+2];
		strcpy(Temp->m_szName, Name);
      
		if(bMipMap)
			hr = D3DXCreateTextureFromFileEx(pDevice,Temp->m_szName, 
			0, 0, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT,
			D3DX_FILTER_TRIANGLE | D3DX_FILTER_DITHER , D3DX_FILTER_BOX,
			0xFF000000, NULL, NULL, &(Temp->m_pTexture));
		else
			hr = D3DXCreateTextureFromFileEx(pDevice,Temp->m_szName, 
			0, 0, 1, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT,
			D3DX_FILTER_TRIANGLE | D3DX_FILTER_DITHER , D3DX_FILTER_BOX,
			0xFF000000, NULL, NULL, &(Temp->m_pTexture));

		if(FAILED(hr))
		{
			delete Temp;
			return NULL;
		}

		Add(Temp);
	}
	return Temp;
}
bool CTextureContainer::Add(STextureList* pTextureList)
{
	if(m_pHead == NULL)
	{
		m_pHead = pTextureList;
		if(m_pTail==NULL)
			m_pTail = pTextureList;
	}
	else
	{
		m_pTail->m_pNext = pTextureList;
		pTextureList->m_pPrev = m_pTail;
		m_pTail = pTextureList;
	}
	return true;
}
STextureList* CTextureContainer::Search(char* Name)
{
	STextureList* Temp = m_pHead;
	while(Temp)
	{
		if(_strcmpi(Temp->m_szName,Name)==0)return Temp;
		Temp = Temp->m_pNext;
	}
	return NULL;
}
STextureList* CTextureContainer::Search(LPDIRECT3DTEXTURE9 pTexture)
{
	STextureList* Temp = m_pHead;
	while(Temp)
	{
		if(Temp->m_pTexture == pTexture)return Temp;
		Temp = Temp->m_pNext;
	}
	return NULL;
}
void CTextureContainer::Delete(LPDIRECT3DTEXTURE9 pTexture)
{
	if(pTexture == NULL)return;
	STextureList* Temp = Search(pTexture);
	if(Temp)
	{
		Temp->m_Count --;
		if(Temp->m_Count<0)
		{
			if(Temp == m_pHead)
				m_pHead = Temp->m_pNext;
			if(Temp == m_pTail)
				m_pTail = Temp->m_pPrev;
			delete Temp;
			Temp = NULL;
		}
	}
}
void CTextureContainer::ReleaseAll()
{
	STextureList* Temp = m_pHead;
	while(Temp)
	{
		SAFE_RELEASE(Temp->m_pTexture);
		Temp = Temp->m_pNext;
	}
}
