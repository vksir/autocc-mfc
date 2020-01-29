
// AutoCC_MFCDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "AutoCC_MFC.h"
#include "AutoCC_MFCDlg.h"
#include "afxdialogex.h"
#include "config.h"
#include "main.h"
#include "ABOUT_MFC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif
	
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
//	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CAutoCCMFCDlg 对话框



CAutoCCMFCDlg::CAutoCCMFCDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_AUTOCC_MFC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAutoCCMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SPIN1, m_Spin_DamageA);
	DDX_Control(pDX, IDC_SPIN2, m_Spin_DamageB);
	DDX_Control(pDX, IDC_COMBO1, m_ComboBox);
	DDX_Control(pDX, IDC_EDIT1, m_Edit_DamageA);
	DDX_Control(pDX, IDC_EDIT2, m_Edit_DamageB);
	DDX_Control(pDX, IDC_EDIT3, m_Edit_TrackA);
	DDX_Control(pDX, IDC_EDIT4, m_Edit_TrackB);
	DDX_Control(pDX, IDC_EDIT5, m_Edit_SafeA);
	DDX_Control(pDX, IDC_EDIT6, m_Edit_SafeB);
	DDX_Control(pDX, IDC_BUTTON1, m_Button_Start);
	DDX_Control(pDX, IDC_BUTTON2, m_Button_End);
	DDX_Control(pDX, IDC_STATIC_TIP, m_Lable_Tip);
}

BEGIN_MESSAGE_MAP(CAutoCCMFCDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_COMBO1, &CAutoCCMFCDlg::OnCbnSelchangeComboBox)
	ON_EN_CHANGE(IDC_EDIT1, &CAutoCCMFCDlg::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT2, &CAutoCCMFCDlg::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT3, &CAutoCCMFCDlg::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT4, &CAutoCCMFCDlg::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT5, &CAutoCCMFCDlg::OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT6, &CAutoCCMFCDlg::OnEnChangeEdit)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, &CAutoCCMFCDlg::OnDeltaposSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN2, &CAutoCCMFCDlg::OnDeltaposSpin)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON1, &CAutoCCMFCDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON2, &CAutoCCMFCDlg::OnBnClickedButtonEnd)
	ON_EN_SETFOCUS(IDC_EDIT1, &CAutoCCMFCDlg::OnEnSetfocusEdit)
	ON_EN_SETFOCUS(IDC_EDIT2, &CAutoCCMFCDlg::OnEnSetfocusEdit)
	ON_WM_HOTKEY()
	ON_WM_HELPINFO()
	ON_COMMAND(ID_MENU_START, &CAutoCCMFCDlg::OnMenuStart)
	ON_COMMAND(ID_MENU_END, &CAutoCCMFCDlg::OnMenuEnd)
	ON_COMMAND(ID_MENU_EXIT, &CAutoCCMFCDlg::OnMenuExit)
	ON_COMMAND(ID_32774, &CAutoCCMFCDlg::OnMenuSetInitial)
	ON_COMMAND(ID_32775, &CAutoCCMFCDlg::OnMenuAbout)
END_MESSAGE_MAP()


// CAutoCCMFCDlg 消息处理程序

BOOL CAutoCCMFCDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	//添加全局热键Ctrl+F1---开启
	RegisterHotKey(GetSafeHwnd(), 8, MOD_CONTROL, VK_F1);
	RegisterHotKey(GetSafeHwnd(), 9, MOD_CONTROL, VK_F2);

	//设置DamageA和DamageB的Spin
	UDACCEL aclA, aclB;
	aclA.nInc = 2;
	aclB.nInc = 10;
	m_Spin_DamageA.SetRange(0, 9999);
	m_Spin_DamageA.SetAccel(2, &aclA);
	m_Spin_DamageA.SetBuddy(GetDlgItem(IDC_EDIT1));

	m_Spin_DamageB.SetRange(0, 9999);
	m_Spin_DamageB.SetAccel(2, &aclB);
	m_Spin_DamageB.SetBuddy(GetDlgItem(IDC_EDIT2));

	//设置编辑框
	m_Edit_DamageA.SetLimitText(6);
	m_Edit_DamageB.SetLimitText(6);
	m_Edit_TrackA.SetLimitText(6);
	m_Edit_TrackB.SetLimitText(6);
	m_Edit_SafeA.SetLimitText(6);
	m_Edit_SafeA.SetLimitText(6);

	//设置提示文本
	m_Lable_Tip.SetWindowTextW(_T("AutoCC Completed!"));

	//设置按钮
	m_Button_Start.EnableWindow(false);
	m_Button_End.EnableWindow(true);

	//加载UI
	loadAllUI();
	

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CAutoCCMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CAutoCCMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//重载OnOK使其失效
void CAutoCCMFCDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}

