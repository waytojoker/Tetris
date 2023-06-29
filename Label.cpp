#include "Label.h"

Label::Label(int x, int y, LPCTSTR text, int size)
{
	this->x = x;
	this->y = y;
	this->text = text;
	this->size = size;
	width = 0;
	height = 0;
	return;
}

bool Label::show()
{
	if (visible) {
		//当前控件可见
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
	outtextxy(x, y, text);
	width = textwidth(text);
	height = textheight(text);
	settextstyle(temp1);
	delete temp1;
	delete temp2;
	setbkmode(temp);
	visible = true;
	return true;
}

void Label::hide()
{
	COLORREF temp = getfillcolor();
	setfillcolor(getbkcolor());
	solidrectangle(x, y, x + width - 1, y + height - 1);
	setfillcolor(temp);
	visible = false;
	return;
}

void Label::reload()
{
	visible = false;
	show();
}
