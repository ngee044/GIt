//////////////////////////////////////////////////////////////////////
//ASE ������ 3D�𵨸� ������ D3D9 ȯ������ �ҷ��������� �ڵ��Դϴ�.///
//////////////////////////////////////////////////////////////////////

#pragma once
#include "common.h"

class cMesh;
class CTextureContainer;
class cTmInfomation;
struct AniSCENE;


struct SVertex//���ؽ��� ���� ������ �ٷ�´� ����ü �Դϴ�.
{
	D3DXVECTOR3 v;

	D3DXVECTOR3 nv;

	DWORD Diffuse;
	
	float tu,tv;

	SVertex():
	v(0,0,0),
	nv(0,0,0),
	Diffuse(0xffffffff),
	tu(0),tv(0)
	{}
};

struct SIndex
{
	WORD m_0,m_1,m_2;

};

struct STvertlist//���ؽ� ����Ʈ ����ü �Դϴ�.
{
	float tu,tv,tw;
}; 

struct STriangle//�ﰢ���� �̷�� ����ü �Դϴ�. 3Dȯ���� �ּҴ��� �Դϴ�.
{
	SIndex		m_sFaceIndex;
	
	STvertlist	m_sTverlist[3];

	D3DXVECTOR3 m_vFaceNomal;

	D3DXVECTOR3	m_vVtNomal[3];

	DWORD		VertexColor[3];

	int			m_iMeterialID;

	bool		m_bDraw;

	void Init();

};



struct SMeterial//���׸����� �ٷ�� ����ü �Դϴ�.
{
	bool bUseTexture;		// �ؽ��� ��� ���� 

	bool bUseOpacity;		// opacity map ��� ���� 

	SMeterial	*m_SubMeterial;

	CTextureContainer *m_pTextureContainer;

	int			m_iSubMeterialCount;

	char		m_TextuerFileName[256];

	char		m_MtrName[256];

	D3DMATERIAL9 m_d3dMaterial;

	LPDIRECT3DTEXTURE9 m_pTexture;

	SMeterial():
	m_pTextureContainer(NULL),
	bUseTexture(false),
	bUseOpacity(false),
	m_SubMeterial(NULL),
	m_iSubMeterialCount(0),
	m_pTexture(NULL)
	{
	}

	~SMeterial()
	{
		if(m_SubMeterial)
			delete[] m_SubMeterial;
	}
};


struct sMeshContainer//�޽ø� ��� �޽������̳� ����ü �Դϴ�.
{
	cMesh *m_pData;

	sMeshContainer *m_pPrev;
	sMeshContainer *m_pNext;

	sMeshContainer():
	m_pData(NULL),
	m_pPrev(NULL),
		m_pNext(NULL)
	{
	}

	~sMeshContainer()
	{
		if(m_pNext)delete m_pNext;
	}

	void Add(sMeshContainer* pMC)
	{
		if(m_pNext)
		{
			m_pNext->Add(pMC);
		}
		else
		{
			m_pNext=pMC;
			pMC->m_pPrev=this;
		}
	}
};



struct sScale_Track//�������� Ʈ�� ������ �ٷ�� ����ü �Դϴ�.
{
	sScale_Track*	m_pNext;
	sScale_Track*	m_pPrev;

	int				m_iIndex;
	int				m_iMyLastIndex;

	float m_fX, m_fY, m_fZ;
	float m_aX, m_aY, m_aZ;
	float m_Ang;

	sScale_Track():
	m_iMyLastIndex(0),
	m_pNext(NULL),
	m_fX(0),m_fY(0),m_fZ(0),
	m_aX(0),m_aY(0),m_aZ(0),
	m_iIndex(0)
	{}

	~sScale_Track()
	{
		if(m_pNext)delete m_pNext;
	}
};

struct sPos_Track//������(��ġ)�� Ʈ�������� �ٷ�� ����ü �Դϴ�.
{
	sPos_Track*	m_pNext;
	sPos_Track*	m_pPrev;

