#include "Renderer.h"

CRenderer* CRenderer::m_pkThis = NULL;
//�����ڿ��� ��� �ʱ�ȭ
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

	//����̽� ������ �����ϴ� �Լ� ȣ��
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
//����̽� ����
bool CRenderer::CreateDevice()
{
	//��ü �������� �˻�
	m_pd3d = Direct3DCreate9(D3D_SDK_VERSION);
	//����ü ����
	m_d3dpp.BackBufferWidth = SCREEN_WIDTH;
	m_d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	m_d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	m_d3dpp.BackBufferCount = 1;
	m_d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	m_d3dpp.MultiSampleQuality = 0;
	m_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_d3dpp.hDeviceWindow = CWindowFrame::Get()->GethWnd();
	m_d3dpp.Windowed = true; 
	m_d3dpp.BackBufferFormat=D3DFMT_UNKNOWN;//�������ȭ�鿡 ��ó�� �ĸ���� ����
	m_d3dpp.EnableAutoDepthStencil = true;
	m_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	m_d3dpp.Flags = 0;
	m_d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	m_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	if(FAILED(m_pd3d->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		CWindowFrame::Get()->GethWnd(), //�������ڵ��� �ٷ� ���´�.
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&m_d3dpp,
		&m_pd3dDevice)))
	{
		MessageBox(NULL,TEXT("����̽���������"),NULL,MB_OK);
		return false;
	}
	return true;
}
void CRenderer::Clear() //����̽� �����
{
	m_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER
		, D3DCOLOR_XRGB(125, 125, 125),
		1.0f, 0);
}
void CRenderer::BeginScene()//�׸���
{
	m_pd3dDevice->BeginScene();
}
void CRenderer::EndScene()//����
{
	m_pd3dDevice->EndScene();//����
}
void CRenderer::Present()//ȭ�麸�̱�
{
	m_pd3dDevice->Present(NULL,NULL,NULL,NULL);
}
LPDIRECT3DDEVICE9 CRenderer::GetDevice()
{
	return m_pd3dDevice;
}
