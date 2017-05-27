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
		Pen pen(Color(clr), 2);

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
	void PointCloser(Rect startRect, Rect endRect) {
		CPoint start, end;
		TRACE("start %d %d %d %d\n", startRect.X, startRect.Y, startRect.Width, startRect.Height);
		TRACE("end   %d %d %d %d\n", endRect.X,endRect.Y,endRect.Width,endRect.Height);
		double min = sqrt(pow(startRect.X+(startRect.Width/2) - endRect.X+(endRect.Width/2),2)+pow(startRect.Y - endRect.Y+endRect.Height,2)); // 첫번째클래스 상단-> 두번째 클래스 하단
		TRACE("tdmin : %lf\n", min);
		start.x = startRect.X + (startRect.Width / 2);
		start.y = startRect.Y;
		end.x = endRect.X + (endRect.Width / 2);
		end.y = endRect.Y + endRect.Height;
		if (sqrt(pow(startRect.X + (startRect.Width / 2) - endRect.X + endRect.Width, 2) + pow(startRect.Y - endRect.Y + (endRect.Height / 2), 2)) < min) { // 첫번째클래스 상단-> 두번째 클래스 우측
			min = sqrt(pow(startRect.X + (startRect.Width / 2) - endRect.X + endRect.Width, 2) + pow(startRect.Y - endRect.Y + (endRect.Height / 2), 2));
			TRACE("trmin : %lf\n", min);
			start.x = startRect.X + (startRect.Width / 2);
			start.y = startRect.Y;
			end.x = endRect.X + endRect.Width;
			end.y = endRect.Y + (endRect.Height / 2);
		}
		if (sqrt(pow(startRect.X + (startRect.Width / 2) - endRect.X, 2) + pow(startRect.Y - endRect.Y + (endRect.Height / 2), 2)) < min) { // 첫번째클래스 상단-> 두번째 클래스 좌측
			min = sqrt(pow(startRect.X + (startRect.Width / 2) - endRect.X, 2) + pow(startRect.Y - endRect.Y + (endRect.Height / 2), 2));
			TRACE("tlmin : %lf\n", min);
			start.x = startRect.X + (startRect.Width / 2);
			start.y = startRect.Y;
			end.x = endRect.X;
			end.y = endRect.Y + (endRect.Height / 2);
		}
		if (sqrt(pow(startRect.X - endRect.X+(endRect.Width/2), 2) + pow(startRect.Y+(startRect.Height/2) - endRect.Y + endRect.Height, 2)) < min) { // 첫번째클래스 좌측-> 두번째 클래스 하단
			min = sqrt(pow(startRect.X - endRect.X + (endRect.Width / 2), 2) + pow(startRect.Y + (startRect.Height / 2) - endRect.Y + endRect.Height / 2, 2));
			TRACE("ldmin : %lf\n", min);
			start.x = startRect.X;
			start.y = startRect.Y + (startRect.Height / 2);
			end.x = endRect.X + (endRect.Width / 2);
			end.y = endRect.Y + endRect.Height;
		}
		if (sqrt(pow(startRect.X - endRect.X + endRect.Width, 2) + pow(startRect.Y + (startRect.Height / 2) - endRect.Y + (endRect.Height / 2), 2)) < min) { // 첫번째클래스 좌측-> 두번째 클래스 우측
			min = sqrt(pow(startRect.X - endRect.X + endRect.Width, 2) + pow(startRect.Y + (startRect.Height / 2) - endRect.Y + (endRect.Height / 2), 2));
			TRACE("lrmin : %lf\n", min);
			start.x = startRect.X;
			start.y = startRect.Y + (startRect.Height / 2);
			end.x = endRect.X + endRect.Width;
			end.y = endRect.Y + (endRect.Height / 2);
		}
		if(sqrt(pow(startRect.X - endRect.X + (endRect.Width/2), 2) + pow(startRect.Y + (startRect.Height / 2) - endRect.Y,2)) < min) { // 첫번째클래스 좌측-> 두번째 클래스 상단
			min = sqrt(pow(startRect.X - endRect.X + (endRect.Width / 2), 2) + pow(startRect.Y + (startRect.Height / 2) - endRect.Y, 2));
			TRACE("ltmin : %lf\n", min);
			start.x = startRect.X;
			start.y = startRect.Y + (startRect.Height / 2);
			end.x = endRect.X + (endRect.Width / 2);
			end.y = endRect.Y;
		}
		if (sqrt(pow(startRect.X +(startRect.Width/2) - endRect.X, 2) + pow(startRect.Y + startRect.Height - endRect.Y+(endRect.Height/2), 2)) < min) {// 첫번째클래스 하단-> 두번째 클래스 좌측
			min = sqrt(pow(startRect.X + (startRect.Width / 2) - endRect.X, 2) + pow(startRect.Y + startRect.Height - endRect.Y + (endRect.Height / 2), 2));
			TRACE("dlmin : %lf\n", min);
			start.x = startRect.X;
			start.y = startRect.Y + (startRect.Height / 2);
			end.x = endRect.X;
			end.y = endRect.Y + (endRect.Height / 2);
		}
		if (sqrt(pow(startRect.X + (startRect.Width / 2) - endRect.X+(endRect.Width/2), 2) + pow(startRect.Y + startRect.Height - endRect.Height, 2)) < min) {// 첫번째클래스 하단-> 두번째 클래스 상단
			min = sqrt(pow(startRect.X + (startRect.Width / 2) - endRect.X + (endRect.Width / 2), 2) + pow(startRect.Y + startRect.Height - endRect.Height, 2));
			TRACE("dtmin : %lf\n", min);
			start.x = startRect.X;
			start.y = startRect.Y + (startRect.Height / 2);
			end.x = endRect.X + (endRect.Width / 2);
			end.y = endRect.Height;
		}
		if (sqrt(pow(startRect.X + (startRect.Width / 2) - endRect.X+endRect.Width, 2) + pow(startRect.Y + startRect.Height - endRect.Y + (endRect.Height / 2), 2)) < min) {// 첫번째클래스 하단-> 두번째 클래스 우측
			min = sqrt(pow(startRect.X + (startRect.Width / 2) - endRect.X + endRect.Width, 2) + pow(startRect.Y + startRect.Height - endRect.Y + (endRect.Height / 2), 2));
			TRACE("drmin : %lf\n", min);
			start.x = startRect.X;
			start.y = startRect.Y + (startRect.Height / 2);
			end.x = endRect.X + endRect.Width;
			end.y = endRect.Y + (endRect.Height / 2);
		}
		if (sqrt(pow(startRect.X + startRect.Width - endRect.X + (endRect.Width / 2), 2) + pow(startRect.Y + (startRect.Height / 2) - endRect.Y + endRect.Height, 2)) < min) {// 첫번째클래스 우측-> 두번째 클래스 하단
			min = sqrt(pow(startRect.X + startRect.Width - endRect.X + (endRect.Width / 2), 2) + pow(startRect.Y + (startRect.Height / 2) - endRect.Y + endRect.Height, 2));
			TRACE("rdmin : %lf\n", min);
			start.x = startRect.X;
			start.y = startRect.Y + (startRect.Height / 2);
			end.x = endRect.X + endRect.Width;
			end.y = endRect.Y + (endRect.Height / 2);
		}
		if (sqrt(pow(startRect.X + startRect.Width - endRect.X, 2) + pow(startRect.Y + (startRect.Height / 2) - endRect.Y + (endRect.Height/2), 2)) < min) {// 첫번째클래스 우측-> 두번째 클래스 좌측
			min = sqrt(pow(startRect.X + startRect.Width - endRect.X, 2) + pow(startRect.Y + (startRect.Height / 2) - endRect.Y + (endRect.Height / 2), 2));
			TRACE("rlmin : %lf\n", min);
			start.x = startRect.X;
			start.y = startRect.Y + (startRect.Height / 2);
			end.x = endRect.X;
			end.y = endRect.Y + (endRect.Height / 2);
		}
		if (sqrt(pow(startRect.X + startRect.Width - endRect.X + (endRect.Width / 2), 2) + pow(startRect.Y + (startRect.Height / 2) - endRect.Y, 2)) < min) {// 첫번째클래스 우측-> 두번째 클래스 상단
			min = sqrt(pow(startRect.X + startRect.Width - endRect.X + (endRect.Width / 2), 2) + pow(startRect.Y + (startRect.Height / 2) - endRect.Y, 2));
			TRACE("rtmin : %lf\n", min);
			start.x = startRect.X;
			start.y = startRect.Y + (startRect.Height / 2);
			end.x = endRect.X + (endRect.Width / 2);
			end.y = endRect.Y;
		}
		SetPoint(start.x, start.y, end.x, end.y);
	}
	~DExtendline() {};
};

