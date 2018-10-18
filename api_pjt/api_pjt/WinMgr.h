#pragma once
#include "Singleton.h"
#include <windows.h>
#include "eType.h"
#include "ButtonClass.h"

class MouseCursor;
class KeyboardClass;
class ButtonClass;
class Collision;

class WinMgr : public Singleton <WinMgr>
{
private:
	HWND m_hWnd;
	bool m_bUpdate;
	bool m_isfirst = true;
	bool m_isgamestart;
	bool m_IsGameOver;
	HINSTANCE m_Inst;
	HDC m_hdc;
	ButtonClass *m_buttonClass;
	MouseCursor *m_MouseCursor;
	KeyboardClass *m_Keyboard;
	Collision *m_Collision;
	int m_nWidth, m_nHeight;
	int m_status;
	bool m_isShowBuu;

public:
	WinMgr();
	~WinMgr();

	int CreatWindows_Main(HINSTANCE _hInstance, HINSTANCE _h, LPSTR _lpstr, INT _int);
	void SetUdatePaint(bool isUdate) { m_bUpdate = isUdate; }
	void SetInstance(HINSTANCE _hInstance) { m_Inst = _hInstance; }
	void SetHdc(HDC _hdc) { m_hdc = _hdc; }
	void SethWnd(HWND _hwnd) { m_hWnd = _hwnd; }
	void CreateCharacter(eTYPE_PLAYER player, HDC hdc);
	void CreateWorldMap(eTYPE_MAP map, HDC hdc);
	void update();
	void Render();
	void Init();
	void Move(eTYPE_ANI type, eTYPE_WATCH watch, eTYPE_KEY_TYPE key, bool is_ani);
	void ButtonCreate(HWND hWnd, TCHAR *type, TCHAR *str, int pi_x, int pi_y, int sz_x, int sz_y,int index);
	int GetWidth()  { return m_nWidth;	}
	int GetHeight() { return m_nHeight; }
	void ChangeMapBit(eTYPE_MAP type);
	void DestroyRender();
	void CharacterIDLE(int type);
	int GetWatchStatus() { return m_status; }
	void SetWatchStatus(eTYPE_WATCH type) { m_status = type; }
	void GetCharacterPosition();
	void GetMapEvent(eTYPE_EVENT type);
	void GameOver(bool isClear);
	bool GetGameOver() { return m_IsGameOver; }
	void SetGameOver(bool idx) { m_IsGameOver = idx; }
	void GameTitle();
	bool Getstart() { return m_isgamestart; }
	void Setstart(bool idx) { m_isgamestart = idx; }
	void GameReStart(HWND hWnd);
	void DoCheat();
	bool GetIsShowBoss() { return m_isShowBuu; }
	void SetIsShowBoss(bool idx) { m_isShowBuu = idx; }
	void ShowBossMonster();
	HINSTANCE GetInstance() { return m_Inst; }
	HDC GetHdc() { return m_hdc; }
	HWND GethWnd() { return m_hWnd; }

};