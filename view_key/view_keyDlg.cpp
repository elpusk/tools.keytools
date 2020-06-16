
// view_keyDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "view_key.h"
#include "view_keyDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
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


// CviewkeyDlg dialog



CviewkeyDlg::CviewkeyDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_VIEW_KEY_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CviewkeyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_VIEW, m_edit_view);
	DDX_Control(pDX, IDC_CHECK_ENABLE_ENTER, m_check_enable_return);
}

BEGIN_MESSAGE_MAP(CviewkeyDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_KEYUP()
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CviewkeyDlg::OnBnClickedButtonClear)
	ON_WM_GETMINMAXINFO()
END_MESSAGE_MAP()


// CviewkeyDlg message handlers

BOOL CviewkeyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	GetWindowRect(m_rect_minimum);

	m_check_enable_return.SetCheck(BST_CHECKED);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CviewkeyDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CviewkeyDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CviewkeyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CviewkeyDlg::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default

	CDialogEx::OnKeyUp(nChar, nRepCnt, nFlags);
}


BOOL CviewkeyDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	unsigned short w_data = pMsg->wParam;
	CString s_data;
	
	if (pMsg->message == WM_KEYDOWN) {
	
		s_data.Format(L"[%s]", get_keystring(w_data));
	}
	else if (pMsg->message == WM_KEYUP) {
		if (w_data == VK_RETURN) {
			if (m_check_enable_return.GetCheck() == BST_CHECKED) {
				s_data.Format(L"{%s}\r\n", get_keystring(w_data));
			}
			else {
				s_data.Format(L"{%s}", get_keystring(w_data));
			}
		}
		else {
			s_data.Format(L"{%s}", get_keystring(w_data));
		}
	}

	if (!s_data.IsEmpty()) {
		CString s_temp;
		m_edit_view.GetWindowText(s_temp);

		s_temp += s_data;
		m_edit_view.SetWindowText(s_temp);

		if (w_data == VK_RETURN) {
			return TRUE;
		}
		if (w_data == VK_ESCAPE) {
			return TRUE;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

CString CviewkeyDlg::get_keystring(unsigned short w_key)
{
	CString s_out;

	do {
		if (w_key >= 'A' && w_key <= 'Z') {
			s_out.Format(L"%c", w_key);
			continue;
		}
		if (w_key >= '0' && w_key <= '9') {
			s_out.Format(L"%c", w_key);
			continue;
		}

		switch (w_key) {
		case VK_BACK:s_out = L"VK_BACK";	break;
		case VK_TAB:s_out = L"VK_TAB";	break;
		case VK_CLEAR:s_out = L"VK_CLEAR";	break;
		case VK_RETURN:s_out = L"VK_RETURN";	break;
		case VK_SHIFT:s_out = L"VK_SHIFT";	break;
		case VK_CONTROL:s_out = L"VK_CONTROL";	break;
		case VK_MENU:s_out = L"VK_MENU";	break;
		case VK_PAUSE:s_out = L"VK_PAUSE";	break;
		case VK_CAPITAL:s_out = L"VK_CAPITAL";	break;
		case VK_HANGUL:s_out = L"VK_HANGUL";	break;
		case VK_ESCAPE:s_out = L"VK_ESCAPE";	break;
		case VK_SPACE:s_out = L"VK_SPACE";	break;
		case VK_PRIOR:s_out = L"VK_PRIOR";	break;
		case VK_NEXT:s_out = L"VK_NEXT";	break;
		case VK_END:s_out = L"VK_END";	break;
		case VK_HOME:s_out = L"VK_HOME";	break;
		case VK_LEFT:s_out = L"VK_LEFT";	break;
		case VK_UP:s_out = L"VK_UP";	break;
		case VK_RIGHT:s_out = L"VK_RIGHT";	break;
		case VK_DOWN:s_out = L"VK_DOWN";	break;
		case VK_SNAPSHOT:s_out = L"VK_SNAPSHOT";	break;
		case VK_INSERT:s_out = L"VK_INSERT";	break;
		case VK_DELETE:s_out = L"VK_DELETE";	break;
		case VK_LWIN:s_out = L"VK_LWIN";	break;
		case VK_RWIN:s_out = L"VK_RWIN";	break;
		case VK_NUMPAD0:s_out = L"VK_NUMPAD0";	break;
		case VK_NUMPAD1:s_out = L"VK_NUMPAD1";	break;
		case VK_NUMPAD2:s_out = L"VK_NUMPAD2";	break;
		case VK_NUMPAD3:s_out = L"VK_NUMPAD3";	break;
		case VK_NUMPAD4:s_out = L"VK_NUMPAD4";	break;
		case VK_NUMPAD5:s_out = L"VK_NUMPAD5";	break;
		case VK_NUMPAD6:s_out = L"VK_NUMPAD6";	break;
		case VK_NUMPAD7:s_out = L"VK_NUMPAD7";	break;
		case VK_NUMPAD8:s_out = L"VK_NUMPAD8";	break;
		case VK_NUMPAD9:s_out = L"VK_NUMPAD9";	break;
		case VK_MULTIPLY:s_out = L"VK_MULTIPLY";	break;
		case VK_ADD:s_out = L"VK_ADD";	break;
		case VK_SEPARATOR:s_out = L"VK_SEPARATOR";	break;
		case VK_SUBTRACT:s_out = L"VK_SUBTRACT";	break;
		case VK_DECIMAL:s_out = L"VK_DECIMAL";	break;
		case VK_DIVIDE:s_out = L"VK_DIVIDE";	break;
		case VK_F1:s_out = L"VK_F1";	break;
		case VK_F2:s_out = L"VK_F2";	break;
		case VK_F3:s_out = L"VK_F3";	break;
		case VK_F4:s_out = L"VK_F4";	break;
		case VK_F5:s_out = L"VK_F5";	break;
		case VK_F6:s_out = L"VK_F6";	break;
		case VK_F7:s_out = L"VK_F7";	break;
		case VK_F8:s_out = L"VK_F8";	break;
		case VK_F9:s_out = L"VK_F9";	break;
		case VK_F10:s_out = L"VK_F10";	break;
		case VK_F11:s_out = L"VK_F11";	break;
		case VK_F12:s_out = L"VK_F12";	break;
		case VK_F13:s_out = L"VK_F13";	break;
		case VK_F14:s_out = L"VK_F14";	break;
		case VK_F15:s_out = L"VK_F15";	break;
		case VK_F16:s_out = L"VK_F16";	break;
		case VK_F17:s_out = L"VK_F17";	break;
		case VK_F18:s_out = L"VK_F18";	break;
		case VK_F19:s_out = L"VK_F19";	break;
		case VK_F20:s_out = L"VK_F20";	break;
		case VK_F21:s_out = L"VK_F21";	break;
		case VK_F22:s_out = L"VK_F22";	break;
		case VK_F23:s_out = L"VK_F23";	break;
		case VK_F24:s_out = L"VK_F24";	break;
		case VK_NUMLOCK:s_out = L"VK_NUMLOCK";	break;
		case VK_SCROLL:s_out = L"VK_SCROLL";	break;
		case VK_OEM_1:s_out = L" VK_OEM_1 ;: ";	break;
		case VK_OEM_PLUS:s_out = L" VK_OEM_PLUS + ";	break;
		case VK_OEM_COMMA:s_out = L" VK_OEM_COMMA , ";	break;
		case VK_OEM_MINUS:s_out = L" VK_OEM_MINUS - ";	break;
		case VK_OEM_PERIOD:s_out = L" VK_OEM_PERIOD . ";	break;
		case VK_OEM_2:s_out = L" VK_OEM_2 /? ";	break;
		case VK_OEM_3:s_out = L" VK_OEM_3 ~ ";	break;
		case VK_OEM_4:s_out = L" VK_OEM_4 [{ ";	break;
		case VK_OEM_5:s_out = L" VK_OEM_5 \\| ";	break;
		case VK_OEM_6:s_out = L" VK_OEM_6 ]} ";	break;
		case VK_OEM_7:s_out = L" VK_OEM_7 single-quote/double-quote ";	break;
		case VK_OEM_8:s_out = L" VK_OEM_8";	break;
		case VK_OEM_102:s_out = L" VK_OEM_102";		break;
		case VK_APPS:s_out = L"VK_APPS";	break;
		case VK_HANJA:s_out = L"VK_HANJA";	break;
		default:
			s_out.Format(L"0x%02X", w_key);
			break;
		}//end switch
	} while (false);

	return s_out;
}

void CviewkeyDlg::OnBnClickedButtonClear()
{
	m_edit_view.SetWindowText(L"");
}


void CviewkeyDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	lpMMI->ptMinTrackSize.x = m_rect_minimum.Width();
	lpMMI->ptMinTrackSize.y = m_rect_minimum.Height();

	CDialogEx::OnGetMinMaxInfo(lpMMI);
}
