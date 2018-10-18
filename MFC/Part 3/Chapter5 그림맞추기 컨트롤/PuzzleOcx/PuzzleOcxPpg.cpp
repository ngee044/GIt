// PuzzleOcxPpg.cpp : Implementation of the CPuzzleOcxPropPage property page class.

#include "stdafx.h"
#include "PuzzleOcx.h"
#include "PuzzleOcxPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CPuzzleOcxPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CPuzzleOcxPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CPuzzleOcxPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CPuzzleOcxPropPage, "PUZZLEOCX.PuzzleOcxPropPage.1",
	0x9abf36a7, 0x6015, 0x11d5, 0x87, 0x4e, 0, 0x50, 0xda, 0x8b, 0xb3, 0x46)


/////////////////////////////////////////////////////////////////////////////
// CPuzzleOcxPropPage::CPuzzleOcxPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CPuzzleOcxPropPage

BOOL CPuzzleOcxPropPage::CPuzzleOcxPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_PUZZLEOCX_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CPuzzleOcxPropPage::CPuzzleOcxPropPage - Constructor

CPuzzleOcxPropPage::CPuzzleOcxPropPage() :
	COlePropertyPage(IDD, IDS_PUZZLEOCX_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CPuzzleOcxPropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CPuzzleOcxPropPage::DoDataExchange - Moves data between page and properties

void CPuzzleOcxPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CPuzzleOcxPropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CPuzzleOcxPropPage message handlers
