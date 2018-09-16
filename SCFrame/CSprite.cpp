#include "header.h"
Sprite::Sprite(LPDIRECT3DDEVICE9 pdev)
{
	
	
	m_pd3dDevice=pdev;
	m_sprite=NULL;
	m_tex=NULL;
	D3DXMatrixIdentity(&m_matSprite);
	
}
Sprite::~Sprite()
{
	Cleanup();
}
void
Sprite::Cleanup()
{
	
	if(m_sprite !=NULL)
		m_sprite->Release();
	if(m_tex !=NULL)
		m_tex->Release();
	

}
void 
Sprite::SetSpriteTrans(D3DXMATRIX trans)
{
	m_matSprite=trans;
}
HRESULT
Sprite::CreateSprite(LPDIRECT3DTEXTURE9 tex,DWORD width,DWORD height)
{
	m_tex=tex;
	//if(FAILED(D3DXCreateTextureFromFile(g_InitDx->GetDev(),texname,&m_tex)))
	//	return E_FAIL;


	if(FAILED(D3DXCreateSprite(m_pd3dDevice,&m_sprite)))
		return E_FAIL;

	return S_OK;
}
HRESULT
Sprite::CreateSprite(LPCSTR texname,DWORD width,DWORD height)
{
	//if(FAILED(D3DXCreateTextureFromFile(g_InitDx->GetDev(),texname,&m_tex)))
	//	return E_FAIL;
	
	if(FAILED(D3DXCreateTextureFromFileEx(m_pd3dDevice, texname,
       width, height, 
	   1, D3DUSAGE_DYNAMIC, 
	   D3DFMT_A8R8G8B8, //D3DFMT_UNKNOWN,
       D3DPOOL_DEFAULT, //D3DPOOL_MANAGED, 
	   D3DX_FILTER_LINEAR, //D3DX_FILTER_TRIANGLE|D3DX_FILTER_MIRROR, 
       D3DX_FILTER_LINEAR, //D3DX_FILTER_TRIANGLE|D3DX_FILTER_MIRROR, 
	   D3DCOLOR_XRGB(203, 200, 207), 
       NULL, NULL, &m_tex)))
	   return E_FAIL;

	if(FAILED(D3DXCreateSprite(m_pd3dDevice,&m_sprite)))
		return E_FAIL;
	
	return S_OK;
}
void
Sprite::DrawSprite(D3DXVECTOR3 posit)
{
	
	
	
	m_sprite->Begin(D3DXSPRITE_ALPHABLEND);

	m_pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE , TRUE) ;
	m_pd3dDevice->SetRenderState( D3DRS_SRCBLEND,D3DBLEND_SRCALPHA) ;
	m_pd3dDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA) ;
	
	m_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1) ;
	m_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE) ;
	
	//D3DXMatrixTranslation(&m_matSprite,-10,-10,0);
	m_sprite->SetTransform(&m_matSprite);
	
	m_sprite->Draw(m_tex,NULL,NULL,&posit,D3DCOLOR_XRGB(255,255,255));
	m_sprite->End();
	m_pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE , FALSE) ;

	

	
}