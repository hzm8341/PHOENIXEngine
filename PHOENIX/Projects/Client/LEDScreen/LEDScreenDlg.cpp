
// LEDScreenDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LEDScreen.h"
#include "LEDScreenDlg.h"
#include "afxdialogex.h"
#include "LEDGBCODE.h"
#include "Globals.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
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

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CLEDScreenDlg 对话框



CLEDScreenDlg::CLEDScreenDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LEDSCREEN_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLEDScreenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_LOG, mEditLog);
	DDX_Control(pDX, IDC_IP_SCREEN, mIP);
	DDX_Control(pDX, IDC_EDIT_TEXTSEND, mEditSend);
}

BEGIN_MESSAGE_MAP(CLEDScreenDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_START_SEVER, &CLEDScreenDlg::OnBnClickedButtonStartSever)
	ON_EN_CHANGE(IDC_EDIT_LOG, &CLEDScreenDlg::OnEnChangeEditLog)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CLEDScreenDlg::OnBnClickedButtonSend)
END_MESSAGE_MAP()


// CLEDScreenDlg 消息处理程序

BOOL CLEDScreenDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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
	mIP.SetAddress(192, 168, 1, 149);
	SetDlgItemText(IDC_EDIT_TEXTSEND, CString("Test"));

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CLEDScreenDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CLEDScreenDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CLEDScreenDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CLEDScreenDlg::OnBnClickedButtonStartSever()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CLEDScreenDlg::OnEnChangeEditLog()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CLEDScreenDlg::OnBnClickedButtonSend()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	mIP.GetWindowText(str);		//目标ip
	CString ip = str;

	mEditSend.GetWindowText(str);	//显示内容
	CString info = str;

	UINT mateuid = 61;
	UINT areaW = 64;
	UINT areaH = 32;

	UINT movestyle = 1;	//显示方式
	UINT movespeed = 1;	//移动速度
	UINT fontsize = 1;	//显示字号
	UINT fontbody = 1;	//显示字体
	UINT fontcolor = 1;	//显示颜色
	UINT stoptim = 0;	//停留时间
	BOOL brownsave = 1;		//掉电保存

	UINT pixelcolor = 0; // 单双基色

	extern filedll qydll;
	HINSTANCE Ddll = qydll.Ddll;
	extern CLEDGBCODEudp LEDGBCODEudp;
	LEDGBCODEudp.ip = ip;
	LEDGBCODEudp.mateuid = mateuid;
	LEDGBCODEudp.areaW = areaW;
	LEDGBCODEudp.areaH = areaH;
	LEDGBCODEudp.movestyle = movestyle;
	LEDGBCODEudp.movespeed = movespeed;
	LEDGBCODEudp.fontsize = fontsize;
	LEDGBCODEudp.fontbody = fontbody;
	LEDGBCODEudp.fontcolor = fontcolor;
	LEDGBCODEudp.stoptim = stoptim;
	LEDGBCODEudp.brownsave = brownsave;
	LEDGBCODEudp.pixelcolor = pixelcolor;
	LEDGBCODEudp.str = info;

	BOOL sign = LEDGBCODEudp.senddt(Ddll);
	if (sign)
	{
		MessageBox(CString("下发成功"));
	}
	else
	{
		MessageBox(CString("下发失败"));
	}
}
