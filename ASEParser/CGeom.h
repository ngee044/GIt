
class CGeom{
	LPDIRECT3DDEVICE9		m_pd3dDevice;
	LPDIRECT3DVERTEXBUFFER9	m_VertexBuffer;

public:
	CGeom(LPDIRECT3DDEVICE9 pdev);
	~CGeom();
	HRESULT MakeVertexBuffer();

	void	Render();
	void	UpdateAni(D3DXMATRIX matParents,float anidt);
	bool	GetPosTrack(float frame,D3DXVECTOR3* Pos);
	bool	GetRotTrack(float frame,D3DXQUATERNION* qr);

	int m_Materialref;
	TYPE Type;
	string m_NodeName,m_ParentsName;
	D3DXMATRIX m_GeomTM;
	D3DXMATRIX m_Current;

	CGeom* m_ParentsGeom;
	vector<CGeom*> m_ChildList;

	D3DXVECTOR3 m_Pos;
	D3DXVECTOR3 m_Rot;
	D3DXVECTOR3 m_Scale;

	ASEMesh* m_Mesh;

	vector<CPosTrack*> m_PosTrackList;
	vector<CRotTrack*> m_RotTrackList;
};