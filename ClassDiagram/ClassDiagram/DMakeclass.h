#pragma once
#include "Diagram.h"
class DMakeclass :
	public Diagram
{
public:
	DMakeclass() {
		m_diagram_mode = CLASS_MODE;
	};
	~DMakeclass() {};
	Rect m_rect;
	void Draw(CDC *MemDC) { //MemDC에 그리는 함수
		Graphics graphics(*MemDC);

		Gdiplus::Color clr;
		clr.SetFromCOLORREF(RGB(0,0,0));
		Pen pen(Color(clr), 2);
		
		graphics.DrawRectangle(&pen, m_rect);
		graphics.DrawLine(&pen, m_rect.X + (m_rect.Width), m_rect.Y + (m_rect.Height / 3), m_rect.X, m_rect.Y + (m_rect.Height / 3));
		graphics.DrawLine(&pen, m_rect.X + (m_rect.Width), m_rect.Y + (m_rect.Height * 2 / 3), m_rect.X, m_rect.Y + (m_rect.Height * 2 / 3));
	
	};

	void SetRect(int x, int y, int width, int height) {
		m_rect.Width = width;
		m_rect.Height = height;
		m_rect.X = x;
		m_rect.Y = y;
		if (width < 0) { // 너비가 -일때
			m_rect.Width *= -1; //abs사용
			if (height < 0) { //너비가 -이고 높이가 -일때
				m_rect.Height *= -1; //abs사용
				m_rect.X = x - m_rect.Width;
				m_rect.Y = y - m_rect.Height;
			}
			else
				m_rect.X = x - m_rect.Width;
		}
		else if (height < 0) {
			m_rect.Height *= -1; //abs사용
			m_rect.Y = y - m_rect.Height;
		}
	};
};

