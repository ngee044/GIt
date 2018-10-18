///////////////////////////////////////////////////
//���Ӽ� ĳ������ ���� �Ӽ��� �����ϴ� �ڵ��Դϴ�//
///////////////////////////////////////////////////

#pragma once
#include "ASE.h"

struct sAnimation;
struct AniSCENE;
class CAse;
class cMesh;
class cTmInfomation;
struct sKeyInfo;

typedef enum enum_DirectionState //���� ����
{
	DIRECTION_NONE,
	DIRECTION_UP,DIRECTION_DOWN,
	DIRECTION_LEFT,DIRECTION_RIGHT,
	DIRECTION_UP_LEFT,DIRECTION_UP_RIGHT,
	DIRECTION_DOWN_LEFT,DIRECTION_DOWN_RIGHT
};

typedef enum enum_WordKeyState //����Ű�� ����
{
	WORDKEY_NONE,
	WORDKEY_Z,
};

typedef enum enum_ActionState	//ĳ������ �׼� ����
{
	ACTION_IDLE,ACTION_RUN,ACTION_ATT
};

class cTmInfomation //TM(translation matrix) ������ �ٷ�� Ŭ����
{
public:
		char			m_AniName[128];
		char			*m_pbipName;

		cTmInfomation *m_pNext;
		cTmInfomation *m_pPrev;

		D3DXMATRIX		m_TmMat;
		D3DXMATRIX		m_InvTm;
		D3DXVECTOR3		m_TmPos;
		D3DXQUATERNION	m_TmRot;
		D3DXMATRIX		m_TransRotMat;	//��� ��Ʈ 
		D3DXVECTOR3		m_vTransvec;

		D3DXVECTOR3		m_TmScale;
		D3DXQUATERNION	m_TmScaleRot;

		void Add(cTmInfomation *pTemp)
		{
			if(m_pNext==NULL)
			{
				m_pNext=pTemp;
				m_pNext->m_pPrev=this;
			}
			else
			{
				m_pNext->Add(pTemp);
			}
		}

		cTmInfomation* SeachTmInfo(char* AniName)
		{
			if(_stricmp(AniName, m_AniName)==0)
			{
				return this;
			}
			else
			{
				if(m_pNext)
				{
					m_pNext->SeachTmInfo(AniName);
				}
				else
				{
					return NULL;
				}
			}
		}


		cTmInfomation()
		{
			m_pNext=NULL;
			m_pPrev=NULL;
		};
		~cTmInfomation(){};

};

class cBoundingBox //�ٿ���ڽ��� ���� Ŭ����(������ �ʾҴ�)
{
public:
	float m_xMin;
	float m_xMax;

	float m_yMin;
	float m_yMax;

	float m_zMin;
	float m_zMax;

	D3DXVECTOR3 m_vLocal;
	D3DXVECTOR3 m_vBoundingMin;
	D3DXVECTOR3 m_vBoundingMax;


	cBoundingBox()
	{
		m_xMin=m_xMax=m_yMin=m_yMax=m_zMin=m_zMax=0.0f;
		m_vLocal=D3DXVECTOR3(0.0f,0.0f,0.0f);
		UpdateLocal(m_vLocal);

	};

	cBoundingBox(float xMin,float xMax,float y_Min,float y_Max,float z_Min,float z_Max)
	{
		m_xMin=xMin;m_xMax=xMax;m_yMin=y_Min;m_yMax=y_Max;m_zMin=z_Min;m_zMax=z_Max;

		m_vBoundingMin.x=m_xMin;
		m_vBoundingMin.y=m_yMin;
		m_vBoundingMin.z=m_zMin;

		m_vBoundingMax.x=m_xMax;
		m_vBoundingMax.y=m_yMax;
		m_vBoundingMax.z=m_zMax;
	}

	void UpdateLocal(D3DXVECTOR3 vLocal)
	{
		m_vLocal=vLocal;

		m_vBoundingMin.x=vLocal.x+m_xMin;
		m_vBoundingMin.y=vLocal.y+m_yMin;
		m_vBoundingMin.z=vLocal.z+m_zMin;

		m_vBoundingMax.x=vLocal.x+m_xMax;
		m_vBoundingMax.y=vLocal.y+m_yMax;
		m_vBoundingMax.z=vLocal.z+m_zMax;
	}

	BOOL TestHit(D3DXVECTOR3 Position)
	{
		if(Position.x < m_vBoundingMin.x)
			return false;
		if(Position.x > m_vBoundingMax.x)
			return false;
		if(Position.y < m_vBoundingMin.y)
			return false;
		if(Position.y > m_vBoundingMax.y)
			return false;
		if(Position.z < m_vBoundingMin.z)
			return false;
		if(Position.z > m_vBoundingMax.z)
			return false;

		return true;
	}
	~cBoundingBox()
	{};
};




class CharacterClass // ĳ������ ���� �ٷ�� Ŭ���� �Դϴ�.
{
public:
	LPDIRECT3DDEVICE9	m_pDevice;

	CAse*	m_pAse;

	bool	m_bMove;

	bool    m_ATT;

	bool	m_AttIdle;

	bool	m_bAniFrameIdle;

	char	m_Name[128];

	char    m_NowAnimationName[128];

	char    m_BeforeAniName[128];

	bool	m_bEndMotion;

	bool	m_bTransitionAni;

	float   m_Power;

	float   m_Radius;

	float	m_FrameSpeed;

	float	MoveSpeed;

	float   m_AniFrame;

	float	m_TransitionFrame;

	D3DXMATRIX m_Scale;

	D3DXMATRIX m_Rot;

	D3DXMATRIX m_Pos;

	D3DXQUATERNION m_qRot;

