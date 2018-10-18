#pragma once
#include "Common.h"
#include "Common2.h"
class Object
{
protected:
	int m_ID;

public:
	Object();
	virtual ~Object();

	virtual void Init() = 0;
	virtual void Reset() = 0;
	virtual void Delete() = 0;

	void SetID(int nID);
	int GetID() { return m_ID; }

};

