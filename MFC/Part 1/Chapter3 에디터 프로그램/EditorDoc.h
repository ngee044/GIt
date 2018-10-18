// EditorDoc.h : interface of the CEditorDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EDITORDOC_H__46EDFDAB_027C_11D5_8745_0050DA8BB346__INCLUDED_)
#define AFX_EDITORDOC_H__46EDFDAB_027C_11D5_8745_0050DA8BB346__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CEditorDoc : public CDocument
{
protected: // create from serialization only
	CEditorDoc();
	DECLARE_DYNCREATE(CEditorDoc)

// Attributes
public:
	CString strDB[256]; //스트링을 저장할 배열(100줄)
	long pline; // 현재 줄을 표시
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditorDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEditorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEditorDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITORDOC_H__46EDFDAB_027C_11D5_8745_0050DA8BB346__INCLUDED_)
