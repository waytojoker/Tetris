#pragma once
#include<graphics.h>
#include"point.h"
#include<vector>
using namespace std;

class Block:public point
{
	//friend class point;把友元改继承了
public:
	Block();
	void drop();
	void moveLeftOrRight(int offset);
	void rotate();//旋转
	void draw(int leftSide,int topSide);
	static IMAGE** getImages();
	int getBlockType();
	Block& operator=(const Block& other);

	bool blockInMap(const vector<vector<int>>& map);
	void solidify(vector<vector<int>>& map);

private:

	int blockType;//方块样式，7种
	point smallBlock[4];//数组储存方块位置，0~7
	IMAGE *img;

	static IMAGE* imgs[7];//方块样式的图片
	static int size;//单个小方块的大小
};

