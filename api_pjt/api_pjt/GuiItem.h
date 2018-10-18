#pragma once
#include "Object.h"
#include "eType.h"

class GuiItem :	public Object
{
protected:
	eTYPE_GDI m_eGDI;
	std::list<void*> m_list;

public:
	GuiItem();
	virtual ~GuiItem();

	void SetGDI(eTYPE_GDI eGdi) { m_eGDI = eGdi; }
};

