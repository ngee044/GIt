#include "ManagerHeader.h"
#include "ButtonClass.h"
#include "MouseCursor.h"
#include "KeyboardClass.h"
#include "../api_pjt/resource.h"
#include <windows.h>

WinMgr::WinMgr()
{

}

WinMgr::~WinMgr()
{
}

HWND button_start;
int TempPos, Red, Green, Blue;
HWND hRed, hGreen, hBlue;
int nCount = 0;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	HDC hdc;

	RECT rt;
	static HWND hList;
	static HWND hCombo;
	static TCHAR *str = TEXT("asdfjasdfjklasdf");
	static TCHAR *t[] = { TEXT("a"), TEXT("b"), TEXT("c"),TEXT("d"), TEXT("e") };
	HINSTANCE _hlstance = WinMgr::Instance()->GetInstance();

	TCHAR sTime[255] = { 0 };
	TCHAR Info[255] = { 0 };
	TCHAR Info2[255] = { 0 };
	
	hdc = GetDC(hWnd);
	WinMgr *pWin = WinMgr::Instance();
	pWin->SethWnd(hWnd);
	wsprintf(Info, TEXT("출력 = %d"), 12);
	wsprintf(Info2, TEXT("출력 = %d"), 15);

	switch (message)
	{
	case WM_CREATE:
	{
		hRed = CreateWindow(TEXT("scrollbar"),
			NULL, WS_CHILD | WS_VISIBLE | SBS_HORZ, 10, 10, 400, 20, hWnd, (HMENU)101, _hlstance, NULL);
		hGreen = CreateWindow(TEXT("scrollbar"),
			NULL, WS_CHILD | WS_VISIBLE | SBS_HORZ, 10, 50, 400, 20, hWnd, (HMENU)102, _hlstance, NULL);
		hBlue = CreateWindow(TEXT("scrollbar"),
			NULL, WS_CHILD | WS_VISIBLE | SBS_HORZ, 10, 100, 400, 20, hWnd, (HMENU)103, _hlstance, NULL);
		SetScrollRange(hRed, SB_CTL, 0, 255, TRUE);
		SetScrollPos(hRed, SB_CTL, 0, TRUE);
		SetScrollRange(hGreen, SB_CTL, 0, 255, TRUE);
		SetScrollPos(hGreen, SB_CTL, 0, TRUE);
		SetScrollRange(hBlue, SB_CTL, 0, 255, TRUE);
		SetScrollPos(hBlue, SB_CTL, 0, TRUE);

		//SetTimer(hWnd, 1, 1000, NULL);
		//SetTimer(hWnd, 2, 2000, NULL);

		//button_start = CreateWindow(
		//	TEXT("button"),
		//	TEXT("게임 시작"),
		//	WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		//	20, 20, 125, 50, hWnd, (HMENU)0, _hlstance, NULL);
		//pWin->GameStartMenu(hWnd);

		// 리스트 박스
		//hList = CreateWindow(
		//	TEXT("listbox"), NULL,
		//	WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOTIFY,
		//	10, 10, 100, 200, hWnd, (HMENU)0, _hlstance, NULL);
		//for (int i = 0; i < 5; i++)
		//	SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)t[i]);

		//hCombo = CreateWindow(
		//	TEXT("combobox"), NULL,
		//	WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST,
		//	10, 10, 100, 200, hWnd, (HMENU)0, _hlstance, NULL);

		//for (int i = 0; i < 5; i++)
		//	SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)t[i]);

	}
	break;
	case WM_HSCROLL:
	{
		if ((HWND)lParam == hRed)
			TempPos = Red;

		if ((HWND)lParam == hGreen)
			TempPos = Green;

		if ((HWND)lParam == hBlue)
			TempPos = Blue;

		switch (LOWORD(wParam))
		{
		case SB_LINELEFT:
		{
			TempPos = max(0, TempPos - 1);

			if ((HWND)lParam == hRed)
				Red = TempPos;

			if ((HWND)lParam == hGreen)
				Green = TempPos;

			if ((HWND)lParam == hBlue)
				Blue = TempPos;

			SetScrollPos((HWND)lParam, SB_CTL, TempPos, TRUE);
			InvalidateRect(hWnd, NULL, FALSE);

		}
		break;
		case SB_LINERIGHT:
		{
			TempPos = min(255, TempPos + 1);

			if ((HWND)lParam == hRed)
				Red = TempPos;

			if ((HWND)lParam == hGreen)
				Green = TempPos;

			if ((HWND)lParam == hBlue)
				Blue = TempPos;

			SetScrollPos((HWND)lParam, SB_CTL, TempPos, TRUE);
			InvalidateRect(hWnd, NULL, FALSE);
		}
		break;
		case SB_PAGELEFT:
		{
			TempPos = max(0, TempPos - 10);

			if ((HWND)lParam == hRed)
				Red = TempPos;

			if ((HWND)lParam == hGreen)
				Green = TempPos;

			if ((HWND)lParam == hBlue)
				Blue = TempPos;

			SetScrollPos((HWND)lParam, SB_CTL, TempPos, TRUE);
			InvalidateRect(hWnd, NULL, FALSE);
		}
		break;
		case SB_PAGERIGHT:
		{
			TempPos = min(255, TempPos + 10);

			if ((HWND)lParam == hRed)
				Red = TempPos;

			if ((HWND)lParam == hGreen)
				Green = TempPos;

			if ((HWND)lParam == hBlue)
				Blue = TempPos;

			SetScrollPos((HWND)lParam, SB_CTL, TempPos, TRUE);
			InvalidateRect(hWnd, NULL, FALSE);
		}
		break;
		case SB_THUMBTRACK:
		{
			TempPos = HIWORD(wParam);

			if ((HWND)lParam == hRed)
				Red = TempPos;

			if ((HWND)lParam == hGreen)
				Green = TempPos;

			if ((HWND)lParam == hBlue)
				Blue = TempPos;

			SetScrollPos((HWND)lParam, SB_CTL, TempPos, TRUE);
			InvalidateRect(hWnd, NULL, FALSE);
		}
		break;
		}
	}
	break;

	case WM_COMMAND:
	{

		//switch (LOWORD(wParam))
		//{
		//case 0:
		//	switch (HIWORD(wParam))
		//	{
		//		case CBN_SELCHANGE:
		//		{
		//			int i = SendMessage(hCombo, CB_GETCURSEL, 0, 0);

		//			SendMessage(hCombo, CB_GETLBTEXT, i, (LPARAM)str);
		//			SetWindowText(hWnd, str);
		//		}
		//		break;

		//		case CBN_EDITCHANGE:
		//		{
		//			GetWindowText(hCombo, str, 255);
		//			SetWindowText(hWnd, str);
		//		}
		//		break;

		//		default:
		//			break;
		//	}
		//	break;

		//}

		// 리스트 박스
		//switch (LOWORD(wParam))
		//{
		//case 0:
		//{
		//	switch (HIWORD(wParam))
		//	{
		//	case LBN_SELCHANGE:
		//	{
		//		int i = SendMessage(hList, LB_GETCURSEL, 0, 0);
		//		SendMessage(hList, LB_GETTEXT, i, (LPARAM)str);
		//		SetWindowText(hWnd, str);
		//		hdc = GetDC(hWnd);
		//		TextOut(hdc, 500, 100, str, lstrlen(str));
		//		ReleaseDC(hWnd, hdc);
		//	}
		//	break;
		//	}
		//}
		//break;

		////switch (LOWORD(wParam))
		////{
		////case ID_FILE_LOAD:
		////	MessageBox(hWnd, TEXT("로드"), TEXT("파일로드"), MB_OK);
		////	break;
		////case ID_FILE_SAVE:
		////	MessageBox(hWnd, TEXT("저장"), TEXT("파일저장"), MB_OK);
		////	break;
		////}
		//default:
		//	break;
	}
	break;
	case WM_TIMER:
	{
#if 0
		switch (wParam)
		{
		case 1:
			GetLocalTime(&st);
			wsprintf(sTime, TEXT("시간 %d %d %d"), st.wHour, st.wMinute, st.wSecond);
			TextOut(hdc, 210, 250, sTime, wcslen(sTime));
			break;
		case 2:
			TextOut(hdc, 310, 250, TEXT("타이머 2"), 5);
			break;
		}
		//InvalidateRect(hWnd, NULL, TRUE);
#endif
	}
	break;
	case WM_SIZE:
	{
		//GetClientRect(hWnd, &rt);
		//InvalidateRect(hWnd, &rt, TRUE);
	}
	break;
	case WM_RBUTTONDOWN:
	{
#if 0
		if (IDOK == MessageBox(hWnd, TEXT("버튼을 눌러주세요"), TEXT("제목"), MB_OKCANCEL))
		{
			for (int i = 0; i < 100; i++)
			{
				SetPixel(hdc, i, i, RGB(255, 0, 0));
			}
			Rectangle(hdc, 300, 300, 500, 500);
			Ellipse(hdc, 500, 100, 600, 200);
					
			TextOut(hdc, 350, 250, TEXT("헬로우 API"), 7);
		}
		else
		{
			TextOut(hdc, 350, 250, TEXT("굿이브닝 API"), 7);
		}
#endif
	}
	break;
	case WM_LBUTTONDOWN:
	{
#if 0
		SetTextAlign(hdc, TA_BOTTOM);
		TextOut(hdc, 150, 100, Info, wcslen(Info));

		MoveToEx(hdc, 100, 100, NULL);
		LineTo(hdc, 200, 200);

		ReleaseDC(hWnd, hdc);
#endif
	}
	break;
	case WM_PAINT:
	{
#if 0
		HBRUSH MyBrush, OldBrush;
		hdc = BeginPaint(hWnd, &ps);

		MyBrush = (HBRUSH)GetStockObject(GRAY_BRUSH); //현재 브러쉬
		OldBrush = (HBRUSH)SelectObject(hdc, MyBrush);
		//현재 선택된 브러쉬
		
		Rectangle(hdc, 50, 50, 300, 200);
		
		SelectObject(hdc, OldBrush);//현재 선택된 브러쉬
		DeleteObject(MyBrush);//현재 선택된 브러쉬는 지울 수 없다.

		HPEN MyPen, OldPen;
		
		MyPen = CreatePen(PS_DASHDOTDOT, 3, RGB(0, 0, 255));
		OldPen = (HPEN)SelectObject(hdc, MyPen);//선택
		Rectangle(hdc, 50, 50, 300, 200);
		SelectObject(hdc, OldPen); //현재 선택된 펜
		DeleteObject(MyPen); //현재 선택된 펜은 지울 수 없다. OldPen이 현재 선택된 펜이라 지울수없다.
		EndPaint(hWnd, &ps);

		TextOut(hdc, 150, 100, Info2, wcslen(Info2));
		
		rt.left = 0;
		rt.right = 500;
		rt.bottom = 300;
		rt.top = 0;

		DrawText(hdc, Info, -1, &rt, DT_SINGLELINE | DT_RIGHT);

		EndPaint(hWnd, &ps);
#endif
#if 0

		//HDC BackBitmap = CreateCompatableBitmap(hdc, nHeight, nWidth);

//		MyBitmap = (HBITMAP)LoadBitmap(_hlstance, MAKEINTRESOURCE(IDB_BITMAP1));


	//	StretchBlt(MemDC, 100, 100, 20, 30, MemDC, 0, 0, 512, 512, SRCAND);

		HBITMAP hBackBmp, hBackOld, hMyBMP, hMyBMPOld;
		HDC dcBackBuffer, MDC;

		hdc = BeginPaint(hWnd, &ps);
		MDC = MemDC = CreateCompatibleDC(hdc);
		dcBackBuffer = CreateCompatibleDC(hdc);

		int nWidth, nHeight;
		nWidth = 65;
		nHeight = 65;

		MyBitmap = (HBITMAP)LoadImage(_hlstance, TEXT("bitmap1.bmp"), IMAGE_BITMAP, nWidth, nHeight, LR_LOADFROMFILE);
		OldBitmap = (HBITMAP)SelectObject(MemDC, MyBitmap);
		//BitBlt(hdc, 150, 150, 150, 160, MemDC, 0, 0, SRCCOPY);

		hBackBmp = CreateCompatibleBitmap(hdc, 800, 600);
		hBackBmp = (HBITMAP)LoadImage(_hlstance, TEXT("bitmap2.bmp"), IMAGE_BITMAP, nWidth, nHeight, LR_LOADFROMFILE);
		hBackOld = (HBITMAP)SelectObject(MemDC, hBackBmp);
		hBackOld = (HBITMAP)SelectObject(dcBackBuffer, hBackBmp);

		BitBlt(dcBackBuffer, 150, 150, 800, 600, MemDC, 0, 0, SRCCOPY);
		BitBlt(hdc, 0, 0, 800, 600, dcBackBuffer, 0, 0, SRCCOPY);

		SelectObject(dcBackBuffer, hBackOld);
		SelectObject(MemDC, OldBitmap);
		DeleteDC(dcBackBuffer); //삭제
		DeleteObject(MyBitmap);
#endif
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		pWin->SetHdc(hdc);
#if 0
		//(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
		HDC MemDC, MemDC2, MemDC3, dcBackBuffer;

		MemDC = CreateCompatibleDC(hdc);
		MemDC2 = CreateCompatibleDC(hdc);
		MemDC3 = CreateCompatibleDC(hdc);
		dcBackBuffer = CreateCompatibleDC(hdc);

		HBITMAP MyBit, MyBit2, MyBit3, OldMyBit, hBackBmp, hBackOld, OldMyBit2, OldMyBit3;
		MyBit = (HBITMAP)LoadImage(_hlstance, TEXT("img\\game3_Goku_mask.bmp"), IMAGE_BITMAP, 1024, 502, LR_LOADFROMFILE);
		MyBit2 = (HBITMAP)LoadImage(_hlstance, TEXT("img\\game3_Goku.bmp"), IMAGE_BITMAP, 1024, 502, LR_LOADFROMFILE);
		MyBit3 = (HBITMAP)LoadImage(_hlstance, TEXT("img\\game1_AniCapture.bmp"), IMAGE_BITMAP, 1024, 502, LR_LOADFROMFILE);

		hBackBmp = CreateCompatibleBitmap(hdc, 1024, 720);

		hBackOld = (HBITMAP)SelectObject(dcBackBuffer, hBackBmp);

		OldMyBit = (HBITMAP)SelectObject(MemDC, MyBit);
		OldMyBit2 = (HBITMAP)SelectObject(MemDC2, MyBit2);
		OldMyBit3 = (HBITMAP)SelectObject(MemDC3, MyBit3);

#if 1
		BitBlt(dcBackBuffer, 0, 0, 1280, 720, MemDC3, 0, 0, SRCCOPY);
		BitBlt(dcBackBuffer, 0, 0, 1280, 720, MemDC, 0, 0, SRCAND);
		BitBlt(dcBackBuffer, 0, 0, 1280, 720, MemDC2, 0, 0, SRCPAINT);
#endif

		BitBlt(hdc, 0, 0, 1280, 720, dcBackBuffer, 0, 0, SRCCOPY);
//		BitBlt(hdc, 0, 0, 1280, 720, MemDC3, 0, 0, SRCCOPY);

		SelectObject(MemDC, OldMyBit);
		SelectObject(MemDC2, OldMyBit2);
		SelectObject(MemDC3, OldMyBit3);
		SelectObject(dcBackBuffer, hBackOld);

		DeleteDC(MemDC); //삭제
		DeleteDC(MemDC2);
		DeleteDC(MemDC3);
		DeleteDC(dcBackBuffer); //삭제

		DeleteObject(MyBit);
		DeleteObject(MyBit2);
		DeleteObject(MyBit3);
		DeleteObject(hBackBmp);
#endif
#if 1
		pWin->Creatbackbuffer(hdc);
		pWin->SetWorldMap(TYPE_MAP1, hdc);
		pWin->CreateCharacter(TYPE_Player1, hdc, TYPE_FRONT, TYPE_IDLE, 0);
		pWin->Render();

		wsprintf(str, TEXT("Number: %d"), nCount);
		TextOut(hdc, 400, 300, str, lstrlen(str));
		nCount++;

#else
		HBRUSH MyBrush, OldBrush;
		MyBrush = CreateSolidBrush(RGB(Red, Green, Blue));//현재 브러쉬
		OldBrush = (HBRUSH)SelectObject(hdc, MyBrush);//현재 선택된 브러쉬
		Rectangle(hdc, 10, 100, 410, 300);
		SelectObject(hdc, OldBrush);//현재 선택된 브러쉬
		DeleteObject(MyBrush);//현재 선택된 브러쉬는 지울 수 없다.

		//HFONT hFont, OldFont;
		//TCHAR *str;
		//hFont = CreateFont(50, 30, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("맑은 고딕"));
		//OldFont = (HFONT)SelectObject(hdc, hFont);

		//TextOut(hdc, 100, 100, str, lstrlen(str));

		//SelectObject(hdc, OldFont);
		//DeleteObject(hFont);
#endif
		EndPaint(hWnd, &ps);

	}
	break;
	case WM_KEYDOWN:
	{

	}
	break;
	case WM_KEYUP:
	{
		switch (wParam)
		{
		case VK_LEFT:
			pWin->CreateCharacter(TYPE_Player1, hdc, TYPE_LEFT, TYPE_IDLE, 0);
		case VK_RIGHT:
			pWin->CreateCharacter(TYPE_Player1, hdc, TYPE_RIGHT, TYPE_IDLE, 0);
		case VK_UP:
		case VK_DOWN:
			break;
		}
	}
	break; 
	case WM_MOUSEMOVE:
	{
#if 0
		hdc = GetDC(hWnd);

		int x = LOWORD(lParam);
		int y = HIWORD(lParam);

		MoveToEx(hdc, x + 10, y + 10, NULL);//시작지점
		LineTo(hdc, x, y); // 끝지점

		ReleaseDC(hWnd, hdc);
#endif
	}
	break;
	case WM_DESTROY:
		KillTimer(hWnd, 2);
		KillTimer(hWnd, 1);
		PostQuitMessage(0);
		break;
	}

	return(DefWindowProc(hWnd, message, wParam, lParam));
}

