
// AutoCC_MFCDlg.h: 头文件
//

#pragma once


// CAutoCCMFCDlg 对话框
class CAutoCCMFCDlg : public CDialog
{
// 构造
public:
	CAutoCCMFCDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AUTOCC_MFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	virtual void OnCancel();
	DECLARE_MESSAGE_MAP()
public:
	//frame
	bool ifRespond = false;
	void loadDamageEditUI();
	void loadAllUI();
	void configLoad();
	void setTextInt(CEdit &mE, int a);
	int getTextInt(CEdit &me);

public:
	afx_msg void OnCbnSelchangeComboBox();
	CSpinButtonCtrl m_Spin_DamageA;
	CSpinButtonCtrl m_Spin_DamageB;
	CComboBox m_ComboBox;
	CEdit m_Edit_DamageA;
	CEdit m_Edit_DamageB;
	CEdit m_Edit_TrackA;
	CEdit m_Edit_TrackB;
	CEdit m_Edit_SafeA;
	CEdit m_Edit_SafeB;
	afx_msg void OnEnChangeEdit();
	afx_msg void OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClose();
	CButton m_Button_Start;
	CButton m_Button_End;
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonEnd();
	CStatic m_Lable_Tip;
	afx_msg void OnEnSetfocusEdit();
	afx_msg void OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2);
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnMenuStart();
	afx_msg void OnMenuEnd();
	afx_msg void OnMenuExit();
	afx_msg void OnMenuSetInitial();
	afx_msg void OnMenuAbout();
};
