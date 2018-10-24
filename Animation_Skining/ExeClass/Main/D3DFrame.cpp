#include "D3DFrame.h"

CD3DFrame* CD3DFrame::m_pkThis = NULL;
CD3DFrame::CD3DFrame()
{
	m_pd3dDevice=NULL;
	m_dwMouseX=NULL; //���콺 X��
	m_dwMouseY=NULL; //���콺 Y��
	m_XPos=0.0f;
	m_YPos=0.0f;
	m_ZPos=0.0f;			// location coord

	D3DXMatrixIdentity(&m_Scale);
	D3DXMatrixIdentity(&m_Rot);
	D3DXMatrixIdentity(&m_Pos);
	frame=0;
}
CD3DFrame::~CD3DFrame()
{}

CD3DFrame* CD3DFrame::Create()
{
	if(!m_pkThis)
		m_pkThis = new CD3DFrame;

	CRenderer::Get()->Create();

	//����Ŭ���� ����
	CD3DFrame::Get()->Init();

	return	m_pkThis;
}
void CD3DFrame::Destroy()
{
	CRenderer::Destroy();
	delete CD3DFrame::Get()->m_pCamera;
	delete CD3DFrame::Get()->m_pCharacter;
	delete CD3DFrame::Get()->m_vChart[1];
	//����Ŭ���� ����
	CD3DFrame* pFrame = CD3DFrame::Get();

	delete pFrame;
}
//�ڱ��ڽ��� ����
CD3DFrame* CD3DFrame::Get()
{
	return m_pkThis;
}
void CD3DFrame::Init()
{
	//����̽��� �޾ƿ´�
	m_pd3dDevice=CRenderer::Get()->GetDevice();

	/// �ø������ ����.
	m_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );
	/// Z���۱���� �Ҵ�.
	m_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
	/// ������ ������ �����Ƿ�, ��������� ����.
	m_pd3dDevice->SetRenderState( D3DRS_LIGHTING, TRUE );

	m_pd3dDevice->SetRenderState(::D3DRS_CULLMODE, ::D3DCULL_CCW);

	D3DXMATRIX matView;
	D3DXVECTOR3 vEye(0.0f, 0.0f, -10.0f);
	D3DXVECTOR3 vLookat(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vUp(0.0f, 1.0f, 0.0f);

	D3DXMatrixLookAtLH(&matView, &vEye, &vLookat, &vUp);
	m_pd3dDevice->SetTransform(D3DTS_VIEW, &matView);

	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 30000.0f);
	m_pd3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);

	D3DXVECTOR3 veye(-55.0f, 80.0f, -125.0f);
	D3DXVECTOR3 vLook(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vCross(1.0f, 0.0f, 0.0f);
	D3DXVECTOR3 Dest = vLook - veye;
	D3DXVec3Normalize(&Dest, &Dest);

	::D3DXVec3Cross(&vUp, &Dest, &vCross);
	D3DXVec3Normalize(&vUp, &vUp);

	m_pCamera = new CameraClass(m_pd3dDevice,	// m_device
		&veye, &vLook, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));

	m_pCamera->InitCamera(CWindowFrame::Get()->GethWnd());

	m_pCharacter = new CharacterClass();
	auto npc_chart = new CharacterClass();

	m_pCharacter->m_id = 0;
	m_pCharacter->InitCharacter(m_pd3dDevice, "calix_stand.ASE", "calix_");
	m_pCharacter->m_Pos._42 = -20.0f;
	m_pCharacter->m_Pos._41 = 10.0f;

	npc_chart->m_id = 1;
	npc_chart->InitCharacter(m_pd3dDevice, "mayel_3rd_stand.ASE", "mayel_3rd_plus");
	npc_chart->m_Pos._42 = -20.0f;
	npc_chart->m_Pos._41 = 10.0f;

	m_vChart.push_back(m_pCharacter);
	m_vChart.push_back(npc_chart);

	m_pKeyInfo = new sKeyInfo();

	m_pMap = new MapClass();
	m_pMap->InitMap(m_pd3dDevice, "Map01", "map.ASE");

	////////////////////////////////////////////////////
	D3DMATERIAL9 mtrl;
	ZeroMemory(&mtrl, sizeof(D3DMATERIAL9));
	mtrl.Diffuse.r = mtrl.Ambient.r = 1.0f;
	mtrl.Diffuse.g = mtrl.Ambient.g = 1.0f;
	mtrl.Diffuse.b = mtrl.Ambient.b = 1.0f;
	mtrl.Diffuse.a = mtrl.Ambient.a = 1.0f;
	m_pd3dDevice->SetMaterial(&mtrl);

	// Set up a white, directional light, with an oscillating direction.
	// Note that many lights may be active at a time (but each one slows down
	// the rendering of our scene). However, here we are just using one. Also,
	// we need to set the D3DRS_LIGHTING renderstate to enable lighting
	D3DXVECTOR3 vecDir;
	D3DLIGHT9 light;
	ZeroMemory(&light, sizeof(D3DLIGHT9));
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Diffuse.r = 1.0f;
	light.Diffuse.g = 1.0f;
	light.Diffuse.b = 1.0f;
	vecDir = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDir);
	light.Range = 100000.0f;
	m_pd3dDevice->SetLight(0, &light);
	m_pd3dDevice->LightEnable(0, TRUE);
	m_pd3dDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// Finally, turn on some ambient light.
	m_pd3dDevice->SetRenderState(D3DRS_AMBIENT, 0x00FFFFFF);
}

