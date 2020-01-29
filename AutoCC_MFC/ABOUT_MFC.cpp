// ABOUT_MFC.cpp: 实现文件
//

#include "pch.h"
#include "AutoCC_MFC.h"
#include "ABOUT_MFC.h"
#include "afxdialogex.h"


// ABOUT_MFC 对话框

IMPLEMENT_DYNAMIC(ABOUT_MFC, CDialogEx)

ABOUT_MFC::ABOUT_MFC(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ABOUTBOX, pParent)
{

}

ABOUT_MFC::~ABOUT_MFC()
{
}

void ABOUT_MFC::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ABOUT_MFC, CDialogEx)
END_MESSAGE_MAP()


// ABOUT_MFC 消息处理程序
