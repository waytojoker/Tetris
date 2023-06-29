#include "Block.h"
#include"point.h"
#include<iostream>
#include<stdlib.h>
#include<graphics.h>
using namespace std;
/*方块的实现
	00     00
	00     *0  
	00     **   
	00     0*

*/
IMAGE* Block::imgs[7] = { NULL,NULL,NULL,NULL,NULL,NULL,NULL };//样式
int Block::size = 36;

Block::Block()//包含对样式的配置以及方块形状的逻辑实现
{
	//配置图片
	if (imgs[0] == NULL) {

		IMAGE impTmp;
		loadimage(&impTmp, "res/tiles.png");

		//切割大图
		SetWorkingImage(&impTmp);//对titles.png切割
		for (int i = 0; i < 7; i++) {
			imgs[i] = new IMAGE;
			getimage(imgs[i], i * size, 0, size, size);//第几种图样，原图x轴，原图y轴，长，宽
		}
		SetWorkingImage();//恢复工作区
	}

	int blocks[7][4] = {
		1,3,5,7,//I
		2,4,5,7,//Z1
		3,5,4,6,//Z2
		3,5,4,7,//T
		2,3,5,7,//L
		3,5,7,6,//J
		2,3,4,5,//田

	};

	//随机生成方块
	blockType = 1 + rand() % 7;
	int rannum = rand() % 8;
	//初始化
	for (int i = 0; i < 4; i++) {
		int value = blocks[blockType - 1][i];
		smallBlock[i].setRow(value/2);
		smallBlock[i].setColumn(value % 2);//+rannum
	}

	img = imgs[blockType - 1];//单个方块的
	
}

void Block::drop()
{
	for (int i = 0; i < 4; i++) {
		smallBlock[i].setRow(smallBlock[i].getRow() + 1);
	}	
}

void Block::moveLeftOrRight(int offset)
{
	for (int i = 0; i < 4; i++) {
		smallBlock[i].setColumn(smallBlock[i].getColumn() + offset);
	}
}

void Block::rotate()
{
	point p = smallBlock[1];
	for (int i = 0; i < 4; i++) {
		point tmp = smallBlock[i];
		//旋转坐标计算
		smallBlock[i].setColumn(p.getColumn()-tmp.getRow()+p.getRow());
		smallBlock[i].setRow(p.getRow()+tmp.getColumn()-p.getColumn());
	}
}

void Block::draw(int leftSide, int topSide)
{
	for (int i = 0; i < 4; i++) {//每种类型的俄罗斯方块有四小块
		int x = leftSide + smallBlock[i].getColumn() * size;
		int y = topSide + smallBlock[i].getRow() * size;
		putimage(x, y, img);//将小方块转化为图片
	}
}

IMAGE** Block::getImages()
{
	return imgs;
}

int Block::getBlockType()
{
	return blockType;
}

Block& Block::operator=(const Block& other)
{
	if (this == &other)return *this;
	this->blockType = other.blockType;
	for (int i = 0; i < 4; i++)this->smallBlock[i] = other.smallBlock[i];
	return *this;
}

//判断Block是否在地图内
bool Block::blockInMap(const vector<vector<int>>& map)
{
	int rows = map.size();
	int cols = map[0].size();
	for (int i = 0; i < 4; i++) {
		if(smallBlock[i].getColumn()<0||smallBlock[i].getRow()<0||
			smallBlock[i].getColumn()>=cols||smallBlock[i].getRow() >= rows||
			map[smallBlock[i].getRow()][smallBlock[i].getColumn()]!=0)
		{
			return false;
		}	
	}
	return true;
}

void Block::solidify(vector<vector<int>>& map)
{
	for (int i = 0; i < 4; i++) {
		map[smallBlock[i].getRow()][smallBlock[i].getColumn()] = blockType;
		//cout<< smallBlock[i].getRow()<<"fixed  " << smallBlock[i].getColumn() << "fixed" <<  '\n';
	}
}
