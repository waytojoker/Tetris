#include "Button.h"

// 构造函数，初始化控件左上角的坐标、宽度、高度、显示的文本与文本的高度（默认为16）
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

// 显示控件,成功返回true，出现异常返回false
bool Button::show()
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
	if (width - textwidth(text) <= 0 || height - textheight(text) <= 0) {
		//文字过大
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

// 隐藏控件
void Button::hide()
{
	COLORREF temp = getfillcolor();
	setfillcolor(getbkcolor());
	solidrectangle(x, y, x + width - 1, y + height - 1);
	setfillcolor(temp);
	visible = false;
	return;
}

// 判断按钮是否被按下，被按下返回true，没有按下或出现异常返回false
bool Button::click(ExMessage m)
{
	if ((x == -1 || y == -1 || width == -1 || height == -1) || !visible) {
		//未初始化控件或当前控件不可见
		return false;
	}
	return m.message == WM_LBUTTONUP && (m.x >= x && m.x <= x + width - 1) && (m.y >= y && m.y <= y + height - 1);
}

// 刷新插件（显示状态下）
void Button::reload()
{
	visible = false;
	show();
}
