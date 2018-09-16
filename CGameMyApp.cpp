#include "header.h"

CGameMyApp* g_pGameMyApp	= NULL;
//HINSTANCE          g_hInst = NULL;

INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR, INT )
{
	
	CGameMyApp myApp;

	g_pGameMyApp  = &myApp;
	
	if( FAILED( myApp.Create( hInst ) ) )
		return 0;

	return g_pGameMyApp->Run();
}
CGameMyApp::CGameMyApp()
{
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matView);
	D3DXMatrixIdentity(&m_matProj);
	ZeroMemory(m_FpsChar,sizeof(m_FpsChar));
	
}
void 
CGameMyApp::FPS()
{
	static int fps=0;
	fps++;
	static DWORD TimeTick=GetTickCount();
	if(GetTickCount()-TimeTick>1000)
	{
		sprintf(m_FpsChar,"FPS::%dÀÔ´Ï´Ù",fps);
		fps=0;
		TimeTick=GetTickCount();
	}	
}
HRESULT
CGameMyApp::InitMatrix()
{
	D3DXMatrixPerspectiveFovLH( &m_matProj, D3DX_PI/2, 1.0f, 1.0f, 1000.0f );
	m_pd3dDevice->SetTransform( D3DTS_WORLD, &m_matWorld );
	m_Camera->Update();
	m_matView=*(m_Camera->Getview());
	m_pd3dDevice->SetTransform( D3DTS_VIEW, &m_matView);
	m_pd3dDevice->SetTransform( D3DTS_PROJECTION, &m_matProj );
	m_pd3dDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_NONE);
	m_pd3dDevice->SetRenderState(D3DRS_FILLMODE,D3DFILL_SOLID);

	D3DXVECTOR3 vecDir;									
	D3DLIGHT9 light;									
	ZeroMemory( &light, sizeof(D3DLIGHT9) );			
	light.Type       = D3DLIGHT_DIRECTIONAL;	
	light.Diffuse.r  = 1.0f;							
	light.Diffuse.g  = 1.0f;
	light.Diffuse.b  = 0.0f;
	vecDir = D3DXVECTOR3( 1, 1, 1 );					
	
	D3DXVec3Normalize( (D3DXVECTOR3*)&light.Direction, &vecDir );	
	light.Range       = 1000.0f;									
	m_pd3dDevice->SetLight( 0, &light );							
	m_pd3dDevice->LightEnable( 0, TRUE );							
	m_pd3dDevice->SetRenderState( D3DRS_LIGHTING, FALSE );			

	m_pd3dDevice->SetRenderState( D3DRS_AMBIENT, 0x00909090 );	

	return S_OK;
}
HRESULT 
CGameMyApp::Init()
{
	m_bStop = false;
	m_Fps=new Font(m_pd3dDevice);
	m_Camera=new Camera(m_pd3dDevice);
	m_Ase=new CASE(m_pd3dDevice);
	m_Ani = new CAniTime();
	m_AseMap = new CASE(m_pd3dDevice);

	if(FAILED(m_Fps->InitFont(34,"asdf")))
		return E_FAIL;
	if(FAILED(m_Ase->ReadASE("woman_01_all.ASE")))
		return E_FAIL;
	if (FAILED(m_AseMap->ReadASE("map.ASE")))
		return E_FAIL;

	m_Ase->Init();
	m_AseMap->Init();
	return S_OK;
}
HRESULT
CGameMyApp::Update()
{
	int dt = 5.0f;
	if(GetAsyncKeyState('W'))
		m_Camera->Movez(0.001f);
	if(GetAsyncKeyState('S'))
		m_Camera->Movez(-0.001f);
	if(GetAsyncKeyState('A'))
		m_Camera->Movex(-0.001f);
	if(GetAsyncKeyState('D'))
		m_Camera->Movex(0.001f);
	if(GetAsyncKeyState('Q'))
		m_Camera->Roty(-0.001f);
	if(GetAsyncKeyState('E'))
		m_Camera->Roty(0.001f);
	if(GetAsyncKeyState('Z'))
		m_Camera->Rotx(-0.001f);
	if(GetAsyncKeyState('C'))
		m_Camera->Rotx(0.001f);
	if (GetAsyncKeyState('M'))
	{
		dt = 0;
	}
	
	FPS();
	D3DXMatrixScaling(&m_matWorld,10.0f,10.0f,10.0f);
	m_Ase->StartUpdate(m_matWorld,dt);
	m_AseMap->StartUpdate(m_matWorld, 0);
	return S_OK;
}

HRESULT 
CGameMyApp::Render()
{
	m_pd3dDevice->Clear(0,NULL,D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,D3DCOLOR_XRGB(0,0,255),1.0f,0);
	if( SUCCEEDED( m_pd3dDevice->BeginScene() ) )
	{
		

		RECT df;
		SetRect(&df,0,0,0,0);
		m_Fps->Render(m_FpsChar,df);
		m_Ase->Render();
		m_AseMap->Render();
        m_pd3dDevice->EndScene();
	}
	m_pd3dDevice->Present(NULL,NULL,NULL,NULL);
	return S_OK;

}
HRESULT 
CGameMyApp::Cleanup()
{
	SAFE_DELETE(m_Fps);
	SAFE_DELETE(m_Ase);
	SAFE_DELETE(m_Camera);
	SAFE_DELETE(m_AseMap);

	return S_OK;
}