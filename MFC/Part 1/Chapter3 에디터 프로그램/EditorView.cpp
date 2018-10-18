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
	pDoc = GetDocument(); // Document ������ ���
	
	TEXTMETRIC txtKey;

	CClientDC dc(this); //dc ���

	dc.GetTextMetrics(&txtKey); //�� dc(View)�� ��Ʈ���� ���

	// ĳ�� ����(���� ��� ������ ����, ������ ����)
	CreateSolidCaret(txtKey.tmAveCharWidth/2, txtKey.tmHeight);

	CPoint pntTmp(0, 0);
	
	// ĳ���� ���� ��ġ ����(0, 0)
	SetCaretPos(pntTmp);
	//ĳ�� ���̱�
	ShowCaret();
	return 0;
}

void CEditorView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	CClientDC dc(this);
	
	TEXTMETRIC txtKey;

	dc.GetTextMetrics(&txtKey);
	
	
	// ���� �Է��ϴ� ���� ĳ���� �����
	HideCaret();

	if(nChar == VK_BACK) //�齺���̽� ���
	{
		if(!pDoc->strDB[pDoc->pline].IsEmpty()) //���ڿ��� ������� �������
		{
			// ���� ���ڿ��� �� ���� �߶󳽴�.
			pDoc->strDB[pDoc->pline] = pDoc->strDB[pDoc->pline].Left(pDoc->strDB[pDoc->pline].GetLength() - 1);
			
			// ���� �߶��� �ٽ� ���
			dc.TextOut(0, pntCur.y, pDoc->strDB[pDoc->pline] + "    ");
		}
	}
	else if(nChar == VK_RETURN) // ������ ���
	{
		// ���� �ϳ� ����
		pDoc->pline++;
	}
	else if(nChar == VK_UP) //�� ���
	{
		// ���� �ϳ� ����
		pDoc->pline--;
	}
	else // �Ϲ� ������ ���
	{
		// �Էµ� ���ڸ� strDB�� �߰�
		pDoc->strDB[pDoc->pline] += nChar;
		// ȭ�鿡 ���
		dc.TextOut(0, (int)pDoc->pline * txtKey.tmHeight, pDoc->strDB[pDoc->pline]);
	}

	// ���� ���ڿ��� ������ ��ġ ���
	CSize strSize;
	strSize = dc.GetTextExtent(pDoc->strDB[pDoc->pline]);
	
	// ĳ����ġ ���
	pntCur.x = strSize.cx;
	pntCur.y = int(pDoc->pline) * txtKey.tmHeight;
	// ĳ�� ��ġ ����
	SetCaretPos(pntCur);
	// ĳ�� �����ֱ�
	ShowCaret();
	
	CView::OnChar(nChar, nRepCnt, nFlags);
}

void CEditorView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
	if(pDoc->pline == 0) // �� ������ ���
		return;
	if(nChar == VK_UP) //�� ���
		OnChar(nChar, nRepCnt, nFlags); 
	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CEditorView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	TEXTMETRIC txtKey;

	dc.GetTextMetrics(&txtKey); //�� dc(View)�� ��Ʈ���� ���

	for(int i=0 ; i<=pDoc->pline ; i++)
	{
		dc.TextOut(0, (int)i * txtKey.tmHeight, pDoc->strDB[i]);
	}

	ShowCaret();
	// Do not call CView::OnPaint() for painting messages
}
