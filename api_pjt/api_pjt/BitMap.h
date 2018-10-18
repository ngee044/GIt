#pragma once
#include "BitParent.h"

class BitMap :public BitParent
{
protected:
	HDC m_MAPDC;
	HBITMAP hBackBmp, hBackOld;
	HBITMAP m_MyBit_GAMEMAP[32];
	std::vector<HBITMAP> m_OldMyBit_GAMEMAP;
	HBITMAP m_maptype[32];
	HDC m_dcBackBuffer;

	HWND m_hWnd;
	HDC m_hdc;
	HINSTANCE m_hlstance;
	int m_nWidth, m_nHeight;

public:
	BitMap(eTYPE_MAP type, HDC hdc, HINSTANCE _hlstance);
	BitMap();
	virtual ~BitMap();

	HBITMAP CreatMapImage(eTYPE_MAP type, TCHAR *STR);
	HDC Get_MAPDC() { return m_MAPDC; }
	HBITMAP Get_MAPBit(int type) { return m_MyBit_GAMEMAP[type]; }
	HBITMAP Get_MAPOldBit(int type) { return m_OldMyBit_GAMEMAP[type]; }
	virtual void MyBitDestroy();
	virtual void CreateMyBit(eTYPE_MONSTER type) {}
	virtual void CreateMyBit(eTYPE_OBJECT type) {}
	virtual void CreateMyBit(eTYPE_PLAYER type) {}
	virtual void CreateMyBit();


};

