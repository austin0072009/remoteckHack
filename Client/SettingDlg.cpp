// SettingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Client.h"
#include "SettingDlg.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CMainFrame	*g_pFrame;
extern CIOCPServer	*m_iocpServer;
/////////////////////////////////////////////////////////////////////////////
// CSettingDlg dialog


CSettingDlg::CSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSettingDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSettingDlg)
	m_disble_poptips = ((CClientApp *)AfxGetApp())->m_IniFile.GetInt("Settings", "PopTips", FALSE);
	m_listen_port = ((CClientApp *)AfxGetApp())->m_IniFile.GetInt("Settings", "ListenPort", 8001);
	m_warning_tone =  ((CClientApp *)AfxGetApp())->m_IniFile.GetInt("Settings", "Alarm", FALSE);
	m_edit_heartbeat_time = ((CClientApp *)AfxGetApp())->m_IniFile.GetInt("Settings", "HeartBeatTime", 0);
	m_bisDisableHostlist = ((CClientApp *)AfxGetApp())->m_IniFile.GetInt("Settings", "Hostlist",FALSE);
	//}}AFX_DATA_INIT
}


void CSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSettingDlg)
	DDX_Check(pDX, IDC_CHECK_DISABLE_POPTIPS, m_disble_poptips);
	DDX_Text(pDX, IDC_EDIT_LISTEN_PORT, m_listen_port);
	DDV_MinMaxUInt(pDX, m_listen_port, 1, 65535);
	DDX_Check(pDX, IDC_CHECK_WARNING_TONE, m_warning_tone);
	DDX_Text(pDX, IDC_EDIT_HEARTBEAT_TIME, m_edit_heartbeat_time);
	DDV_MinMaxUInt(pDX, m_edit_heartbeat_time, 0, 60);
	DDX_Check(pDX, IDC_DISABLE_HOSTLIST, m_bisDisableHostlist);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSettingDlg, CDialog)
	//{{AFX_MSG_MAP(CSettingDlg)
	ON_BN_CLICKED(IDC_CUSTOM_SKIN, OnCustomSkin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSettingDlg message handlers

CString CSettingDlg::Base64Encode(LPCTSTR lpszSrc)   //加密函数
{
 ASSERT(lpszSrc != NULL && AfxIsValidString(lpszSrc));
 const char BASE64_ENCODE_TABLE[64] = {
  65,  66,  67,  68,  69,  70,  71,  72,  // 00 - 07
   73,  74,  75,  76,  77,  78,  79,  80,  // 08 - 15
   81,  82,  83,  84,  85,  86,  87,  88,  // 16 - 23
   89,  90,  97,  98,  99, 100, 101, 102,  // 24 - 31
   103, 104, 105, 106, 107, 108, 109, 110,  // 32 - 39
   111, 112, 113, 114, 115, 116, 117, 118,  // 40 - 47
   119, 120, 121, 122,  48,  49,  50,  51,  // 48 - 55
   52,  53,  54,  55,  56,  57,  43,  47 };// 56 - 63

  unsigned int iTest;

  LPCTSTR pInBuffer=lpszSrc;

  int nSize = (int)_tcslen(lpszSrc);
  char* pOutBuffer=new char[nSize/3*4+5];
  ZeroMemory(pOutBuffer,nSize/3*4+5);

  for(UINT i=0;i<_tcslen(lpszSrc) / 3;i++)
  {
   iTest = (unsigned char) *pInBuffer++;
   iTest = iTest << 8;

   iTest = iTest | (unsigned char) *pInBuffer++;
   iTest = iTest << 8;

   iTest = iTest | (unsigned char) *pInBuffer++;

   //以4 byte倒序写入输出缓冲
   pOutBuffer[3] = BASE64_ENCODE_TABLE[iTest & 0x3F];
   iTest = iTest >> 6;
   pOutBuffer[2] = BASE64_ENCODE_TABLE[iTest & 0x3F];
   iTest = iTest >> 6;
   pOutBuffer[1] = BASE64_ENCODE_TABLE[iTest & 0x3F];
   iTest = iTest >> 6;
   pOutBuffer[0] = BASE64_ENCODE_TABLE[iTest];
   pOutBuffer+=4;
  }

  //设置尾部
  switch (_tcslen(lpszSrc) % 3)
  {
  case 0:
   break;
  case 1:
   iTest = (unsigned char) *pInBuffer;
   iTest = iTest << 4;
   pOutBuffer[1] = BASE64_ENCODE_TABLE[iTest & 0x3F];
   iTest = iTest >> 6;
   pOutBuffer[0] = BASE64_ENCODE_TABLE[iTest];
   pOutBuffer[2] = '='; //用'='也就是64码填充剩余部分
   pOutBuffer[3] = '=';
   break;
  case 2:
   iTest = (unsigned char) *pInBuffer++;
   iTest = iTest << 8;
   iTest = iTest | (unsigned char) *pInBuffer;
   iTest = iTest << 2;
   pOutBuffer[2] = BASE64_ENCODE_TABLE[iTest & 0x3F];
   iTest = iTest >> 6;
   pOutBuffer[1] = BASE64_ENCODE_TABLE[iTest & 0x3F];
   iTest = iTest >> 6;
   pOutBuffer[0] = BASE64_ENCODE_TABLE[iTest];
   pOutBuffer[3] = '='; // Fill remaining byte.
   break;
  }
  pOutBuffer-=nSize/3*4;
  CString strEncode=pOutBuffer;
  delete [] pOutBuffer;
  pOutBuffer=NULL;
  return strEncode;
}

CString CSettingDlg::Base64Decode(LPCTSTR lpszSrc)  //解密函数
{
 ASSERT(lpszSrc != NULL && AfxIsValidString(lpszSrc));
 const unsigned int BASE64_DECODE_TABLE[256] = {
  255, 255, 255, 255, 255, 255, 255, 255, //  00 -  07
   255, 255, 255, 255, 255, 255, 255, 255, //  08 -  15
   255, 255, 255, 255, 255, 255, 255, 255, //  16 -  23
   255, 255, 255, 255, 255, 255, 255, 255, //  24 -  31
   255, 255, 255, 255, 255, 255, 255, 255, //  32 -  39
   255, 255, 255,  62, 255, 255, 255,  63, //  40 -  47
   52,  53,  54,  55,  56,  57,  58,  59, //  48 -  55
   60,  61, 255, 255, 255, 255, 255, 255, //  56 -  63
   255,   0,   1,   2,   3,   4,   5,   6, //  64 -  71
   7,   8,   9,  10,  11,  12,  13,  14, //  72 -  79
   15,  16,  17,  18,  19,  20,  21,  22, //  80 -  87
   23,  24,  25, 255, 255, 255, 255, 255, //  88 -  95
   255,  26,  27,  28,  29,  30,  31,  32, //  96 - 103
   33,  34,  35,  36,  37,  38,  39,  40, // 104 - 111
   41,  42,  43,  44,  45,  46,  47,  48, // 112 - 119
   49,  50,  51, 255, 255, 255, 255, 255, // 120 - 127
   255, 255, 255, 255, 255, 255, 255, 255,
   255, 255, 255, 255, 255, 255, 255, 255,
   255, 255, 255, 255, 255, 255, 255, 255,
   255, 255, 255, 255, 255, 255, 255, 255,
   255, 255, 255, 255, 255, 255, 255, 255,
   255, 255, 255, 255, 255, 255, 255, 255,
   255, 255, 255, 255, 255, 255, 255, 255,
   255, 255, 255, 255, 255, 255, 255, 255,
   255, 255, 255, 255, 255, 255, 255, 255,
   255, 255, 255, 255, 255, 255, 255, 255,
   255, 255, 255, 255, 255, 255, 255, 255,
   255, 255, 255, 255, 255, 255, 255, 255,
   255, 255, 255, 255, 255, 255, 255, 255,
   255, 255, 255, 255, 255, 255, 255, 255,
   255, 255, 255, 255, 255, 255, 255, 255,
   255, 255, 255, 255, 255, 255, 255, 255 };


  const int nSrcCount=(int)_tcslen(lpszSrc);
  int nSize=nSrcCount/4*3;
  if(lpszSrc[nSrcCount-1]=='=')
   nSize--;
  if(lpszSrc[nSrcCount-2]=='=')
   nSize--;
  char* pOutBuffer=new char[nSize+3];
  ZeroMemory(pOutBuffer,nSize+3);
  LPCTSTR pInBuffer=lpszSrc;
  UINT iTest,iPack;
  for(int i=0;i<nSize/3 ;i++)
  {
   for(int j=0;j<4;j++)
   {
    iTest = BASE64_DECODE_TABLE[*pInBuffer++]; // Read from InputBuffer.
    //InPtr++;
    if (iTest == 0xFF) 
    {
     j--;
     continue; //读到255非法字符
    }
    iPack = iPack << 6 ;
    iPack = iPack | iTest ;
   }
   pOutBuffer[2] = iPack;
   iPack = iPack >> 8;
   pOutBuffer[1] = iPack;
   iPack = iPack >> 8;
   pOutBuffer[0] = iPack;
   //准备写入后3位
   pOutBuffer+= 3; iPack = 0;

  }
  switch(nSize%3)
  {
  case 1:
   iTest = BASE64_DECODE_TABLE[*pInBuffer++]; // Read from InputBuffer.
   if (iTest != 0xFF)
   {
    iPack = iPack << 6 ;
    iPack = iPack | iTest ;
   }
   iTest = BASE64_DECODE_TABLE[*pInBuffer++]; // Read from InputBuffer.
   if (iTest != 0xFF)
   {
    iPack = iPack << 6 ;
    iPack = iPack | iTest ;
   }
   iPack = iPack >> 4;
   pOutBuffer[0] = iPack;
   pOutBuffer++;
   break;
  case 2:
   iTest = BASE64_DECODE_TABLE[*pInBuffer++]; // Read from InputBuffer.
   if (iTest != 0xFF)
   {
    iPack = iPack << 6 ;
    iPack = iPack | iTest ;
   }
   iTest = BASE64_DECODE_TABLE[*pInBuffer++]; // Read from InputBuffer.
   if (iTest != 0xFF)
   {
    iPack = iPack << 6 ;
    iPack = iPack | iTest ;
   }
   iTest = BASE64_DECODE_TABLE[*pInBuffer++]; // Read from InputBuffer.
   if (iTest != 0xFF)
   {
    iPack = iPack << 6 ;
    iPack = iPack | iTest ;
   }
   iPack = iPack >> 2;
   pOutBuffer[1] = iPack;
   iPack = iPack >> 8;
   pOutBuffer[0] = iPack;
   pOutBuffer+=2;
   break;
  default:
   break;
  }
  pOutBuffer-=nSize;
  CString strDecode=pOutBuffer;
  delete pOutBuffer;
  return strDecode;
}
void CSettingDlg::OnOK() 
{
	// TODO: Add extra validation here
	UINT prev_heatbeattime = m_edit_heartbeat_time;
	int prev_port = m_listen_port;
	BOOL pre_poptips = m_disble_poptips;
	BOOL pre_Warning_tone = m_warning_tone;
	UpdateData(TRUE);
	if (prev_port != m_listen_port)
		g_pFrame->Activate(m_listen_port, m_iocpServer->m_nMaxConnections);

	if (pre_poptips != m_disble_poptips)
		((CClientApp *)AfxGetApp())->m_bIsDisablePopTips = m_disble_poptips;

	if (pre_Warning_tone != m_warning_tone)
		((CClientApp *)AfxGetApp())->m_bIsWarning_Tone = m_warning_tone;


	if(prev_heatbeattime!= m_edit_heartbeat_time)
	{
		AfxMessageBox("设置心跳,请重启软件");
	}

	((CClientApp *)AfxGetApp())->m_bisDisableHostlist = m_bisDisableHostlist;
	if ( ((CButton *)GetDlgItem(IDC_DISABLE_HOSTLIST))->GetCheck() == TRUE )
	{
		CString strText = _T("系统设置->已关闭详细信息显示");
		//设置窗口标题
		SetWindowText(strText);
	}
	else
	{
		CString strText = _T("系统设置->已开启详细信息显示");
		//设置窗口标题
		SetWindowText(strText);
	}

	((CClientApp *)AfxGetApp())->m_IniFile.SetInt("Settings", "ListenPort", m_listen_port);
	((CClientApp *)AfxGetApp())->m_IniFile.SetInt("Settings", "PopTips", m_disble_poptips);
	((CClientApp *)AfxGetApp())->m_IniFile.SetInt("Settings", "Alarm", m_warning_tone);
	((CClientApp *)AfxGetApp())->m_IniFile.SetInt("Settings", "HeartBeatTime", m_edit_heartbeat_time);
	((CClientApp *)AfxGetApp())->m_IniFile.SetInt("Settings", "Hostlist", m_bisDisableHostlist);
	CDialog::OnOK();
}
void CSettingDlg::OnDisableHostlist() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	((CClientApp *)AfxGetApp())->m_IniFile.SetInt("Settings", "Hostlist", m_bisDisableHostlist);
	((CClientApp *)AfxGetApp())->m_bisDisableHostlist = m_bisDisableHostlist;
	if ( ((CButton *)GetDlgItem(IDC_DISABLE_HOSTLIST))->GetCheck() == TRUE )
	{
		CString strText = _T("系统设置->已关闭详细信息显示");
		//设置窗口标题
		SetWindowText(strText);
	}
	else
	{
		CString strText = _T("系统设置->已开启详细信息显示");
		//设置窗口标题
		SetWindowText(strText);
	}
}

// void CSettingDlg::OnCustomSkin() 
// {
// 	// TODO: Add your control notification handler code here
// 	
// }
void CSettingDlg::OnCustomSkin() //载入皮肤
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	CString strCurrentPath;
	GetCurrentDirectory(200,strCurrentPath.GetBuffer(200)); //获取当前路径
	strCurrentPath.ReleaseBuffer();
    char szFilters[]= "skins (*.she)|*.she|All Files (*.*)|*.*||";
    CFileDialog fileDlg (TRUE, "*", "", OFN_FILEMUSTEXIST| OFN_HIDEREADONLY, szFilters, this);
	fileDlg.m_ofn.lpstrInitialDir = strCurrentPath; //初始化当前路径
	if( IDOK == fileDlg.DoModal() )
	{
		((CClientApp *)AfxGetApp())->m_IniFile.SetString("Settings", "Skin", fileDlg.GetPathName());   
		CString fileName = fileDlg.GetFileName();
		::SkinH_AttachEx(fileName, NULL);
		SetDlgItemText(IDC_SKIN_PATH, fileDlg.GetPathName());
	} 
}