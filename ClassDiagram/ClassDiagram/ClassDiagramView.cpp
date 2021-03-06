
// ClassDiagramView.cpp : CClassDiagramView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
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
	// 표준 인쇄 명령입니다.
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
ON_COMMAND(ID_FILE_SAVE, &CClassDiagramView::OnFileSave)
END_MESSAGE_MAP()

bool SaveBMP(CDC* pDC, CRect BitmapSize, int BitCount, LPCTSTR filename);

// CClassDiagramView 생성/소멸


CClassDiagramView::CClassDiagramView()
	: m_ptPrev(0)
	, m_draw_mode(-1)
	, m_selectcnt(0)
	, pWideChar(NULL)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CClassDiagramView::~CClassDiagramView()
{
}

BOOL CClassDiagramView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CClassDiagramView 그리기

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

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &MemDC, 0, 0, SRCCOPY); //memdc를 dc에 한번에 넣어서 더블버퍼링 기법 구현

	MemDC.SelectObject(pOldBitmap);
	MemDC.DeleteDC();
}


// CClassDiagramView 인쇄


void CClassDiagramView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CClassDiagramView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CClassDiagramView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CClassDiagramView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
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


// CClassDiagramView 진단

#ifdef _DEBUG
void CClassDiagramView::AssertValid() const
{
	CView::AssertValid();
}

void CClassDiagramView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CClassDiagramDoc* CClassDiagramView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CClassDiagramDoc)));
	return (CClassDiagramDoc*)m_pDocument;
}
#endif //_DEBUG


// CClassDiagramView 메시지 처리기
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
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
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
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CClassDiagramView::OnOperation()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
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
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (m_list.GetCount() > 0) {
		m_list_backup.AddTail(m_list.GetTail());
		m_list.RemoveTail();
		Invalidate(FALSE);
	}
}

