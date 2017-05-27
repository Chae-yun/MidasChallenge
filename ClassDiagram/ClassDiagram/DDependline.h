#pragma once
#include "Diagram.h"
class DDependline :
	public Diagram
{
public:
	DDependline() {
		m_diagram_mode = DEPEND_MODE;
	};
	Point m_startPoint;
	Point m_endPoint;
	void Draw(CDC *MemDC) { //MemDC에 그리는 함수
		Graphics graphics(*MemDC);

		Gdiplus::Color clr;
		clr.SetFromCOLORREF(RGB(0, 0, 0));
		Pen pen(Color(clr), 2);
		pen.SetDashStyle(DashStyleDash);

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
	~DDependline() {};
};

