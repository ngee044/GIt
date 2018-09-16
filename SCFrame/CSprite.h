class Sprite{
	LPDIRECT3DDEVICE9 m_pd3dDevice;
	LPD3DXSPRITE m_sprite;
	LPDIRECT3DTEXTURE9 m_tex;
    D3DXMATRIX	m_matSprite;
	
	
public:
	Sprite(LPDIRECT3DDEVICE9 pdev);
	~Sprite();
	void Cleanup();
	void SetSpriteTrans(D3DXMATRIX trans);
	HRESULT CreateSprite(LPDIRECT3DTEXTURE9 tex,DWORD width,DWORD height);
	HRESULT CreateSprite(LPCSTR texname,DWORD width,DWORD height);
	void DrawSprite(D3DXVECTOR3 posit);

};
