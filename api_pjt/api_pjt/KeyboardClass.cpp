#include "KeyboardClass.h"

KeyboardClass::KeyboardClass()
{
}

KeyboardClass::~KeyboardClass()
{
}

void KeyboardClass::GetKeyValue(HWND hWnd, WPARAM wParam)
{
	HDC hdc;
	hdc = GetDC(hWnd);
	TCHAR Info[255];

	switch (wParam)
	{
	case VK_LEFT:
		wsprintf(Info, TEXT("LEFT API"));
		TextOut(hdc, 350, 250, Info, wcslen(Info));
		break;
	case VK_RIGHT:
		wsprintf(Info, TEXT("RIGHT API"));
		TextOut(hdc, 350, 250, Info, wcslen(Info));
		break;
	case VK_UP:
		wsprintf(Info, TEXT("UP API"));
		TextOut(hdc, 350, 250, Info, wcslen(Info));
		break;
	case VK_DOWN:
		wsprintf(Info, TEXT("DOWN API"));
		TextOut(hdc, 350, 250, Info, wcslen(Info));
		break;
	case VK_ESCAPE:
		PostQuitMessage(0);
		break;
	}
}