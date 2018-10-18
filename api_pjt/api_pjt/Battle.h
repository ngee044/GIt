#pragma once
#include "ApiClass.h"
#include "WorldMgr.h"
#include "CharacterMgr.h"

class Battle :
	public ApiClass
{
private:

protected:
	bool GameOver;
public:
	Battle();
	virtual ~Battle();

	virtual void Init() override;
	virtual void Reset() override;
	virtual void Delete() override;

	int Damage(int ATK, int DEF);
	void Battle_DisPlay(Character *player, Character * Monster);
	int Is_GameOver() { return GameOver; }
};

