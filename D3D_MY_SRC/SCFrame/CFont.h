class Font{
	LPDIRECT3DDEVICE9 m_pd3dDevice;
	LPD3DXFONT	m_Font;
	UINT		m_FontPoint;
	DWORD		m_FontColor;
public:
	Font(LPDIRECT3DDEVICE9 pdev);
	~Font();
	HRESULT InitFont(int Point,LPSTR pName,DWORD Color=D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));
	void Cleanup();
	void Render(LPCSTR word,RECT rect);
};