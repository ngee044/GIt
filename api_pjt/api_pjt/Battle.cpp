#include "Battle.h"
#include "Common.h"


Battle::Battle()
{
}


Battle::~Battle()
{
}

void Battle::Init()
{
	GameOver = false;
}

void Battle::Battle_DisPlay(Character *player, Character * Monster)
{
	int sel;

	Print("주인공과 몬스터가 대결합니다 !!!");
	Print("1.이벤트 발생 / 2. 아이템 보기 / 3. 종료");
	sel = Scanf();
}

int Battle::Damage(int ATK, int DEF)
{
	int dmg;

	dmg = ATK - DEF + (ATK - DEF) / 2;

	if (dmg < 1)
		dmg = 1;

	return dmg;
}

void Battle::Reset()
{

}

void Battle::Delete()
{

 }