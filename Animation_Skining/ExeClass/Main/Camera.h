///////////////////////////////////////////
//게임속의 카메라를 관장하는 코드 입니다.//
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

	D3DXVECTOR3		m_vEye;			// 카메라의 현재 위치
	D3DXVECTOR3		m_vLookat;		// 카메라의 시선 위치
	D3DXVECTOR3		m_vUp;			// 카메라의 상방벡터

	D3DXVECTOR3		m_vView;		// 카메라가 향하는 단위방향벡터
	D3DXVECTOR3		m_vCross;		// 카마레의 측면벡터 cross( view, up )

	D3DXMATRIXA16	m_matView;		// 카메라 행렬
	D3DXMATRIXA16	m_matBill;		// 빌보드 행렬(카메라의 역행렬)

	//빌보드
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
	// 카메라,빌보드 행렬 얻기 
	//=======================================================================	
	D3DXMATRIXA16*	GetViewMatrix() { return &m_matView; }
	D3DXMATRIXA16*	GetBillMatrix() { return &m_matBill; }

    //=======================================================================
    // 카메라 행렬 반영
    //=======================================================================
    D3DXMATRIXA16*	SetView(  D3DXVECTOR3* pvEye,D3DXVECTOR3* pvLookat,D3DXVECTOR3* pvUp);
	// 값을 갱신한다.
	void			Flush() { SetView( &m_vEye, &m_vLookat, &m_vUp ); }
	//=======================================================================
	// 카메라 위치 설정 
	//=======================================================================
	void			SetEye( D3DXVECTOR3* pv ) { m_vEye = *pv; }
	D3DXVECTOR3*	GetEye() { return &m_vEye; }	
	void			SetLookat( D3DXVECTOR3* pv ) { m_vLookat = *pv; }
	//void			SetLookat( D3DXVECTOR3 pv ) { m_vLookat = pv; }
	D3DXVECTOR3*	GetLookat() { return &m_vLookat; }
	void			SetUp( D3DXVECTOR3* pv ) { m_vUp = *pv; }	//
	D3DXVECTOR3*	GetUp() { return &m_vUp; }
	
	//=======================================================================
	// 카메라 회전 
	//=======================================================================	
	D3DXMATRIXA16*	RotateLocalX( float angle );	
	D3DXMATRIXA16*	RotateLocalY( float angle );
	
	// 카메라 마우스 처리 
	float				m_RotxAxis;
	float				m_RotyAxis;
	float				m_Dist;

	float				m_prevxRot;
	float				m_prevyRot;
	float				m_prevDist;	
	void InitCamera(HWND hWnd);
	void UpdateCamera(float &xRot, float &yRot, float &dist, unsigned long &frame);
	

	//=======================================================================
	// 카메라 이동 
	//=======================================================================	
	D3DXMATRIXA16*	MoveTo( D3DXVECTOR3* pv );	
	D3DXMATRIXA16*	MoveLocalX( float dist );
	D3DXMATRIXA16*	MoveLocalY( float dist );
	D3DXMATRIXA16*	MoveLocalZ( float dist );
};