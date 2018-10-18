#pragma once
#include "BitParent.h"

class BitMonster : public BitParent
{
private:
	HBITMAP m_MyBit[256], m_MyBitMask[256];
	HDC MonsterDC, MaskDC, m_dcBackBuffer;
	int m_bit = 0, m_mask = 0;
	
public:
	BitMonster(eTYPE_MONSTER type, HDC hdc, HINSTANCE _hlstance);
	BitMonster();
	virtual ~BitMonster();

	HBITMAP CreatMonsterImage(HDC hdc, HINSTANCE _hlstance, TCHAR *STR);
	HDC Get_MonsterDC() { return MonsterDC; }
	HDC Get_MonsterMaskDC() { return MaskDC; }
	HBITMAP Get_MonsterBit(int nFrame) { return m_MyBit[nFrame]; }
	HBITMAP Get_MonsterMaskBit(int nFrame) { return m_MyBitMask[nFrame]; }
	
	virtual void CreateMyBit(eTYPE_MONSTER type);
	virtual void CreateMyBit(eTYPE_PLAYER type) {}
	virtual void CreateMyBit(eTYPE_OBJECT type) {}
	virtual void CreateMyBit() {}
	virtual void MyBitDestroy();

	void CreateImage(eTYPE_MONSTER type, TCHAR *str, bool is_mask);

};

