// Caption.cpp : implementation file
//

#include "stdafx.h"
#include "tipmanager.h"
#include "Caption.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCaption

CCaption::CCaption()
{
	m_strCaptionText = _T("");
	
	m_clrBack = GetSysColor(COLOR_BTNFACE);//RGB(192, 198, 216);
	m_clrTopLeft = GetSysColor(COLOR_BTNHILIGHT);//RGB(213, 216, 230);
	m_clrBottomRight = GetSysColor(COLOR_BTNSHADOW);//RGB(138, 148, 185);

	m_clrFont = GetSysColor(COLOR_WINDOWTEXT);
}

CCaption::~CCaption()
{
	m_Font.DeleteObject();
}


BEGIN_MESSAGE_MAP(CCaption, CStatic)
	//{{AFX_MSG_MAP(CCaption)
	ON_WM_PAINT()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCaption message handlers

int CCaption::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CStatic::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CreateCaptionFont();	// Font Create

	return 0;
}


//------------------------------------------------------------------//
// Function		: OnPaint
// Parameter	: None
// Return		: None
// Note			: 캡션바를 그린다.
//------------------------------------------------------------------//
void CCaption::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect rcClient;
	GetClientRect(&rcClient);

	dc.FillSolidRect(rcClient, m_clrBack);
	dc.Draw3dRect(&rcClient, m_clrTopLeft, m_clrBottomRight);

	// Caption title 설정
	CRect rcTitle;

	rcTitle.left = rcClient.left+10;
	rcTitle.top = rcClient.top;
	rcTitle.right = rcClient.right-10;
	rcTitle.bottom = rcClient.bottom;

	CFont* pOldFont = dc.SelectObject(&m_Font);

	dc.SetTextColor(m_clrFont);
	dc.SetBkMode(TRANSPARENT);
	dc.DrawText(m_strCaptionText, rcTitle, DT_SINGLELINE | DT_VCENTER);
	dc.SelectObject(pOldFont);
	
	// Do not call CStatic::OnPaint() for painting messages
}


/////////////////////////////////////////////////////////////////////////////
// User Defines...

//------------------------------------------------------------------//
// Function		: CreateCaptionFont
// Parameter	: None
// Return		: None
// Note			: 폰트 생성
//------------------------------------------------------------------//
void CCaption::CreateCaptionFont()
{
	// Font 생성
	LOGFONT lf;
	::ZeroMemory (&lf, sizeof (lf));
	lf.lfHeight = 90;
	lf.lfWeight = FW_NORMAL;	
	::lstrcpy (lf.lfFaceName, _T("Verdana"));
	
	m_Font.CreatePointFontIndirect(&lf);
}


//------------------------------------------------------------------//
// Function		: SetBackColor
// Parameter	: clrBack		- Back Color
//				  clrTopLeft	- Top Left Color
//				  clrBottomRight- Bottom Right Color
// Return		: None
// Note			: 캡션바의 배경 색 지정.
//------------------------------------------------------------------//
void CCaption::SetCaptionColor(COLORREF clrBack, COLORREF clrTopLeft, COLORREF clrBottomRight)
{
	m_clrBack = clrBack;
	m_clrTopLeft = clrTopLeft;
	m_clrBottomRight = clrBottomRight;

	Invalidate();
}


void CCaption::SetFontColor(COLORREF clrFont)
{
	m_clrFont = clrFont;

	Invalidate();
}


//------------------------------------------------------------------//
// Function		: SetCaptionText
// Parameter	: strCaption : Caption 내용
// Return		: None
// Note			: 캡션바에 내용을 나타낸다.
//------------------------------------------------------------------//
void CCaption::SetCaptionText(const CString& strCaption)
{
	m_strCaptionText = strCaption;	
	Invalidate();
}
