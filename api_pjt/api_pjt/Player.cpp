#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::Init()
{
	Character::CreatePlayer();
}

void Player::Reset()
{

}

void Player::Delete()
{

}

void Player::ChangeStatus(int nValue, eTYPE_STATUS type)
{
	Character::ChangeStatus(nValue, type);

	if (m_hp <= 0)
	{
		//BATTLE LOSE!!
	}
}

void Player::GetCharRect(RECT *rc1, eTYPE_PLAYER PlayerType, eTYPE_MONSTER MonsterType)
{
	Character::SetPosition();

	if (PlayerType == TYPE_Player1)
	{
		rc1->left = m_PlayerX + 8;
		rc1->right = m_PlayerX + CHAR_SIZE_X - 8;
		rc1->top = m_PlayerY + 8;
		rc1->bottom = m_PlayerY + CHAR_SIZE_Y - 8;
	}
	else
	{
		rc1->left = m_PlayerX + 10;
		rc1->right = m_PlayerX + CHAR_SIZE_X - 10;
		rc1->top = m_PlayerY + 10;
		rc1->bottom = m_PlayerY + CHAR_SIZE_Y - 10;
	}
}