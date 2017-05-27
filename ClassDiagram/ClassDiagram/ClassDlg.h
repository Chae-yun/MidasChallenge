#pragma once


// CClassDlg 대화 상자입니다.

class CClassDlg : public CDialog
{
	DECLARE_DYNAMIC(CClassDlg)

public:
	CClassDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CClassDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CLASS_SETTING };
#endif
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedAtAdd();
	CString m_at_type;
	CString m_at_name;
	CListBox m_list_at;
	CList <CString> m_list;
	afx_msg void OnBnClickedAtDel();
	CString m_op_return;
	CString m_op_name;
	CString m_op_param;
	CListBox m_list_op;
	afx_msg void OnBnClickedOpAdd();
	afx_msg void OnBnClickedOpDel();
	afx_msg void OnBnClickedOk();
	CString m_class_name;
	CString class_name;
	CString at;
	CString op;
};
