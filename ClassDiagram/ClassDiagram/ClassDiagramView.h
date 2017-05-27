
// ClassDiagramView.h : CClassDiagramView Ŭ������ �������̽�
//

#pragma once


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
};

#ifndef _DEBUG  // ClassDiagramView.cpp�� ����� ����
inline CClassDiagramDoc* CClassDiagramView::GetDocument() const
   { return reinterpret_cast<CClassDiagramDoc*>(m_pDocument); }
#endif

