#pragma once

#include "Object.h"
#include "eType.h"

struct ANI
{
	eTYPE_ANI eANI;

	int MaxAni;
	int CurAni;
};

typedef std::vector<ANI*> VECANI;

class BitPlayer;
class BitMonster;

class Animation : public Object
{
private:
	BitPlayer *BitPlayer;
	BitMonster *BitMonster;

	VECANI m_vecAni;

	eTYPE_ANI m_eCurAni;

	ANI m_Atk;
	ANI m_idle;


public:
	Animation();
	virtual ~Animation();

	virtual void Init();
	virtual void Reset();
	virtual void Delete();

};

