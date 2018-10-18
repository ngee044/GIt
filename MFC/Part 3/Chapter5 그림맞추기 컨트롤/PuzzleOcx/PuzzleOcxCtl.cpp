// PuzzleOcxCtl.cpp : Implementation of the CPuzzleOcxCtrl ActiveX Control class.

#include "stdafx.h"
#include "PuzzleOcx.h"
#include "PuzzleOcxCtl.h"
#include "PuzzleOcxPpg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CPuzzleOcxCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CPuzzleOcxCtrl, COleControl)
	//{{AFX_MSG_MAP(CPuzzleOcxCtrl)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CPuzzleOcxCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CPuzzleOcxCtrl)
	DISP_PROPERTY_EX(CPuzzleOcxCtrl, "HintTime", GetHintTime, SetHintTime, VT_I4)
	DISP_FUNCTION(CPuzzleOcxCtrl, "GameStart", GameStart, VT_EMPTY, VTS_NONE)
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CPuzzleOcxCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CPuzzleOcxCtrl, COleControl)
	//{{AFX_EVENT_MAP(CPuzzleOcxCtrl)
	// NOTE - ClassWizard will add and remove event map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CPuzzleOcxCtrl, 1)
	PROPPAGEID(CPuzzleOcxPropPage::guid)
END_PROPPAGEIDS(CPuzzleOcxCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CPuzzleOcxCtrl, "PUZZLEOCX.PuzzleOcxCtrl.1",
	0x9abf36a6, 0x6015, 0x11d5, 0x87, 0x4e, 0, 0x50, 0xda, 0x8b, 0xb3, 0x46)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CPuzzleOcxCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DPuzzleOcx =
		{ 0x9abf36a4, 0x6015, 0x11d5, { 0x87, 0x4e, 0, 0x50, 0xda, 0x8b, 0xb3, 0x46 } };
const IID BASED_CODE IID_DPuzzleOcxEvents =
		{ 0x9abf36a5, 0x6015, 0x11d5, { 0x87, 0x4e, 0, 0x50, 0xda, 0x8b, 0xb3, 0x46 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwPuzzleOcxOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CPuzzleOcxCtrl, IDS_PUZZLEOCX, _dwPuzzleOcxOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CPuzzleOcxCtrl::CPuzzleOcxCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CPuzzleOcxCtrl

BOOL CPuzzleOcxCtrl::CPuzzleOcxCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegApartmentThreading to 0.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_PUZZLEOCX,
			IDB_PUZZLEOCX,
			afxRegApartmentThreading,
			_dwPuzzleOcxOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CPuzzleOcxCtrl::CPuzzleOcxCtrl - Constructor

CPuzzleOcxCtrl::CPuzzleOcxCtrl()
{
	InitializeIIDs(&IID_DPuzzleOcx, &IID_DPuzzleOcxEvents);

	// TODO: Initialize your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CPuzzleOcxCtrl::~CPuzzleOcxCtrl - Destructor

CPuzzleOcxCtrl::~CPuzzleOcxCtrl()
{
	// TODO: Cleanup your control's instance data here.
	delete dlgGame;
}


/////////////////////////////////////////////////////////////////////////////
// CPuzzleOcxCtrl::OnDraw - Drawing function

void CPuzzleOcxCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	// TODO: Replace the following code with your own drawing code.
	if(GetSafeHwnd())
	{
		pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));

		// 다이얼로그의 위치가 OCX의 중앙이 되도록 한다.
		CRect DlgRect;
		dlgGame->GetWindowRect(&DlgRect);
		
		int x = rcBounds.left;
		int y = rcBounds.top;
		if (DlgRect.Width() < rcBounds.Width())
		{
			int xMargin = (rcBounds.Width() - DlgRect.Width()) / 2;
			x = rcBounds.left+xMargin;
		}

		if (DlgRect.Height() < rcBounds.Height())
		{
			int yMargin = (rcBounds.Height() - DlgRect.Height()) /2;
			y = rcBounds.top+yMargin;
		}
		dlgGame->MoveWindow(x, y, DlgRect.Width(), DlgRect.Height(),TRUE);
	}
}


/////////////////////////////////////////////////////////////////////////////
// CPuzzleOcxCtrl::DoPropExchange - Persistence support

void CPuzzleOcxCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.

}


/////////////////////////////////////////////////////////////////////////////
// CPuzzleOcxCtrl::OnResetState - Reset control to default state

void CPuzzleOcxCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CPuzzleOcxCtrl::AboutBox - Display an "About" box to the user

void CPuzzleOcxCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_PUZZLEOCX);
	dlgAbout.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CPuzzleOcxCtrl message handlers

int CPuzzleOcxCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	dlgGame = new CDlgGame;
	dlgGame->Create(IDD_DIALOG_GAME, this);

	// 기본 시간은 5초
	m_dHintTime = 5000;
		
	return 0;
}

void CPuzzleOcxCtrl::GameStart() 
{
	// TODO: Add your dispatch handler code here
	dlgGame->DlgGameStart();
}


long CPuzzleOcxCtrl::GetHintTime() 
{
	// TODO: Add your property handler here

	return m_dHintTime;
}

void CPuzzleOcxCtrl::SetHintTime(long nNewValue) 
{
	// TODO: Add your property handler here
	m_dHintTime = nNewValue;
	dlgGame->m_dHintTime = m_dHintTime;
	SetModifiedFlag();
}
