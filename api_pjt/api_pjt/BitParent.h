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
	virtual void CreateMyBit(eTYPE_MONSTER type) = 0;	//����
	virtual void CreateMyBit(eTYPE_OBJECT type) = 0;	//������Ʈ
	virtual void CreateMyBit(eTYPE_PLAYER type) = 0;	//�÷��̾�
	virtual void CreateMyBit() = 0;						//��

	void GetReSize();

};

