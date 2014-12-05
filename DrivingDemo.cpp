
// DrivingDemo.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "DrivingDemo.h"
#include "MainFrm.h"
#include "Util.h"
#include "afxwin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDrivingDemoApp

BEGIN_MESSAGE_MAP(CDrivingDemoApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CDrivingDemoApp::OnAppAbout)
END_MESSAGE_MAP()


// CDrivingDemoApp 构造

CDrivingDemoApp::CDrivingDemoApp()
{
	// TODO: 将以下应用程序 ID 字符串替换为唯一的 ID 字符串；建议的字符串格式
	//为 CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("DrivingDemo.AppID.NoVersion"));

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}

// 唯一的一个 CDrivingDemoApp 对象

CDrivingDemoApp theApp;


// CDrivingDemoApp 初始化

BOOL CDrivingDemoApp::InitInstance()
{
	CWinApp::InitInstance();


	// 初始化 OLE 库
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// 使用 RichEdit 控件需要  AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));


	// 若要创建主窗口，此代码将创建新的框架窗口
	// 对象，然后将其设置为应用程序的主窗口对象
	CMainFrame* pFrame = new CMainFrame;
	if (!pFrame)
		return FALSE;
	m_pMainWnd = pFrame;
	// 创建并加载框架及其资源
	pFrame->LoadFrame(IDR_MAINFRAME,
		WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL,
		NULL);






	// 唯一的一个窗口已初始化，因此显示它并对其进行更新
	pFrame->ShowWindow(SW_SHOWMAXIMIZED);
	pFrame->UpdateWindow();
	// 仅当具有后缀时才调用 DragAcceptFiles
	//  在 SDI 应用程序中，这应在 ProcessShellCommand 之后发生
	return TRUE;
}

int CDrivingDemoApp::ExitInstance()
{
	//TODO: 处理可能已添加的附加资源
	AfxOleTerm(FALSE);

	return CWinApp::ExitInstance();
}

// CDrivingDemoApp 消息处理程序


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	CStatic m_lbl_version;
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_VERSION, m_lbl_version);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// 用于运行对话框的应用程序命令
void CDrivingDemoApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CDrivingDemoApp 消息处理程序


BOOL CAboutDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	TCHAR cPath[200],szVersionBuffer[200];
 DWORD dwHandle,InfoSize;
 CString strVersion;
 ::GetModuleFileName(NULL,cPath,sizeof(cPath)); //首先获得版本信息资源的长度
 InfoSize = GetFileVersionInfoSize(cPath,&dwHandle); //将版本信息资源读入缓冲区
 if(InfoSize==0) 
 {
  AfxMessageBox(_T("None VerSion Supprot"));
  return TRUE;
 }
 char *InfoBuf = new char[InfoSize];
 GetFileVersionInfo(cPath,0,InfoSize,InfoBuf); //获得生成文件使用的代码页及文件版本
 unsigned int  cbTranslate = 0;
 struct LANGANDCODEPAGE {
  WORD wLanguage;
  WORD wCodePage;
 } *lpTranslate;
 VerQueryValue(InfoBuf, TEXT("\\VarFileInfo\\Translation"),(LPVOID*)&lpTranslate,&cbTranslate);
 // Read the file description for each language and code page.
 for( int i=0; i < (cbTranslate/sizeof(struct LANGANDCODEPAGE)); i++ )
 {
  TCHAR  SubBlock[200];
  wsprintf( SubBlock,
            TEXT("\\StringFileInfo\\%04x%04x\\FileVersion"),
            lpTranslate[i].wLanguage,
            lpTranslate[i].wCodePage);
  void *lpBuffer=NULL;
  unsigned int dwBytes=0;
  VerQueryValue(InfoBuf,
   SubBlock,
   &lpBuffer,
   &dwBytes);
  CString strTemp=(TCHAR *)lpBuffer;
  strVersion+=strTemp;
 }

delete InfoBuf;
 //AfxMessageBox(strVersion);
CString tmp;
tmp.Format(L"作者:陆键霏 版本:%s",strVersion);
//Util::LOG(L"version=%s",strVersion);
m_lbl_version.SetWindowTextW(tmp);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
