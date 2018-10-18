#include "Monster.h"

Monster::Monster()
{
}


Monster::~Monster()
{
}

void Monster::Init()
{
	Character::CreateMonster(false);
}

void Monster::Reset()
{

}

void Monster::Delete()
{

}

void Monster::ChangeStatus(int nValue, eTYPE_STATUS type)
{
	Character::ChangeStatus(nValue, type);

	if (m_hp <= 0)
	{
		//BATTLE WIN
	}
}


void Monster::GetCharRect(RECT *rc1, eTYPE_PLAYER PlayerType, eTYPE_MONSTER MonsterType)
{
	Character::SetPosition();

	if (MonsterType == TYPE_MINION)
	{
		//NOMAL MONSTER RECT
		rc1->left = m_MonsterX;
		rc1->right = m_MonsterX + CHAR_SIZE_X;
		rc1->top = m_MonsterY;
		rc1->bottom = m_MonsterY + CHAR_SIZE_Y;
	}
}