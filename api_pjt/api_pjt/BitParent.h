#pragma once
#include "Common.h"
#include "Common2.h"
#include "eType.h"
#include <Windows.h>

class BitParent
{
protected:
	int m_nWidth;
	int m_nHeight;
	HDC m_hdc;
	HINSTANCE m_hlstance;

public:
	BitParent();
	virtual ~BitParent();

	virtual void MyBitDestroy() = 0;
	virtual void CreateMyBit(eTYPE_MONSTER type) = 0;	//몬스터
	virtual void CreateMyBit(eTYPE_OBJECT type) = 0;	//오브젝트
	virtual void CreateMyBit(eTYPE_PLAYER type) = 0;	//플레이어
	virtual void CreateMyBit() = 0;						//맵

	void GetReSize();

};

