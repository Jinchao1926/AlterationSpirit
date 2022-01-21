; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAlterationSpiritApp
LastTemplate=CEdit
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "alterationspirit.h"
LastPage=0

ClassCount=4
Class1=CAlterationSpiritApp
Class2=CAboutDlg
Class3=CAlterationSpiritDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Class4=CEditEx
Resource2=IDD_ALTERATIONSPIRIT_DIALOG
Resource3=IDR_POPUPMENU

[CLS:CAlterationSpiritApp]
Type=0
BaseClass=CWinApp
HeaderFile=AlterationSpirit.h
ImplementationFile=AlterationSpirit.cpp
Filter=N
VirtualFilter=AC
LastObject=CAlterationSpiritApp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=AlterationSpiritDlg.cpp
ImplementationFile=AlterationSpiritDlg.cpp

[CLS:CAlterationSpiritDlg]
Type=0
BaseClass=CDialog
HeaderFile=AlterationSpiritDlg.h
ImplementationFile=AlterationSpiritDlg.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDM_TRAY_EXIT

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_ALTERATIONSPIRIT_DIALOG]
Type=1
Class=CAlterationSpiritDlg
ControlCount=14
Control1=IDC_SAVE,button,1342242817
Control2=IDC_EDIT_NUM7,edit,1350631560
Control3=IDS_NUM7,static,1342308352
Control4=IDC_EDIT_NUM4,edit,1350631560
Control5=IDS_NUM4,static,1342308352
Control6=IDC_EDIT_NUM1,edit,1350631560
Control7=IDS_NUM1,static,1342308352
Control8=IDC_EDIT_NUM8,edit,1350631560
Control9=IDS_NUM8,static,1342308352
Control10=IDC_EDIT_NUM5,edit,1350631560
Control11=IDS_NUM5,static,1342308352
Control12=IDC_EDIT_NUM2,edit,1350631560
Control13=IDS_NUM2,static,1342308352
Control14=IDS_PROMPT,button,1342177287

[CLS:CEditEx]
Type=0
HeaderFile=EditEx.h
ImplementationFile=EditEx.cpp
BaseClass=CEdit
Filter=W
LastObject=CEditEx
VirtualFilter=WC

[MNU:IDR_POPUPMENU]
Type=1
Class=CAlterationSpiritDlg
Command1=IDM_TRAY_OPEN
Command2=IDM_TRAY_EXIT
CommandCount=2

