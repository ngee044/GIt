///////////////////////////////////////////
//���Ӽ��� ī�޶� �����ϴ� �ڵ� �Դϴ�.//
///////////////////////////////////////////
#include "Camera.h"

CameraClass::CameraClass(void)
{
	// �ʱ�ȭ 
	D3DXVECTOR3	eye(0.0f,0.0f,0.0f);
	D3DXVECTOR3	lookat(0.0f,0.0f, 0.0f);    // target
	D3DXVECTOR3	up(0.0f,1.0f,0.0f);

	D3DXMatrixIdentity( &m_matView );
	D3DXMatrixIdentity( &m_matBill );
	
	SetView( &eye, &lookat, &up );
}

CameraClass::CameraClass(LPDIRECT3DDEVICE9 d3d,D3DXVECTOR3* pvEye,D3DXVECTOR3* pvLookat,D3DXVECTOR3* pvUp)
{
	 SetKeyFocus(false);
     m_pd3d = d3d;
     SetView( pvEye, pvLookat,pvUp );
}

CameraClass::~CameraClass(void)
{

}

void CameraClass::Update()
{
	//if(GetKeyFocus())
	{
		ProcessMouse();
		ProcessKey();
	}
}

void CameraClass::DrawBillboard()
{
	m_pd3d->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pd3d->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pd3d->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	m_pd3d->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	m_pd3d->SetRenderState(D3DRS_ALPHAREF, 0x08);
	m_pd3d->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);

	MY_VERTEX vtx[4] =
	{
		{-1, 0, 0, 0, 1},
		{-1, 4, 0, 0, 0},
		{1, 0, 0, 1, 1 },
		{1, 4, 0, 1, 0 }
	};
	
	m_pd3d->SetTexture(1, NULL);
	m_pd3d->SetFVF(MY_VERTEX::FVF);

	if (m_bBillboard)
	{
		m_matBill._11 = m_matView._11;
		m_matBill._13 = m_matView._13;
		m_matBill._31 = m_matView._31;
		m_matBill._33 = m_matView._33;
		D3DXMatrixInverse(&m_matBill, NULL, &m_matBill);
	}

	for (int z = 0; z <= -40; z += 5) //��ǥ�� �ٲ��鼭 ��´�
	{
		for (int x = 40; x >= 0; x -= 5)
		{
			m_matBill._41 = x - 20;
			m_matBill._42 = 0;
			m_matBill._43 = z - 20;
			m_pd3d->SetTexture(0, m_pTexBillboard[(x + z) % 4]);

			if ((x + z) % 4 == 3)
			{
				//vtx[0].uv = tblUV[nStep][0];
				//vtx[1].uv = tblUV[nStep][1];
				//vtx[2].uv = tblUV[nStep][2];
				//vtx[3].uv = tblUV[nStep][3];
				//m_pd3d->SetTransform(D3DTS_WORLD, &m_matBill);
				//m_pd3d->DrawIndexedPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vtx, sizeof(MY_VERTEX);
			}
		}
	}

	m_pd3d->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	m_pd3d->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	m_pd3d->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	m_pd3d->SetTransform(D3DTS_WORLD, &m_matView);
}

/// ī�޶� ����� �����ϱ����� �⺻ ���Ͱ����� �����Ѵ�.
D3DXMATRIXA16*	CameraClass::SetView( D3DXVECTOR3* pvEye,D3DXVECTOR3* pvLookat,D3DXVECTOR3* pvUp)
{
	m_vEye		= *pvEye;
	m_vLookat	= *pvLookat;
	m_vUp		= *pvUp;

	D3DXVec3Normalize( &m_vView, &( m_vLookat - m_vEye ) );
	D3DXVec3Cross( &m_vCross, &m_vUp, &m_vView );

	D3DXMatrixLookAtLH( &m_matView, &m_vEye, &m_vLookat, &m_vUp);

	// ������ ��� ���ϱ� 
	D3DXMatrixInverse( &m_matBill, NULL, &m_matView );
	m_matBill._41 = 0.0f;
	m_matBill._42 = 0.0f;
	m_matBill._43 = 0.0f;

	// ī�޶� ��� �ݿ�
    m_pd3d->SetTransform(D3DTS_VIEW,&m_matView);

	return &m_matView;
}


