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
	CString class_name;
	CString at_list;
	CString op_list;

	void Draw(CDC *MemDC) { //MemDC에 그리는 함수
		Graphics graphics(*MemDC);

		Gdiplus::Color clr;
		clr.SetFromCOLORREF(RGB(0,0,0));
		Pen pen(Color(clr), 2);

		graphics.DrawRectangle(&pen, m_rect);
		graphics.DrawLine(&pen, m_rect.X + (m_rect.Width), m_rect.Y + (m_rect.Height / 3), m_rect.X, m_rect.Y + (m_rect.Height / 3));
		graphics.DrawLine(&pen, m_rect.X + (m_rect.Width), m_rect.Y + (m_rect.Height * 2 / 3), m_rect.X, m_rect.Y + (m_rect.Height * 2 / 3));

		
		Gdiplus::Font font(Gdiplus::FontFamily::GenericSansSerif(), 4, FontStyleRegular, UnitMillimeter);
		PointF ptf(m_rect.X + 20, m_rect.Y + 20);
		SolidBrush sbrush(Color(0, 0, 0));

		int nLen = class_name.GetLength() + 1;
		WCHAR* pwsz = new WCHAR[nLen];

		size_t nSize;
		mbstowcs_s(&nSize, pwsz, nLen, (LPCTSTR)class_name, nLen);

		graphics.DrawString(pwsz, nLen, &font, ptf, &sbrush);
		delete[] pwsz;


		ptf.X = m_rect.X + 20;
		ptf.Y = m_rect.Y + 70;
		sbrush.SetColor(Color(0, 0, 0));

		nLen = at_list.GetLength() + 1;
		pwsz = new WCHAR[nLen];

		mbstowcs_s(&nSize, pwsz, nLen, (LPCTSTR)at_list, nLen);

		graphics.DrawString(pwsz, nLen, &font, ptf, &sbrush);
		delete[] pwsz;

		ptf.X = m_rect.X + 20;
		ptf.Y = m_rect.Y + 180;
		sbrush.SetColor(Color(0, 0, 0));

		nLen = op_list.GetLength() + 1;
		pwsz = new WCHAR[nLen];

		mbstowcs_s(&nSize, pwsz, nLen, (LPCTSTR)op_list, nLen);

		graphics.DrawString(pwsz, nLen, &font, ptf, &sbrush);
		delete[] pwsz;
	
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

