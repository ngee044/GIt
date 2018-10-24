#ifndef MAIN_H
#define MAIN_H

#define _CRT_SECURE_NO_DEPRECATE

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <stdio.h>
#include <string.h>

///////////////
// 상수 정의 //
///////////////
#define ERR             -1  // 에러 처리용 코드 -1.

#define SCREEN_WIDTH    800 // 화면의 가로 크기.
#define SCREEN_HEIGHT   600 // 화면의 세로 크기.
#define CLASS_NAME      "D3D Game Program"

/////////////////
// 매크로 함수 //
/////////////////
#define KEYUP(KeyCode)      ((GetAsyncKeyState(KeyCode))? 0 : 1)
#define KEYDOWN(KeyCode)    ((GetAsyncKeyState(KeyCode))? 1 : 0)

// 메모리 해제 
#define SAFE_RELEASE(Object) if(Object) { Object->Release(); Object = NULL; }
#define SAFE_DELETE(p)			{if(p) {delete (p);     (p)=NULL; }}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p);   (p)=NULL; }}

#endif