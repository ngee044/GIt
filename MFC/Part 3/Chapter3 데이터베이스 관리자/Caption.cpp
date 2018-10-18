// Caption.cpp : implementation file
//

#include "stdafx.h"
#include "datamanager.h"
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
	m_strCaption = _T("");
	m_strCaptionTip = _T("");
}

CCaption::~CCaption()
{
}


BEGIN_MESSAGE_MAP(CCaption, CWnd)
	//{{AFX_MSG_MAP(CCaption)
	ON_WM_PAINT()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCaption message handlers

//------------------------------------------------------------------//
// Function		: OnCreate
// Parameter	: NlpCreateStructone
// Return		: int
// Note			: 팁컨트롤과 폰트 생성
//------------------------------------------------------------------//
int CCaption::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (lpCreateStruct->style & TCS_TOOLTIPS)
	{
	    m_ToolTip.Create(this);
	    m_ToolTip.Activate(TRUE);
	    m_ToolTip.AddTool(this, _T("ToolTip"));
        m_ToolTip.SendMessage(TTM_SETMAXTIPWIDTH, 0, SHRT_MAX); // Allow multiline tooltips
    }
	
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

	dc.FillSolidRect(rcClient, RGB(192, 198, 216));
	dc.Draw3dRect(&rcClient, RGB(213, 216, 230), RGB(138, 148, 185));

	// Caption title 설정
	CRect rcTitle;

	rcTitle.left = rcClient.left+10;
	rcTitle.top = rcClient.top;
	rcTitle.right = rcClient.right-10;
	rcTitle.bottom = rcClient.bottom;

	CFont* pOldFont = dc.SelectObject(&m_Font);

	dc.SetTextColor(GetSysColor(COLOR_WINDOWTEXT));	
	dc.SetBkMode(TRANSPARENT);
	dc.DrawText(m_strCaption, rcTitle, DT_SINGLELINE | DT_VCENTER);
	dc.SelectObject(pOldFont);
}


//------------------------------------------------------------------//
// Function		: PreTranslateMessage
// Parameter	: pMsg
// Return		: BOOL
// Note			: 팁 처리
//------------------------------------------------------------------//
BOOL CCaption::PreTranslateMessage(MSG* pMsg) 
{
	if( m_ToolTip.m_hWnd )
	{
		if( pMsg->message == WM_MOUSEMOVE )
		{
			m_ToolTip.UpdateTipText(m_strCaptionTip, this);
			m_ToolTip.RelayEvent(pMsg);
		}
		else
			::SendMessage(m_ToolTip.m_hWnd, TTM_POP, 0, 0L);
	}
	
	return CWnd::PreTranslateMessage(pMsg);
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
	lf.lfWeight = FW_BOLD;	
	::lstrcpy (lf.lfFaceName, _T("Verdana"));
	
	m_Font.CreatePointFontIndirect(&lf);
}


//------------------------------------------------------------------//
// Function		: SetCaptionText
// Parameter	: strCaption : Caption 내용
// Return		: None
// Note			: 캡션바에 내용을 나타낸다.
//------------------------------------------------------------------//
void CCaption::SetCaptionText(const CString& strCaption)
{
	m_strCaption = m_strCaptionTip = strCaption; // Default	 
}


//------------------------------------------------------------------//
// Function		: SetCaptionTip
// Parameter	: strCaption : Caption 내용
// Return		: None
// Note			: 캡션바에 팁을 보여준다.
//------------------------------------------------------------------//
void CCaption::SetCaptionTip(const CString& strCaptionTip)
{
	m_strCaptionTip = strCaptionTip;
}
