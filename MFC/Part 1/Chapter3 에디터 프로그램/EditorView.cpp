// EditorView.cpp : implementation of the CEditorView class
//

#include "stdafx.h"
#include "Editor.h"

#include "EditorDoc.h"
#include "EditorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditorView

IMPLEMENT_DYNCREATE(CEditorView, CView)

BEGIN_MESSAGE_MAP(CEditorView, CView)
	//{{AFX_MSG_MAP(CEditorView)
	ON_WM_CREATE()
	ON_WM_CHAR()
	ON_WM_KEYUP()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditorView construction/destruction

CEditorView::CEditorView()
{
	// TODO: add construction code here
	pntCur.x = 0;
	pntCur.y = 0;
}

CEditorView::~CEditorView()
{
}

BOOL CEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEditorView drawing

void CEditorView::OnDraw(CDC* pDC)
{
	CEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here

}

/////////////////////////////////////////////////////////////////////////////
// CEditorView printing

BOOL CEditorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CEditorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CEditorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CEditorView diagnostics

#ifdef _DEBUG
void CEditorView::AssertValid() const
{
	CView::AssertValid();
}

void CEditorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEditorDoc* CEditorView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEditorDoc)));
	return (CEditorDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEditorView message handlers


int CEditorView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	pDoc = GetDocument(); // Document 포인터 얻기
	
	TEXTMETRIC txtKey;

	CClientDC dc(this); //dc 얻기

	dc.GetTextMetrics(&txtKey); //현 dc(View)의 폰트정보 얻기

	// 캐럿 생성(문자 평균 넓이의 절반, 문자의 높이)
	CreateSolidCaret(txtKey.tmAveCharWidth/2, txtKey.tmHeight);

	CPoint pntTmp(0, 0);
	
	// 캐럿의 최초 위치 지정(0, 0)
	SetCaretPos(pntTmp);
	//캐럿 보이기
	ShowCaret();
	return 0;
}

void CEditorView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	CClientDC dc(this);
	
	TEXTMETRIC txtKey;

	dc.GetTextMetrics(&txtKey);
	
	
	// 문자 입력하는 동안 캐럿을 숨긴다
	HideCaret();

	if(nChar == VK_BACK) //백스페이스 경우
	{
		if(!pDoc->strDB[pDoc->pline].IsEmpty()) //문자열이 비어있지 않은경우
		{
			// 원래 문자열의 맨 끝을 잘라낸다.
			pDoc->strDB[pDoc->pline] = pDoc->strDB[pDoc->pline].Left(pDoc->strDB[pDoc->pline].GetLength() - 1);
			
			// 끝을 잘라낸후 다시 출력
			dc.TextOut(0, pntCur.y, pDoc->strDB[pDoc->pline] + "    ");
		}
	}
	else if(nChar == VK_RETURN) // 엔터의 경우
	{
		// 줄을 하나 증가
		pDoc->pline++;
	}
	else if(nChar == VK_UP) //↑ 경우
	{
		// 줄을 하나 감소
		pDoc->pline--;
	}
	else // 일반 문자의 경우
	{
		// 입력된 문자를 strDB에 추가
		pDoc->strDB[pDoc->pline] += nChar;
		// 화면에 출력
		dc.TextOut(0, (int)pDoc->pline * txtKey.tmHeight, pDoc->strDB[pDoc->pline]);
	}

	// 현재 문자열이 끝나는 위치 계산
	CSize strSize;
	strSize = dc.GetTextExtent(pDoc->strDB[pDoc->pline]);
	
	// 캐럿위치 계산
	pntCur.x = strSize.cx;
	pntCur.y = int(pDoc->pline) * txtKey.tmHeight;
	// 캐럿 위치 지정
	SetCaretPos(pntCur);
	// 캐럿 보여주기
	ShowCaret();
	
	CView::OnChar(nChar, nRepCnt, nFlags);
}

void CEditorView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
	if(pDoc->pline == 0) // 맨 윗줄일 경우
		return;
	if(nChar == VK_UP) //↑ 경우
		OnChar(nChar, nRepCnt, nFlags); 
	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CEditorView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	TEXTMETRIC txtKey;

	dc.GetTextMetrics(&txtKey); //현 dc(View)의 폰트정보 얻기

	for(int i=0 ; i<=pDoc->pline ; i++)
	{
		dc.TextOut(0, (int)i * txtKey.tmHeight, pDoc->strDB[i]);
	}

	ShowCaret();
	// Do not call CView::OnPaint() for painting messages
}
