#pragma once
#include "eType.h"
#include <windows.h>

class MouseCursor
{
private:

public:
	MouseCursor();
	~MouseCursor();

	int GetMousCursor() { return 0; }  //FIXME
	HCURSOR SetMouseCursor(int Type);
	void Default_Cursor();

};

