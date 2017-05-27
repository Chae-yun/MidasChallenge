#pragma once
#include "stdafx.h"
#include <gdiplusgraphics.h>
#include "define.h"
#include "define.h"
// Diagram

class Diagram : public CWnd
{
	DECLARE_DYNAMIC(Diagram)

public:
	Diagram();
	virtual ~Diagram();
	virtual void Draw(CDC *MemDC)=0; //MemDC�� �׸��� �Լ�
	void Swap(int *n1, int *n2) {
		int temp;
		temp = *n1;
		*n1 = *n2;
		*n2 = temp;
	};
	void Setclick(bool flag) {
		m_diagram_select = flag;
	};
	int m_draw_mode;
	bool m_diagram_select = false; // üũ�Ǿ����� �ȵǾ��ִ��� Ȯ��
	Rect m_selectRect;
protected:
	DECLARE_MESSAGE_MAP()
};


