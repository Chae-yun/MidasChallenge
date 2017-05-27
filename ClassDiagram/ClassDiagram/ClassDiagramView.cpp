
// ClassDiagramView.cpp : CClassDiagramView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "ClassDiagram.h"
#endif

#include "ClassDiagramDoc.h"
#include "ClassDiagramView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CClassDiagramView

IMPLEMENT_DYNCREATE(CClassDiagramView, CView)

BEGIN_MESSAGE_MAP(CClassDiagramView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CClassDiagramView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_UNDO, &CClassDiagramView::OnUndo)
	ON_COMMAND(ID_REDO, &CClassDiagramView::OnRedo)
	ON_COMMAND(ID_BITMAP, &CClassDiagramView::OnBitmap)
	ON_COMMAND(ID_CLASS, &CClassDiagramView::OnClass)
	ON_COMMAND(ID_ATTRIBUTE, &CClassDiagramView::OnAttribute)
	ON_COMMAND(ID_OPERATION, &CClassDiagramView::OnOperation)
	ON_COMMAND(ID_EXTEND, &CClassDiagramView::OnExtend)
	ON_COMMAND(ID_DEPEND, &CClassDiagramView::OnDepend)
	ON_COMMAND(ID_DELETE, &CClassDiagramView::OnDelete)
END_MESSAGE_MAP()

// CClassDiagramView ����/�Ҹ�

CClassDiagramView::CClassDiagramView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CClassDiagramView::~CClassDiagramView()
{
}

BOOL CClassDiagramView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CClassDiagramView �׸���

void CClassDiagramView::OnDraw(CDC* pDC)
{
	CClassDiagramDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// CClassDiagramView �μ�


void CClassDiagramView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CClassDiagramView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CClassDiagramView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CClassDiagramView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}

void CClassDiagramView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CClassDiagramView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CClassDiagramView ����

#ifdef _DEBUG
void CClassDiagramView::AssertValid() const
{
	CView::AssertValid();
}

void CClassDiagramView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CClassDiagramDoc* CClassDiagramView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CClassDiagramDoc)));
	return (CClassDiagramDoc*)m_pDocument;
}
#endif //_DEBUG


// CClassDiagramView �޽��� ó����


void CClassDiagramView::OnUndo()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

}


void CClassDiagramView::OnRedo()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}


void CClassDiagramView::OnBitmap()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}


void CClassDiagramView::OnClass()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}


void CClassDiagramView::OnAttribute()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}


void CClassDiagramView::OnOperation()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}


void CClassDiagramView::OnExtend()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}


void CClassDiagramView::OnDepend()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}


void CClassDiagramView::OnDelete()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}
