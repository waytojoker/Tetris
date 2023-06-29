#pragma once
#include <graphics.h>
//�ı�
class Label {
private:
	int width, height;
public:

	int x = -1, y = -1;
	LPCTSTR text = "";
	int size = 16;
	bool visible = false;//�ؼ��Ƿ�ɼ����ɼ�Ϊtrue������Ϊfalse

	//���캯������ʼ���ؼ����Ͻǵ����ꡢ��ʾ���ı����ı��ĸ߶ȣ�Ĭ��Ϊ16��
	Label(int x, int y, LPCTSTR text, int size = 16);

	// ��ʾ�ؼ�,�ɹ�����true�������쳣����false
	bool show();

	// ���ؿؼ�
	void hide();

	//ˢ�²������ʾ״̬�£�
	void reload();
};
