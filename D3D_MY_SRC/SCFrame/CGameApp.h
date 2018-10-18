class CGameApp{
protected:

	LPDIRECT3D9             m_pD3D;
	LPDIRECT3DDEVICE9       m_pd3dDevice;
	D3DPRESENT_PARAMETERS   m_pd3dpp;
	HWND					m_hWnd;
	HWND					m_hWndFocus;
public:
	CGameApp();
	virtual ~CGameApp() {}
	virtual LRESULT MsgProc( HWND m_hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
	virtual HRESULT Create(HINSTANCE hInst);
	virtual HRESULT Run();
	
	virtual HRESULT Init()		{return S_OK;}
	virtual HRESULT InitMatrix(){return S_OK;}
	virtual HRESULT Update()	{return S_OK;}
	virtual HRESULT Render()	{return S_OK;}
	virtual HRESULT Cleanup()	{return S_OK;}

};