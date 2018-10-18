#pragma once
#include "eType.h"

class MouseCurser
{
private:

public:
	MouseCurser();
	~MouseCurser();

	int GetMousCursor() { return 0; }
	void SetMouseCurser(eType_Mouse Type);
	void Default_Curser();

};

