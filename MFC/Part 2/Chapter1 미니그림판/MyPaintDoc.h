// MyPaintDoc.h : interface of the CMyPaintDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYPAINTDOC_H__41C0D88B_4C36_11D5_9E3E_901253C10000__INCLUDED_)
#define AFX_MYPAINTDOC_H__41C0D88B_4C36_11D5_9E3E_901253C10000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMyPaintDoc : public CDocument
{
protected: // create from serialization only
	CMyPaintDoc();
	DECLARE_DYNCREATE(CMyPaintDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyPaintDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyPaintDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyPaintDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYPAINTDOC_H__41C0D88B_4C36_11D5_9E3E_901253C10000__INCLUDED_)
