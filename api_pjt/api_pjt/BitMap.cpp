#include "BitMap.h"
#include "ManagerHeader.h"

BitMap::BitMap(eTYPE_MAP type, HDC hdc, HINSTANCE _hlstance)
{
	m_dcBackBuffer = BitMgr::Instance()->GetBackBufferDC();
	m_nWidth = BitMgr::Instance()->GetWidth();
	m_nHeight = BitMgr::Instance()->GetHeight();

	m_hdc = hdc;
	m_hlstance = _hlstance;
}

BitMap::BitMap()
{

}

BitMap::~BitMap()
{

}

void BitMap::CreateMyBit()
{
	m_MyBit_GAMEMAP[0] = CreatMapImage(TYPE_MAP1, TEXT("img_background\\satancity_middle.bmp")); //맵 이미지 생성
	m_MyBit_GAMEMAP[1] = CreatMapImage(TYPE_MAP2, TEXT("img_background\\satancity_below.bmp")); //맵 이미지 생성
	m_MyBit_GAMEMAP[2] = CreatMapImage(TYPE_MAP3, TEXT("img_background\\satancity_below_down.bmp")); //맵 이미지 생성
}

void BitMap::MyBitDestroy()
{
	for(int i = 0 ; i < sizeof(m_MyBit_GAMEMAP) ; i++)
		DeleteObject(m_MyBit_GAMEMAP[i]);
}

HBITMAP BitMap::CreatMapImage(eTYPE_MAP type, TCHAR *STR)
{
	return (HBITMAP)LoadImage(m_hlstance, STR, IMAGE_BITMAP, WORLD_SIZE_X, WORLD_SIZE_Y, LR_LOADFROMFILE);
}