	D3DXQUATERNION m_qDestRot;

	bool		   m_bTransRot;

	float		   m_fTransRot;

	D3DXVECTOR3 m_Direction;

	D3DXVECTOR3 m_DestDir;

	D3DXVECTOR3 m_Cross;

	D3DXVECTOR3 m_Up;

	float m_fAttGage;
	float m_fAttStartFrame;
	float m_fAttEndFrame;
	float m_fAttFrameSpeed;

////////////////////////////////////////////////
	enum_DirectionState		m_eDirectionState;
	enum_ActionState		m_eActionState;
	enum_WordKeyState		m_eWordKeyState;

	AniSCENE*		m_pAniSceneList;
	AniSCENE*		m_pNowAniScene;

	cBoundingBox*	m_BoundingBox;
/////////////////////////////////////////////////
	//ĳ���� ��� ����
	bool bUsed;
	//�ð��� ����
	int iTime;
////////////////////////////


	//sAnimation	*m_pAniList;
	//sAnimation  *m_NowAnimation;
	//sAnimation	*m_DestAnimation;
	void SetNowAniScene(char* AniName);
	void SetAnimation(char* AniName);

	void ReadFileName(char* Src,char *Dest);

	void ReadAniMationFromFile(char* AniFileName);
	void ReadRot_Track(cTmInfomation *pTmInfo,sAnimation *p_Animation,FILE *pf);
	void ReadAnimation(cTmInfomation *pTmInfo,sAnimation *p_Animation,FILE *pf);
	void InitCharacter(LPDIRECT3DDEVICE9 pDevice,char* AseFileName,char* ModelName);

	void ReadTm(cTmInfomation *pTmInfo,FILE* fp);
	//void ReadAnimation(cTmInfomation *pTmInfo,sAnimation *p_Animation,FILE *pf);

	void SetDevice(LPDIRECT3DDEVICE9 pDevice){m_pDevice=pDevice;};
	LPDIRECT3DDEVICE9 GetDevice(){return m_pDevice;};


	void Update();
	//Update() ���� ���� �żҵ�  
	//////////////////////////////////////////
	void UpdateProcessKey(sKeyInfo* spKeyInfo); //���� Ű���»̱�
	void UpdateState();							//�������� ���°���
	void UpdateAnimation();						//�⺻ ���ϸ��̼� ������Ʈ
	void UpdateTransitionAni();					//���� ���ϸ��̼� ������Ʈ
	void TransRot();							//ȸ�������Ͽ� ȸ�� ��ķ� �̱�
	void UpdateAniFrame();
	////////////////////////////////////////

	//UpdateState() ���� ���� �޼ҵ� 
	///////////////////////////////////////
	void UpdateActionState();					//���� ���ǻ��� �̾� Ű���¿� �����Ͽ� �׼� ����
	void UpdateMove();							//ĳ������ǥ ����
	void UpdateDestqRot();						//(������) ȸ�����ʹϿ� �̱�
	///////////////////////////////////////

	//UpdateActionState() ���� ���� �żҵ�
	//////////////////////////////////////
	void IDLE_ActionProcess();				//������ ó��
	void RUN_ActionProcess();				//�ٱ���� ó��
	void ATT_ActionProcess();				//���ݻ��� ó�� 
	//////////////////////////////////////




	void Render();

	CharacterClass()
	{
		
		m_fAttFrameSpeed=0.0f;
		m_fAttGage=0.0f;
		m_fAttStartFrame=0.0f;
		m_fAttEndFrame=0.0f;
		m_Power=0.3f;
		m_bMove=true;
		m_bAniFrameIdle=false;
		m_AttIdle=false;
		m_bEndMotion=false;
		m_eWordKeyState=WORDKEY_NONE;
		m_eDirectionState=DIRECTION_NONE;
		m_eActionState=ACTION_IDLE;
		m_Radius=5.0f;
		m_ATT=false;
		m_AniFrame=0.0f;
		m_TransitionFrame=0.0f;
		::strcpy(m_NowAnimationName,"STAND");
		::strcpy(m_BeforeAniName,"STAND");
		m_bTransitionAni=false;
		float fx=0.0f,fy=1.0f,fz=0.0f,fw=0.0f;
		m_qRot.w=cosf(fw /2.0f);
		m_qRot.x=sinf(fw /2.0f) * fx;
		m_qRot.y=sinf(fw /2.0f) * fy;
		m_qRot.z=sinf(fw /2.0f) * fz;

		m_qDestRot.w=cosf(fw /2.0f);
		m_qDestRot.x=sinf(fw /2.0f) * fx;
		m_qDestRot.y=sinf(fw /2.0f) * fy;
		m_qDestRot.z=sinf(fw /2.0f) * fz;

		m_fTransRot=0.0f;
		m_bTransRot=false;
		m_pAse=NULL;
		m_pAniSceneList=NULL;
		MoveSpeed=1.0f;
		D3DXMatrixIdentity(&m_Scale);
		D3DXMatrixIdentity(&m_Rot);
		D3DXMatrixIdentity(&m_Pos);
		//m_Pos._42=-20.0f;
		m_Direction=D3DXVECTOR3(0.0f,0.0f,-1.0f);
		m_DestDir=D3DXVECTOR3(0.0f,0.0f,-1.0f);
		m_Cross=D3DXVECTOR3(1.0f,0.0f,0.0f);
		m_Up=D3DXVECTOR3(0.0f,1.0f,0.0f);
		bUsed = false;
		iTime = NULL;


	};
	~CharacterClass()
	{
		if(m_pAse)
		delete m_pAse;
	};

	float Get_pos_x();
	float Get_pos_z();
	
};
