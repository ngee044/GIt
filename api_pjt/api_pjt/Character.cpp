#include "Character.h"
#include "windows.h"
#include "time.h"
#include "Common.h"
#include "ManagerHeader.h"

Character::Character()
{
}

Character::~Character()
{
}

void Character::Init()
{
}

void Character::CreateMonster(bool is_Boss)
{
	if (is_Boss)
	{
		strcpy(m_name, "마인부우");
		m_hp = m_maxhp = 8500;
		m_mp = m_maxmp = 3500;
		m_af = m_df = 150;
	}
	else //minions
	{
		strcpy(m_name, "몬스터");
		m_hp = m_maxhp = 1200;
		m_mp = m_maxmp = 0;
		m_af = m_df = 80;
	}
}	

void Character::CreatePlayer()
{
	strcpy(m_name, "손오공");
	m_hp = m_maxhp = 500;
	m_mp = m_maxmp = 320;
	m_af = m_df = 50;
}

void Character::ChangeStatus(int nValue, eTYPE_STATUS type)
{
	if (type == eHP)
	{
		//DAMAGE EVENT
		m_hp += nValue;

		if (m_hp < m_maxhp)
			m_hp = m_maxhp;
		else if (m_hp < 0)
			m_hp = 0;
	}
	else if (type == eMP)
	{
		m_mp += nValue;

		if (m_mp < m_maxmp)
			m_mp = m_maxmp;
		else if (m_mp < 0)
			m_mp = 0;
	}
	else if (type == eAF)
	{
	}
	else if (type == eDF)
	{
	}
}

void Character::SetPosition()
{
	m_PlayerX = CharacterMgr::Instance()->GetPosition(true, true);
	m_PlayerY = CharacterMgr::Instance()->GetPosition(false, true);

	m_MonsterX = CharacterMgr::Instance()->GetPosition(true, false);
	m_MonsterY = CharacterMgr::Instance()->GetPosition(false, false);
}

void Character::Reset()
{

}

void Character::Delete()
{

}