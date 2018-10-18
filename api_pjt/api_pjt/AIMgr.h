#pragma once

#include "Singleton.h"

class Monster;

class AIMgr : public Singleton<AIMgr>
{
protected:

private:
	int m_MonsterX;
	int m_MonsterY;
	int m_PlayerX;
	int m_PlayerY;
	bool m_IsShowMajinBuu;
	
	Monster * m_pMonster;

public:
	AIMgr();
	virtual ~AIMgr();

	void Init();
	void GetPosition();
	void update();
	void AIMove();
	void SetShowMajinBuu(bool idx) { m_IsShowMajinBuu = idx; }
	bool GetShowMajinBuu() { return m_IsShowMajinBuu; }
};

