#pragma once
#include "Character.h"
class BossMonster :	public Character
{
public:
	BossMonster();
	virtual ~BossMonster();

	virtual void SetPos(int x, int y) { m_MonsterX = x, m_MonsterX = y; }
	virtual void Init();
	virtual void Reset();
	virtual void Delete();

	virtual void ChangeStatus(int nValue, eTYPE_STATUS type);
	virtual void GetCharRect(RECT *rc1, eTYPE_PLAYER PlayerType, eTYPE_MONSTER monsterType);

};

