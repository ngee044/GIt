// InternetTamDoc.h : interface of the CInternetTamDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_INTERNETTAMDOC_H__8E8F234B_5F52_11D5_874E_0050DA8BB346__INCLUDED_)
#define AFX_INTERNETTAMDOC_H__8E8F234B_5F52_11D5_874E_0050DA8BB346__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CInternetTamDoc : public CDocument
{
protected: // create from serialization only
	CInternetTamDoc();
	DECLARE_DYNCREATE(CInternetTamDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInternetTamDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CInternetTamDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CInternetTamDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INTERNETTAMDOC_H__8E8F234B_5F52_11D5_874E_0050DA8BB346__INCLUDED_)
