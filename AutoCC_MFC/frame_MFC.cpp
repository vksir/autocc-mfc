#include "pch.h"
#include "framework.h"
#include "AutoCC_MFC.h"
#include "AutoCC_MFCDlg.h"
#include "afxdialogex.h"
#include "config.h"

//创建combobox参数列表
int damageBoxPara[][2] = { {54, 162}, {52, 150}, {48, 130}, {45, 120}, {45, 110} };
//
LPCTSTR lstr = NULL;

//加载Damage编辑框的控件参数
void CAutoCCMFCDlg::loadDamageEditUI()
{
	if (cc_Config.damageIndex <= 4)				//一二三四五档
	{
		//设置damage两个编辑框为只读
		m_Edit_DamageA.SetReadOnly(true);
		m_Edit_DamageB.SetReadOnly(true);
		//设置damage两个编辑框不显示光标

		//为damage两个编辑框赋combobox参数列表中的值
		setTextInt(m_Edit_DamageA, damageBoxPara[cc_Config.damageIndex][0]);
		setTextInt(m_Edit_DamageB, damageBoxPara[cc_Config.damageIndex][1]);
	}
	else {										//自定义
		//设置damage两个编辑框为可编辑
		m_Edit_DamageA.SetReadOnly(false);
		m_Edit_DamageB.SetReadOnly(false);
		//为damage两个编辑框赋cc_config中的cc参数值
		setTextInt(m_Edit_DamageA, cc_Config.damage[0]);
		setTextInt(m_Edit_DamageB, cc_Config.damage[1]);
	}
}

//加载所有的控件参数
void CAutoCCMFCDlg::loadAllUI()
{
	ifRespond = false;
	{
		//加载damage_comboBox的参数
		m_ComboBox.SetCurSel(cc_Config.damageIndex);
		loadDamageEditUI();
		//加载track和safe编辑框的参数
		setTextInt(m_Edit_TrackA, cc_Config.track[0]);
		setTextInt(m_Edit_TrackB, cc_Config.track[1]);
		setTextInt(m_Edit_SafeA, cc_Config.safe[0]);
		setTextInt(m_Edit_SafeB, cc_Config.safe[1]);
	}
	//启用响应
	ifRespond = true;
}

//将frame中的数据存储到config中
void CAutoCCMFCDlg::configLoad()
{
	cc_Config.damageIndex = m_ComboBox.GetCurSel();
	cc_Config.damage[0] = getTextInt(m_Edit_DamageA);
	cc_Config.damage[1] = getTextInt(m_Edit_DamageB);

	cc_Config.track[0] = getTextInt(m_Edit_TrackA);
	cc_Config.track[1] = getTextInt(m_Edit_TrackB);

	cc_Config.safe[0] = getTextInt(m_Edit_SafeA);
	cc_Config.safe[1] = getTextInt(m_Edit_SafeB);
}

//为CEdit控件设置int类型的文本
void CAutoCCMFCDlg::setTextInt(CEdit &mE, int a)
{
	CString cstr;
	cstr.Format(_T("%d"), a);
	mE.SetWindowTextW(cstr);
}

//将CEdit控件的文本以int类型读取出来
int CAutoCCMFCDlg::getTextInt(CEdit &mE)
{
	CString l = NULL;
	mE.GetWindowTextW(l);
	return _ttoi((LPCTSTR)l);
}