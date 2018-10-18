#include "MouseCursor.h"

MouseCursor::MouseCursor()
{
}

MouseCursor::~MouseCursor()
{
}

HCURSOR MouseCursor::SetMouseCursor(int Type)
{
	return LoadCursor(NULL, MAKEINTRESOURCE(Type));
}

void MouseCursor::Default_Cursor()
{
	//NOT DOING
}