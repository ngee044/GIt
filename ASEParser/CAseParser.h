//이번에는 ASE파서에 도전한다....쉬운 여정은 아니지만 최선을 다해봐야지~
	
class CASE
{
	LPDIRECT3DDEVICE9 m_pd3dDevice;
	char* m_Filename;
	CScene* m_Scene;
	vector<CMaterial*> m_MaterialList;
	vector<CGeom*>	   m_GeomList;

	CAniTime*	m_AniTime;

	int m_LineCount;
	char m_TempLine[256];
	char m_TempString[80];

public:
	CASE(LPDIRECT3DDEVICE9 pdev);
	~CASE();
	
	void	Init();
	void	Render();
	void	StartUpdate(D3DXMATRIX matWorld,float dt);
	CGeom*  Search(string filename);
	HRESULT MakeParents();
	HRESULT ReadASE(char* filename);							//전체적인구조	
	HRESULT DecodeASE(FILE *fp);
	void ReadGEOMOBJECT(FILE * pf);
	void ReadPHYSIQUE(FILE * pf);
	//ReadASE
	void ReadPHYSIQUE_VT_LIST(FILE * pf);
	HRESULT DecodeSCENE(FILE *fp);								//		DecodeASE	
	HRESULT DecodeMATERIAL(FILE* fp,CMaterial *Material);		//		DecodeScene
	HRESULT DecodeMATERIALLIST(FILE* fp);						//		DecodeMaterialList		
	HRESULT DecodeGEOM(FILE *fp);								//		DecodeMaterial
	HRESULT DecodePOSTRACK(FILE* fp,CGeom* Geom);				//		DecodeGeom	
	HRESULT DecodeROTTRACK(FILE* fp,CGeom* Geom);				//		DecodeTM
	HRESULT DecodeTM(FILE *fp,CGeom* Geometri);					//		DecodeMesh
	HRESULT DecodeMESH(FILE *fp,ASEMesh* Geometri);				//		DecodePOSROT	
	void	Cleanup();

	Mesh *m_pNowMesh;

};
