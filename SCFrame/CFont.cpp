#include "header.h"
Font::Font(LPDIRECT3DDEVICE9 pdev)
{
	m_pd3dDevice=pdev;
	m_Font=NULL;
	m_FontPoint=0;
	
}
Font::~Font()
{
	Cleanup();
}
HRESULT
Font::InitFont(int Point,LPSTR fName,DWORD Color)
{
	
	m_FontColor=Color;
	HDC hDC=GetDC(NULL);
	m_FontPoint=-MulDiv(Point,GetDeviceCaps(hDC,LOGPIXELSY),72);
	if(FAILED(D3DXCreateFont(m_pd3dDevice,m_FontPoint,0,0,FW_NORMAL,FALSE,DEFAULT_CHARSET
		,OUT_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,fName,&m_Font)))
		return E_FAIL;
	return S_OK;
    	
}
void 
Font::Render(LPCSTR word,RECT rect)
{
	m_Font->DrawTextA(NULL,word,strlen(word),&rect,DT_NOCLIP,m_FontColor);
}
void
Font::Cleanup()
{
	SAFE_RELEASE(m_Font);
		
}