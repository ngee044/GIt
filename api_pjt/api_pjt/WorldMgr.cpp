#include "ManagerHeader.h"
#include "Common.h"
#include "World.h"
#include "BitMap.h"
#include <windows.h>

WorldMgr::WorldMgr()
{
}

WorldMgr::~WorldMgr()
{
}

void WorldMgr::Init()
{
}

void WorldMgr::CreatBattle()
{

}

void WorldMgr::Reset()
{

}

void WorldMgr::Delete()
{

}

void WorldMgr::MapEvent(eTYPE_EVENT type)
{
	int x, y;

	x = CharacterMgr::Instance()->GetPosition(1, 1);
	y = CharacterMgr::Instance()->GetPosition(0, 1);

	if (type == TYPE_EVENT_ONE && m_mapstatus == TYPE_MAP3)
	{
		if (m_collsion->CheckBox(EventRec1, x, y))
		{
			WinMgr::Instance()->ChangeMapBit(TYPE_MAP1);
			CharacterMgr::Instance()->SetisReturn(true);
			CharacterMgr::Instance()->SetCharacterPosition(true, 740, 20, false);
		}
		else if (m_collsion->CheckBox(EventRec2, x, y))
		{
			BitMgr::Instance()->SetSSJ(1);
#if 0
			CharacterMgr::Instance()->SetGameClear(true);
			CharacterMgr::Instance()->HideChar(false);
			AIMgr::Instance()->SetShowMajinBuu(false);
#endif
		}
	}
}

void WorldMgr::MoveLocation()
{
	int idx;
	idx = m_mapstatus;

	if (isMoveOrReturn)
	{
		//´ÙÀ½ ¸ÊÀ¸·Î ÀÌµ¿
		if (idx == TYPE_MAP1) //¸Ê »çÅº½ÃÆ¼ 
		{
			WinMgr::Instance()->ChangeMapBit(TYPE_MAP2);
		}
		else if (idx == TYPE_MAP2) //¸Ê »çÅº½ÃÆ¼ 2
		{
			WinMgr::Instance()->ChangeMapBit(TYPE_MAP3);
		}

		CharacterMgr::Instance()->SetisReturn(false);
	}
	else
	{
		//ÀÌÀü¸ÊÀ¸·Î ÀÌµ¿
		if (idx == TYPE_MAP2)
		{
			WinMgr::Instance()->ChangeMapBit(TYPE_MAP1);
		}
		else if (idx == TYPE_MAP3)
		{
			WinMgr::Instance()->ChangeMapBit(TYPE_MAP2);
		}
		CharacterMgr::Instance()->SetisReturn(true);
	}
}

bool WorldMgr::ChangeMap()
{
	int x, y;
	bool isCollision;

	x = CharacterMgr::Instance()->GetPosition(1, 1);
	y = CharacterMgr::Instance()->GetPosition(0, 1);

	if (m_collsion->CheckBox(MoveRec, x, y))
	{
		isMoveOrReturn = true;
		isCollision = true;
	}
	else if (m_collsion->CheckBox(ReturnRec, x, y))
	{
		isMoveOrReturn = false;
		isCollision = true;
	}
	else
	{
		isCollision = false;
	}

	return isCollision;

}

void WorldMgr::GetMapInfo()
{
	m_worldClass->CreateMapRECT((eTYPE_MAP)m_mapstatus, &rc1, &rc2, &rc3, &rc4, &rc5);
	m_worldClass->MapMove((eTYPE_MAP) m_mapstatus, &MoveRec, &ReturnRec);
	m_worldClass->GameMapEvent((eTYPE_MAP)m_mapstatus, &EventRec1, &EventRec2);
}

bool WorldMgr::GetRectValue()
{
	int x, y;
	bool isCollision;

	x = CharacterMgr::Instance()->GetPosition(1, 1);
	y = CharacterMgr::Instance()->GetPosition(0, 1);
		
	if (m_collsion->CheckBox(rc1, x, y) ||
		m_collsion->CheckBox(rc2, x, y) ||
		m_collsion->CheckBox(rc3, x, y) ||
		m_collsion->CheckBox(rc4, x, y) ||
		m_collsion->CheckBox(rc5, x, y))
	{
		isCollision = true;
	}
	else
	{
		isCollision = false;
	}
	return isCollision;
}
