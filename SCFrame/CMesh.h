class Mesh{
	LPDIRECT3DDEVICE9 m_pd3dDevice;
	LPD3DXMESH m_Mesh;
	D3DMATERIAL9* m_MeshMaterial;
	LPDIRECT3DTEXTURE9* m_MeshTexture;
	DWORD m_numMaterial;
public:
	Mesh(LPDIRECT3DDEVICE9 pdev);
	~Mesh();
	LPD3DXMESH GetMesh(){return m_Mesh;}
	HRESULT InitMesh(LPCSTR filename);
	void Render();
	void Cleanup();


};
