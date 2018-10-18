// ListCtrlEx.cpp : implementation file
//

#include "stdafx.h"
#include "datamanager.h"
#include "ListCtrlEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListCtrlEx

CListCtrlEx::CListCtrlEx()
{
}

CListCtrlEx::~CListCtrlEx()
{
}


BEGIN_MESSAGE_MAP(CListCtrlEx, CListCtrl)
	//{{AFX_MSG_MAP(CListCtrlEx)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnCustomDraw)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListCtrlEx message handlers

void CListCtrlEx::OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLVCUSTOMDRAW lplvcd = (LPNMLVCUSTOMDRAW)pNMHDR;

	NMLVCUSTOMDRAW* pLVCD = (NMLVCUSTOMDRAW*)pNMHDR;

	switch (pLVCD->nmcd.dwDrawStage)
	{
	case CDDS_PREPAINT:
		// �̷��� �ؾ� ��μ� custom draw �����ϰ� CDDS_ITEMPREPAINT�� �´�.
		*pResult = CDRF_NOTIFYITEMDRAW;
		break;

	case CDDS_ITEMPREPAINT:
		// �����۸��� �׸���
		*pResult = CDRF_NOTIFYSUBITEMDRAW;
		break;

	case CDDS_ITEMPOSTPAINT :
		{
			
		}
		break;

	case CDDS_ITEMPREPAINT | CDDS_SUBITEM:
		{
			// �� �����ۿ� ���� �׸���.
			if( pLVCD->iSubItem == 0 )	// ù��° �÷�
			{
				CDC* pDC = CDC::FromHandle(pLVCD->nmcd.hdc);
			
				CRect rcItem;
				GetItemRect(pLVCD->nmcd.dwItemSpec, &rcItem, LVIR_BOUNDS);

				CString strText = GetItemText(pLVCD->nmcd.dwItemSpec, 0);
				
				// Bold ��Ʈ����
				LOGFONT lf;
				::ZeroMemory(&lf, sizeof(lf));
				lf.lfHeight = 90;
				lf.lfWeight = FW_BOLD;
				lf.lfItalic = FALSE;
				::lstrcpy(lf.lfFaceName, _T("����ü"));

				CFont font;
				font.CreatePointFontIndirect(&lf);
				pDC->SelectObject(&font);
				
				rcItem.InflateRect(-6, -2, 0, 4);				
				
				pDC->SetBkMode(TRANSPARENT);
				pDC->SetTextColor(RGB(65, 74, 109));
				pDC->DrawText(strText, rcItem, DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS);				
			}
			else if( pLVCD->iSubItem == 1 )	// �ι�° �÷�
			{
				CDC* pDC = CDC::FromHandle(pLVCD->nmcd.hdc);
				
				CRect rcItem;
				GetSubItemRect(pLVCD->nmcd.dwItemSpec, 1, LVIR_BOUNDS, rcItem);

				CString strText = GetItemText(pLVCD->nmcd.dwItemSpec, 1);				
				
				// Normal ��Ʈ����
				LOGFONT lf;
				::ZeroMemory(&lf, sizeof (lf));
				lf.lfHeight = 90;
				lf.lfWeight = FW_NORMAL;
				lf.lfItalic = FALSE;
				::lstrcpy(lf.lfFaceName, _T("����ü"));

				CFont font;
				font.CreatePointFontIndirect(&lf);
				pDC->SelectObject(&font);

				rcItem.InflateRect(-6, -3, 0, 2);
				
				pDC->SetBkMode(TRANSPARENT);
				pDC->SetTextColor(RGB(65, 74, 109));
				pDC->DrawText(strText, rcItem, DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS);
			}
		}
		*pResult = CDRF_SKIPDEFAULT;
		break;

	default:
		*pResult = CDRF_DODEFAULT;
		break;
	}
}