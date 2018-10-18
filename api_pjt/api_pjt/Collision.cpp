#include "Collision.h"

Collision::Collision()
{
}

Collision::~Collision()
{
}

bool Collision::CheckBox(RECT rt, int x, int y)//x,y = ĳ����, RECT = ����, �ʿ�����,������ ���
{
	if ((rt.left <= x && rt.right >= x)
		&& (rt.top <= y && rt.bottom >= y))
		return true;

	return false;
}

bool Collision::CheckMapBox(RECT rt, int x, int y)//���� ������� ����
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

bool Collision::CheckBox(RECT rt, RECT rt2)//��ǥ�� ����  rt, rt2�� �ٲ��� �Ѵ�.
{
	if ((rt.left <= rt2.right && rt.right >= rt2.left)
		&& (rt.top <= rt2.bottom && rt.bottom >= rt2.top))
		return true;

	return false;
}