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

	Print("���ΰ��� ���Ͱ� ����մϴ� !!!");
	Print("1.�̺�Ʈ �߻� / 2. ������ ���� / 3. ����");
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