#pragma once
#include "afxwin.h"


// CClassDlg ��ȭ �����Դϴ�.

class CClassDlg : public CDialog
{
	DECLARE_DYNAMIC(CClassDlg)

public:
	CClassDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CClassDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CLASS_SETTING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedAtAdd();
	CString m_at_type;
	CString m_at_name;
	CListBox m_list_at;
	afx_msg void OnBnClickedAtDel();
	CString m_op_return;
	CString m_op_name;
	CString m_op_param;
	CListBox m_list_op;
	afx_msg void OnBnClickedOpAdd();
	afx_msg void OnBnClickedOpDel();
};
