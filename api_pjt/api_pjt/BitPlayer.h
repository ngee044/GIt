#pragma once
#include "BitParent.h"

class BitPlayer :public BitParent
{
private:
	HDC m_dcBackBuffer;

	HBITMAP m_MyBit[256];
	HBITMAP m_MyBit_Mask[256];

	int m_BitFrame;
	int m_px, m_py;
	int m_nbit = 0;
	int m_nmask = 0;

public:
	BitPlayer(eTYPE_PLAYER type, HDC hdc, HINSTANCE _hlstance);
	BitPlayer();
	virtual ~BitPlayer();

	
	HBITMAP CreatPlayerImage(TCHAR *STR, eTYPE_PLAYER type, HDC hdc, HINSTANCE _hlstance, int size_x, int size_y);

	void CreateImage(eTYPE_PLAYER type, TCHAR *str, bool is_mask, int size_x, int size_y);

	HBITMAP Get_PlayerBit(int nFrame)		{ return m_MyBit[nFrame];		  }
	HBITMAP Get_PlayerMaskBit(int nFrame)	{ return m_MyBit_Mask[nFrame];    }

	virtual void CreateMyBit(eTYPE_PLAYER type);
	virtual void CreateMyBit(eTYPE_MONSTER type) {}
	virtual void CreateMyBit(eTYPE_OBJECT type) {}
	virtual void CreateMyBit() {}

	void GetAniFrame(int nFrame);
	void MyBitDestroy();


};

