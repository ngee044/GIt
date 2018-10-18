///////////////////////////////////////
//키입력 부분을 담당하는 코드 입니다.//
///////////////////////////////////////

#pragma once

#include "Common.h"


struct sKeyInfo
{
	//DirectionKey
	bool	m_bUp;
	bool	m_bDown;
	bool	m_bLeft;
	bool	m_bRight;

	//NomalKey
	bool	m_bLbutton;
	bool	m_bRbutton;
	bool	m_bZ;
	bool	m_Esc;
	bool	m_bN;
	bool	m_bB;

	bool	m_bDirectionKey;
	bool	m_bNomalKey;


	bool CheckDirectionKeyList();
	bool CheckNomalKeyList();

	bool CheckKey(int vKey);
	bool CheckKeyA(int vKey);

	sKeyInfo():
	m_bLbutton(false),m_bRbutton(false),
	m_bZ(false),m_bUp(false),m_bDown(false),m_bLeft(false),m_bRight(false),m_Esc(false),
		m_bDirectionKey(false),m_bNomalKey(false),m_bN(false),m_bB(false)
	{}
	~sKeyInfo(){};
};

class cKeyMgr
{
public:
	sKeyInfo	*m_sKeyInfo;

	static cKeyMgr*	m_KeyMgr;

	static cKeyMgr* CreateKeyMgr()
	{
		cKeyMgr *pKeyMgr=new cKeyMgr();
		sKeyInfo* p= new sKeyInfo;
		pKeyMgr->m_sKeyInfo=p;

		m_KeyMgr =pKeyMgr;

		return pKeyMgr;
	};

	static cKeyMgr* GetKeyMgr(){return m_KeyMgr;};

	cKeyMgr()
	{
		m_sKeyInfo=NULL;
	};
	~cKeyMgr()
	{
		if(m_sKeyInfo)
		{
			delete m_sKeyInfo;
		}
	};

	sKeyInfo* GetKeyState(){return m_sKeyInfo;};
	void InitKeyMgr();
	void UpdateKeyState();
};



