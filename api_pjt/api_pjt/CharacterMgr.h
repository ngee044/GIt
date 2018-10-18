#pragma once
#include "Singleton.h"
#include "Character.h"
#include "eType.h"

#define DISTANCE 12

class Character;
class Player;
class Monster;
class BossMonster;
class Collision;

class CharacterMgr : public Singleton<CharacterMgr>
{
private:
	std::list <Character*> m_listCharacter;
	Character *m_character;
	Player	*m_player;
	Monster *m_monster;
	BossMonster *m_BossMonster;
	Collision *m_Collision;
	eTYPE_MAP m_MapStatus;
	int m_Px, m_Py;
	int m_Mx, m_My;
	int m_nWidth, m_nHeight;
	bool m_IsGameOver;
	bool m_IsGameClear;
	RECT mainRc;
	RECT CharacterRC;
	RECT BossRC;
	RECT MonsterRC[16];
	int m_nCheatCount;
	bool m_IsReturn;
	bool m_IsRunBoss;

public:
	CharacterMgr();
	~CharacterMgr();

	void Init();
	void Reset();
	void Delete();

	void CreatePlayer(eTYPE_PLAYER player);
	void CreateMonster(bool is_boss);
	int GetRandValue(int Max, int min);
	int DamageEvent(int ATK, int DEF, bool is_battle, int dmg);
	void Move(eTYPE_WATCH e_watch, eTYPE_KEY_TYPE key, bool is_ani, bool isPlayer);
	int GetPosition(bool x_position, bool is_player) 
	{ 
		if (is_player) 
			return (x_position) ? m_Px : m_Py; 
		else 
			return(x_position) ? m_Mx : m_My; 
	}
	Character *CreateCharacter(eTYPE_CHARACTER _eChar);
	void update();
	void SetMonster(Monster *m) { m_monster = m; };
	void SetMapStatus(int map) { m_MapStatus = (eTYPE_MAP)map; }
	void SetCharacterPosition(bool isPlayer, int x, int y, bool isMoveLocation);
	void GameOverEvent();
	void SetRunBoss(bool idx) { m_IsRunBoss = idx; }
	bool GetRunBoss() { return m_IsRunBoss; }
	void SetGameOver(bool idx) { m_IsGameOver = idx; }
	bool GetGameOver() { return m_IsGameOver; }
	void SetGameClear(bool idx) { m_IsGameClear = idx; }
	bool GetGameClear() { return m_IsGameClear; }
	void SetCheatIndex(int idx) { m_nCheatCount = idx; }
	int GetCheatIndex() { return m_nCheatCount;	}
	void CheatGame();
	void HideChar(bool isPlayer);
	void ShowBossMonster();
	void SetisReturn(bool idx) { m_IsReturn = idx; }
	void CharacterInit();
};

