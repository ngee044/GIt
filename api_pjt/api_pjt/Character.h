#pragma once
#include "Object.h"
#include "eType.h"


class Character : public Object
{
protected:
	char m_name[20];
	int m_hp;
	int m_maxhp;
	int m_mp;
	int m_maxmp;
	int m_af;
	int m_df;

	int m_empty; //사이야 게이지
	int m_empty1;
	int m_empty2;

	int m_speed;

	int m_PlayerX, m_PlayerY;
	int m_MonsterX, m_MonsterY;

private:


public:
	Character();
	virtual ~Character();

	virtual void Init();
	virtual void Reset();
	virtual void Delete();
	virtual void GetCharRect(RECT *r1, eTYPE_PLAYER PlayerType, eTYPE_MONSTER monsterType) {}
	virtual void ChangeStatus(int nValue, eTYPE_STATUS type);

	void CreateMonster(bool is_Boss);
	void CreatePlayer();

	char GetName()		{ return *m_name; }
	int GetHp()			{ return m_hp;	  }
	int GetMaxHp()		{ return m_maxhp; }
	int GetMp()			{ return m_mp;    }
	int GetMaxMp()		{ return m_maxmp; }
	int GetAttack()		{ return m_af;    }
	int GetDeffend()	{ return m_df;    }
	int GetPx()			{ return m_PlayerX;   }
	int GetPy()			{ return m_PlayerY;   }
	int GetMx()			{ return m_MonsterX;  }
	int GetMy()			{ return m_MonsterY;  }
	void SetPosition();
};