	int			m_iIndex;
	int			m_iMyLastIndex;
	D3DXVECTOR3	m_Pos;

	sPos_Track():
	m_iMyLastIndex(0),
	m_pNext(NULL),
	m_pPrev(NULL),
	m_iIndex(0),
	m_Pos(0,0,0)
	{}

	~sPos_Track()
	{
		if(m_pNext)delete m_pNext;
	}
};

struct sRot_Track//�����̼�(ȸ��)�� Ʈ�� ������ �ٷ�� ����ü �Դϴ�.
{
	sRot_Track*	m_pNext;
	sRot_Track*	m_pPrev;

	int			m_iIndex;
	int			m_iMyLastIndex;
	float		m_x,m_y,m_z,m_w;

	D3DXQUATERNION	m_qrot;

	sRot_Track():
	m_pNext(NULL),
	m_pPrev(NULL),
	m_iMyLastIndex(0),
	m_iIndex(0),
	m_x(0),m_y(0),m_z(0),m_w(0),
	m_qrot(0,0,0,0)
	{}

	~sRot_Track()
	{
		if(m_pNext)delete m_pNext;
	}
};


struct sAnimation//���ϸ��̼� ������ �ٷ�� ����ü �Դϴ�. 
{
	char			m_Name[128];
	char			m_AniName[128];

	AniSCENE*		m_pNowAniScene;

	sAnimation*		m_pNext;
	sAnimation*		m_pPrev;

	sScale_Track*	m_Scale;

	sPos_Track*		m_Pos;

	sRot_Track*		m_Rot;

	sAnimation():
	m_pNowAniScene(NULL),
	m_Scale(NULL),
	m_Pos(NULL),
	m_Rot(NULL),
	m_pNext(NULL),
	m_pPrev(NULL)
	{}
	~sAnimation()
	{
		if(m_Scale)delete m_Scale;
		if(m_Pos)delete m_Pos;
		if(m_Rot)delete m_Rot;
	}

public:
	void Add(sAnimation* pANI)
	{
		if(m_pNext)
		{
			m_pNext->Add(pANI);
		}
		else
		{
			m_pNext=pANI;
			pANI->m_pPrev=this;
		}
	}

	sPos_Track* GetNowPosTrack(float Frame);

	sRot_Track*	GetNowRotTrack(float Frame);

	sScale_Track* GetNowScaleTrack(float Frame);
};

struct AniSCENE//���ϸ��̼��� ��(scene) ������ �ٷ�� ����ü �Դϴ�.
{
	AniSCENE*	m_pNext;
	AniSCENE*	m_pPrev;

	char					m_AniName[256];
	bool					m_bTransition;
	bool					m_bEndMotion;
	float					m_FirstFrame; 
	float					m_LastFrame;
	float					m_TickPerFrame;
	float					m_FrameSpeed;

	AniSCENE():
	m_pNext(NULL),
	m_pPrev(NULL),
	m_bTransition(false),
	m_bEndMotion(false),
	m_FirstFrame(0),m_LastFrame(0),m_TickPerFrame(0),m_FrameSpeed(0)
	{}

	AniSCENE* Search(char *pAniName)
	{
		if(_stricmp(m_AniName, pAniName)==0)
		{
			return this;
		}
		else
		{
			if(m_pNext)
			{
				m_pNext->Search(pAniName);
			}
			else
			{
				return NULL;
			}
		}
	}

	void Add(AniSCENE* pANI)
	{
		if(m_pNext)
		{
			m_pNext->Add(pANI);
		}
		else
		{
			m_pNext=pANI;
			pANI->m_pPrev=this;
		}
	}
};


struct AnimationControl //���ϸ��̼��� ��Ʈ�� �ϱ� ���� ����ü �Դϴ�.
{
	BOOL	Transition;
	float					m_NowFrame;
	float					m_FirstFrame; 
	float					m_LastFrame;
	float					m_TickPerFrame;
	float					m_FrameSpeed;
};

