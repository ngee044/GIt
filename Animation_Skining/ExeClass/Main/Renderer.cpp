#include "Renderer.h"

CRenderer* CRenderer::m_pkThis = NULL;
//생성자에서 멤버 초기화
CRenderer::CRenderer()
{
	m_pd3d = NULL;
	m_pd3dDevice = NULL;
	ZeroMemory(&m_d3dpp,sizeof(m_d3dpp));
}
CRenderer::~CRenderer()
{}
CRenderer* CRenderer::Create()
{
	if(!m_pkThis)
		m_pkThis = new CRenderer;

	//디바이스 정보를 셋팅하는 함수 호출
	CRenderer::Get()->CreateDevice();

	return	m_pkThis;
}
void CRenderer::Destroy()
{
	CRenderer::Get()->m_pd3dDevice->Release();
	CRenderer::Get()->m_pd3d->Release();
	CRenderer* pRenderer = CRenderer::Get();
	delete pRenderer;
}
CRenderer* CRenderer::Get()
{
	return m_pkThis;
}
//디바이스 셋팅
bool CRenderer::CreateDevice()
{
	//객체 생성여부 검사
	m_pd3d = Direct3DCreate9(D3D_SDK_VERSION);
	//구조체 설정
	m_d3dpp.BackBufferWidth = SCREEN_WIDTH;
	m_d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	m_d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	m_d3dpp.BackBufferCount = 1;
	m_d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	m_d3dpp.MultiSampleQuality = 0;
	m_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_d3dpp.hDeviceWindow = CWindowFrame::Get()->GethWnd();
	m_d3dpp.Windowed = true; 
	m_d3dpp.BackBufferFormat=D3DFMT_UNKNOWN;//현재바탕화면에 맞처서 후면버퍼 생성
	m_d3dpp.EnableAutoDepthStencil = true;
	m_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	m_d3dpp.Flags = 0;
	m_d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	m_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	if(FAILED(m_pd3d->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		CWindowFrame::Get()->GethWnd(), //윈도우핸들을 바로 얻어온다.
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&m_d3dpp,
		&m_pd3dDevice)))
	{
		MessageBox(NULL,TEXT("디바이스생성실패"),NULL,MB_OK);
		return false;
	}
	return true;
}
void CRenderer::Clear() //디바이스 지우고
{
	m_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER
		, D3DCOLOR_XRGB(125, 125, 125),
		1.0f, 0);
}
void CRenderer::BeginScene()//그리고
{
	m_pd3dDevice->BeginScene();
}
void CRenderer::EndScene()//종료
{
	m_pd3dDevice->EndScene();//종료
}
void CRenderer::Present()//화면보이기
{
	m_pd3dDevice->Present(NULL,NULL,NULL,NULL);
}
LPDIRECT3DDEVICE9 CRenderer::GetDevice()
{
	return m_pd3dDevice;
}
