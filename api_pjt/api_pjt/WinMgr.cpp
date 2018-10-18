#include "ManagerHeader.h"
#include "ButtonClass.h"
#include "MouseCursor.h"
#include "Collision.h"
#include "../api_pjt/resource.h"
#include <windows.h>


int nCount = 0;
int x = 0, y = 0;
TCHAR ptr[128];
TCHAR ptr2[128];

WinMgr::WinMgr()
{
}

WinMgr::~WinMgr()
{
	DestroyRender();
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	HDC hdc;
	PAINTSTRUCT ps;
	HINSTANCE _hlstance = WinMgr::Instance()->GetInstance();
	
	hdc = GetDC(hWnd);
	WinMgr *pWin = WinMgr::Instance();
	pWin->SethWnd(hWnd);

	switch (message)
	{
	case WM_CREATE:
	{

	}
	break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case TYPE_BUTTON_START:
			pWin->Setstart(false);
			pWin->SetGameOver(false);
			pWin->SetIsShowBoss(false);

			SetTimer(hWnd, 0, 2000, NULL);
			SetTimer(hWnd, 1, 75, NULL);
			SetTimer(hWnd, 2, 4000, NULL);
			break;
		case TYPE_BUTTON_BACK:
			pWin->GameTitle();
			break;
		case TYPE_BUTTON_EXIT:
			KillTimer(hWnd, 2);
			KillTimer(hWnd, 1);
			KillTimer(hWnd, 0);
			PostQuitMessage(0);
			break;

		default:
			break;

		}
	}
	break;
	case WM_TIMER:
	{
		switch(wParam)
		{
			case 0:
			{
				int type;
				type = pWin->GetWatchStatus();
				pWin->CharacterIDLE(type);
				break;
			}

			case 1:
			{
				pWin->SetUdatePaint(true);
				AIMgr::Instance()->update();
				break;
			}

			case 2:
			{
				bool IsShowBoss = pWin->GetIsShowBoss();
				if (IsShowBoss)
				{
					//Not Doing
				}
				else
				{
					pWin->ShowBossMonster();
					pWin->SetIsShowBoss(true);
				}
				break;
			}

			default:
				break;
		}
	}
	break;
	case WM_SIZE:
	{
	}
	break;
	case WM_RBUTTONDOWN:
	{
	}
	break;
	case WM_LBUTTONDOWN:
	{
	}
	break;
	case WM_PAINT:
	{
		HDC hdc = BeginPaint(hWnd, &ps);
		pWin->SetHdc(hdc);
		pWin->Render();
		
		pWin->GetCharacterPosition();
		wsprintf(ptr, TEXT("Number: %d"), nCount);
		wsprintf(ptr2, TEXT("X = %d, Y = %d"), x, y);
		TextOut(hdc, 400, 270, ptr2, lstrlen(ptr2));
		TextOut(hdc, 400, 300, ptr, lstrlen(ptr));
		nCount++;

		EndPaint(hWnd, &ps);
	}
	break;
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_LEFT:
			pWin->Move(TYPE_WALK, TYPE_LEFT, TYPE_LEFT_KEY, false);
			break;
		case VK_RIGHT:
			pWin->Move(TYPE_WALK, TYPE_RIGHT, TYPE_RIGHT_KEY, false);
			break;
		case VK_UP:
			pWin->Move(TYPE_WALK, TYPE_BACK, TYPE_UP_KEY, false);
			break;
		case VK_DOWN:
			pWin->Move(TYPE_WALK, TYPE_FRONT, TYPE_DOWN_KEY, false);
			break;
		case VK_ESCAPE:
			//
			break;
		default:
			break;
		}
		
		SetTimer(hWnd, 0, 500, NULL); // 타이머
	}
	break;
	case WM_KEYUP:
	{
		switch (wParam)
		{
		case VK_LEFT:
			pWin->Move(TYPE_IDLE, TYPE_LEFT, TYPE_LEFT_KEY, true);
			break;
		case VK_RIGHT:
			pWin->Move(TYPE_IDLE, TYPE_RIGHT, TYPE_RIGHT_KEY, true);
			break;
		case VK_UP:
			pWin->Move(TYPE_IDLE, TYPE_BACK, TYPE_UP_KEY, true);
			break;
		case VK_DOWN:
			pWin->Move(TYPE_IDLE, TYPE_FRONT, TYPE_DOWN_KEY, true);
			break;
		case VK_SPACE:
			pWin->GetMapEvent(TYPE_EVENT_ONE);
		case VK_F6:
			pWin->DoCheat();
		case VK_ESCAPE:
			//
			break;
		default:
			break;
		}

		SetTimer(hWnd, 0, 500, NULL); // 타이머
	}
	break; 
	case WM_MOUSEMOVE:
	{
	}
	break;
	case WM_DESTROY:
		KillTimer(hWnd, 2);
		KillTimer(hWnd, 1);
		KillTimer(hWnd, 0);
		PostQuitMessage(0);
		break;
	}

	return(DefWindowProc(hWnd, message, wParam, lParam));
}

