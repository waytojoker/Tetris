#include "Button.h"

// ���캯������ʼ���ؼ����Ͻǵ����ꡢ��ȡ��߶ȡ���ʾ���ı����ı��ĸ߶ȣ�Ĭ��Ϊ16��
Button::Button(int x, int y, int width, int height, LPCTSTR text, int size)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->text = text;
	this->size = size;
	return;
}

// ��ʾ�ؼ�,�ɹ�����true�������쳣����false
bool Button::show()
{
	if (visible) {
		//��ǰ�ؼ��ɼ�
		return false;
	}
	int temp = getbkmode();
	setbkmode(TRANSPARENT);
	LOGFONT* temp1 = new LOGFONT();
	LOGFONT* temp2 = new LOGFONT();
	gettextstyle(temp1);
	gettextstyle(temp2);
	temp2->lfHeight = size;
	settextstyle(temp2);
	if (width - textwidth(text) <= 0 || height - textheight(text) <= 0) {
		//���ֹ���
		settextstyle(temp1);
		return false;
	}
	fillrectangle(x, y, x + width - 1, y + height - 1);
	outtextxy(x + (width - textwidth(text)) / 2, y + (height - textheight(text)) / 2, text);
	settextstyle(temp1);
	setbkmode(temp);
	delete temp1;
	delete temp2;
	visible = true;
	return true;
}

// ���ؿؼ�
void Button::hide()
{
	COLORREF temp = getfillcolor();
	setfillcolor(getbkcolor());
	solidrectangle(x, y, x + width - 1, y + height - 1);
	setfillcolor(temp);
	visible = false;
	return;
}

// �жϰ�ť�Ƿ񱻰��£������·���true��û�а��»�����쳣����false
bool Button::click(ExMessage m)
{
	if ((x == -1 || y == -1 || width == -1 || height == -1) || !visible) {
		//δ��ʼ���ؼ���ǰ�ؼ����ɼ�
		return false;
	}
	return m.message == WM_LBUTTONUP && (m.x >= x && m.x <= x + width - 1) && (m.y >= y && m.y <= y + height - 1);
}

// ˢ�²������ʾ״̬�£�
void Button::reload()
{
	visible = false;
	show();
}
