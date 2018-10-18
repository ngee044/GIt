#include "BitMgr.h"
#include "WinMgr.h"
#include "CharacterMgr.h"
#include <windows.h>

BitMgr::BitMgr()
{	
}

BitMgr::~BitMgr()
{
}

void BitMgr::Init()
{
	m_hdc = WinMgr::Instance()->GetHdc();
	m_nWidth = WinMgr::Instance()->GetWidth();
	m_nHeight = WinMgr::Instance()->GetHeight();
}
void BitMgr::CreatBackBuffer(HDC hdc)
{
	Init();

	m_BackBufferDC = CreateCompatibleDC(m_hdc);
	m_hBackBmp = CreateCompatibleBitmap(hdc, m_nWidth, m_nHeight);
	m_hBackOld = (HBITMAP)SelectObject(m_BackBufferDC, m_hBackBmp);

}

void BitMgr::CreatePlayerImage(eTYPE_PLAYER type, HDC hdc, HINSTANCE _hlstance)
{
	BitPlayer *Bitplayer = new BitPlayer(type, hdc, _hlstance);

	Bitplayer->CreateMyBit(type);
	m_vBitPlayer.push_back(Bitplayer);
	SetBitImage((eTYPE_ANI)0, (eTYPE_WATCH)0, (eTYPE_KEY_TYPE)0);
	SetSSJ(0);
	m_nCountAni = 0;
	m_BitFrame = 0;
	m_nCountAni_2 = 0;
}

void BitMgr::CreateMonsterImage(eTYPE_MONSTER type, HDC hdc, HINSTANCE _hlstance)
{
	BitMonster *Bitmonster = new BitMonster(type, hdc, _hlstance);

	Bitmonster->CreateMyBit(TYPE_BOSS_MAJINBUU);
	m_vBitMonster.push_back(Bitmonster); //Moster 비트맵 데이터 추가
	SetBitMonsterImage((eTYPE_ANI)0, (eTYPE_WATCH)0);
	m_MonsterAni = 0;
	m_BitMonsterFrame = 0;
}

void BitMgr::SetBitMonsterImage(eTYPE_ANI type, eTYPE_WATCH watch)
{
	if (watch == TYPE_FRONT)
	{
		if (type == TYPE_IDLE)
		{
			SetMonsterFrame(0);
		}
		else if (type == TYPE_WALK)
		{
			SetMonsterFrame(10 + m_MonsterAni);
		}
	}
	else if (watch == TYPE_LEFT)
	{
		if (type == TYPE_IDLE)
		{
			SetMonsterFrame(3);
		}
		else if (type == TYPE_WALK)
		{
			SetMonsterFrame(15 + m_MonsterAni);
		}
	}
	else if (watch == TYPE_RIGHT)
	{
		if (type == TYPE_IDLE)
		{
			SetMonsterFrame(6);
		}
		else if (type == TYPE_WALK)
		{
			SetMonsterFrame(20 + m_MonsterAni);
		}
	}
	else if (watch == TYPE_BACK)
	{
		if (type == TYPE_IDLE)
		{
			SetMonsterFrame(9);
		}
		else if (type == TYPE_WALK)
		{
			SetMonsterFrame(25 + m_MonsterAni);
		}
	}

	if (type != TYPE_IDLE)
	{
		m_nCountAni++;
		if (m_nCountAni > 3)
		{
			SetCountAni(0);
		}
	}
	GetPosition();
}

void BitMgr::update()
{
	GetPosition();
	
	//MAP OBJECT
	if (GetBitGameMap() == TYPE_MAP1)
	{
		
	}
	else if (GetBitGameMap() == TYPE_MAP2)
	{

	}
	else if (GetBitGameMap() == TYPE_MAP3)
	{
		m_oy += 3;		//OBJECT ANIMATION

		if (m_oy > 330)
		{
			m_oy = 300;
		}
	}
}