void CD3DFrame::Update()
{
	if (NULL != m_pCamera)
	{
		m_pCamera->Update();

		D3DXVECTOR3 pLook_pos = D3DXVECTOR3(m_pCharacter->m_Pos._41, m_pCharacter->m_Pos._42, m_pCharacter->m_Pos._43);

		D3DXVECTOR3 pEye_pos = D3DXVECTOR3(
			((m_pCharacter->m_Pos._41) - 55.0f),
			((m_pCharacter->m_Pos._42) + 80.0f),
			((m_pCharacter->m_Pos._43) - 125.0f));

		m_pCamera->SetView(&pEye_pos, &pLook_pos, m_pCamera->GetUp());
	}

	if (NULL != m_pCharacter)
	{
		m_pKeyInfo->CheckNomalKeyList();
		m_pKeyInfo->CheckDirectionKeyList();

		m_pCharacter->UpdateProcessKey(m_pKeyInfo);
		
		for(auto it = m_vChart.begin(); it != m_vChart.end(); ++it )
			(*it)->Update();
	}
}
//�����Լ��� �ҷ��� ������
void CD3DFrame::Run()
{
	Update(); //����

	D3DXMATRIX mat;
	D3DXMatrixIdentity(&mat);

	D3DXMATRIXA16 half;			//�������� ������
	D3DXMatrixIdentity(&half);
	half._11 = half._22 = half._33 = 0.5f;
	//g_pSprite->SetTransform( &half );

	D3DXMATRIXA16 x1;				//�������� ���� ũ���
	D3DXMatrixIdentity(&x1);
	x1._11 = x1._22 = x1._33 = 1.0f;

	D3DXMATRIXA16 x2;				//�������� 2���� ũ���
	D3DXMatrixIdentity(&x2);
	x2._11 = x2._22 = x2._33 = 2.0f;

	m_pd3dDevice->SetTransform(D3DTS_WORLD, &mat);

	CRenderer::Get()->Clear();
	CRenderer::Get()->BeginScene();
	//�޽þ�����Ʈ �� ������

	if (NULL != m_pCharacter)
	{
		//m_pCharacter->Render();
		for (auto it = m_vChart.begin(); it != m_vChart.end(); ++it)
			(*it)->Render();
	}
	if (NULL != m_pMap)
		m_pMap->Render();

	CRenderer::Get()->EndScene();
	CRenderer::Get()->Present();
}
void CD3DFrame::ProcessInput() //�Է°� ó��
{
	Processkey();
	ProcessMouse();
}
int CD3DFrame::Processkey(void)
{
	return 0;
}
int CD3DFrame::ProcessMouse(void)
{
	POINT	pt;
	float	fDelta = 0.01f;	// ���콺�� �ΰ���, �� ���� Ŀ������ ���� �����δ�.

	GetCursorPos( &pt );
	int dx = pt.x -m_dwMouseX;	// ���콺�� ��ȭ��
	int dy = pt.y - m_dwMouseY;	// ���콺�� ��ȭ��

	m_pCamera->RotateLocalX( dy * fDelta );	// ���콺�� Y�� ȸ������ 3D world��  X�� ȸ����
	m_pCamera->RotateLocalY( dx * fDelta );	// ���콺�� X�� ȸ������ 3D world��  Y�� ȸ����

	if( GetAsyncKeyState( VK_LBUTTON ) ) 
		m_pCamera->MoveLocalZ( 1.0f );	// ī�޶� ����!
	if( GetAsyncKeyState(VK_RBUTTON ) )
		m_pCamera->MoveLocalZ( -1.0f );	// ī�޶� ����!

	if( GetAsyncKeyState( VK_MBUTTON ) ) 
		m_pd3dDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_WIREFRAME );
	if( GetAsyncKeyState( VK_RBUTTON ) ) 
		m_pd3dDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID );

	D3DXMATRIXA16*	pmatView = m_pCamera->GetViewMatrix();		// ī�޶� ����� ��´�.
	m_pd3dDevice->SetTransform( D3DTS_VIEW, pmatView );			// ī�޶� ��� ����

	// ���콺�� �������� �߾����� �ʱ�ȭ
	SetCursor( NULL );	// ���콺�� ��Ÿ���� �ʰ� �ʴ�.
	RECT	rc;
	GetClientRect( CWindowFrame::Get()->GethWnd(), &rc );
	pt.x = (rc.right - rc.left) / 2;
	pt.y = (rc.bottom - rc.top) / 2;
	ClientToScreen( CWindowFrame::Get()->GethWnd(), &pt );
	SetCursorPos( pt.x, pt.y );
	m_dwMouseX = pt.x;
	m_dwMouseY = pt.y;

	return 0;
}