class ASEMesh{						
public:
	ASEMesh();
	~ASEMesh();

	int m_NumVertex;
	int m_NumIndex;
	vector<D3DXVECTOR3> m_VertexList;
	vector<MYINDEX> m_IndexList;

	int m_NumTextureVertex;
	int m_NumTextureFace;
	vector<D3DXVECTOR2> m_TextureVertexList;
	vector<MYINDEX> m_TextureFaceList;

	int m_iTexture;//먼지 모르겠음;;;;
	vector<CNormal*> m_NormalList;
};