#include "BitMonster.h"
#include "ManagerHeader.h"

BitMonster::BitMonster(eTYPE_MONSTER type, HDC hdc, HINSTANCE _hlstance)
{
	BitParent::GetReSize();
	m_hdc = hdc;
	m_hlstance = _hlstance;
}

void BitMonster::CreateImage(eTYPE_MONSTER type, TCHAR *str, bool is_mask)
{
	if (is_mask)
	{
		m_MyBitMask[m_mask]=(CreatMonsterImage(m_hdc, m_hlstance, str));
	}
	else
	{
		m_MyBit[m_bit]=(CreatMonsterImage(m_hdc, m_hlstance, str));
	}
	m_bit = m_mask = 0;
}

void BitMonster::CreateMyBit(eTYPE_MONSTER type)
{
	int nFrame = 0;
	TCHAR image[256], mask[256];
	memset(image, 0x00, sizeof((TCHAR*)image));
	memset(mask, 0x00, sizeof((TCHAR*)mask));

	if (type == TYPE_BOSS_MAJINBUU)
	{
		//!--idle--!//
		//front
		wsprintf(image, TEXT("img\\majin.bmp"), nFrame);
		wsprintf(mask, TEXT("img_mask\\majin_mask.bmp"), nFrame); // 0~2
		CreateImage(type, image, FALSE);	//Player 捞固瘤 积己
		CreateImage(type, mask, TRUE); //Player 付胶农 积己
	}
}

void BitMonster::MyBitDestroy()
{
	for (int i = 0; i < sizeof(m_MyBitMask); i++)
	{
		DeleteObject(m_MyBit[i]);
		DeleteObject(m_MyBitMask[i]);
	}
}

BitMonster::BitMonster()
{
}

BitMonster::~BitMonster()
{
}

HBITMAP BitMonster::CreatMonsterImage(HDC hdc, HINSTANCE _hlstance, TCHAR *STR)
{
	return (HBITMAP)LoadImage(_hlstance, STR, IMAGE_BITMAP, 60, 118, LR_LOADFROMFILE);
}
