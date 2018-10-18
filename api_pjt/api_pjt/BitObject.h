#pragma once
#include "BitParent.h"
#include "eType.h"

class BitObject : public BitParent
{
private:
	HBITMAP m_ObjBit[256];
	HBITMAP m_ObjBit_Mask[256];

	int m_nbit = 0;
	int m_nmask = 0;

public:
	BitObject();
	BitObject(HDC hdc, HINSTANCE _hlstance);
	virtual ~BitObject();

	HBITMAP CreateObjectImage(TCHAR *STR, int size_x, int size_y);
	HBITMAP Get_ObjectBit(int nFrame) { return m_ObjBit[nFrame]; }
	HBITMAP Get_ObjectMaskBit(int nFrame) { return m_ObjBit_Mask[nFrame]; }

	void CreateImage(eTYPE_OBJECT type, TCHAR *str, bool is_mask);
	virtual void CreateMyBit(eTYPE_OBJECT type);
	virtual void CreateMyBit(eTYPE_MONSTER type) {}
	virtual void CreateMyBit(eTYPE_PLAYER type) {}
	virtual void CreateMyBit() {}
	virtual void MyBitDestroy();
};

