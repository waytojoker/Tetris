#pragma once
// ��ť 
#include<iostream>
#include<graphics.h>

class Button {
public:

	int x = -1, y = -1, width = -1, height = -1;
	LPCTSTR text = "";  // �ؼ�����ʾ���ı� 
	int size = 16;       // �ؼ���ʾ���ı��߶�	
	bool visible = false;// �ؼ��Ƿ�ɼ����ɼ�Ϊtrue������Ϊfalse

	Button(int x, int y, int width, int height, LPCTSTR text, int size = 16);
	bool show(); 	
	void hide(); 
	bool click(ExMessage m); 	
	void reload();
};
