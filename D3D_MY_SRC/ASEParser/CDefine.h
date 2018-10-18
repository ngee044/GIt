enum TYPE {NOT,MESH,BONE};

struct CScene{						//ASE전체 파일의 정보를 담고있따
	float m_FirstFrame;
	float m_LastFrame;
	float m_FrameSpeed;
	float m_TickPerFrame;
};

struct CMaterial{					//메터리얼 정보
	CMaterial(LPDIRECT3DDEVICE9 pdev);
	~CMaterial();
	HRESULT CreateTexture();
	void SetTexture();
	void SetMaterial();
	LPDIRECT3DDEVICE9 m_pd3dDevice;
	D3DMATERIAL9 m_Material;
	LPDIRECT3DTEXTURE9	m_Texture;
	D3DXVECTOR3 m_Ambient;
	D3DXVECTOR3 m_Diffuse;
	D3DXVECTOR3 m_Specular;
	string m_TextureName;	
};

struct CNormal {						//메쉬의 노말값이다
	D3DXVECTOR3 m_FaceNormal;
	DWORD		m_NormalIndex[3];
	D3DXVECTOR3 m_VertexNormal[3];
};

struct CPosTrack {					//에니메이션할때 포지션 트랙
	float m_Time;
	D3DXVECTOR3 m_Pos;
};

struct CRotTrack {					//에니메이션 할때 포지션 로테이션
	float m_Time;
	D3DXQUATERNION m_Rot;
};

class CGameMyApp;

class CAniTime
{
	CGameMyApp *m_myapp;
	bool m_IsStop;
public:
	float m_StartTime;
	float m_EndTime;
	float m_CurrentTime;
	CAniTime();
	void Init(float firstframe,float endframe,float tickperframe);
	void Update(float dt);
	float GetDT(){return m_CurrentTime;}
	void SetStop(bool index) { m_IsStop = index; }
	bool GetStop() { return m_IsStop; }
};

class CharacterClass
{
	D3DMATRIX m_Rot;
	CASE *m_pAse;

public:
	void Render();
	void UpdateTransitionAni();
	void Update();
};