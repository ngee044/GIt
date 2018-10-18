// DasepoDoc.h : interface of the CDasepoDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DASEPODOC_H__627FE16B_9EC7_44E4_AE16_D42F604A343C__INCLUDED_)
#define AFX_DASEPODOC_H__627FE16B_9EC7_44E4_AE16_D42F604A343C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDasepoDoc : public CDocument
{
protected: // create from serialization only
	CDasepoDoc();
	DECLARE_DYNCREATE(CDasepoDoc)

// Attributes
public:

// Operations
public:
	CDPConf m_dp;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDasepoDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDasepoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDasepoDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DASEPODOC_H__627FE16B_9EC7_44E4_AE16_D42F604A343C__INCLUDED_)