int WinMgr::CreatWindows_Main(HINSTANCE _hlstance, HINSTANCE _h, LPSTR _lpstr, INT _int)
{
	WNDCLASS WndClass;

	m_nWidth = WORLD_SIZE_X;
	m_nHeight = WORLD_SIZE_Y;

	WndClass.cbClsExtra = 0;//
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(COLOR_WINDOW + 1);//윈도우 
	WndClass.hCursor = (HCURSOR)LoadCursor(NULL, IDC_ARROW);//m_MouseCursor->SetMouseCursor(IDC_POINTER);//IDC_CURSOR1 ,IDC_ARROW
	WndClass.hIcon = (HICON)LoadIcon(_hlstance, MAKEINTRESOURCE(IDI_ICON1)); //윈도우 ICON
	WndClass.hInstance = _hlstance;//인스턴스 핸들 자기자신의 값, 프로그램 번호
	WndClass.lpfnWndProc = WndProc; //메시지 콜백
	WndClass.lpszClassName = TEXT("Dragonball Z"); //윈도우 이름
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1); //메뉴 = 리소스메뉴와 합쳐진다.
	WndClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&WndClass);//윈도우 클래스 등록
	
	HWND hWnd = CreateWindow(TEXT("Dragonball Z"),
		TEXT("Dragonball Z"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		m_nWidth,//속성값은 멤버변수로
		m_nHeight,
		NULL, (HMENU)NULL, _hlstance, NULL);//클래스이름, 윈도우타이틀 이름, 스타일, 윈도우 크기와 위치, 부모윈도우 핸들, 윈도우 메뉴, 자신의 핸들, 

	SetInstance(_hlstance);
	m_hWnd = hWnd;	
	m_isfirst = true;

#if 1
	RECT rc;

	GetClientRect(hWnd, &rc);
	m_nWidth = m_nWidth + (m_nWidth - rc.right);
	m_nHeight = m_nHeight + (m_nHeight - rc.bottom);
	MoveWindow(hWnd, 0, 0, m_nWidth, m_nHeight, TRUE);
#endif

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

		update();
	}

	return (INT)Msg.wParam; //메세지에러
}

void WinMgr::ButtonCreate(HWND hWnd, TCHAR *type, TCHAR *str, int pi_x, int pi_y, int sz_x, int sz_y,int index)
{
	m_buttonClass->Creatbutton(type, str, pi_x, pi_y, sz_x, sz_y, hWnd, m_Inst, index);
}

void WinMgr::DoCheat()
{
	CharacterMgr::Instance()->CheatGame();
}

void WinMgr::Init()
{

}

void WinMgr::Render()
{

	BitMgr::Instance()->CreatBackBuffer(m_hdc);
	
	if (m_isfirst)
	{
		CreateWorldMap((eTYPE_MAP)0, m_hdc);
		ChangeMapBit((eTYPE_MAP)0);
		CreateCharacter(TYPE_Player1, m_hdc);
		GameTitle();
		m_isfirst = false;	
	}
	BitMgr::Instance()->Render();
}

void WinMgr::DestroyRender()
{
	BitMgr::Instance()->Destroy();
}

void WinMgr::CreateCharacter(eTYPE_PLAYER player, HDC hdc)
{
	CharacterMgr::Instance()->Init();
	CharacterMgr::Instance()->HideChar(false);
	AIMgr::Instance()->Init();

	BitMgr::Instance()->CreatePlayerImage(player, hdc, m_Inst);
	BitMgr::Instance()->CreateMonsterImage(TYPE_BOSS_MAJINBUU, hdc, m_Inst);
	BitMgr::Instance()->CreateObjectImage(TYPE_OBJ_ARROW, hdc, m_Inst);
}

