#if !defined(AFX_DIALOGBAR_H__105BC9BC_2144_44D1_A00D_C4DAD3A849AA__INCLUDED_)
#define AFX_DIALOGBAR_H__105BC9BC_2144_44D1_A00D_C4DAD3A849AA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialogbar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogbar dialog
#include "HtmlCtrl.h"

class CMyHtmlCtrl : public CHtmlCtrl 
{
};


class CDialogbar : public CDialogBar
{
// Construction
public:
	CDialogbar(CWnd* pParent = NULL,ClientContext *pContext = NULL);   // standard constructor
	
// Dialog Data
	//{{AFX_DATA(CDialogbar)
//	enum { IDD = IDD_DIALOGBAR };
	CListCtrl	m_HostList;
	CString m_Staic;
	//}}AFX_DATA

public:
	CXTPTabControl m_wndTabControl;
	ClientContext* m_pContext;
	CString m_IPAddress;
	CString m_x,m_y;
	CString htmlmap();
	CMyHtmlCtrl m_page;
	CImageList     m_ImgList;
	CString IPAddress;
public:
	void ShowSysinfoList(ClientContext* pContext);
	void ShowSysinfoListDel();
	void DeleteList();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogbar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	afx_msg LONG OnInitDialog(UINT, LONG);

	// Generated message map functions
	//{{AFX_MSG(CDialogbar)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGBAR_H__105BC9BC_2144_44D1_A00D_C4DAD3A849AA__INCLUDED_)
