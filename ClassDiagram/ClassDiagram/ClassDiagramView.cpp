
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

#include "ClassDlg.h"

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
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_MOVE, &CClassDiagramView::OnMove)
//	ON_WM_MBUTTONDBLCLK()
ON_WM_LBUTTONDBLCLK()
ON_WM_PAINT()
END_MESSAGE_MAP()

// CClassDiagramView ����/�Ҹ�

CClassDiagramView::CClassDiagramView()
	: m_ptPrev(0)
	, m_draw_mode(-1)
	, m_selectcnt(0)
	, pWideChar(NULL)
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

	CDC MemDC;
	CBitmap* pOldBitmap;
	CBitmap bmp;

	CRect rect;
	GetClientRect(&rect);

	MemDC.CreateCompatibleDC(pDC);
	bmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	pOldBitmap = (CBitmap *)MemDC.SelectObject(&bmp);
	MemDC.PatBlt(0, 0, rect.Width(), rect.Height(), WHITENESS);

	POSITION ps = m_list.GetHeadPosition();
	while (ps) {
		Diagram *diagram;
		diagram = m_list.GetAt(ps);
		if (diagram->m_diagram_mode == CLASS_MODE) {
			DMakeclass *makeclass = (DMakeclass *)diagram;
			makeclass->Draw(&MemDC);
		}
		if (diagram->m_diagram_mode == EXTEND_MODE) {
			DExtendline *extendline = (DExtendline *)diagram;
			extendline->Draw(&MemDC);
		}
		if (diagram->m_diagram_mode == DEPEND_MODE) {
			DDependline *dependline = (DDependline *)diagram;
			dependline->Draw(&MemDC);
		}
		if (diagram->m_diagram_mode == IMAGE_MODE) {
			DImage *image = (DImage *)diagram;
			image->Draw(&MemDC);
		}
		m_list.GetNext(ps);
	}

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &MemDC, 0, 0, SRCCOPY); //memdc�� dc�� �ѹ��� �־ ������۸� ��� ����

	MemDC.SelectObject(pOldBitmap);
	MemDC.DeleteDC();
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
	if (m_list.GetCount() > 0) {
		m_list_backup.AddTail(m_list.GetTail());
		m_list.RemoveTail();
		Invalidate(FALSE);
	}
}


void CClassDiagramView::OnRedo()
{
	if (m_list_backup.GetCount() > 0) {
		m_list.AddTail(m_list_backup.GetTail());
		m_list_backup.RemoveTail();
		Invalidate(FALSE);
	}
}


void CClassDiagramView::OnBitmap()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	char szFilter[] = "Image (*.BMP, *.GIF, *.JPG) | *.BMP;*.GIF;*.JPG | All Files(*.*)|*.*||";
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, szFilter);
	if (IDOK == dlg.DoModal())
	{
		CString strPathName = dlg.GetPathName();
		WCHAR *FilePath = ConvertMultibyteToUnicode((LPSTR)(LPCSTR)strPathName);
		DImage *image = new DImage();
		image->SetFilePath(pWideChar);
		m_list.AddTail((Diagram *)image);
	}
	Invalidate(FALSE);
}

void CClassDiagramView::OnClass()
{
	m_draw_mode = CLASS_MODE;
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
	m_draw_mode = EXTEND_MODE;
	m_selectcnt = 0;
}


void CClassDiagramView::OnDepend()
{
	m_draw_mode = DEPEND_MODE;
	m_selectcnt = 0;
}


void CClassDiagramView::OnDelete()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	if (m_list.GetCount() > 0) {
		m_list_backup.AddTail(m_list.GetTail());
		m_list.RemoveTail();
		Invalidate(FALSE);
	}
}

void CClassDiagramView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (m_draw_mode == CLASS_MODE && nFlags == MK_LBUTTON) { //�簢���׸���
		DMakeclass *makeclass = new DMakeclass();
		makeclass->SetRect(m_ptPrev.x, m_ptPrev.y, point.x - m_ptPrev.x, point.y - m_ptPrev.y);

		POSITION Index;
		Index = m_list.GetTailPosition();
		m_list.SetAt(Index, (Diagram *)makeclass);

		Invalidate(FALSE);
	}
	CView::OnMouseMove(nFlags, point);
}


void CClassDiagramView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	m_ptPrev = point;
	AddDiagramList(point);
	CView::OnLButtonDown(nFlags, point);
}