void CClassDiagramView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_draw_mode == CLASS_MODE && nFlags == MK_LBUTTON) { //사각형그릴때
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
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
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
							if (class2->m_rect.Y > class1->m_rect.Y) {  // 아래 -> 위
								if (class2->m_rect.Y < class1->m_rect.Y + class1->m_rect.Height) { //옆인가?
									if (class2->m_rect.X < class1->m_rect.X + class1->m_rect.Width) { //왼 -> 오
										extendline->SetPoint(
										
											class2->m_rect.X + (class2->m_rect.Width),
											class2->m_rect.Y + (class2->m_rect.Height / 2),
											class1->m_rect.X,
											class1->m_rect.Y + (class1->m_rect.Height / 2)
										);
									}
									else {  // 오 -> 왼
										extendline->SetPoint(
											class2->m_rect.X,
											class2->m_rect.Y + (class2->m_rect.Height / 2),
											class1->m_rect.X + (class1->m_rect.Width),
											class1->m_rect.Y + (class1->m_rect.Height / 2)
										);

									}
								}
								else { //옆이아니면
									extendline->SetPoint(
										class2->m_rect.X + (class2->m_rect.Width / 2),
										class2->m_rect.Y, //첫번째 선택 클래스
										class1->m_rect.X + (class1->m_rect.Width / 2),
										class1->m_rect.Y + class1->m_rect.Height);//두번째 선택 클래스
								}
							}
							else { // 위 -> 아래
								if (class1->m_rect.Y < class2->m_rect.Y + class2->m_rect.Height) { //옆인가?
									if (class2->m_rect.X > class1->m_rect.X + class1->m_rect.Width) { //오 -> 왼
										extendline->SetPoint(
											class2->m_rect.X,
											class2->m_rect.Y + (class2->m_rect.Height / 2),
											class1->m_rect.X + (class1->m_rect.Width),
											class1->m_rect.Y + (class1->m_rect.Height / 2)
											
										);
									}
									else { //왼 -> 오
										extendline->SetPoint(
											class2->m_rect.X + (class2->m_rect.Width),
											class2->m_rect.Y + (class2->m_rect.Height / 2),
											class1->m_rect.X,
											class1->m_rect.Y + (class1->m_rect.Height / 2)
										);
									}
								}
								else {//옆이아니면
									extendline->SetPoint(
										class2->m_rect.X + (class2->m_rect.Width / 2),
										class2->m_rect.Y + (class2->m_rect.Height), //첫번째 선택 클래스
										class1->m_rect.X + (class1->m_rect.Width / 2),
										class1->m_rect.Y);//두번째 선택 클래스
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
							if (class2->m_rect.Y > class1->m_rect.Y) {  // 아래 -> 위
								if (class2->m_rect.Y < class1->m_rect.Y + class1->m_rect.Height) { //옆인가?
									if (class2->m_rect.X < class1->m_rect.X + class1->m_rect.Width) { //왼 -> 오
										dependline->SetPoint(

											class2->m_rect.X + (class2->m_rect.Width),
											class2->m_rect.Y + (class2->m_rect.Height / 2),
											class1->m_rect.X,
											class1->m_rect.Y + (class1->m_rect.Height / 2)
										);
									}
									else {  // 오 -> 왼
										dependline->SetPoint(
											class2->m_rect.X,
											class2->m_rect.Y + (class2->m_rect.Height / 2),
											class1->m_rect.X + (class1->m_rect.Width),
											class1->m_rect.Y + (class1->m_rect.Height / 2)
										);

									}
								}
								else { //옆이아니면
									dependline->SetPoint(
										class2->m_rect.X + (class2->m_rect.Width / 2),
										class2->m_rect.Y, //첫번째 선택 클래스
										class1->m_rect.X + (class1->m_rect.Width / 2),
										class1->m_rect.Y + class1->m_rect.Height);//두번째 선택 클래스
								}
							}
							else { // 위 -> 아래
								if (class1->m_rect.Y < class2->m_rect.Y + class2->m_rect.Height) { //옆인가?
									if (class2->m_rect.X > class1->m_rect.X + class1->m_rect.Width) { //오 -> 왼
										dependline->SetPoint(
											class2->m_rect.X,
											class2->m_rect.Y + (class2->m_rect.Height / 2),
											class1->m_rect.X + (class1->m_rect.Width),
											class1->m_rect.Y + (class1->m_rect.Height / 2)

										);
									}
									else { //왼 -> 오
										dependline->SetPoint(
											class2->m_rect.X + (class2->m_rect.Width),
											class2->m_rect.Y + (class2->m_rect.Height / 2),
											class1->m_rect.X,
											class1->m_rect.Y + (class1->m_rect.Height / 2)
										);
									}
								}
								else {//옆이아니면
									dependline->SetPoint(
										class2->m_rect.X + (class2->m_rect.Width / 2),
										class2->m_rect.Y + (class2->m_rect.Height), //첫번째 선택 클래스
										class1->m_rect.X + (class1->m_rect.Width / 2),
										class1->m_rect.Y);//두번째 선택 클래스
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
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_ptPrev = point;

	if (m_draw_mode == NONE) {
		POSITION ps = m_list.GetTailPosition();
		Diagram *diagram;
		BOOL modal;

		while (ps) {
			diagram = m_list.GetAt(ps);
			if (diagram->m_diagram_mode == CLASS_MODE) {
				DMakeclass *class1 = (DMakeclass*)diagram;
				if (class1->m_rect.Contains(point.x, point.y)) {
					modal = m_class_dlg.DoModal();

					m_class_dlg.GetClassName(class1->class_name);
					m_class_dlg.GetAtList(class1->at_list);
					m_class_dlg.GetOpList(class1->op_list);

					if (modal == IDOK) 
						Invalidate(FALSE);
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

bool SaveBMP(CDC* pDC, CRect BitmapSize, int BitCount, LPCTSTR filename)
{
	CDC memDC;
	CBitmap Bitmap, *pOldBmp;

	HANDLE handle;
	HANDLE hDIB;
	HPALETTE hPal = NULL;

	BITMAP bm;
	BITMAPINFOHEADER bi;
	LPBITMAPINFOHEADER lpbi;

	DWORD dwLen;

	/*----- CDC의 내용을 Bitmap으로 전송 ----*/
	memDC.CreateCompatibleDC(pDC);
	Bitmap.CreateCompatibleBitmap(pDC, BitmapSize.Width(), BitmapSize.Height());
	pOldBmp = (CBitmap*)memDC.SelectObject(&Bitmap);
	memDC.BitBlt(0, 0, BitmapSize.Width(), BitmapSize.Height(), pDC, 0, 0, SRCCOPY);
	memDC.SelectObject(pOldBmp);

	/*------------------------- 비트멥 헤더를 기록함 -------------------------*/
	if (hPal == NULL)
		hPal = (HPALETTE)GetStockObject(DEFAULT_PALETTE);

	GetObject(HBITMAP(Bitmap), sizeof(BITMAP), &bm);

	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = bm.bmWidth;
	bi.biHeight = bm.bmHeight;
	bi.biPlanes = 1;
	bi.biBitCount = BitCount;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = bm.bmWidth * bm.bmHeight * 3;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrUsed = 0;
	bi.biClrImportant = 0;

	int nColors = (1 << bi.biBitCount);
	if (nColors > 256)
		nColors = 0;

	dwLen = bi.biSize + nColors * sizeof(RGBQUAD);

	hPal = SelectPalette(pDC->GetSafeHdc(), hPal, FALSE);

	RealizePalette(pDC->GetSafeHdc());

	hDIB = GlobalAlloc(GMEM_FIXED, dwLen);

	lpbi = (LPBITMAPINFOHEADER)hDIB;

	*lpbi = bi;

	GetDIBits(pDC->GetSafeHdc(), HBITMAP(Bitmap), 0, (DWORD)bi.biHeight,
		(LPBYTE)NULL, (LPBITMAPINFO)lpbi, (DWORD)DIB_RGB_COLORS);

	bi = *lpbi;

	if (bi.biSizeImage == 0)
		bi.biSizeImage = ((((bi.biWidth * bi.biBitCount) + 31) & ~31) / 8) * bi.biHeight;

	dwLen += bi.biSizeImage;

	if (handle = GlobalReAlloc(hDIB, dwLen, GMEM_MOVEABLE))
		hDIB = handle;

	lpbi = (LPBITMAPINFOHEADER)hDIB;

	GetDIBits(pDC->GetSafeHdc(), HBITMAP(Bitmap), 0, (DWORD)bi.biHeight,
		(LPBYTE)lpbi + (bi.biSize + nColors * sizeof(RGBQUAD)),
		(LPBITMAPINFO)lpbi, (DWORD)DIB_RGB_COLORS);

	BITMAPFILEHEADER hdr;

	hdr.bfType = ((WORD)('M' << 8) | 'B');
	hdr.bfSize = (DWORD)(GlobalSize(hDIB) + sizeof(hdr));
	hdr.bfReserved1 = 0;
	hdr.bfReserved2 = 0;
	hdr.bfOffBits = (DWORD)(sizeof(hdr) + lpbi->biSize + nColors * sizeof(RGBQUAD));

	char* pBmpBuf;
	DWORD FileSize;
	FileSize = (DWORD)(sizeof(hdr) + GlobalSize(hDIB));
	pBmpBuf = new char[FileSize];

	memcpy(pBmpBuf, &hdr, sizeof(hdr));
	memcpy(pBmpBuf + sizeof(hdr), lpbi, GlobalSize(hDIB));

	/*--------------------- 실제 파일에 기록함 --------------------------*/
	FILE *pFile = NULL;

	fopen_s(&pFile, filename, "wb");

	bool bResult = false;
	if (pFile != NULL)
	{
		fwrite(pBmpBuf, FileSize, 1, pFile);
		fclose(pFile);
		bResult = true;
	}

	delete[] pBmpBuf;

	if (hDIB)
		GlobalFree(hDIB);

	SelectPalette(pDC->GetSafeHdc(), hPal, FALSE);

	return bResult;
}

void CClassDiagramView::OnFileSave()
{
	CClientDC dc(this);
	CRect rect;
	GetClientRect(&rect);
	char name_filter[] = "All Files (*.*)|*.*|BMP Files (*.bmp)|*.bmp|";
	CFileDialog ins_dlg(FALSE, "bmp", "*.bmp", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT |
		OFN_NOCHANGEDIR, name_filter, NULL);

	// 파일 형식 콤보박스에 나열된 필터들 중에서 2번째 항목(*.txt)을 선택한다.
	ins_dlg.m_ofn.nFilterIndex = 2;

	// 다이얼로그를 띄운다.
	if (ins_dlg.DoModal() == IDOK) {
		SaveBMP(&dc, rect, 24, ins_dlg.GetPathName());
	}
}
