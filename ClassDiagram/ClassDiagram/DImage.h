#pragma once
#include "Diagram.h"
class DImage :
	public Diagram
{
public:
	DImage() {
		m_diagram_mode = IMAGE_MODE;
	};
	~DImage() {};
	void Draw(CDC *MemDC) {
		Bitmap *pBitmap;
		Graphics graphics(*MemDC);
		pBitmap = (Bitmap *)Image::FromFile(m_filePath);
		graphics.DrawImage(pBitmap, 0, 0);
		delete pBitmap;
	}
	void SetFilePath(WCHAR *path) {
		m_filePath = path;
	};
	void SetPenColor(COLORREF color) {}
	void SetPenSize(int size) {}
	WCHAR *m_filePath;

};