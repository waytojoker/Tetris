#pragma once
#include <graphics.h>
//文本
class Label {
private:
	int width, height;
public:

	int x = -1, y = -1;
	LPCTSTR text = "";
	int size = 16;
	bool visible = false;//控件是否可见，可见为true，否则为false

	//构造函数，初始化控件左上角的坐标、显示的文本与文本的高度（默认为16）
	Label(int x, int y, LPCTSTR text, int size = 16);

	// 显示控件,成功返回true，出现异常返回false
	bool show();

	// 隐藏控件
	void hide();

	//刷新插件（显示状态下）
	void reload();
};
