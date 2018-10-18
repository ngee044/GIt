// ToolBarDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Exploer.h"
#include "ToolBarDlg.h"
#include "MainFrm.h"
#include "DirView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CToolBarDlg

CToolBarDlg::CToolBarDlg()
{
	btn_status=false;
	//btn_Img.Create(IDB_OK,16,ILC_COLOR8,RGB(128,128,128));
	CBitmap		bitmap;
	bitmap.LoadBitmap(IDB_OK);
	btn_Img.Create(20,17,ILC_COLOR8,1,1);
	btn_Img.Add(&bitmap,RGB(255,0,255));
}

CToolBarDlg::~CToolBarDlg()
{
}


BEGIN_MESSAGE_MAP(CToolBarDlg, CDialogBar)
	//{{AFX_MSG_MAP(CToolBarDlg)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CToolBarDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	CPen pn(PS_SOLID, 1, GetSysColor(COLOR_3DSHADOW));
	CPen * op = dc.SelectObject(&pn);
	CRect rect;
	GetClientRect(rect);
	dc.MoveTo(0,0);
	dc.LineTo(rect.right,0);
	dc.SelectObject(op);

	CPen pn2(PS_SOLID, 1, GetSysColor(COLOR_3DHILIGHT));
	CPen * op2 = dc.SelectObject(&pn2);
	dc.MoveTo(0,1);
	dc.LineTo(rect.right,1);
	dc.SelectObject(op2);

	// TODO: Add your message handler code here
	ButtonIcon(0);
	// Do not call CDialogBar::OnPaint() for painting messages
}

void CToolBarDlg::ButtonDraw()
{
	CClientDC dc(this);
	CRect rect;

	CComboBox* pCombo = (CComboBox*)GetDlgItem(IDC_COMBO);
	pCombo->GetClientRect(rect);

	rect.top = rect.bottom/4;
	rect.bottom += rect.top;
	rect.left = rect.right+rect.top;
	rect.right= rect.left+(rect.bottom-rect.top)+(rect.bottom/4);
	if(btn_status==false)
	{
		dc.Draw3dRect(rect,GetSysColor(COLOR_3DHILIGHT),GetSysColor(COLOR_3DSHADOW));
		ButtonIcon(1);
	}
	else
	{
		dc.Draw3dRect(rect,GetSysColor(COLOR_3DSHADOW),GetSysColor(COLOR_3DHILIGHT));
		ButtonIcon(0);
	}
}

void CToolBarDlg::ButtonErase()
{
	CClientDC dc(this);
	CRect rect;

	CComboBox* pCombo = (CComboBox*)GetDlgItem(IDC_COMBO);
	pCombo->GetClientRect(rect);

	rect.top = rect.bottom/4;
	rect.bottom += rect.top;
	rect.left = rect.right+rect.top;
	rect.right= rect.left+rect.bottom-rect.top+(rect.bottom/4);
	dc.Draw3dRect(rect,GetSysColor(COLOR_3DFACE),GetSysColor(COLOR_3DFACE));
	ButtonIcon(0);
}

void CToolBarDlg::ButtonIcon(int index)
{
	CDC pDC;
	CClientDC dc(this);
	CRect rect,clientRc;
	pDC.CreateCompatibleDC(&dc);

	CComboBox* pCombo = (CComboBox*)GetDlgItem(IDC_COMBO);
	pCombo->GetClientRect(&rect);
	GetClientRect(clientRc);

	CBitmap bmp;
	bmp.CreateCompatibleBitmap(&dc, clientRc.Width(), clientRc.Height());
	CBitmap * originbmp = pDC.SelectObject(&bmp);

	rect.top = rect.bottom/4;
	rect.bottom += rect.top;
	rect.left = rect.right+rect.top;
	rect.right= rect.left+rect.bottom-rect.top+(rect.bottom/4);

	CPoint pt;
	pt.x=rect.left+((rect.Width()-20)/2);
	pt.y=rect.top+((rect.Height()-17)/2);

	btn_Img.Draw(&pDC,index,pt,ILD_NORMAL);

	dc.BitBlt(pt.x,pt.y, 20,17, &pDC, pt.x,pt.y, SRCCOPY);
	
	Button[0]=rect;

	pDC.SelectObject(originbmp);
	ReleaseDC(&pDC);
}


void CToolBarDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	int idx; 
	HitTestEx(point, idx);


	if(btn_status==true && idx>=0 && idx<BTN_COUNT)
		return;

	if(btn_status==false && (idx<0 || idx>=BTN_COUNT))
		return;

	if(idx>=0 && idx<BTN_COUNT)
	{
		if (::GetCapture() == NULL)
			SetCapture();
		ButtonDraw();
		btn_status=true;
	}
	else
	{
		ReleaseCapture();
		ButtonErase();
		btn_status=false;
	}

	CDialogBar::OnMouseMove(nFlags, point);
}

void CToolBarDlg::HitTestEx(const CPoint &pt,int &idx)
{
	CRect rc;
	for (int t = 0; t < BTN_COUNT; t++)
	{
		rc=Button[t];
		if (rc.PtInRect(pt)) 
			idx=t;
	}
}

void CToolBarDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	int idx; 
	HitTestEx(point, idx);

	if(idx>=0 && idx<BTN_COUNT)
	{
		btn_status=true;
		SetTimer(1,50,NULL);
		ButtonDraw();
	}		
	CDialogBar::OnLButtonDown(nFlags, point);
}

void CToolBarDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	int idx; 
	HitTestEx(point, idx);

	if(idx>=0 && idx<BTN_COUNT)
	{
		btn_status=false;
		ButtonDraw();
		switch(idx)
		{
			case 0:
				UpMove();
				break;
			default:
				break;
		}
	}
	CDialogBar::OnLButtonUp(nFlags, point);
}

void CToolBarDlg::UpMove()
{
	CWnd* LeftWnd=((CMainFrame*)(AfxGetApp()->m_pMainWnd))->wndSplitter.GetPane(0,0);
	LeftWnd->SendMessage(WM_UPMOVETREE,0,0);
}

void CToolBarDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	CPoint pt(GetMessagePos());

	ScreenToClient(&pt);

	CRect rc;
	GetClientRect(rc);

	if (!(rc.PtInRect(pt)))
	{
		ButtonErase();
		btn_status=false;
		ReleaseCapture();
		KillTimer(1);
	}
	CDialogBar::OnTimer(nIDEvent);
}
