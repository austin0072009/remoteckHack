// Client.h : main header file for the CLIENT application
//

#if !defined(AFX_CLIENT_H__3B33D150_C1FD_45C6_A2C7_C03DEC66EC1D__INCLUDED_)
#define AFX_CLIENT_H__3B33D150_C1FD_45C6_A2C7_C03DEC66EC1D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "IniFile.h"
#include "SplashScreenEx.h"
/////////////////////////////////////////////////////////////////////////////
// CClientApp:
// See Client.cpp for the implementation of this class
//

class CClientApp : public CWinApp
{
public:
	CClientApp();
	CSplashScreenEx *pSplash;
	CIniFile	m_IniFile;
	bool m_bIsQQwryExist;
	bool m_bIsDisablePopTips;
	bool m_bIsWarning_Tone;	
	HMODULE m_Hmodule;
	bool m_bisDisableHostlist;
	DWORD GetRand();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CClientApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENT_H__3B33D150_C1FD_45C6_A2C7_C03DEC66EC1D__INCLUDED_)