void WinMgr::CreateWorldMap(eTYPE_MAP map, HDC hdc)
{
	BitMgr::Instance()->CreatMapImage(map, hdc, m_Inst);
//	WorldMgr::Instance()->Init();
}

void WinMgr::update()
{
	CharacterMgr::Instance()->update();
	BitMgr::Instance()->update();

	if (m_bUpdate)
	{
		InvalidateRect(m_hWnd, NULL, FALSE);
		m_bUpdate = false;
	}
}

void WinMgr::CharacterIDLE(int type)
{
	m_bUpdate = true;
	int key_status = type;
	BitMgr::Instance()->SetBitImage(TYPE_IDLE, (eTYPE_WATCH)type, (eTYPE_KEY_TYPE)key_status);
}

void WinMgr::Move(eTYPE_ANI type, eTYPE_WATCH watch, eTYPE_KEY_TYPE key, bool is_ani)
{
	if (m_IsGameOver)
		return;

	m_bUpdate = true;
	CharacterMgr::Instance()->Move(watch, key, is_ani, true);
	AIMgr::Instance()->AIMove();
	BitMgr::Instance()->SetBitImage(type, watch, key);
	m_status = watch;
}

void WinMgr::GetCharacterPosition()
{
	x = CharacterMgr::Instance()->GetPosition(1, 1);
	y = CharacterMgr::Instance()->GetPosition(0, 1);
}

void WinMgr::GetMapEvent(eTYPE_EVENT type)
{
	HWND hWnd = GethWnd();
	if (m_IsGameOver)
	{
		GameReStart(hWnd);
	}
	else
	{
		if (type == TYPE_EVENT_ONE)
		{
			WorldMgr::Instance()->MapEvent(type);
		}
	}
}

void WinMgr::ChangeMapBit(eTYPE_MAP type)
{
	SetIsShowBoss(false);
	CharacterMgr::Instance()->HideChar(false);
	AIMgr::Instance()->SetShowMajinBuu(false);
	BitMgr::Instance()->SetBitGameMap(type);
	WorldMgr::Instance()->SetMapStatus(type);
	WorldMgr::Instance()->GetMapInfo();
}

void WinMgr::GameTitle()
{
	m_IsGameOver = true;
	BitMgr::Instance()->GameTitleBit(m_Inst, TYPE_TITLE_START);
//	m_buttonClass->GameMenu(m_hWnd, m_Inst);
}

void WinMgr::GameOver(bool isClear)
{
	TCHAR *str;

	if (isClear)
	{
		m_IsGameOver = true;
		BitMgr::Instance()->GameTitleBit(m_Inst, TYPE_TITLE_CLEAR);
		str = TEXT("    GAME CLEAR    ");
		TextOut(m_hdc, 400, 300, str, lstrlen(str));
	}
	else
	{
		BitMgr::Instance()->SetBitFrame(30);
		BitMgr::Instance()->GameTitleBit(m_Inst, TYPE_TITLE_OVER);
		m_IsGameOver = true;

#if 1
		str = TEXT("    GAME OVER    ");
		TextOut(m_hdc, 400, 300, str, lstrlen(str));
#else
		m_buttonClass->GameOver(m_hWnd, m_Inst);
#endif
	}
}

void WinMgr::GameReStart(HWND hWnd)
{
	m_IsGameOver = false;
	ChangeMapBit(TYPE_MAP1);

	SetIsShowBoss(false);
	BitMgr::Instance()->SetBitFrame(0);
	BitMgr::Instance()->SetSSJ(0);
	CharacterMgr::Instance()->SetisReturn(false);
	CharacterMgr::Instance()->SetCharacterPosition(true, 740, 20, false);
	CharacterMgr::Instance()->HideChar(false);
	CharacterMgr::Instance()->SetGameClear(false);
	CharacterMgr::Instance()->SetGameOver(false);
	CharacterMgr::Instance()->SetRunBoss(false);

	SetTimer(hWnd, 0, 2000, NULL);
	SetTimer(hWnd, 1, 75, NULL);
	SetTimer(hWnd, 2, 4000, NULL);
}

void WinMgr::ShowBossMonster()
{
	AIMgr::Instance()->SetShowMajinBuu(true);
	CharacterMgr::Instance()->ShowBossMonster();
}