struct sBlandVertexInfo//���ؽ� ������ ���� ����ü �Դϴ�.
{
	char		m_NodeName[256];
	cMesh*		m_pMesh;
	float		m_fWeight;
	D3DXVECTOR3	m_vBipLocal;

	sBlandVertexInfo():
	m_pMesh(NULL),
	m_fWeight(0),
	m_vBipLocal(0,0,0)
	{}
};

struct sSkinningVertex//��Ű���� ���� ����ü �Դϴ�.
{
	int			m_NumBlend;
	int			m_VtIndex;
	bool		m_bBland;

	D3DXVECTOR3*	m_pVertex;
	sBlandVertexInfo *m_pBlandVt;

	sSkinningVertex():
	m_NumBlend(0),m_VtIndex(0),m_pVertex(NULL),m_pBlandVt(NULL),m_bBland(false)
	{}
	~sSkinningVertex()
	{
		delete[] m_pBlandVt;
	}

	void MakeLoaclVt(cMesh* pMeshList,cMesh* pBoneList);
	cMesh* SearchMesh(cMesh* pList,char* Name);

};

struct sViewList
{
	sViewList*	m_pNext;

	SVertex*	m_pVertex;

	sSkinningVertex* m_pSknVt;

	int			m_iNumVertex;

	int			m_iMaxVertex;

	int*		m_pSkinningVtIndex;

	int*		m_pIndex;

	SMeterial*	m_pMeterial;

	sViewList():
	m_pSknVt(NULL),
	m_pNext(NULL),
	m_pVertex(NULL),
	m_iNumVertex(0),
	m_iMaxVertex(0),
	m_pIndex(NULL),
	m_pMeterial(NULL)
	{}
	~sViewList()
	{
		if(m_pNext)delete m_pNext;
		if(m_pVertex)delete m_pVertex;
		if(m_pIndex)delete m_pIndex;
	}

	inline void Add(sViewList* pData)
	{
		if(m_pNext)
		{
			m_pNext->Add(pData);
		}
		else
		{
			m_pNext=pData;
		}
	}
};

class cMesh//�޽��� �����ϴ� Ŭ���� �Դϴ�.
{
	public:
		bool		m_bParents;
		bool		m_bAniData;

		cMesh*		m_pNext;
		cMesh*		m_pParents;

		sViewList*	m_pViewList;

		char		m_NodeName[256];
		char		m_parentsName[256];

		int			m_iNumVertex;
		int			m_iNumPhysiqueVt;
		int			m_iNumFace;  
		int			m_iNumTvVertex;
		int			m_iNUMTVFACES;
		int			m_iNumColorVt;
		int			m_iNumColorFace;
		int			m_iMeterial_Ref;
		
		STriangle	*m_sTriangle;
		SVertex*	m_sVertex;	
		sSkinningVertex* m_sSkinningVt;//��������Ÿ
		STvertlist* m_sTvertlist;
		SMeterial*	m_sMeterial;

		sMeshContainer* m_pChild;

		cTmInfomation* m_pTmInfoList;

		sAnimation	m_sAnimation;

		sAnimation	*m_pAniList;

		sAnimation  *m_NowAnimation;

		sAnimation	*m_DestAnimation;

		D3DXCOLOR* m_ColorList;
		D3DXMATRIX	m_AniMat;
		D3DXMATRIX	m_TmMat;
		D3DXMATRIX	m_InvTm;
		D3DXVECTOR3		m_TmPos;
		D3DXQUATERNION	m_TmRot;
		D3DXMATRIX		m_TransRotMat;	//��� ��Ʈ 
		D3DXVECTOR3		m_vTransvec;

		D3DXVECTOR3		m_TmScale;
		D3DXQUATERNION	m_TmScaleRot;

