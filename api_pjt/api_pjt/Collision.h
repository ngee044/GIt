#pragma once

#include "Object.h"
#include "Windows.h"

class Collision : public Object
{
public:

	Collision();
	virtual ~Collision();

	virtual void Init() {};
	virtual void Reset() {};
	virtual void Delete() {};

	bool CheckBox(RECT rt, int x, int y);
	bool CheckMapBox(RECT rt, int x, int y);
	bool CheckBox(RECT rt, RECT rt2);
	bool CheckGameOverRect(RECT rt, RECT rt2);
};