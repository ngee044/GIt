#include "BossMonster.h"

BossMonster::BossMonster()
{
}


BossMonster::~BossMonster()
{
}

void BossMonster::Init()
{
	Character::CreateMonster(true);
}

void BossMonster::Reset()
{

}

void BossMonster::Delete()
{

}

void BossMonster::ChangeStatus(int nValue, eTYPE_STATUS type)
{
	Character::ChangeStatus(nValue, type);

	if (m_hp <= 0)
	{
		//BATTLE WIN
	}
}

void BossMonster::GetCharRect(RECT *rc1, eTYPE_PLAYER PlayerType, eTYPE_MONSTER MonsterType)
{
	Character::SetPosition();

	if (MonsterType == TYPE_BOSS_MAJINBUU)
	{
		//Boss
		rc1->left = m_MonsterX + 10;
		rc1->right = m_MonsterX + 40;
		rc1->top = m_MonsterY + 10;
		rc1->bottom = m_MonsterY + 80;
	}
}