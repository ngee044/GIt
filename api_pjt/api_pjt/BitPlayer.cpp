#include "BitPlayer.h"
#include "WinMgr.h"
#include "BitMgr.h"

BitPlayer::BitPlayer(eTYPE_PLAYER type, HDC hdc, HINSTANCE _hlstance)
{
	BitParent::GetReSize();
	m_hdc = hdc;
	m_hlstance = _hlstance;
}

BitPlayer::BitPlayer()
{
}

BitPlayer::~BitPlayer()
{
}

void BitPlayer::GetAniFrame(int nFrame)
{
	if (nFrame < 0)
		m_BitFrame = BitMgr::Instance()->GetBitFrame();
	else
		m_BitFrame = nFrame;
}

void BitPlayer::CreateImage(eTYPE_PLAYER type, TCHAR *str, bool is_mask, int size_x, int size_y)
{
	if (is_mask)
	{
		m_MyBit_Mask[m_nmask++] = CreatPlayerImage(str, type, m_hdc, m_hlstance, size_x, size_y);
	}
	else
	{
		m_MyBit[m_nbit++] = CreatPlayerImage(str, type, m_hdc, m_hlstance, size_x, size_y);
	}
}

void BitPlayer::MyBitDestroy()
{
	for (int i = 0; i < sizeof(m_MyBit_Mask); i++)
	{
		DeleteObject(m_MyBit_Mask[i]);
		DeleteObject(m_MyBit[i]);
	}
}

