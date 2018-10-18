#pragma once

#include "GdiItem.h"

class Gdi
{
protected:
	std::list<GdiItem*> m_list;

public:
	Gdi();
	virtual ~Gdi();
};

