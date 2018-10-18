// StatusView.cpp : implementation file
//

#include "stdafx.h"
#include "myftp.h"
#include "StatusView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStatusView

IMPLEMENT_DYNCREATE(CStatusView, CListView)

CStatusView::CStatusView()
{
}

CStatusView::~CStatusView()
{
}


BEGIN_MESSAGE_MAP(CStatusView, CListView)
	//{{AFX_MSG_MAP(CStatusView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStatusView drawing

void CStatusView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CStatusView diagnostics

#ifdef _DEBUG
void CStatusView::AssertValid() const
{
	CListView::AssertValid();
}

void CStatusView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CStatusView message handlers

BOOL CStatusView::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	cs.style|=LVS_REPORT|
		LVS_SINGLESEL|
		LVS_SHOWSELALWAYS|
		LVS_EDITLABELS;
	return CListView::PreCreateWindow(cs);
}

void CStatusView::OnInitialUpdate() 
{
	CListView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	GetListCtrl().InsertColumn (0, "번호", LVCFMT_LEFT, 50);
	GetListCtrl().InsertColumn (1, "시간", LVCFMT_LEFT, 160);
	GetListCtrl().InsertColumn (2, "메세지", LVCFMT_LEFT, 400);

	// 리스트 컨트롤에 이미지 연결
	m_imgList.Create(IDB_STSTUS, 16, 7, RGB(255, 255, 255));
	
	GetListCtrl().SetImageList(&m_imgList, LVSIL_SMALL);
	
	SetStatus("MyFTP에 오신걸 환영합니다.", IDB_START);
	UpdateData(FALSE);
}

CString CStatusView::GetStringTime()
{
	// 현재 시간을 얻어 리턴
	CTime cTim;
	CString strTime;
	cTim = cTim.GetCurrentTime();
	strTime.Format("%02d-%02d-%02d  %02d:%02d:%02d", cTim.GetYear(), cTim.GetMonth(), cTim.GetDay(), cTim.GetHour(), cTim.GetMinute(), cTim.GetSecond());

	return strTime;
}
int CStatusView::AddItemList(LPCTSTR strItem, int nItem, int nSubItem, UINT nState, int nImageIndex, long nParam)
{
	// 상태창에 아이템 입력
	LVITEM lvItem;
	lvItem.mask = LVIF_TEXT;
	lvItem.iItem = nItem;
	lvItem.iSubItem = nSubItem;
	lvItem.pszText = (LPTSTR)strItem;

	if (nState != -1)
	{
		lvItem.mask |= LVIF_STATE;
		lvItem.state = nState;
	}
	if (nImageIndex != -1)
	{
		lvItem.mask |= LVIF_IMAGE;
		lvItem.iImage = nImageIndex;
	}
	if (nParam != -1)
	{
		lvItem.mask |= LVIF_PARAM;
		lvItem.lParam = nParam;
	}
	if (nSubItem == 0)
		return GetListCtrl().InsertItem(&lvItem);
	else
		return GetListCtrl().SetItem(&lvItem);
}

void CStatusView::SetStatus(CString strStatus, int nImage)
{
	// 리스트뷰에 출력
	
	CString strTime, strNum;
	strTime = GetStringTime(); //현재시간 얻기

	int i = GetListCtrl().GetItemCount();
	strNum.Format("%d", i);

	AddItemList(strNum, i, 0, -1, nImage, -1);
	AddItemList(strTime, i, 1);
	AddItemList(strStatus, i, 2);
}
