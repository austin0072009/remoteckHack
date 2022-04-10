#if !defined(AFX_SETTINGDLG_H__8F21CBB2_F9C5_4382_8CDF_598D3360D927__INCLUDED_)
#define AFX_SETTINGDLG_H__8F21CBB2_F9C5_4382_8CDF_598D3360D927__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SettingDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSettingDlg dialog

class CSettingDlg : public CDialog
{
// Construction
public:
	CSettingDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSettingDlg)
	enum { IDD = IDD_DIALOG_SETTING };
	BOOL	m_disble_poptips;
	UINT	m_listen_port;
	BOOL	m_warning_tone;
	UINT	m_edit_heartbeat_time;
	BOOL	m_bisDisableHostlist;
	//}}AFX_DATA

	CString Base64Encode(LPCTSTR lpszSrc);   //加密函数
	CString Base64Decode(LPCTSTR lpszSrc);  //解密函数
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSettingDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSettingDlg)
	virtual void OnOK();
	afx_msg void OnDisableHostlist();
	afx_msg void OnCustomSkin();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETTINGDLG_H__8F21CBB2_F9C5_4382_8CDF_598D3360D927__INCLUDED_)
