#include "header.h"


static CGameApp* g_GameApp = NULL;


CGameApp::CGameApp()
{
    g_GameApp=this;
	m_pD3D=NULL;
	m_pd3dDevice=NULL;
	m_hWnd=NULL;
	ZeroMemory( &m_pd3dpp, sizeof(m_pd3dpp) );
	
}
LRESULT CALLBACK WndProc( HWND m_hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	return g_GameApp->MsgProc( m_hWnd, msg, wParam, lParam );
}

LRESULT 
CGameApp::MsgProc( HWND m_hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch( msg )
	{
	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:
			SAFE_RELEASE(m_pd3dDevice);
			SAFE_RELEASE(m_pD3D);
			Cleanup();
			PostQuitMessage( 0 );
			return 0;
		case VK_RETURN:
			return 0;

		}
		return 0;
	case WM_LBUTTONDOWN:
		return 0;
	case WM_LBUTTONUP:
		return 0;
	case WM_DESTROY:
		SAFE_RELEASE(m_pd3dDevice);
		SAFE_RELEASE(m_pD3D);
		PostQuitMessage( 0 );
		Cleanup();
		return 0;
	}

	return DefWindowProc( m_hWnd, msg, wParam, lParam );
}
HRESULT 
CGameApp::Run()
{
	MSG msg;
	ZeroMemory( &msg, sizeof(msg) );
	while( msg.message!=WM_QUIT )
	{
		/// �޽���ť�� �޽����� ������ �޽��� ó��
		if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );

		}
		else
		{
			Update();
			Render();
			
		}
	}
	return (INT)msg.wParam;
}
HRESULT 
CGameApp::Create(HINSTANCE hInst)
{
	/// ����̽��� �����ϱ����� D3D��ü ����
	if( NULL == ( m_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
		return E_FAIL;

	/// ����̽��� ������ ����ü
	/// ������ ������Ʈ�� �׸����̱⶧����, �̹����� Z���۰� �ʿ��ϴ�.
	
#ifdef FULLSCREEN
	m_pd3dpp.Windowed = FALSE;
	m_pd3dpp.FullScreen_RefreshRateInHz	= D3DPRESENT_RATE_DEFAULT;
#else
	m_pd3dpp.Windowed = TRUE;
	
#endif
	m_pd3dpp.BackBufferWidth=800;
	m_pd3dpp.BackBufferHeight=600;
	m_pd3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_pd3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;

	m_pd3dpp.BackBufferCount=1;
	m_pd3dpp.MultiSampleQuality=NULL;
	m_pd3dpp.MultiSampleType=D3DMULTISAMPLE_NONE;
	m_pd3dpp.EnableAutoDepthStencil = TRUE;
	m_pd3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	m_pd3dpp.Flags=NULL;
	m_pd3dpp.PresentationInterval=D3DPRESENT_INTERVAL_IMMEDIATE;


	//������ ����
	WNDCLASS wc = { 0, WndProc, 0, 0,hInst,
		NULL,
		NULL,
		NULL,
		NULL, "SCFrame" };
	RegisterClass( &wc );


	m_hWnd = CreateWindow( "SCFrame", "SCFrame",
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
		0, NULL, hInst, NULL );
	//����̽� ����
	m_hWndFocus=m_hWnd;
	if( FAILED( m_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWndFocus,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&m_pd3dpp, &m_pd3dDevice ) ) )
	{
		return E_FAIL;
	}

	//��ü�� �ʱ�ȭ

	if(FAILED(Init()))
		return E_FAIL;

	ShowWindow( m_hWnd, SW_SHOWDEFAULT );
	UpdateWindow( m_hWnd );

	InitMatrix();//��Ʈ���� �¾�

	return S_OK;


}