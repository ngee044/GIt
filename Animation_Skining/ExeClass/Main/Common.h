#pragma once

#define  _CRT_SECURE_NO_DEPRECATE//빌드할때deprecated경고를 없애버린다. 

#include <windows.h>
#include <stdio.h>

#include <d3d9.h>
#include <d3dx9.h>
#include <cstdlib>
#include <ctime>

#include "TextureContainer.h"
#include <map>

using namespace std;

#if 0
#include "fmod.h"
#include "fmod_errors.h"
#include "fmod_dsp.h"
#include "fmod_codec.h"
#include "fmod_output.h"
#endif

//#define SCREEN_WIDTH    800 // 화면의 가로 크기.(float)SCREEN_WIDTH/SCREEN_HEIGHT
//#define SCREEN_HEIGHT   600 // 화면의 세로 크기.
#define SCREEN_WIDTH    808 // 창틀때문에 +8
#define SCREEN_HEIGHT   634 // 창틀때문에+34
#define CLASS_NAME      "D3D Game Program"

#define D3D_FVF (D3DFVF_XYZ | D3DFVF_TEX1)

 //원본
#define FRAMESPEED    20
#define	ROTSPEED	  100
#define MAXIMUM_INTERPOLATION_FRAME 400
//원본#define INTERPOLATION_SPEED	  10400
#define INTERPOLATION_SPEED	  20400
#define MOVESPEED	  450
//#define MOVESPEED	  225

//#define MOUSE_INTERFACE

/////////////////
// 매크로 함수 //
/////////////////
#define KEYUP(KeyCode)      ((GetAsyncKeyState(KeyCode))? 0 : 1)
#define KEYDOWN(KeyCode)    ((GetAsyncKeyState(KeyCode))? 1 : 0)

// 메모리 해제 
#define SAFE_RELEASE(Object)	if(Object) { Object->Release(); Object = NULL; }
#define SAFE_DELETE(p)			{if(p) {delete (p);     (p)=NULL; }}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p);   (p)=NULL; }}
#define SAFE_DELETE2(p)			{if(p) {delete[] p; p=NULL;}}