void CClassDiagramView::AddDiagramList(CPoint point)
{
	if (m_draw_mode == CLASS_MODE) {
		DMakeclass *makeclass = new DMakeclass();
		m_list.AddTail((Diagram *)makeclass);
	}
	if (m_draw_mode == EXTEND_MODE) {
		POSITION ps = m_list.GetTailPosition();
		Diagram *diagram;
		while (ps) {
			diagram = m_list.GetAt(ps);
			if (diagram->m_diagram_mode == CLASS_MODE) {
				DMakeclass *class1 = (DMakeclass*)diagram;
				if (class1->m_rect.Contains(point.x, point.y)) {
					if (ps != m_Prev_ps) {
						m_selectcnt++;
						if (m_selectcnt == 2) {
							diagram = m_list.GetAt(m_Prev_ps);
							DMakeclass *class2 = (DMakeclass *)diagram;
							DExtendline *extendline = new DExtendline;
							if (class2->m_rect.Y > class1->m_rect.Y) {  // �Ʒ� -> ��
								if (class2->m_rect.Y < class1->m_rect.Y + class1->m_rect.Height) { //���ΰ�?
									if (class2->m_rect.X + class2->m_rect.Width  < class1->m_rect.X) { //�� -> ��
										extendline->SetPoint(
											class1->m_rect.X,
											class1->m_rect.Y + (class1->m_rect.Height / 2),
											class2->m_rect.X + (class2->m_rect.Width),
											class2->m_rect.Y + (class2->m_rect.Height / 2)
										);
									}
									else {  // �� -> ��
										extendline->SetPoint(
											class1->m_rect.X + (class1->m_rect.Width),
											class1->m_rect.Y + (class1->m_rect.Height / 2),
											class2->m_rect.X,
											class2->m_rect.Y + (class2->m_rect.Height / 2)
										);

									}
								}
								else { //���̾ƴϸ�
									extendline->SetPoint(
										class2->m_rect.X + (class2->m_rect.Width / 2),
										class2->m_rect.Y, //ù��° ���� Ŭ����
										class1->m_rect.X + (class1->m_rect.Width / 2),
										class1->m_rect.Y + class1->m_rect.Height);//�ι�° ���� Ŭ����
								}
							}
							else { // �� -> �Ʒ�
								if (class1->m_rect.Y < class2->m_rect.Y + class2->m_rect.Height) { //���ΰ�?
									if (class2->m_rect.X > class1->m_rect.X + class1->m_rect.Width) { //�� -> ��
										extendline->SetPoint(
											class1->m_rect.X + (class1->m_rect.Width),
											class1->m_rect.Y + (class1->m_rect.Height / 2),
											class2->m_rect.X,
											class2->m_rect.Y + (class2->m_rect.Height / 2)
										);
									}
									else { //�� -> ��
										extendline->SetPoint(
											class1->m_rect.X,
											class1->m_rect.Y + (class1->m_rect.Height / 2),
											class2->m_rect.X + (class2->m_rect.Width),
											class2->m_rect.Y + (class2->m_rect.Height / 2)
										);
									}
								}
								else {//���̾ƴϸ�
									extendline->SetPoint(
										class2->m_rect.X + (class2->m_rect.Width / 2),
										class2->m_rect.Y + (class2->m_rect.Height), //ù��° ���� Ŭ����
										class1->m_rect.X + (class1->m_rect.Width / 2),
										class1->m_rect.Y);//�ι�° ���� Ŭ����
								}
							}
							m_list.AddTail((Diagram *)extendline);
							Invalidate(FALSE);
							m_selectcnt = 0;
							m_Prev_ps = NULL;
							break;
						}
						else {
							m_Prev_ps = ps;
							break;
						}
					}
				}
			}
			m_list.GetPrev(ps);
		}
	}
	if (m_draw_mode == DEPEND_MODE) {
		POSITION ps = m_list.GetTailPosition();
		Diagram *diagram;
		while (ps) {
			diagram = m_list.GetAt(ps);
			if (diagram->m_diagram_mode == CLASS_MODE) {
				DMakeclass *class1 = (DMakeclass*)diagram;
				if (class1->m_rect.Contains(point.x, point.y)) {
					if (ps != m_Prev_ps) {
						m_selectcnt++;
						if (m_selectcnt == 2) {
							diagram = m_list.GetAt(m_Prev_ps);
							DMakeclass *class2 = (DMakeclass *)diagram;
							DDependline *dependline = new DDependline;
							if (class2->m_rect.Y > class1->m_rect.Y) {  // �Ʒ� -> ��
								if (class2->m_rect.Y < class1->m_rect.Y + class1->m_rect.Height) { //���ΰ�?
									if (class2->m_rect.X + class2->m_rect.Width  < class1->m_rect.X) { //�� -> ��
										dependline->SetPoint(
											class1->m_rect.X,
											class1->m_rect.Y + (class1->m_rect.Height / 2),
											class2->m_rect.X + (class2->m_rect.Width),
											class2->m_rect.Y + (class2->m_rect.Height / 2)
										);
									}
									else {  // �� -> ��
										dependline->SetPoint(
											class1->m_rect.X + (class1->m_rect.Width),
											class1->m_rect.Y + (class1->m_rect.Height / 2),
											class2->m_rect.X,
											class2->m_rect.Y + (class2->m_rect.Height / 2)
										);

									}
								}
								else { //���̾ƴϸ�
									dependline->SetPoint(
										class2->m_rect.X + (class2->m_rect.Width / 2),
										class2->m_rect.Y, //ù��° ���� Ŭ����
										class1->m_rect.X + (class1->m_rect.Width / 2),
										class1->m_rect.Y + class1->m_rect.Height);//�ι�° ���� Ŭ����
								}
							}
							else { // �� -> �Ʒ�
								if (class1->m_rect.Y < class2->m_rect.Y + class2->m_rect.Height) { //���ΰ�?
									if (class2->m_rect.X > class1->m_rect.X + class1->m_rect.Width) { //�� -> ��
										dependline->SetPoint(
											class1->m_rect.X + (class1->m_rect.Width),
											class1->m_rect.Y + (class1->m_rect.Height / 2),
											class2->m_rect.X,
											class2->m_rect.Y + (class2->m_rect.Height / 2)
										);
									}
									else { //�� -> ��
										dependline->SetPoint(
											class1->m_rect.X,
											class1->m_rect.Y + (class1->m_rect.Height / 2),
											class2->m_rect.X + (class2->m_rect.Width),
											class2->m_rect.Y + (class2->m_rect.Height / 2)
										);
									}
								}
								else {//���̾ƴϸ�
									dependline->SetPoint(
										class2->m_rect.X + (class2->m_rect.Width / 2),
										class2->m_rect.Y + (class2->m_rect.Height), //ù��° ���� Ŭ����
										class1->m_rect.X + (class1->m_rect.Width / 2),
										class1->m_rect.Y);//�ι�° ���� Ŭ����
								}
							}
							m_list.AddTail((Diagram *)dependline);
							Invalidate(FALSE);
							m_selectcnt = 0;
							m_Prev_ps = NULL;
							break;
						}
						else {
							m_Prev_ps = ps;
							break;
						}
					}
				}
			}
			m_list.GetPrev(ps);
		}
	}
}

void CClassDiagramView::OnMove()
{
	m_draw_mode = NONE;
}

void CClassDiagramView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	m_ptPrev = point;

	if (m_draw_mode == NONE) {
		POSITION ps = m_list.GetTailPosition();
		Diagram *diagram;
		while (ps) {
			diagram = m_list.GetAt(ps);
			if (diagram->m_diagram_mode == CLASS_MODE) {
				DMakeclass *class1 = (DMakeclass*)diagram;
				if (class1->m_rect.Contains(point.x, point.y)) {
					//m_class_dlg.SetStringAt(at);
					m_class_dlg.DoModal();
				}
			}
			m_list.GetPrev(ps);
		}
	}

	CView::OnLButtonDblClk(nFlags, point);
}

WCHAR * CClassDiagramView::ConvertMultibyteToUnicode(char * pMultibyte)
{
	int nLen = strlen(pMultibyte);

	pWideChar = new WCHAR[nLen];
	memset(pWideChar, 0x00, (nLen) * sizeof(WCHAR));

	MultiByteToWideChar(CP_ACP, 0, (LPCSTR)pMultibyte, -1, pWideChar, nLen);

	CString strUnicode;
	strUnicode.Format("%s", pWideChar);

	return pWideChar;
}
