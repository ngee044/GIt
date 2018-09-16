#include "header.h"
CMaterial::CMaterial(LPDIRECT3DDEVICE9 pdev)
{
	m_pd3dDevice=pdev;
	ZeroMemory(&m_Material,sizeof(D3DMATERIAL9));
	ZeroMemory(&m_Texture,sizeof(LPDIRECT3DTEXTURE9));
	ZeroMemory(&m_Ambient,sizeof(D3DXVECTOR3));
	ZeroMemory(&m_Diffuse,sizeof(D3DXVECTOR3));
	ZeroMemory(&m_Specular,sizeof(D3DXVECTOR3));

}
CMaterial::~CMaterial()
{
	SAFE_RELEASE(m_Texture);
}
HRESULT
CMaterial::CreateTexture()
{
	LPCSTR temp = m_TextureName.c_str(); 

	if(FAILED(D3DXCreateTextureFromFile(m_pd3dDevice,temp,&m_Texture)))
		return E_FAIL;	
	return S_OK;
}
void
CMaterial::SetTexture()
{
	m_pd3dDevice->SetTexture(0,m_Texture);
	m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
	m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
	m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_SELECTARG1);
	m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
}
void 
CMaterial::SetMaterial()
{
	m_Material.Diffuse.r =m_Diffuse.x;
	m_Material.Diffuse.g =m_Diffuse.y;
	m_Material.Diffuse.b =m_Diffuse.z;
	m_Material.Diffuse.a =1.0f;
	m_Material.Ambient.r =m_Ambient.x; 
	m_Material.Ambient.g =m_Ambient.y; 
	m_Material.Ambient.b =m_Ambient.z; 
	m_Material.Ambient.a =1.0f;
	m_Material.Specular.r=m_Specular.x;
	m_Material.Specular.g=m_Specular.y;
	m_Material.Specular.b=m_Specular.z;
	m_Material.Specular.a=1.0f;
	m_pd3dDevice->SetMaterial( &m_Material );
}

CAniTime::CAniTime()
{
	m_StartTime=0.0f;
	m_EndTime=0.0f;
	m_CurrentTime=0.0f;
}
void
CAniTime::Init(float firstframe,float endframe,float tickperframe)
{

	m_StartTime=firstframe*tickperframe;
	m_EndTime=endframe*tickperframe;
	m_CurrentTime=m_StartTime;


}
void
CAniTime::Update(float dt)
{
	m_CurrentTime+=dt;
	if(m_CurrentTime>=m_EndTime)
		m_CurrentTime=m_StartTime;
}