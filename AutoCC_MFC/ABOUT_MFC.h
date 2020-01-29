#pragma once


// ABOUT_MFC 对话框

class ABOUT_MFC : public CDialogEx
{
	DECLARE_DYNAMIC(ABOUT_MFC)

public:
	ABOUT_MFC(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~ABOUT_MFC();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
