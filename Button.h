#pragma once
// 按钮 
#include<iostream>
#include<graphics.h>

class Button {
public:

	int x = -1, y = -1, width = -1, height = -1;
	LPCTSTR text = "";  // 控件所显示的文本 
	int size = 16;       // 控件显示的文本高度	
	bool visible = false;// 控件是否可见，可见为true，否则为false

	Button(int x, int y, int width, int height, LPCTSTR text, int size = 16);
	bool show(); 	
	void hide(); 
	bool click(ExMessage m); 	
	void reload();
};
