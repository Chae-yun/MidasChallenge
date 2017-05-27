
// ClassDiagramView.h : CClassDiagramView Ŭ������ �������̽�
//

#pragma once

#include "Diagram.h"
#include "DDependline.h"
#include "DExtendline.h"
#include "DMakeclass.h"
#include "atltypes.h"
#include "ClassDiagramView.h"
#include "ClassDiagramDoc.h"
#include "ClassDlg.h"

class CClassDiagramView : public CView
{
protected: // serialization������ ��������ϴ�.
	CClassDiagramView();
	DECLARE_DYNCREATE(CClassDiagramView)

// Ư���Դϴ�.
public:
	CClassDiagramDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CClassDiagramView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	CList<Diagram *> m_list;
	afx_msg void OnUndo();
	afx_msg void OnRedo();
	afx_msg void OnBitmap();
	afx_msg void OnClass();
	afx_msg void OnAttribute();
	afx_msg void OnOperation();
	afx_msg void OnExtend();
	afx_msg void OnDepend();
	afx_msg void OnDelete();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	CPoint m_ptPrev; // Lbutton�� ó�� �������� ��ǥ ���
	void AddDiagramList(CPoint point);
	int m_draw_mode;
	afx_msg void OnMove();
	int m_selectcnt;
	POSITION m_Prev_ps;
	CClassDlg m_class_dlg;
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	CString at="�ȳ�";
	CString op;
};

#ifndef _DEBUG  // ClassDiagramView.cpp�� ����� ����
inline CClassDiagramDoc* CClassDiagramView::GetDocument() const
   { return reinterpret_cast<CClassDiagramDoc*>(m_pDocument); }
#endif