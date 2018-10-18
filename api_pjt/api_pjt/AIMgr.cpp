#include "Monster.h"
#include "ManagerHeader.h"

AIMgr::AIMgr()
{
}


AIMgr::~AIMgr()
{
}

void AIMgr::Init()
{
	m_IsShowMajinBuu = false;
}

void AIMgr::update()
{
	GetPosition();
	AIMove();
}

void AIMgr::GetPosition()
{
	m_MonsterX = CharacterMgr::Instance()->GetPosition(true, false);
	m_MonsterY = CharacterMgr::Instance()->GetPosition(false, false);

	m_PlayerX = CharacterMgr::Instance()->GetPosition(true, true);
	m_PlayerY = CharacterMgr::Instance()->GetPosition(false, true);
}

void AIMgr::AIMove()
{
	if (!m_IsShowMajinBuu)
		return;

	GetPosition();

	int tempX,tempY;
	bool WatchX, WatchY; //bool is false = left
//	int SSJ_Status = BitMgr::Instance()->GetSSJ();

	tempX = m_PlayerX - m_MonsterX;
	tempY = m_PlayerY - m_MonsterY;
	WatchX = true;
	WatchY = true;

	if (tempX < 0) //left
	{
		tempX *= -1;
		WatchX = false;
	}

	if (tempY < 0)
	{
		tempY *= -1;
		WatchY = false;
	}

	if (tempX >= tempY)
	{
		if (WatchX)
		{
			CharacterMgr::Instance()->Move(TYPE_RIGHT, (eTYPE_KEY_TYPE)NULL, NULL, false);
		}
		else
		{
			CharacterMgr::Instance()->Move(TYPE_LEFT, (eTYPE_KEY_TYPE)NULL, NULL, false);
		}
	}
	else if(tempX <= tempY)
	{
		if (WatchY)
		{
			CharacterMgr::Instance()->Move(TYPE_FRONT, (eTYPE_KEY_TYPE)NULL, NULL, false);
		}
		else
		{
			CharacterMgr::Instance()->Move(TYPE_BACK, (eTYPE_KEY_TYPE)NULL, NULL, false);
		}
	}
	else
	{

	}
}