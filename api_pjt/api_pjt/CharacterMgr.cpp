#include "Common.h"
#include "ManagerHeader.h"
#include <time.h>
#include "Player.h"
#include "Monster.h"
#include "BossMonster.h"
#include "Collision.h"


CharacterMgr::CharacterMgr()
{
	m_Px = 740;
	m_Py = 20;
	m_Mx = m_My = 1500,1500;
}

CharacterMgr::~CharacterMgr()
{
	Delete();
}

void CharacterMgr::Init()
{
	m_nWidth = WinMgr::Instance()->GetWidth();
	m_nHeight = WinMgr::Instance()->GetHeight();
	GetClientRect(WinMgr::Instance()->GethWnd(), &mainRc);
	
	SetGameOver(false);
	SetGameClear(false);
	SetisReturn(false);
	SetCheatIndex(0);

#if 0
	for(int i=0; i<10; i ++)
		CreateCharacter(TYPE_MONSTER);
	
	CreateCharacter(TYPE_PLAYER);

	CharacterInit();
#else
	CreatePlayer(TYPE_Player1);
	CreateMonster(true);
#endif
}

Character *CharacterMgr::CreateCharacter(eTYPE_CHARACTER _eChar)
{
	//팩토리 패턴 사용법
	Character *pCreate = NULL;

	switch (_eChar)
	{
	case TYPE_CHARACTER_NONE:
		pCreate = new Character;
	case TYPE_PLAYER:
		pCreate = new Player;
		break;
	case TYPE_MONSTER:
		pCreate = new Monster;
		break;
	case TYPE_NPC:
		pCreate = new Character;
		break;
	case TYPE_PET:
		pCreate = new Character;
		break;
	default:
		break;
	}

	m_listCharacter.push_back(pCreate);

	return pCreate;
}

void CharacterMgr::CharacterInit()
{
	std::list <Character*>::iterator itr = m_listCharacter.begin();
	std::list <Character*>::iterator end = m_listCharacter.end();

	while (itr != end)
	{
		Character* ch = *itr;

		ch->Init();
		itr++;
	}
	m_player->SetPos(0, 0);
}

void CharacterMgr::CreatePlayer(eTYPE_PLAYER player)
{
	if (player == TYPE_Player1)
	{
		m_player = new Player;
		m_player->Init();
	}
}

void CharacterMgr::CreateMonster(bool is_boss)
{
	if (is_boss)
	{
		m_BossMonster = new BossMonster;
		m_BossMonster->Init();
	}
	else
	{
		m_monster = new Monster;
		m_monster->Init();
	}
}

void CharacterMgr::Reset()
{
}

void CharacterMgr::Delete()
{
	if(m_character)  delete m_character;
	if(m_player)	 delete m_player;
	if(m_BossMonster)delete m_BossMonster;
	if(m_monster)	 delete m_monster;
}

int CharacterMgr::GetRandValue(int Max, int min)
{
	int nValue = 0;

	srand((unsigned int)time(NULL));
	nValue = rand() % Max + min;

	if (nValue > Max) 
		nValue = Max;

	return nValue;
}

void CharacterMgr::update()
{
	if (m_player)
		m_player->SetPos(m_Px, m_Py);
	
	if(m_BossMonster)
		m_BossMonster->SetPos(m_Mx, m_My);

	GameOverEvent();

	if (m_IsGameOver)
	{
		WinMgr::Instance()->GameOver(false);
	}

	if(m_IsGameClear)
	{
		WinMgr::Instance()->GameOver(true);
	}
}

void CharacterMgr::GameOverEvent()
{
	m_player->GetCharRect(&CharacterRC, TYPE_Player1, (eTYPE_MONSTER)NULL);
	m_BossMonster->GetCharRect(&BossRC,(eTYPE_PLAYER)NULL, TYPE_BOSS_MAJINBUU);

	bool isCollision1, isCollision2;
	int isSSJ_Status = 0;

	isSSJ_Status = BitMgr::Instance()->GetSSJ();
	isCollision1 = m_Collision->CheckBox(CharacterRC, BossRC);
	isCollision2 = m_Collision->CheckBox(BossRC, CharacterRC);

	bool temp = isCollision1 || isCollision2;

	if (isSSJ_Status >= 1 && temp)
	{
		CharacterMgr::Instance()->SetGameClear(true);
		CharacterMgr::Instance()->HideChar(false);
		AIMgr::Instance()->SetShowMajinBuu(false);
	}
	else
	{
		if (temp)
		{
			//goto GameOver
			SetGameOver(true);
		}
	}
}