int WinMgr::CreatWindows_Main(HINSTANCE _hlstance, HINSTANCE _h, LPSTR _lpstr, INT _int)
{
	WNDCLASS WndClass;
	
	WndClass.cbClsExtra = 0;//
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(COLOR_WINDOW + 1);//윈도우 
	WndClass.hCursor = (HCURSOR)LoadCursor(NULL, IDC_ARROW);//m_MouseCursor->SetMouseCursor(IDC_POINTER);//IDC_CURSOR1 ,IDC_ARROW
	WndClass.hIcon = (HICON)LoadIcon(_hlstance, MAKEINTRESOURCE(IDI_ICON1)); //윈도우 ICON
	WndClass.hInstance = _hlstance;//인스턴스 핸들 자기자신의 값, 프로그램 번호
	WndClass.lpfnWndProc = WndProc; //메시지 콜백
	WndClass.lpszClassName = TEXT("Win32"); //윈도우 이름
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1); //메뉴 = 리소스메뉴와 합쳐진다.
	WndClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&WndClass);//윈도우 클래스 등록
	
	HWND hWnd = CreateWindow(TEXT("Win32"),
		TEXT("Win32"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		WORLD_SIZE_X,//속성값은 멤버변수로
		WORLD_SIZE_Y,
		NULL, (HMENU)NULL, _hlstance, NULL);//클래스이름, 윈도우타이틀 이름, 스타일, 윈도우 크기와 위치, 부모윈도우 핸들, 윈도우 메뉴, 자신의 핸들, 

	SetInstance(_hlstance);
	m_hWnd = hWnd;

	RECT rc;

	GetClientRect(hWnd, &rc);
	m_nHeight = WORLD_SIZE_Y + (WORLD_SIZE_X - rc.right);
	m_nWidth = WORLD_SIZE_X + (WORLD_SIZE_Y - rc.bottom);

	MoveWindow(hWnd, 0, 0, m_nWidth, m_nHeight, TRUE);

	ShowWindow(hWnd, 1);
	UpdateWindow(hWnd);

	MSG Msg;

	while (1)
	{
		// 메시지가 있다면 처리한다.
		if (PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE))
		{
			if (Msg.message == WM_QUIT)
				break;

			// 메시지 처리.
			TranslateMessage(&Msg); // 메시지 번역. (키보드, 마우스)
			DispatchMessage(&Msg);  // 번역된 메시지 전달.(메시지 큐)
		}
	}

	return (INT)Msg.wParam; //메세지에러
}

