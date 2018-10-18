#pragma once
#include <windows.h>

#define BUTTON_TYPE TEXT("button")

class ButtonClass
{
private:
	HWND m_button;

public:
	ButtonClass();
	virtual ~ButtonClass();

	void GameMenu(HWND hWnd, HINSTANCE _hlstance);
	void GameOver(HWND hWnd, HINSTANCE _hlstance);
	void Creatbutton(TCHAR *type, TCHAR *str, int pi_x, int pi_y, int sz_x, int sz_y, HWND hWnd, HINSTANCE _hlstance, int index);

};

