#pragma once
#include "Object.h"
#include "eType.h"
#include "Common2.h"

class GdiItem :	public Object
{
protected:
	eTYPE_GDI m_eGDI;
	std::list<void*> m_list;

public:
	GdiItem();
	virtual ~GdiItem();

	void SetGDI(eTYPE_GDI eGdi) { m_eGDI = eGdi; }
};

