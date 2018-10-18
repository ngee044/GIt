#pragma once
#include <windows.h>

class KeyboardClass
{

public:
	KeyboardClass();
	~KeyboardClass();

	void GetKeyValue(HWND hWnd, WPARAM wParam);
};

