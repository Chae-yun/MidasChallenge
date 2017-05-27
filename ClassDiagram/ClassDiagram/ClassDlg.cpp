// ClassDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ClassDiagram.h"
#include "ClassDlg.h"
#include "afxdialogex.h"
#include "ClassDiagramView.h"


// CClassDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CClassDlg, CDialog)

CClassDlg::CClassDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_CLASS_SETTING, pParent)
	, m_at_type(_T(""))
	, m_at_name(_T(""))
	, m_op_return(_T(""))
	, m_op_name(_T(""))
	, m_op_param(_T(""))
{

}

CClassDlg::~CClassDlg()
{
}

void CClassDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_AT_TYPE, m_at_type);
	DDV_MaxChars(pDX, m_at_type, 15);
	DDX_Text(pDX, IDC_AT_NAME, m_at_name);
	DDV_MaxChars(pDX, m_at_name, 30);
	DDX_Control(pDX, IDC_LIST_AT, m_list_at);
	DDX_Text(pDX, IDC_OP_RETURN, m_op_return);
	DDV_MaxChars(pDX, m_op_return, 15);
	DDX_Text(pDX, IDC_OP_NAME, m_op_name);
	DDV_MaxChars(pDX, m_op_name, 30);
	DDX_Text(pDX, IDC_OP_PARAM, m_op_param);
	DDV_MaxChars(pDX, m_op_param, 40);
	DDX_Control(pDX, IDC_LIST_OP, m_list_op);
}


BEGIN_MESSAGE_MAP(CClassDlg, CDialog)
	ON_BN_CLICKED(IDC_AT_ADD, &CClassDlg::OnBnClickedAtAdd)
	ON_BN_CLICKED(IDC_AT_DEL, &CClassDlg::OnBnClickedAtDel)
	ON_BN_CLICKED(IDC_OP_ADD, &CClassDlg::OnBnClickedOpAdd)
	ON_BN_CLICKED(IDC_OP_DEL, &CClassDlg::OnBnClickedOpDel)
END_MESSAGE_MAP()


// CClassDlg �޽��� ó�����Դϴ�.


void CClassDlg::OnBnClickedAtAdd()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);   //Edit Box�� �ִ� ���ڿ��� ������ ����
	//at = m_at_type + " " + m_at_name;
	m_list_at.AddString(m_at_type + " " + m_at_name);    //����Ʈ������ ������ AddString�� ����Ͽ� ���ڿ��� �߰�
	m_at_type = "";
	m_at_name = "";
	UpdateData(FALSE);    //������ �ִ� ���� ������ ���ڷ� ����
}


void CClassDlg::OnBnClickedAtDel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int nList = 0;
	nList = m_list_at.GetCurSel();    //���õ� ����� �ε����� �����Ѵ�.
	m_list_at.DeleteString(nList);
}


void CClassDlg::OnBnClickedOpAdd()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);   //Edit Box�� �ִ� ���ڿ��� ������ ����
	m_list_op.AddString(m_op_return + " " + m_op_name + "(" + m_op_param + ")");    //����Ʈ������ ������ AddString�� ����Ͽ� ���ڿ��� �߰�
	m_op_return = "";
	m_op_name = "";
	m_op_param = "";
	UpdateData(FALSE);    //������ �ִ� ���� ������ ���ڷ� ����
}


void CClassDlg::OnBnClickedOpDel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int nList = 0;
	nList = m_list_op.GetCurSel();    //���õ� ����� �ε����� �����Ѵ�.
	m_list_op.DeleteString(nList);
}

void CClassDlg::SetStringAt(CString &s) {
	m_list_at.AddString("hhgjgj");
}