void BitMgr::SetBitImage(eTYPE_ANI type, eTYPE_WATCH watch, eTYPE_KEY_TYPE key)
{
	int Walk_Front_Frame = 0, Walk_Back_Frame = 0;
	int Walk_Left_Frame = 0, Walk_Right_Frame = 0;

	int idle_Front_Frame = 0, idle_Back_Frame = 0;
	int idle_Left_Frame = 0, idle_Right_Frame = 0;
	
	if (m_supersaiyajin >= 1)
	{
		idle_Front_Frame = 31;
		idle_Left_Frame = 35;
		idle_Right_Frame = 39;
		idle_Back_Frame = 43;

		Walk_Front_Frame = 31;
		Walk_Left_Frame = 35;
		Walk_Right_Frame = 39;
		Walk_Back_Frame = 43;
	}
	else
	{
		idle_Front_Frame = 0;
		idle_Left_Frame = 3;
		idle_Right_Frame = 6;
		idle_Back_Frame = 9;

		Walk_Front_Frame = 10;
		Walk_Left_Frame = 15;
		Walk_Right_Frame = 20;
		Walk_Back_Frame = 25;
	}
	
	
	if (watch == TYPE_FRONT)
	{
		if (type == TYPE_IDLE)
		{
			SetBitFrame(idle_Front_Frame + m_nCountAni_2);
		}
		else if (type == TYPE_WALK)
		{
			SetBitFrame(Walk_Front_Frame + m_nCountAni);
		}
	}
	else if (watch == TYPE_LEFT)
	{
		if (type == TYPE_IDLE)
		{
			SetBitFrame(idle_Left_Frame + m_nCountAni_2);
		}
		else if (type == TYPE_WALK)
		{
			SetBitFrame(Walk_Left_Frame + m_nCountAni);
		}
	}
	else if (watch == TYPE_RIGHT)
	{
		if (type == TYPE_IDLE)
		{
			SetBitFrame(idle_Right_Frame + m_nCountAni_2);
		}
		else if (type == TYPE_WALK)
		{
			SetBitFrame(Walk_Right_Frame + m_nCountAni);
		}
	}
	else if (watch == TYPE_BACK)
	{
		if (type == TYPE_IDLE)
		{
			SetBitFrame(idle_Back_Frame);
		}
		else if (type == TYPE_WALK)
		{
			SetBitFrame(Walk_Back_Frame + m_nCountAni);
		}
	}

	if (type == TYPE_IDLE)
	{
		if (m_supersaiyajin >= 1)
		{
			if(m_nCountAni_2 > 0)
				m_nCountAni_2 = 0;
			
		}
		else
		{
			m_nCountAni_2++;
			if (m_nCountAni_2 > 2)
			{
				m_nCountAni_2 = 0;
			}
		}
	}
	else if (type == TYPE_WALK)
	{
		m_nCountAni++;

		if (m_supersaiyajin >= 1)
		{
			if (m_nCountAni > 3)
			{
				SetCountAni(0);
			}
		}
		else
		{
			if (m_nCountAni > 4)
			{
				SetCountAni(0);
			}
		}
	}

	GetPosition();
}



bool BitMgr::Destroy()
{
#if 0
	DeleteRender(i, j, k);

	DeleteObjectBit(o);

	m_vBitPlayer[0]->MyBitDestroy(); 
	m_vBitMap[0]->MapBitDestroy();
	m_vBitMonster[0]->DestroyMonster();
	m_vBitObject[0]->MyBitDestroy();
#endif
	return true;
}

void BitMgr::CreatMapImage(eTYPE_MAP type, HDC hdc, HINSTANCE _hlstance)
{
	BitMap *pBP = new BitMap(type, hdc, _hlstance);
	
	m_vBitMap.push_back(pBP); //맵 데이터 추가
	m_vBitMap[0]->CreateMyBit();
}

void BitMgr::GetPosition()
{
	m_px = CharacterMgr::Instance()->GetPosition(true, true);
	m_py = CharacterMgr::Instance()->GetPosition(false, true);

	m_mx = CharacterMgr::Instance()->GetPosition(true, false);
	m_my = CharacterMgr::Instance()->GetPosition(false, false);
}

void BitMgr::CreateObjectImage(eTYPE_OBJECT type, HDC hdc, HINSTANCE _hlstance)
{
	BitObject *pOJT = new BitObject(hdc, _hlstance);

	m_vBitObject.push_back(pOJT);
	m_vBitObject[0]->CreateMyBit(type);
	m_BitObject = 0;
	m_ox = 240;
	m_oy = 300;
}

