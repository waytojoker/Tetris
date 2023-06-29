#pragma once
#include<graphics.h>
#include"point.h"
#include<vector>
using namespace std;

class Block:public point
{
	//friend class point;����Ԫ�ļ̳���
public:
	Block();
	void drop();
	void moveLeftOrRight(int offset);
	void rotate();//��ת
	void draw(int leftSide,int topSide);
	static IMAGE** getImages();
	int getBlockType();
	Block& operator=(const Block& other);

	bool blockInMap(const vector<vector<int>>& map);
	void solidify(vector<vector<int>>& map);

private:

	int blockType;//������ʽ��7��
	point smallBlock[4];//���鴢�淽��λ�ã�0~7
	IMAGE *img;

	static IMAGE* imgs[7];//������ʽ��ͼƬ
	static int size;//����С����Ĵ�С
};