/// ī�޶� ��ǥ���� X������ angle��ŭ ȸ���Ѵ�.
D3DXMATRIXA16* CameraClass::RotateLocalX( float angle )
{
	D3DXMATRIXA16 matRot;
	D3DXMatrixRotationAxis( &matRot, &m_vCross, angle );

	D3DXVECTOR3 vNewDst,vNewUp;
	D3DXVec3TransformCoord( &vNewDst, &m_vView, &matRot );	// view * rot�� ���ο� dst vector�� ���Ѵ�.
	D3DXVec3Cross( &vNewUp, &vNewDst, &m_vCross );			// cross( dst, x��)���� up vector�� ���Ѵ�.
	D3DXVec3Normalize( &vNewUp, &vNewUp );					// up vector�� unit vector��...
	vNewDst += m_vEye;										// ���� dst position =  eye Position + dst vector

	return SetView( &m_vEye, &vNewDst, &m_vUp );
}

/// ī�޶� ��ǥ���� Y������ angle��ŭ ȸ���Ѵ�.
D3DXMATRIXA16* CameraClass::RotateLocalY( float angle )
{
	D3DXMATRIXA16 matRot;
	D3DXMatrixRotationAxis( &matRot, &D3DXVECTOR3(0.0f,1.0f,0.0f), angle );

	D3DXVECTOR3 vNewDst;
	D3DXVec3TransformCoord( &vNewDst, &m_vView, &matRot );	// view * rot�� ���ο� dst vector�� ���Ѵ�.
	vNewDst += m_vEye;										
	// ���� dst position =  eye Position + dst vector

	return SetView( &m_vEye, &vNewDst, &m_vUp );
}

/// ī�޶� ��ǥ���� X��������� dist��ŭ �����Ѵ�.(������ -dist�� ������ �ȴ�.)
D3DXMATRIXA16* CameraClass::MoveLocalX( float dist )
{
	D3DXVECTOR3 vNewEye	= m_vEye;
	D3DXVECTOR3 vNewDst	= m_vLookat;

	D3DXVECTOR3 vMove;
	D3DXVec3Normalize( &vMove, &m_vCross );
	vMove	*= dist;
	vNewEye += vMove;
	vNewDst += vMove;

	return SetView( &vNewEye, &vNewDst, &m_vUp );
}

/// ī�޶� ��ǥ���� Y��������� dist��ŭ �����Ѵ�.(������ -dist�� ������ �ȴ�.)
D3DXMATRIXA16* CameraClass::MoveLocalY( float dist )
{
	D3DXVECTOR3 vNewEye	= m_vEye;
	D3DXVECTOR3 vNewDst	= m_vLookat;

	D3DXVECTOR3 vMove;
	D3DXVec3Normalize( &vMove, &m_vUp );
	vMove	*= dist;
	vNewEye += vMove;
	vNewDst += vMove;

	return SetView( &vNewEye, &vNewDst, &m_vUp );
}

/// ī�޶� ��ǥ���� Z��������� dist��ŭ �����Ѵ�.(������ -dist�� ������ �ȴ�.)
D3DXMATRIXA16* CameraClass::MoveLocalZ( float dist )
{
	D3DXVECTOR3 vNewEye	= m_vEye;
	D3DXVECTOR3 vNewDst	= m_vLookat;

	D3DXVECTOR3 vMove;
	D3DXVec3Normalize( &vMove, &m_vView );
	vMove	*= dist;
	vNewEye += vMove;
	vNewDst += vMove;

	return SetView( &vNewEye, &vNewDst, &m_vUp );
}


/// ������ǥ���� *pv���� ��ġ�� ī�޶� �̵��Ѵ�.
D3DXMATRIXA16* CameraClass::MoveTo( D3DXVECTOR3* pv )
{
	D3DXVECTOR3	dv = *pv - m_vEye;
	m_vEye = *pv;
	m_vLookat += dv;


	return SetView( &m_vEye, &m_vLookat, &m_vUp );
}

void CameraClass::InitCamera(HWND hWnd)
{
	SetHwnd(hWnd);
	SetMousePt_Center();
}