void BitMgr::MapObjectBit(int idx)
{
	if (m_BitGameMap == TYPE_MAP3)
	{
		m_vBitObject[0]->CreateMyBit((eTYPE_OBJECT)idx);

		m_ObjectDC[idx] = CreateCompatibleDC(m_hdc);
		m_MaskODC[idx] = CreateCompatibleDC(m_hdc);

		m_ObjectMyBit[idx] = m_vBitObject[0]->Get_ObjectBit(idx);
		m_ObjectMyBit_Mask[idx] = m_vBitObject[0]->Get_ObjectMaskBit(idx);

		m_ObjectOldMyBit[idx] = (HBITMAP)SelectObject(m_ObjectDC[idx], m_ObjectMyBit[idx]);
		m_ObjectOldMyBit_Mask[idx] = (HBITMAP)SelectObject(m_MaskODC[idx], m_ObjectMyBit_Mask[idx]);

		BitBlt(m_BackBufferDC, m_ox, m_oy, m_nWidth, m_nHeight, m_MaskODC[idx], 0, 0, SRCAND);	//오브젝트
		BitBlt(m_BackBufferDC, m_ox, m_oy, m_nWidth, m_nHeight, m_ObjectDC[idx], 0, 0, SRCPAINT);
	}
}

void BitMgr::PlayerRender(int i)
{
	m_vBitPlayer[0]->CreateMyBit(TYPE_Player1); //캐릭터 비트 생성

	m_MaskPDC[i] = CreateCompatibleDC(m_hdc);
	m_PlayerDC[i] = CreateCompatibleDC(m_hdc);

	m_PlayerMyBit_Mask[i] = m_vBitPlayer[0]->Get_PlayerMaskBit(i); //캐릭터마스크
	m_PlayerMyBit[i] = m_vBitPlayer[0]->Get_PlayerBit(i);	//캐릭터

	m_PlayerOldMyBit_Mask[i] = (HBITMAP)SelectObject(m_MaskPDC[i], m_PlayerMyBit_Mask[i]);
	m_PlayerOldMyBit[i] = (HBITMAP)SelectObject(m_PlayerDC[i], m_PlayerMyBit[i]);
}

void BitMgr::MonsterRender(int j)
{
	m_vBitMonster[0]->CreateMyBit(TYPE_BOSS_MAJINBUU);

	m_MonsterDC[j] = CreateCompatibleDC(m_hdc);
	m_MaskMDC[j] = CreateCompatibleDC(m_hdc);

	m_MonsterMyBit_Mask[j] = m_vBitMonster[0]->Get_MonsterMaskBit(j); //몬스터 마스크
	m_MonsterMyBit[j] = m_vBitMonster[0]->Get_MonsterBit(j);	//몬스터

	m_MonsterOldMyBit_Mask[j] = (HBITMAP)SelectObject(m_MaskMDC[j], m_MonsterMyBit_Mask[j]);
	m_MonsterOldMyBit[j] = (HBITMAP)SelectObject(m_MonsterDC[j], m_MonsterMyBit[j]);
}

void BitMgr::MapRender(int k)
{
	m_vBitMap[0]->CreateMyBit();  // 맵 비트 생성
	m_MapDC[k] = CreateCompatibleDC(m_hdc);
	m_MapMyBit[k] = m_vBitMap[0]->Get_MAPBit(k); //맵
	m_MapOldMyBit[k] = ((HBITMAP)SelectObject(m_MapDC[k], m_MapMyBit[k]));
}

void BitMgr::DeleteObjectBit(int idx)
{
	if (m_ObjectDC[idx] != NULL)//m_BitGameMap == TYPE_MAP3)
	{
		SelectObject(m_ObjectDC[idx], m_ObjectOldMyBit[idx]);
		SelectObject(m_MaskODC[idx], m_ObjectOldMyBit_Mask[idx]);
		DeleteObject(m_ObjectMyBit);
		DeleteObject(m_ObjectMyBit_Mask);
		DeleteDC(m_ObjectDC[idx]);
		DeleteDC(m_MaskODC[idx]);
	}
}