void CharacterMgr::ShowBossMonster()
{
	int map;
	map = WorldMgr::Instance()->GetMapStatus();

	if (!m_IsReturn)
	{
		if (map == TYPE_MAP1)
		{
			SetCharacterPosition(false, 740, 20, false);
		}
		else if (map == TYPE_MAP2)
		{
			SetCharacterPosition(false, 136, 122, false);
		}
		else if (map == TYPE_MAP3)
		{
			SetCharacterPosition(false, 820, 37, false);
		}
	}
	else
	{
		if (map == TYPE_MAP1)
		{
			SetCharacterPosition(false, 140, 590, false);
		}
		else if (map == TYPE_MAP2)
		{
			SetCharacterPosition(false, 820, 600, false);
		}
		else if (map == TYPE_MAP3)
		{
		//	SetCharacterPosition(false, 820, 37, false);
		}
	}
}

void CharacterMgr::CheatGame()
{
	m_nCheatCount++;
	if (m_nCheatCount > 6)
	{
		m_nCheatCount = 0;
	}
}

void CharacterMgr::HideChar(bool isPlayer)
{
	if (isPlayer)
	{
		SetCharacterPosition(true, 1500, 1500, false);
	}
	else
	{
		SetCharacterPosition(false, 1500, 1500, false);
	}
}

void CharacterMgr::Move(eTYPE_WATCH e_watch, eTYPE_KEY_TYPE key, bool is_ani, bool isPlayer)
{
	if (isPlayer)
	{
#if 1
		int tempX = m_Px, tempY = m_Py;
		bool is_Collision;
		bool is_ChangeMap;
#endif
		if (is_ani)
		{
			return;
		}

		if (e_watch == TYPE_FRONT)
		{
			m_Py += DISTANCE;
		}
		else if (e_watch == TYPE_LEFT)
		{
			m_Px -= DISTANCE;
		}
		else if (e_watch == TYPE_RIGHT)
		{
			m_Px += DISTANCE;
		}
		else if (e_watch == TYPE_BACK)
		{
			m_Py -= DISTANCE;
		}

		is_Collision = WorldMgr::Instance()->GetRectValue();
		if (is_Collision)
		{
			m_Px = tempX;
			m_Py = tempY;
		}
		else
		{
			is_Collision = m_Collision->CheckMapBox(mainRc, m_Px, m_Py);
			if (is_Collision)
			{
				m_Px = tempX;
				m_Py = tempY;
			}
		}

		is_ChangeMap = WorldMgr::Instance()->ChangeMap();
		if (is_ChangeMap)
		{
			WorldMgr::Instance()->MoveLocation();
			SetCharacterPosition(0, 0, 0, true);
		}
	}
	else
	{
		if (1)//(MonsterType == TYPE_BOSS_MAJINBUU)
		{
			if (e_watch == TYPE_FRONT)
			{
				m_My += DISTANCE - m_nCheatCount;
			}
			else if (e_watch == TYPE_LEFT)
			{
				m_Mx -= DISTANCE - m_nCheatCount;
			}
			else if (e_watch == TYPE_RIGHT)
			{
				m_Mx += DISTANCE - m_nCheatCount;
			}
			else if (e_watch == TYPE_BACK)
			{
				m_My -= DISTANCE - m_nCheatCount;
			}
		}
	}
}

void CharacterMgr::SetCharacterPosition(bool isPlayer, int x, int y, bool isMoveLocation)
{
	if (isMoveLocation)
	{
		int map; 
		bool isNextMap;
		isNextMap = WorldMgr::Instance()->GetMoveMapInfo();
		map = WorldMgr::Instance()->GetMapStatus();

		if (map == TYPE_MAP1)
		{
			if (isNextMap)
			{
				//EMPTY
			}
			else
			{
				m_Px = 136;
				m_Py = 614;
			}
		}
		else if (map == TYPE_MAP2)
		{
			if (isNextMap)
			{
				m_Px = 136;
				m_Py = 10;
			}
			else
			{
				m_Px = 820;
				m_Py = 640;
			}
		}
		else if (map == TYPE_MAP3)
		{
			if (isNextMap)
			{
				m_Px = 820;
				m_Py = 25;
			}
			else
			{
				//EMPTY
			}
		}
	}
	else
	{
		if (isPlayer)
		{
			m_Px = x;
			m_Py = y;
		}
		else
		{
			m_Mx = x;
			m_My = y;
		}
	}
}

int CharacterMgr::DamageEvent(int ATK, int DEF, bool is_battle, int dmg)
{
	if (is_battle)
	{
		dmg = 0;
		dmg = (ATK - DEF+(DEF/10)) - ATK / 3; //데미지 공식
	}
	
	if (dmg < 1)
		dmg = 1;

	return dmg;
}