#pragma once
#include "Diagram.h"
class DExtendline :
	public Diagram
{
public:
	DExtendline() {
		m_diagram_mode = EXTEND_MODE;
	};
	Point m_startPoint;
	Point m_endPoint;
	void Draw(CDC *MemDC) { //MemDC에 그리는 함수
		Graphics graphics(*MemDC);

		Gdiplus::Color clr;
		clr.SetFromCOLORREF(RGB(0, 0, 0));
		Pen pen(Color(clr), 6);
		pen.SetStartCap(LineCapNoAnchor);
		pen.SetEndCap(LineCapArrowAnchor);

		graphics.DrawLine(&pen, m_startPoint, m_endPoint);
	};

	void SetPoint(int startX, int startY, int endX, int endY) {
		m_startPoint.X = startX;
		m_startPoint.Y = startY;
		m_endPoint.X = endX;
		m_endPoint.Y = endY;
		if (m_startPoint.X > m_endPoint.X)
			Swap(&m_startPoint, &m_endPoint);
	}
	~DExtendline() {};
};