		void AddChild(cMesh* pMesh);

		void MakeIndex(SMeterial* pMeterial);

		void MakeVertex();

		cMesh()
		{
			m_pTmInfoList=NULL;
			m_sSkinningVt=NULL;
			m_pAniList=NULL;
			m_pViewList=NULL;
			m_pNext=NULL;
			m_pParents=NULL;
			m_pChild=NULL;
			m_bParents=false;
			m_bAniData=false;
			m_iNumVertex=0;
			m_iNumFace=0;
			m_iNumTvVertex=0;
			m_iNUMTVFACES=0;
			m_iNumColorVt=0;
			m_iNumColorFace=0;
			m_iMeterial_Ref=0;
			m_sTriangle=NULL;
			m_sVertex=NULL;	
			m_sTvertlist=NULL;
			m_sMeterial=NULL;
			m_ColorList=NULL;
		};
		~cMesh()
		{
			delete []m_sTriangle;
			delete []m_sVertex;	
			delete []m_sTvertlist;
			delete []m_sMeterial;
			delete []m_ColorList;
		};

public:
	void UpdateAniTm(char *pAniName,D3DXMATRIX matParents,float frame);
	void UpdateTransitionAniTm(char *pDestAniName,D3DXMATRIX matParents,float Nowframe);
	void UpdateSkinning();
};

class CAse//ASE������ ��ü���� ������ �ٷ�� Ŭ���� �Դϴ�.
{
public:
	char*					m_pAniName;

	float					m_NowFrame;

	float					m_FirstFrame; 

	float					m_LastFrame;

	float					m_TickPerFrame;

	float					m_FrameSpeed;

	bool					m_NormalFlag;

	char					m_str[80];

	char					m_line[256];

	int						m_iNumMaterial;

	SMeterial*				m_Meterial;

	sAnimation				*m_pAniList;

	cMesh*					m_pMeshList;//��Ų�޽�
	cMesh*					m_pBoneList;//���޽�
	cMesh*					m_pNowMesh;//���� ����ǰ��ִ� �޽�

	CTextureContainer* m_pTextureContainer;

	LPDIRECT3DDEVICE9		m_pd3dDevice;

	LPDIRECT3DVERTEXBUFFER9 m_pVB;

	LPDIRECT3DINDEXBUFFER9 m_pIB;

public:

	void UpdateAnimation(float Frame);

	void BoneAnimation(D3DXMATRIX mat,float frame);

	void MeshAnimation(D3DXMATRIX mat,float frame);
	
	void SetDevice(LPDIRECT3DDEVICE9 Device){m_pd3dDevice=Device;}

	HRESULT LoadAse(char* FileName);

	void ReadSCENE(FILE *pf);

	void ReadMATERIAL_LIST(FILE *pf);
	void ReadMATERIAL(FILE *pf,SMeterial* pNowMeterial);
	void ReadMtrTextureName(FILE *pf,SMeterial *pNowMeterial);

	void ReadFileName(char* Src,char *Dest);

	void ReadGEOMOBJECT(FILE *pf);
	void ReadPHYSIQUE(FILE *pf);
	void ReadPHYSIQUE_VT_LIST(FILE *pf);
	void ReadTM(FILE *pf);

	void ReadAnimation(sAnimation *p_Animation,FILE *pf);
	void ReadAniMationFromFile(char* AniFileName);
	void ReadPos_Track(sAnimation *p_Animation,FILE *pf);
	void ReadScale_Track(sAnimation *p_Animation,FILE *pf);
	void ReadRot_Track(sAnimation *p_Animation,FILE *pf);

	void ReadMESH(FILE *pf);
	void ReadMESH_VERTEX_LIST(FILE *pf);
	void ReadMESH_FACE_LIST(FILE *pf);
	void ReadMESH_TVERTLIST(FILE *pf);
	void ReadMESH_TFACELIST(FILE *pf);

