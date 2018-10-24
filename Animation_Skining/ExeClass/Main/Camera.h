///////////////////////////////////////////
//���Ӽ��� ī�޶� �����ϴ� �ڵ� �Դϴ�.//
///////////////////////////////////////////

#pragma once
#include "Common.h"

struct MY_VERTEX
{
	enum { FVF = D3DFVF_XYZ | D3DFVF_TEX1};
	float px, py, pz;
	float tu, tv;
};



class CameraClass
{
private:
    // device
	HWND					m_hWnd;
	LPDIRECT3DDEVICE9		m_pd3d;

	BOOL					m_bKeyFocus;

	D3DXVECTOR3		m_vEye;			// ī�޶��� ���� ��ġ
	D3DXVECTOR3		m_vLookat;		// ī�޶��� �ü� ��ġ
	D3DXVECTOR3		m_vUp;			// ī�޶��� ��溤��

	D3DXVECTOR3		m_vView;		// ī�޶� ���ϴ� �������⺤��
	D3DXVECTOR3		m_vCross;		// ī������ ���麤�� cross( view, up )

	D3DXMATRIXA16	m_matView;		// ī�޶� ���
	D3DXMATRIXA16	m_matBill;		// ������ ���(ī�޶��� �����)

	//������
	bool m_bBillboard;
	LPDIRECT3DTEXTURE9 m_pTexBillboard[3];

public:
	void Update();

	BOOL GetKeyFocus(){return m_bKeyFocus;};

	DWORD	m_dwMouseX;
	DWORD	m_dwMouseY;

	float   m_XPos, m_YPos, m_ZPos;	

	void SetKeyFocus(BOOL b_Focus){m_bKeyFocus=b_Focus;};
	void ProcessMouse();
	void ProcessKey();

	void SetMousePt_Center();

	void SetHwnd(HWND hWnd){m_hWnd=hWnd;};
	HWND GetHwnd(){return m_hWnd;};

	LPDIRECT3DDEVICE9 GetDevice(){return m_pd3d;};

	void DrawBillboard();

	CameraClass(void);
	~CameraClass(void);

	CameraClass(LPDIRECT3DDEVICE9 d3d,D3DXVECTOR3* pvEye,D3DXVECTOR3* pvLookat,D3DXVECTOR3* pvUp);

	
	//=======================================================================
	// ī�޶�,������ ��� ��� 
	//=======================================================================	
	D3DXMATRIXA16*	GetViewMatrix() { return &m_matView; }
	D3DXMATRIXA16*	GetBillMatrix() { return &m_matBill; }

    //=======================================================================
    // ī�޶� ��� �ݿ�
    //=======================================================================
    D3DXMATRIXA16*	SetView(  D3DXVECTOR3* pvEye,D3DXVECTOR3* pvLookat,D3DXVECTOR3* pvUp);
	// ���� �����Ѵ�.
	void			Flush() { SetView( &m_vEye, &m_vLookat, &m_vUp ); }
	//=======================================================================
	// ī�޶� ��ġ ���� 
	//=======================================================================
	void			SetEye( D3DXVECTOR3* pv ) { m_vEye = *pv; }
	D3DXVECTOR3*	GetEye() { return &m_vEye; }	
	void			SetLookat( D3DXVECTOR3* pv ) { m_vLookat = *pv; }
	//void			SetLookat( D3DXVECTOR3 pv ) { m_vLookat = pv; }
	D3DXVECTOR3*	GetLookat() { return &m_vLookat; }
	void			SetUp( D3DXVECTOR3* pv ) { m_vUp = *pv; }	//
	D3DXVECTOR3*	GetUp() { return &m_vUp; }
	
	//=======================================================================
	// ī�޶� ȸ�� 
	//=======================================================================	
	D3DXMATRIXA16*	RotateLocalX( float angle );	
	D3DXMATRIXA16*	RotateLocalY( float angle );
	
	// ī�޶� ���콺 ó�� 
	float				m_RotxAxis;
	float				m_RotyAxis;
	float				m_Dist;

	float				m_prevxRot;
	float				m_prevyRot;
	float				m_prevDist;	
	void InitCamera(HWND hWnd);
	void UpdateCamera(float &xRot, float &yRot, float &dist, unsigned long &frame);
	

	//=======================================================================
	// ī�޶� �̵� 
	//=======================================================================	
	D3DXMATRIXA16*	MoveTo( D3DXVECTOR3* pv );	
	D3DXMATRIXA16*	MoveLocalX( float dist );
	D3DXMATRIXA16*	MoveLocalY( float dist );
	D3DXMATRIXA16*	MoveLocalZ( float dist );
};