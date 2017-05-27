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
	void Swap(void *n1, void *n2) {
		void *temp;
		temp = n1;
		n1 = n2;
		n2 = temp;
	};
	virtual void Draw(CDC *MemDC)=0; //MemDC�� �׸��� �Լ�

	void Setclick(bool flag) {
		m_diagram_select = flag;
	};
	int m_diagram_mode;
	bool m_diagram_select = false; // üũ�Ǿ����� �ȵǾ��ִ��� Ȯ��
	Rect m_selectRect;
protected:
	DECLARE_MESSAGE_MAP()
};