	void ReadMESH_CVERTEX(FILE *pf);
	void ReadMESH_CFACELIST(FILE *pf);
	void ReadMESH_NORMALS(FILE *pf);


	void AddBone(cMesh* pNowMesh);
	void AddMesh(cMesh* pNowMesh);

	void MakeFaceNormalFromWorldVertex();
	void MakeVertexNormalFromFaceNormal();

	void MakeInherite();

	void MakeSkinningLocal();

	void SetAllMesh();

	cMesh* Search(char* Name);
	cMesh* SearchBone(char* Name);

	void Alpha(bool flag);


	//�ʱ�ȭ �Լ�
	HRESULT MakeVertexBuffer();
	HRESULT MakeIndexBuffer();
	void	SetUvVertexIndex();

	
	void LoadAseTexture();

	void RenderAse(D3DXMATRIX Scalemat,D3DXMATRIX Rotmat,D3DXMATRIX Posmat,cMesh* pNowMesh);
	//�׸��� �Լ� 

	CAse()
	{
		m_pAniName=NULL;
		m_pAniList=NULL;
		m_NowFrame=0.0f;
		m_FirstFrame=0.0f; 
		m_LastFrame=0.0f; 
		m_TickPerFrame=0.0f; 
		m_FrameSpeed=0.0f; 
		m_NormalFlag=false;
		m_pTextureContainer=NULL;
		m_iNumMaterial=0;
		m_Meterial=NULL;
		m_pMeshList=NULL;
		m_pBoneList=NULL;
		m_pNowMesh=NULL;
		m_pd3dDevice=NULL;
		m_pVB=NULL;
		m_pIB=NULL;
	};		//������
	~CAse()
	{
	};	//�Ҹ���
};

class cBaseMesh;

struct sBaseMeshContainer//���̽� �޽��� �����̳� �Դϴ�.
{
	cBaseMesh *m_pData;

	sBaseMeshContainer *m_pPrev;
	sBaseMeshContainer *m_pNext;

	sBaseMeshContainer():
	m_pData(NULL),
	m_pPrev(NULL),
		m_pNext(NULL)
	{
	}

	~sBaseMeshContainer()
	{
		if(m_pNext)delete m_pNext;
	}

	void Add(sBaseMeshContainer* pMC)
	{
		if(m_pNext)
		{
			m_pNext->Add(pMC);
		}
		else
		{
			m_pNext=pMC;
			pMC->m_pPrev=this;
		}
	}
};

class cBaseMesh//���̽� �޽��� �ٷ�� Ŭ���� �Դϴ�.
{
public:
		LPDIRECT3DDEVICE9		m_pd3dDevice;

		bool		    m_bParents;

		cBaseMesh*		m_pNext;
		cBaseMesh*		m_pParents;

		sViewList*	m_pViewList;

		char		m_NodeName[256];
		char		m_parentsName[256];

		int			m_iNumVertex;
		int			m_iNumFace;  
		int			m_iNumTvVertex;
		int			m_iNUMTVFACES;
		int			m_iNumColorVt;
		int			m_iNumColorFace;
		int			m_iMeterial_Ref;
		
		STriangle	*m_sTriangle;
		SVertex*	m_sVertex;	
		STvertlist* m_sTvertlist;
		SMeterial*	m_sMeterial;

		sBaseMeshContainer* m_pChild;

		D3DXCOLOR* m_ColorList;

		D3DXMATRIX		m_TmMat;
		D3DXMATRIX		m_InvTm;
		D3DXVECTOR3		m_TmPos;
		D3DXQUATERNION	m_TmRot;

		D3DXVECTOR3		m_TmScale;
		D3DXQUATERNION	m_TmScaleRot;

		void SetDevice(LPDIRECT3DDEVICE9 Device){m_pd3dDevice=Device;};
		LPDIRECT3DDEVICE9 GetDevice(){return m_pd3dDevice;};

