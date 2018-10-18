// FileTamDoc.h : interface of the CFileTamDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILETAMDOC_H__68AC933E_0FE7_11D5_8745_0050DA8BB346__INCLUDED_)
#define AFX_FILETAMDOC_H__68AC933E_0FE7_11D5_8745_0050DA8BB346__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CFileTamDoc : public CDocument
{
protected: // create from serialization only
	CFileTamDoc();
	DECLARE_DYNCREATE(CFileTamDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileTamDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFileTamDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFileTamDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILETAMDOC_H__68AC933E_0FE7_11D5_8745_0050DA8BB346__INCLUDED_)
