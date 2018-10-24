#ifndef MAIN_H
#define MAIN_H

#define _CRT_SECURE_NO_DEPRECATE

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <stdio.h>
#include <string.h>

///////////////
// ��� ���� //
///////////////
#define ERR             -1  // ���� ó���� �ڵ� -1.

#define SCREEN_WIDTH    800 // ȭ���� ���� ũ��.
#define SCREEN_HEIGHT   600 // ȭ���� ���� ũ��.
#define CLASS_NAME      "D3D Game Program"

/////////////////
// ��ũ�� �Լ� //
/////////////////
#define KEYUP(KeyCode)      ((GetAsyncKeyState(KeyCode))? 0 : 1)
#define KEYDOWN(KeyCode)    ((GetAsyncKeyState(KeyCode))? 1 : 0)

// �޸� ���� 
#define SAFE_RELEASE(Object) if(Object) { Object->Release(); Object = NULL; }
#define SAFE_DELETE(p)			{if(p) {delete (p);     (p)=NULL; }}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p);   (p)=NULL; }}

#endif