#pragma once
#include "Singleton.h"
#include "BitParent.h"
#include "BitMap.h"
#include "BitMonster.h"
#include "BitPlayer.h"
#include "BitObject.h"

class BitMgr : public Singleton<BitMgr>
{
private:
	std::vector<BitPlayer*>		m_vBitPlayer;
	std::vector<BitMap*>		m_vBitMap;
	std::vector<BitMonster*>	m_vBitMonster;
	std::vector<BitObject*>		m_vBitObject;

	HDC m_hdc;			  //화면 DC
	HDC m_MapDC[5];		  //맵 DC
	HDC m_PlayerDC[128];		  //플레이어DC
	HDC m_MaskPDC[128];		  //플레이어 마스크 DC

	HDC m_MonsterDC[128];	  //몬스터 DC
	HDC m_MaskMDC[128];		  //몬스터 마스크 DC

	HDC m_ObjectDC[16];
	HDC m_MaskODC[16];

	HDC m_BackBufferDC;   //더블 버퍼링 DC

	int m_BitFrame;
	int m_nCountAni;
	int m_nCountAni_2;

	int m_MonsterAni;
	int m_BitMonsterFrame;
	int m_BitGameMap;
	int m_BitObject;
	int m_TempWatch;

	int m_nWidth, m_nHeight;
	int m_px, m_py, m_mx, m_my, m_ox, m_oy;

	int m_supersaiyajin;

	HBITMAP m_MapMyBit[128], m_MapOldMyBit[128];

	HBITMAP m_PlayerMyBit[128], m_PlayerOldMyBit[128];
	HBITMAP m_PlayerMyBit_Mask[128], m_PlayerOldMyBit_Mask[128];

	HBITMAP m_MonsterMyBit[128], m_MonsterOldMyBit[128];
	HBITMAP m_MonsterMyBit_Mask[128], m_MonsterOldMyBit_Mask[128];

	HBITMAP m_ObjectMyBit[128], m_ObjectOldMyBit[128];
	HBITMAP m_ObjectMyBit_Mask[128], m_ObjectOldMyBit_Mask[128];
	HBITMAP m_hBackBmp, m_hBackOld;

public:
	BitMgr();
	virtual ~BitMgr();

	BitParent *GetBitMap(int nNum) { return m_vBitMap[nNum]; }
	BitParent *GetBitMonster(int nNum) { return m_vBitMonster[nNum]; }
	HDC GetHdc() { return m_hdc; }
	HDC GetBackBufferDC() { return m_BackBufferDC; }
	int GetBitFrame() { return m_BitFrame; }
	void SetBitFrame(int nFrame) { m_BitFrame = nFrame; }
	void SetMonsterFrame(int nFrame) { m_BitMonsterFrame = nFrame; }
	void SetMonsterAni(int cnt) { m_MonsterAni = cnt; }
	void SetCountAni(int cnt) { m_nCountAni = cnt; }
	void SetBitGameMap(int map) { m_BitGameMap = map; }
	int GetBitGameMap() { return m_BitGameMap; }
	int GetBitMonsterFrame() { return m_BitMonsterFrame; }
	void SetBitObject(int idx) { m_BitObject = idx; }
	int GetBitObject() { return m_BitObject; }
	int GetCountAni() { return m_nCountAni; }
	int GetMonsterAni() { return m_MonsterAni; }
	int GetWidth() { return m_nWidth; }
	int GetHeight() { return m_nHeight; }
	int GetPx() { return m_px; }
	int GetPy() { return m_py; }

	bool Destroy();
	void SetSSJ(int idx) { m_supersaiyajin = idx; }
	int GetSSJ() { return m_supersaiyajin; }
	void update();
	void CreatePlayerImage(eTYPE_PLAYER type, HDC hdc, HINSTANCE _hlstance);
	void CreateMonsterImage(eTYPE_MONSTER type, HDC hdc, HINSTANCE _hlstance);
	void CreatMapImage(eTYPE_MAP type, HDC hdc, HINSTANCE _hlstance);
	void CreateObjectImage(eTYPE_OBJECT type, HDC hdc, HINSTANCE _hlstance);
	void CreatBackBuffer(HDC hdc);
	void Render();
	void SetHdc(HDC hdc) { m_hdc = hdc; }
	void GetPosition();
	void SetBitImage(eTYPE_ANI type, eTYPE_WATCH watch, eTYPE_KEY_TYPE key);
	void SetBitMonsterImage(eTYPE_ANI type, eTYPE_WATCH watch);
	void MapObjectBit(int idx );
	void DeleteObjectBit(int idx);
	void MapRender(int k);
	void MonsterRender(int j);
	void PlayerRender(int i);
	void DeleteRender(int i, int j, int k);
	void GameTitleBit(HINSTANCE _hlstance, eTYPE_TITLE index);
	void Init();

};

