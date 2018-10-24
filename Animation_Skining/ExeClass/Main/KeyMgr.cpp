///////////////////////////////////////
//키입력 부분을 담당하는 코드 입니다.//
///////////////////////////////////////
#include "KeyMgr.h"


cKeyMgr* cKeyMgr::m_KeyMgr=NULL;

bool sKeyInfo::CheckDirectionKeyList()
{
	bool bDirectionKey=false;

	//방향키
	m_bUp=CheckKey(VK_UP);
	m_bDown=CheckKey(VK_DOWN);
	m_bLeft=CheckKey(VK_LEFT);
	m_bRight=CheckKey(VK_RIGHT);


	if(m_bUp || m_bDown || m_bLeft || m_bRight)
	{
		bDirectionKey=true;
	}

	m_bDirectionKey=bDirectionKey;

	return m_bDirectionKey;
}
bool sKeyInfo::CheckNomalKeyList()
{
//	bool bNomalKey=false;

	//노말키
	m_bNomalKey=m_bZ=CheckKeyA(' ');
	m_bNomalKey=m_bZ=CheckKeyA(VK_RETURN);
	m_bNomalKey=m_bZ=CheckKeyA('A');
	m_bN=CheckKey('N');
	m_bB=CheckKey('B');
	//m_bLbutton=CheckKey(VK_LBUTTON);
	//m_bRbutton=CheckKey(VK_RBUTTON);

	//if(bNomalKey || m_bLbutton || m_bRbutton )
	//{
	//	bNomalKey=true;
	//}

	//m_bNomalKey=bNomalKey;

	return m_bNomalKey;
}
bool sKeyInfo::CheckKey(int vKey)
{
	bool Check=false;
	if( GetAsyncKeyState( vKey  )  )
	{Check=true;}

	return Check;
}

bool sKeyInfo::CheckKeyA(int vKey)
{
		bool Check=false;
	if( GetAsyncKeyState( vKey  )  )
	{Check=true;}
	//
	if( GetAsyncKeyState(' ') || GetAsyncKeyState(VK_RETURN))
	{Check=true;}
	//
	return Check;
}



void cKeyMgr::InitKeyMgr()
{
	m_sKeyInfo=new sKeyInfo();
}

void cKeyMgr::UpdateKeyState()
{
	m_sKeyInfo->CheckNomalKeyList();
	m_sKeyInfo->CheckDirectionKeyList();
}