void CameraClass::UpdateCamera(float &xRot, float &yRot, float &dist, unsigned long &frame)
{
	D3DXVECTOR3 vDir;
	D3DXVECTOR3 vTarget = m_vLookat;        //pCameraTarget
	float value = (0.85f - (frame - 1.0f) / 10.0f);

	if(xRot == 0.0f)
	{
		if(fabsf(m_prevxRot) > 0.02f)
			xRot = m_prevxRot *= value;
	}
	else
	{
		m_prevxRot = xRot;
	}

	if(yRot == 0.0f)
	{
		if(fabsf(m_prevyRot) > 0.02f)
			yRot = m_prevyRot *= value;
	}
	else
	{
		m_prevyRot = yRot;
	}

	if(dist == 0.0f)
	{
		if(fabsf(m_prevDist) > 0.02f)
			dist = m_prevDist *= (value + 0.03f);
	}
	else
	{
		m_prevDist = dist;
	}

	// ȸ���� ���� �ʱ�ȭ 
	m_RotyAxis += yRot;
	if(m_RotyAxis > 360.0f)
		m_RotyAxis -= 360.0f;
	else if(m_RotyAxis < 0.0f)
		m_RotyAxis += 360.0f;

	m_RotxAxis += xRot;
	if(m_RotxAxis < -60.0f)
		m_RotxAxis = -60.0f;
	else if(m_RotxAxis > 60.0f)
		m_RotxAxis = 60.0f;

	// �Ÿ��� min-max ���� 
	m_Dist += dist;
	if(m_Dist < 30.0f)
		m_Dist = 30.0f;
	else if(m_Dist > 600.0f)		// dist min-max
		m_Dist = 600.0f;

    // �̵������� ���� �ະ ȸ�� 
	m_vEye.x = m_Dist * cosf(m_RotxAxis * D3DX_PI / 180.0f) * cosf(m_RotyAxis * D3DX_PI / 180.0f);
	m_vEye.y = m_Dist * sinf(m_RotxAxis * D3DX_PI / 180.0f);
	m_vEye.z = m_Dist * cosf(m_RotxAxis * D3DX_PI / 180.0f) * sinf(m_RotyAxis * D3DX_PI / 180.0f);	
	
	// ȸ���� ī�޶��� ��ġ�� �̵� �ݿ� 
	m_vEye += vTarget  ;          

	
	SetView(&m_vEye,&vTarget, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	
}

void CameraClass::ProcessMouse()
{
	////////////////////
	//���콺 ó��	  //
	////////////////////
	POINT	pt;
	float	fDelta = 0.001f;	// ���콺�� �ΰ���, �� ���� Ŀ������ ���� �����δ�.

	GetCursorPos( &pt );
	//m_dwMouseX=pt.x;
	//m_dwMouseY=pt.y;

	int dx = pt.x - m_dwMouseX;	// ���콺�� ��ȭ��
	int dy = pt.y - m_dwMouseY;	// ���콺�� ��ȭ��

	RotateLocalX( dy * fDelta );	// ���콺�� Y�� ȸ������ 3D world��  X�� ȸ����
	RotateLocalY( dx * fDelta );	// ���콺�� X�� ȸ������ 3D world��  Y�� ȸ����


	D3DXMATRIXA16*	pmatView = GetViewMatrix();		// ī�޶� ����� ��´�.
	GetDevice()->SetTransform( D3DTS_VIEW, pmatView );			// ī�޶� ��� ����

	// ���콺�� �������� �߾����� �ʱ�ȭ
	SetCursor( NULL );	// ���콺�� ��Ÿ���� �ʰ� �ʴ�.
	SetMousePt_Center();
}
void CameraClass::ProcessKey()
{
	if( GetAsyncKeyState( 'W'  ) & 0x8000  ) 
	{
		MoveLocalZ( 0.5f * 1.0f );	// ī�޶� ����!
		m_ZPos += 1.5f;
	}
	if( GetAsyncKeyState( 'S'  ) & 0x8000 )
	{
		MoveLocalZ( -0.5f * 1.0f);	// ī�޶� ����!
		m_ZPos -= 1.5f;
	}
	if( GetAsyncKeyState( 'A'  ) & 0x8000 )
	{
		MoveLocalX( -0.5f * 1.0f);	// ī�޶� ����!
		m_XPos -= 1.5f;
	}

	if( GetAsyncKeyState( 'D'  ) & 0x8000  )
	{
		MoveLocalX( 0.5f* 1.0f);	// ī�޶� ������!
		m_XPos += 1.5f;
	}

	if( GetAsyncKeyState( WM_LBUTTONUP ) & 0x8000  ) 
	{
		GetDevice()->SetRenderState( D3DRS_FILLMODE, D3DFILL_WIREFRAME );
		//g_pPick->Pick();
	}
	if( GetAsyncKeyState( VK_RBUTTON ) & 0x8000  ) 
		GetDevice()->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID );
}

void CameraClass::SetMousePt_Center()
{
	RECT	rc;
	POINT	pt;
	GetClientRect( GetHwnd(), &rc );
	pt.x = (rc.right - rc.left) / 2;
	pt.y = (rc.bottom - rc.top) / 2;
	ClientToScreen( GetHwnd(), &pt );
	SetCursorPos( pt.x, pt.y );
	m_dwMouseX = pt.x;
	m_dwMouseY = pt.y;
}