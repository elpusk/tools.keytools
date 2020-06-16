
// view_keyDlg.h : header file
//

#pragma once


// CviewkeyDlg dialog
class CviewkeyDlg : public CDialogEx
{
// Construction
public:
	CviewkeyDlg(CWnd* pParent = nullptr);	// standard constructor

	CString get_keystring(unsigned short w_key);
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VIEW_KEY_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

private:
	CRect m_rect_minimum;

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CEdit m_edit_view;
	afx_msg void OnBnClickedButtonClear();
	CButton m_check_enable_return;
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
};
