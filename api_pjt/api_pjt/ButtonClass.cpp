#include "ButtonClass.h"
#include "eType.h"

ButtonClass::ButtonClass()
{
}


ButtonClass::~ButtonClass()
{
}

void ButtonClass::GameMenu(HWND hWnd, HINSTANCE _hlstance)
{
	Creatbutton(BUTTON_TYPE, TEXT("게임 시작"), 500, 360, 125, 50, hWnd, _hlstance, TYPE_BUTTON_START);
	Creatbutton(BUTTON_TYPE, TEXT("게임 종료"), 500, 440, 125, 50, hWnd, _hlstance, TYPE_BUTTON_END);
}

void ButtonClass::GameOver(HWND hWnd, HINSTANCE _hlstance)
{
	Creatbutton(BUTTON_TYPE, TEXT("처음으로 돌아가기"), 500, 360, 125, 50, hWnd, _hlstance, TYPE_BUTTON_BACK);
	Creatbutton(BUTTON_TYPE, TEXT("게임 종료"), 500, 440, 125, 50, hWnd, _hlstance, TYPE_BUTTON_END);
}
void ButtonClass::Creatbutton(TCHAR *type, TCHAR * str, int pi_x, int pi_y, int sz_x, int sz_y, HWND hWnd, HINSTANCE _hlstance, int index)
{
	CreateWindow(
		type,
		str,
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		pi_x, pi_y, sz_x, sz_y, hWnd, (HMENU)index, _hlstance, NULL);
}
