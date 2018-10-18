#include "BitObject.h"
#include "ManagerHeader.h"

BitObject::BitObject(HDC hdc, HINSTANCE _hlstance)
{
	BitParent::GetReSize();
	m_hdc = hdc;
	m_hlstance = _hlstance;
	m_nbit = m_nmask = 0;
}

BitObject::BitObject()
{
}

BitObject::~BitObject()
{
}

void BitObject::CreateImage(eTYPE_OBJECT type, TCHAR *str, bool is_mask)
{
	if (is_mask)
	{
		m_ObjBit_Mask[m_nmask++] = CreateObjectImage(str,64,64);
	}
	else
	{
		m_ObjBit[m_nbit++] = CreateObjectImage(str,64,64);
	}
}

void BitObject::CreateMyBit(eTYPE_OBJECT type)
{
	int nFrame;
	TCHAR image[256], mask[256];
	memset(image, 0x00, sizeof((TCHAR*)image));
	memset(mask, 0x00, sizeof((TCHAR*)mask));

	if (type == TYPE_OBJ_ARROW)
	{
		nFrame = 0;

		wsprintf(image, TEXT("img\\Arrow_%d.bmp"), nFrame);
		wsprintf(mask, TEXT("img_mask\\Arrow_mask%d.bmp"), nFrame);
		CreateImage(type, image, FALSE);	//Player 捞固瘤 积己
		CreateImage(type, mask, TRUE); //Player 付胶农 积己
	}

	m_nbit = m_nmask = 0;
}

void BitObject::MyBitDestroy()
{
	int Max = sizeof(m_ObjBit);

	for (int i = 0; i < 16; i++)
	{
		DeleteObject(m_ObjBit[i]);
		DeleteObject(m_ObjBit_Mask[i]);
	}
}

HBITMAP BitObject::CreateObjectImage(TCHAR *STR, int size_x, int size_y)
{
	HBITMAP bitmap;

	bitmap = (HBITMAP)LoadImage(m_hlstance, STR, IMAGE_BITMAP, size_x, size_y, LR_LOADFROMFILE);

	if (!bitmap)
	{
		return 0;
		//error
	}
	return bitmap;
}