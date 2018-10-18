#pragma once
#include "Character.h"

class Player : public Character
{
private:

public:
	Player();
	virtual ~Player();

	virtual void SetPos(int x, int y) { m_PlayerX = x, m_PlayerY = y; }
	virtual void Init();
	virtual void Reset();
	virtual void Delete();

	virtual void ChangeStatus(int nValue, eTYPE_STATUS type);
	virtual void GetCharRect(RECT *r1, eTYPE_PLAYER PlayerType, eTYPE_MONSTER monsterType);
};

