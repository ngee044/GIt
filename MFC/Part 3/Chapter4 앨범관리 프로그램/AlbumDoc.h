// AlbumDoc.h : interface of the CAlbumDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ALBUMDOC_H__85300154_B3D2_46C7_BF9A_25E76D7230D5__INCLUDED_)
#define AFX_ALBUMDOC_H__85300154_B3D2_46C7_BF9A_25E76D7230D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CAlbumDoc : public CDocument
{
protected: // create from serialization only
	CAlbumDoc();
	DECLARE_DYNCREATE(CAlbumDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAlbumDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAlbumDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CAlbumDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ALBUMDOC_H__85300154_B3D2_46C7_BF9A_25E76D7230D5__INCLUDED_)