void WinMgr::GameStartMenu(HWND hWnd)
{
	m_buttonClass->GameMenu(hWnd, m_Inst);
}

void WinMgr::ButtonCreate(HWND hWnd, TCHAR *type, TCHAR *str, int pi_x, int pi_y, int sz_x, int sz_y)
{
	m_buttonClass->Creatbutton(type, str, pi_x, pi_y, sz_x, sz_y, hWnd, m_Inst);
}

void WinMgr::Render()
{
	BitMgr::Instance()->Render();
}

void WinMgr::CreateCharacter(eTYPE_PLAYER player, HDC hdc, eTYPE_WATCH e_watch , eTYPE_ANI e_ani, int nFrame)
{
	BitMgr::Instance()->CreatPlayer(player, hdc, m_Inst, e_watch, e_ani, nFrame);
	BitMgr::Instance()->CreatMonster(TYPE_BOSS, hdc, m_Inst, e_watch, e_ani, nFrame);

	CharacterMgr::Instance()->CreatePlayer(player);
	CharacterMgr::Instance()->CreateMonster(false);
}

void WinMgr::SetWorldMap(eTYPE_MAP map, HDC hdc)
{
	BitMgr::Instance()->CreatMap(map, hdc, m_Inst);
	WorldMgr::Instance()->Init();
}

void WinMgr::Creatbackbuffer(HDC hdc)
{
	BitMgr::Instance()->SetHdc(hdc);
	BitMgr::Instance()->CreatBackBuffer(hdc);
}

void WinMgr::update()
{
	BitMgr::Instance()->update();

	if (m_bUpdate)
	{
		InvalidateRect(m_hWnd, NULL, FALSE);
		m_bUpdate = false;
	}
}

void WinMgr::GetAnimation(eTYPE_ANI type, eTYPE_WATCH watch)
{
	if (watch == TYPE_FRONT)
	{
	
	}
	else if (watch == TYPE_LEFT)
	{

	}
	else if (watch == TYPE_RIGHT)
	{

	}
	else if (watch == TYPE_BACK)
	{

	}
	else
	{
		if (IDOK == MessageBox(m_hWnd, TEXT("watch을 찾을 수 없습니다"), TEXT("에러"), MB_OKCANCEL));
	}
}