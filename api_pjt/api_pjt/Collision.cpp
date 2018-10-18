#include "Collision.h"

Collision::Collision()
{
}

Collision::~Collision()
{
}

bool Collision::CheckBox(RECT rt, int x, int y)//x,y = 캐릭터, RECT = 몬스터, 맵오브젝,아이템 등등
{
	if ((rt.left <= x && rt.right >= x)
		&& (rt.top <= y && rt.bottom >= y))
		return true;

	return false;
}

bool Collision::CheckMapBox(RECT rt, int x, int y)//맵을 벗어나는지 조건
{
	if ( (rt.left <= x && rt.right >= x)
		&& (rt.top <= y && rt.bottom >= y) )
		return false;

	return true;
}

bool Collision::CheckGameOverRect(RECT rt, RECT rt2)
{
	if ((rt.left - rt2.left && rt.right <= rt2.right)&& 
		(rt.top <= rt2.top && rt.bottom <= rt2.bottom))
		return true;

	return false;
}

bool Collision::CheckBox(RECT rt, RECT rt2)//좌표에 따라  rt, rt2가 바껴야 한다.
{
	if ((rt.left <= rt2.right && rt.right >= rt2.left)
		&& (rt.top <= rt2.bottom && rt.bottom >= rt2.top))
		return true;

	return false;
}