//重载OnCancel使其失效
void CAutoCCMFCDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnCancel();
}

//重载onclose使点击X按钮时关闭窗口
void CAutoCCMFCDlg::OnClose()
{
	//EndDialog(IDCANCEL);	//关闭窗口
	//CDialog::OnClose();
	CDialog::OnCancel();
}

//重载OnHelpInfo函数处理WM_HELPINFO消息使其失效
BOOL CAutoCCMFCDlg::OnHelpInfo(HELPINFO* pHelpInfo)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//return CDialog::OnHelpInfo(pHelpInfo);
	return true;
}

/**
 * 添加响应事件
 *
 */

//设置响应ComboBox
void CAutoCCMFCDlg::OnCbnSelchangeComboBox()
{
	// TODO: 在此添加控件通知处理程序代码
	if (ifRespond)
	{
		//加载数据
		configLoad();
		Config::load();
		//加载UI
		loadDamageEditUI();
	}

}

//设置响应Edit
void CAutoCCMFCDlg::OnEnChangeEdit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	if (ifRespond)
	{
		configLoad();
		Config::load();
	}
}

//设置响应Spin
void CAutoCCMFCDlg::OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	//将comboBox置为自定义
	m_ComboBox.SetCurSel(5);
	//调用comboBox响应函数
	OnCbnSelchangeComboBox();
}

//设置响应"启用"按钮
void CAutoCCMFCDlg::OnBnClickedButtonStart()
{
	// TODO: 在此添加控件通知处理程序代码

	//设置按钮UI
	m_Button_Start.EnableWindow(false);
	m_Button_End.EnableWindow(true);
	//设置提示文本
	m_Lable_Tip.SetWindowTextW(_T("AutoCC Completed!"));
	//开启主线程
	main::openMainThread();
}

//设置响应"禁用"按钮
void CAutoCCMFCDlg::OnBnClickedButtonEnd()
{
	// TODO: 在此添加控件通知处理程序代码

	//设置按钮UI
	m_Button_End.EnableWindow(false);
	m_Button_Start.EnableWindow(true);
	//设置提示文本
	m_Lable_Tip.SetWindowTextW(_T(""));
	//关闭所有线程
	main::closeAllThread();
}

//处理使Edit控件在只读状态下不显示光标
void CAutoCCMFCDlg::OnEnSetfocusEdit()
{
	// TODO: 在此添加控件通知处理程序代码

	//间接判断Edit控件是否为只读状态
	bool ifReadOnly = (m_ComboBox.GetCurSel() <= 4);
	//隐藏Edit光标
	if (ifReadOnly)
	{
		m_Edit_DamageA.HideCaret();
		m_Edit_DamageB.HideCaret();
	}
}

/**
 * 响应全局热键
 *
 */

void CAutoCCMFCDlg::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if (nKey2 == VK_F1)
	{
		//视为"启用"按钮被点击
		OnBnClickedButtonStart();
	}
	else if(nKey2 == VK_F2)
	{
		//视为"禁用"按钮被点击
		OnBnClickedButtonEnd();
	}

	CDialog::OnHotKey(nHotKeyId, nKey1, nKey2);
}

/**
 * 添加菜单栏处理函数
 *
 */

//设置-开启
void CAutoCCMFCDlg::OnMenuStart()
{
	// TODO: 在此添加命令处理程序代码

	//视为"启用"按钮被点击
	OnBnClickedButtonStart();
}

//设置-关闭
void CAutoCCMFCDlg::OnMenuEnd()
{
	// TODO: 在此添加命令处理程序代码

	//视为"禁用"按钮被点击
	OnBnClickedButtonEnd();
}

//设置-退出
void CAutoCCMFCDlg::OnMenuExit()
{
	// TODO: 在此添加命令处理程序代码

	CDialog::OnCancel();
}

//帮助-初始化
void CAutoCCMFCDlg::OnMenuSetInitial()
{
	// TODO: 在此添加命令处理程序代码

	//config初始化
	cc_Config.setInitial();
	//数据加载
	Config::load();
	//加载UI
	loadAllUI();
}


void CAutoCCMFCDlg::OnMenuAbout()
{
	// TODO: 在此添加命令处理程序代码

	ABOUT_MFC about_Frame;
	about_Frame.DoModal();
}