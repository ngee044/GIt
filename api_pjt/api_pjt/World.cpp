#include "World.h"
#include "Common.h"
#include "ManagerHeader.h"

World::World()
{
}

World::~World()
{
}

void World::Init()
{
}

void World::Reset()
{
}

void World::Delete()
{
}

void World::GameMapEvent(eTYPE_MAP map, RECT *EventRec1, RECT *EventRec2)
{
	if (map == TYPE_MAP3)
	{
		EventRec1->left = 220;
		EventRec1->right = 270;
		EventRec1->top = 345;
		EventRec1->bottom = 425;
		
		EventRec2->left = 16;
		EventRec2->right = 64;
		EventRec2->top = 390;
		EventRec2->bottom = 470;
	}
	else
	{
		EventRec1->left = 0;
		EventRec1->right = 0;
		EventRec1->top = 0;
		EventRec1->bottom = 0;

		EventRec2->left = 0;
		EventRec2->right = 0;
		EventRec2->top = 0;
		EventRec2->bottom = 0;
	}
}

void World::MapMove(eTYPE_MAP type, RECT *MoveRec, RECT *ReturnRec)
{
	if (type == TYPE_MAP1)
	{
		MoveRec->left = 110;
		MoveRec->right = 170;
		MoveRec->top = 650;
		MoveRec->bottom = 720;

		ReturnRec->left = 0;
		ReturnRec->right = 0;
		ReturnRec->top = 0;
		ReturnRec->bottom = 0;

	}
	else if (type == TYPE_MAP2)
	{
		MoveRec->left = 800;
		MoveRec->right = 850;
		MoveRec->top = 650;
		MoveRec->bottom = 720;

		ReturnRec->left = 85;
		ReturnRec->right = 200;
		ReturnRec->top = 0;
		ReturnRec->bottom = 15;
	}
	else if (type == TYPE_MAP3)
	{
		MoveRec->left = 0;
		MoveRec->right = 0;
		MoveRec->top = 0;
		MoveRec->bottom = 0;

		ReturnRec->left = 780;
		ReturnRec->right = 880;
		ReturnRec->top = 0;
		ReturnRec->bottom = 10;
	}
}

void World::CreateMapRECT(eTYPE_MAP type, RECT *rc1, RECT *rc2, RECT *rc3, RECT *rc4, RECT *rc5)
{

	if (type == TYPE_MAP1)
	{
		rc1->left = 0;
		rc1->right = 40;
		rc1->top = 0;
		rc1->bottom = 720;

		rc2->left = 0;
		rc2->right = 450;
		rc2->top = 0;
		rc2->bottom = 300;

		rc3->left = 0;
		rc3->right = 40;
		rc3->top = 0;
		rc3->bottom = 720;

		rc4->left = 240;
		rc4->right = 900;
		rc4->top = 590;
		rc4->bottom = 720;

		rc5->left = 880;
		rc5->right = 980;
		rc5->top = 0;
		rc5->bottom = 720;
	}
	else if (type == TYPE_MAP2)
	{
		rc1->left = 0;
		rc1->right = 40;
		rc1->top = 0;
		rc1->bottom = 720;

		rc2->left = 300;
		rc2->right = 820;
		rc2->top = 0;
		rc2->bottom = 180;

		rc3->left = 870;
		rc3->right = 1024;
		rc3->top = 0;
		rc3->bottom =180;

		rc4->left = 88;
		rc4->right = 730;
		rc4->top = 500;
		rc4->bottom = 720;

		rc5->left = 920;
		rc5->right = 1024;
		rc5->top = 560;
		rc5->bottom = 720;
	}
	else if (type == TYPE_MAP3)
	{
		rc1->left = 0;
		rc1->right = 740;
		rc1->top = 0;
		rc1->bottom = 190;

		rc2->left = 920;
		rc2->right = 1024;
		rc2->top = 0;
		rc2->bottom = 720;

		rc3->left = 0;
		rc3->right = 1024;
		rc3->top = 520;
		rc3->bottom = 720;

		rc4->left = 0;
		rc4->right = 0;
		rc4->top = 0;
		rc4->bottom = 0;

		rc5->left = 0;
		rc5->right = 0;
		rc5->top = 0;
		rc5->bottom = 0;
	}
}