void BitMgr::DeleteRender(int i, int j, int k)
{
	SelectObject(m_MapDC[k], m_MapOldMyBit[k]);
	SelectObject(m_MaskPDC[i], m_PlayerOldMyBit_Mask[i]);
	SelectObject(m_PlayerDC[i], m_PlayerOldMyBit[i]);
	SelectObject(m_MaskMDC[i], m_MonsterOldMyBit_Mask[j]);
	SelectObject(m_MonsterDC[i], m_MonsterOldMyBit[j]);
	SelectObject(m_BackBufferDC, m_hBackOld);

	DeleteObject(m_PlayerMyBit[i]);
	DeleteObject(m_MonsterMyBit[j]);
	DeleteObject(m_PlayerMyBit_Mask[i]);
	DeleteObject(m_MonsterMyBit_Mask[j]);
	DeleteObject(m_MapMyBit[k]);
	DeleteObject(m_hBackBmp);

	DeleteDC(m_PlayerDC[i]);
	DeleteDC(m_MonsterDC[j]);
	DeleteDC(m_MaskPDC[i]);
	DeleteDC(m_MaskMDC[j]);
	DeleteDC(m_MapDC[k]);
	DeleteDC(m_BackBufferDC);
}

void BitMgr::GameTitleBit(HINSTANCE _hlstance, eTYPE_TITLE index)
{
	HDC DC;
	HBITMAP title, oldtitle;
	TCHAR *str;

	DC = CreateCompatibleDC(m_hdc);;

	if (index == TYPE_TITLE_START)
		str = TEXT("img_background\\game_title.bmp");
	else if (index == TYPE_TITLE_OVER)
		str = TEXT("img_background\\game_over.bmp");
	else if (index == TYPE_TITLE_CLEAR)
		str = TEXT("img_background\\game_clear.bmp");
	else
		return;

	title = (HBITMAP)LoadImage(_hlstance, str, IMAGE_BITMAP, WORLD_SIZE_X, WORLD_SIZE_Y, LR_LOADFROMFILE);
	oldtitle = (HBITMAP)SelectObject(DC, title);

	BitBlt(m_hdc, 0, 0, m_nWidth, m_nHeight, DC, 0, 0, SRCCOPY);

	SelectObject(DC, oldtitle);
	DeleteObject(title);
	DeleteDC(DC);
}

void BitMgr::Render()
{
	bool isGameOver = WinMgr::Instance()->GetGameOver();
	if (isGameOver) 
		return;

	int i = 0, j = 0, k = 0, o = 0;
	i = m_BitFrame;
	j = m_BitMonsterFrame;
	k = m_BitGameMap;
	o = m_BitObject;

	MapRender(k);
	MonsterRender(j);
	PlayerRender(i);

	BitBlt(m_BackBufferDC, 0, 0, m_nWidth, m_nHeight, m_MapDC[k], 0, 0, SRCCOPY);	//맵
	
	BitBlt(m_BackBufferDC, m_mx, m_my, m_nWidth, m_nHeight, m_MaskMDC[j], 0, 0, SRCAND);	//몬스터
	BitBlt(m_BackBufferDC, m_mx, m_my, m_nWidth, m_nHeight, m_MonsterDC[j], 0, 0, SRCPAINT);
	
	BitBlt(m_BackBufferDC, m_px, m_py, m_nWidth, m_nHeight, m_MaskPDC[i], 0, 0, SRCAND);	// 플레이어
	BitBlt(m_BackBufferDC, m_px, m_py, m_nWidth, m_nHeight, m_PlayerDC[i], 0, 0, SRCPAINT);

	MapObjectBit(o);

	BitBlt(m_hdc, 0, 0, m_nWidth, m_nHeight, m_BackBufferDC, 0, 0, SRCCOPY);

	DeleteRender(i, j, k);
	
	DeleteObjectBit(o);

	m_vBitPlayer[0]->MyBitDestroy();
	m_vBitMap[0]->MyBitDestroy();
	m_vBitMonster[0]->MyBitDestroy();
	m_vBitObject[0]->MyBitDestroy();
}