void BitPlayer::CreateMyBit(eTYPE_PLAYER type)
{
	int nFrame = 0;
	TCHAR image[256], mask[256];
	memset(image, 0x00, sizeof((TCHAR*)image));
	memset(mask, 0x00, sizeof((TCHAR*)mask));
	GetAniFrame(0);

	//!--idle--!//
	//front
	for (nFrame = 0; nFrame < 3; nFrame++)
	{
		wsprintf(image, TEXT("img\\Goku_idle_front%d.bmp"), nFrame);
		wsprintf(mask, TEXT("img_mask\\Goku_idle_front%d_mask.bmp"), nFrame); // 0~2
		CreateImage(type, image, FALSE, CHAR_SIZE_X, CHAR_SIZE_Y);	//Player 捞固瘤 积己
		CreateImage(type, mask, TRUE, CHAR_SIZE_X, CHAR_SIZE_Y); //Player 付胶农 积己
	}
	//left
	for (nFrame = 0; nFrame < 3; nFrame++)
	{
		wsprintf(image, TEXT("img\\Goku_idle_left%d.bmp"), nFrame);
		wsprintf(mask, TEXT("img_mask\\Goku_idle_left%d_mask.bmp"), nFrame); // 3~5
		CreateImage(type, image, FALSE, CHAR_SIZE_X, CHAR_SIZE_Y);	//Player 捞固瘤 积己
		CreateImage(type, mask, TRUE, CHAR_SIZE_X, CHAR_SIZE_Y); //Player 付胶农 积己
	}
	//right
	for (nFrame = 0; nFrame < 3; nFrame++)
	{
		wsprintf(image, TEXT("img\\Goku_idle_right%d.bmp"), nFrame);
		wsprintf(mask, TEXT("img_mask\\Goku_idle_right%d_mask.bmp"), nFrame); // 6~8
		CreateImage(type, image, FALSE, CHAR_SIZE_X, CHAR_SIZE_Y);	//Player 捞固瘤 积己
		CreateImage(type, mask, TRUE, CHAR_SIZE_X, CHAR_SIZE_Y); //Player 付胶农 积己	}
	}
	//back
	wsprintf(image, TEXT("img\\Goku_idle_back.bmp"), nFrame);
	wsprintf(mask, TEXT("img_mask\\Goku_idle_back_mask.bmp"), nFrame); // 9
	CreateImage(type, image, FALSE, CHAR_SIZE_X, CHAR_SIZE_Y);	//Player 捞固瘤 积己
	CreateImage(type, mask, TRUE, CHAR_SIZE_X, CHAR_SIZE_Y); //Player 付胶农 积己

	//!--walk--!//
	//front
	for (nFrame = 0; nFrame < 5; nFrame++)
	{
		wsprintf(image, TEXT("img\\Goku_walk_front%d.bmp"), nFrame);
		wsprintf(mask, TEXT("img_mask\\Goku_walk_front%d_mask.bmp"), nFrame); // 10~14
		CreateImage(type, image, FALSE, CHAR_SIZE_X, CHAR_SIZE_Y);	//Player 捞固瘤 积己
		CreateImage(type, mask, TRUE, CHAR_SIZE_X, CHAR_SIZE_Y); //Player 付胶农 积己
	}
	//left
	for (nFrame = 0; nFrame < 5; nFrame++)
	{
		wsprintf(image, TEXT("img\\Goku_walk_left%d.bmp"), nFrame);
		wsprintf(mask, TEXT("img_mask\\Goku_walk_left%d_mask.bmp"), nFrame); // 15~19
		CreateImage(type, image, FALSE, CHAR_SIZE_X, CHAR_SIZE_Y);	//Player 捞固瘤 积己
		CreateImage(type, mask, TRUE, CHAR_SIZE_X, CHAR_SIZE_Y); //Player 付胶农 积己
	}
	//right
	for (nFrame = 0; nFrame < 5; nFrame++)
	{
		wsprintf(image, TEXT("img\\Goku_walk_right%d.bmp"), nFrame);
		wsprintf(mask, TEXT("img_mask\\Goku_walk_right%d_mask.bmp"), nFrame); // 20~24
		CreateImage(type, image, FALSE, CHAR_SIZE_X, CHAR_SIZE_Y);	//Player 捞固瘤 积己
		CreateImage(type, mask, TRUE, CHAR_SIZE_X, CHAR_SIZE_Y);		//Player 付胶农 积己
	}
	//back
	for (nFrame = 0; nFrame < 5; nFrame++)
	{
		wsprintf(image, TEXT("img\\Goku_walk_back%d.bmp"), nFrame);
		wsprintf(mask, TEXT("img_mask\\Goku_walk_back%d_mask.bmp"), nFrame); // 25~29
		CreateImage(type, image, FALSE, CHAR_SIZE_X, CHAR_SIZE_Y);	//Player 捞固瘤 积己
		CreateImage(type, mask, TRUE, CHAR_SIZE_X, CHAR_SIZE_Y);		//Player 付胶农 积己
	}

	wsprintf(image, TEXT("img\\Goku_gameover.bmp"));
	wsprintf(mask, TEXT("img_mask\\Goku_gameover_mask.bmp")); // 30
	CreateImage(type, image, FALSE, 72, 41);	//Player 捞固瘤 积己
	CreateImage(type, mask, TRUE, 72, 41);		//Player 付胶农 积己

	//--walk_ssj--//
	//front
	for (nFrame = 0; nFrame < 4; nFrame++)
	{
		wsprintf(image, TEXT("img\\SSJ_Goku_walk_front%d.bmp"), nFrame);
		wsprintf(mask, TEXT("img_mask\\SSJ_Goku_walk_front%d.bmp"), nFrame); // 31~34
		CreateImage(type, image, FALSE, SSJ_GOKU_X, SSJ_GOKU_Y);	//Player 捞固瘤 积己
		CreateImage(type, mask, TRUE, SSJ_GOKU_X, SSJ_GOKU_Y);		//Player 付胶农 积己
	}
	//left
	for (nFrame = 0; nFrame < 4; nFrame++)
	{
		wsprintf(image, TEXT("img\\SSJ_Goku_walk_left%d.bmp"), nFrame);
		wsprintf(mask, TEXT("img_mask\\SSJ_Goku_walk_left%d.bmp"), nFrame); // 35~38
		CreateImage(type, image, FALSE, SSJ_GOKU_X, SSJ_GOKU_Y);	//Player 捞固瘤 积己
		CreateImage(type, mask, TRUE, SSJ_GOKU_X, SSJ_GOKU_Y);		//Player 付胶农 积己
	}
	//right
	for (nFrame = 0; nFrame < 4; nFrame++)
	{
		wsprintf(image, TEXT("img\\SSJ_Goku_walk_right%d.bmp"), nFrame);
		wsprintf(mask, TEXT("img_mask\\SSJ_Goku_walk_right%d.bmp"), nFrame); // 39~42
		CreateImage(type, image, FALSE, SSJ_GOKU_X, SSJ_GOKU_Y);	//Player 捞固瘤 积己
		CreateImage(type, mask, TRUE, SSJ_GOKU_X, SSJ_GOKU_Y);		//Player 付胶农 积己
	}
	//back
	for (nFrame = 0; nFrame < 4; nFrame++)
	{
		wsprintf(image, TEXT("img\\SSJ_Goku_walk_back%d.bmp"), nFrame);
		wsprintf(mask, TEXT("img_mask\\SSJ_Goku_walk_back%d.bmp"), nFrame); // 43~46
		CreateImage(type, image, FALSE, SSJ_GOKU_X, SSJ_GOKU_Y);	//Player 捞固瘤 积己
		CreateImage(type, mask, TRUE, SSJ_GOKU_X, SSJ_GOKU_Y);		//Player 付胶农 积己
	}

	m_nbit = m_nmask = 0;
}

HBITMAP BitPlayer::CreatPlayerImage(TCHAR *STR, eTYPE_PLAYER type, HDC hdc, HINSTANCE _hlstance, int size_x, int size_y)
{
	HBITMAP bitmap;
	
	bitmap = (HBITMAP)LoadImage(_hlstance, STR, IMAGE_BITMAP, size_x, size_y, LR_LOADFROMFILE);

	if (!bitmap)
	{
		return 0;
		//error
	}
	return bitmap; 
	// (HBITMAP)LoadImage(_hlstance, STR, IMAGE_BITMAP, CHAR_SIZE_X, CHAR_SIZE_Y, LR_LOADFROMFILE);


}
