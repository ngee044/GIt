// DasepoView.cpp : implementation of the CDasepoView class
//

#include "stdafx.h"
#include "Dasepo.h"

#include "DasepoDoc.h"
#include "DasepoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDasepoView

IMPLEMENT_DYNCREATE(CDasepoView, CHtmlView)

BEGIN_MESSAGE_MAP(CDasepoView, CHtmlView)
	//{{AFX_MSG_MAP(CDasepoView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDasepoView construction/destruction

CDasepoView::CDasepoView()
{
	// TODO: add construction code here

}

CDasepoView::~CDasepoView()
{
}

BOOL CDasepoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CHtmlView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDasepoView drawing

void CDasepoView::OnDraw(CDC* pDC)
{
	CDasepoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

void CDasepoView::OnInitialUpdate()
{
	CHtmlView::OnInitialUpdate();

	// TODO: This code navigates to a popular spot on the web.
	//  change the code to go where you'd like.
	ViewMain();
}

/////////////////////////////////////////////////////////////////////////////
// CDasepoView diagnostics

#ifdef _DEBUG
void CDasepoView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CDasepoView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}


CDasepoDoc* CDasepoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDasepoDoc)));
	return (CDasepoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDasepoView message handlers

void CDasepoView::ViewMain()
{
	// 최초 페이지 보여주기
	Navigate2(GetDocument()->m_dp.GetMainPage(),NULL,NULL);
}

void CDasepoView::ViewPage(CString strTitle)
{
	// 제목에 따른 만화 보여주기
	Navigate2(GetDocument()->m_dp.GetPage(strTitle),NULL,NULL);
}