		virtual void AddChild(cBaseMesh* pMesh);

		virtual void MakeIndex(SMeterial* pMeterial);

		virtual void MakeVertex();

		virtual void Render(D3DXMATRIX WorldTm);

		void Alpha(bool flag);

		cBaseMesh()
		{
			m_pViewList=NULL;
			m_pNext=NULL;
			m_pParents=NULL;
			m_pChild=NULL;
			m_bParents=false;
			m_iNumVertex=0;
			m_iNumFace=0;
			m_iNumTvVertex=0;
			m_iNUMTVFACES=0;
			m_iNumColorVt=0;
			m_iNumColorFace=0;
			m_iMeterial_Ref=0;
			m_sTriangle=NULL;
			m_sVertex=NULL;	
			m_sTvertlist=NULL;
			m_sMeterial=NULL;
			m_ColorList=NULL;
		};
		~cBaseMesh()
		{
			delete []m_sTriangle;
			delete []m_sVertex;	
			delete []m_sTvertlist;
			delete []m_sMeterial;
			delete []m_ColorList;
		};
};


class cBaseAse//���̽� ASE������ �ٷ�� Ŭ���� �Դϴ�.
{
public:

	bool						m_NormalFlag;

	char						m_str[80];

	char						m_line[256];

	int							m_iNumMaterial;

	SMeterial*					m_Meterial;

	cBaseMesh*					m_pMeshList;

	cBaseMesh*					m_pNowMesh;

	CTextureContainer* m_pTextureContainer;

	LPDIRECT3DDEVICE9		m_pd3dDevice;

	LPDIRECT3DVERTEXBUFFER9 m_pVB;

	LPDIRECT3DINDEXBUFFER9 m_pIB;

public:
	void JumpFIlePointer(int Num,FILE *pf);

	void SetDevice(LPDIRECT3DDEVICE9 Device){m_pd3dDevice=Device;}

	HRESULT LoadAse(char* FileName);

	void ReadMATERIAL_LIST(FILE *pf);
	void ReadMATERIAL(FILE *pf,SMeterial* pNowMeterial);
	void ReadMtrTextureName(FILE *pf,SMeterial *pNowMeterial);

	void ReadFileName(char* Src,char *Dest);

	void ReadGEOMOBJECT(FILE *pf);
	void ReadTM(FILE *pf);

	void ReadMESH(FILE *pf);
	void ReadMESH_VERTEX_LIST(FILE *pf);
	void ReadMESH_FACE_LIST(FILE *pf);
	void ReadMESH_TVERTLIST(FILE *pf);
	void ReadMESH_TFACELIST(FILE *pf);

	void ReadMESH_CVERTEX(FILE *pf);
	void ReadMESH_CFACELIST(FILE *pf);
	void ReadMESH_NORMALS(FILE *pf);

	void AddMesh(cBaseMesh *pNowMesh);

	void MakeFaceNormalFromWorldVertex();
	void MakeVertexNormalFromFaceNormal();

	void MakeInherite();

	void SetAllMesh();

	cBaseMesh* Search(char* Name);

	//�ʱ�ȭ �Լ�
	HRESULT MakeVertexBuffer();
	HRESULT MakeIndexBuffer();
	void	SetUvVertexIndex();

	void LoadAseTexture();

	void RenderAse(D3DXMATRIX Scalemat,D3DXMATRIX Rotmat,D3DXMATRIX Posmat);
	//�׸��� �Լ� 

	cBaseAse()
	{
		m_NormalFlag=false;
		m_pTextureContainer=NULL;
		m_iNumMaterial=0;
		m_Meterial=NULL;
		m_pMeshList=NULL;
		m_pNowMesh=NULL;
		m_pd3dDevice=NULL;
		m_pVB=NULL;
		m_pIB=NULL;
	};		//������
	~cBaseAse()
	{

	
	};	//�Ҹ���
};

