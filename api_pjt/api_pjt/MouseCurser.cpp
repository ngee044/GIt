#include "MouseCurser.h"
#include "WinMgr.h"

MouseCurser::MouseCurser()
{
}


MouseCurser::~MouseCurser()
{
}

void MouseCurser::SetMouseCurser(eType_Mouse Type)
{
	WNDCLASS WndClass;

	if (Type == TYPE_ARROW)
		WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	else if (Type == TYPE_WAIT)
		WndClass.hCursor = LoadCursor(NULL, IDC_WAIT);
	else
		WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
}

void MouseCurser::Default_Curser()
{
	WNDCLASS WndClass;
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
}