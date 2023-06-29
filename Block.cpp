#include "Block.h"
#include"point.h"
#include<iostream>
#include<stdlib.h>
#include<graphics.h>
using namespace std;
/*�����ʵ��
	00     00
	00     *0  
	00     **   
	00     0*

*/
IMAGE* Block::imgs[7] = { NULL,NULL,NULL,NULL,NULL,NULL,NULL };//��ʽ
int Block::size = 36;

Block::Block()//��������ʽ�������Լ�������״���߼�ʵ��
{
	//����ͼƬ
	if (imgs[0] == NULL) {

		IMAGE impTmp;
		loadimage(&impTmp, "res/tiles.png");

		//�и��ͼ
		SetWorkingImage(&impTmp);//��titles.png�и�
		for (int i = 0; i < 7; i++) {
			imgs[i] = new IMAGE;
			getimage(imgs[i], i * size, 0, size, size);//�ڼ���ͼ����ԭͼx�ᣬԭͼy�ᣬ������
		}
		SetWorkingImage();//�ָ�������
	}

	int blocks[7][4] = {
		1,3,5,7,//I
		2,4,5,7,//Z1
		3,5,4,6,//Z2
		3,5,4,7,//T
		2,3,5,7,//L
		3,5,7,6,//J
		2,3,4,5,//��

	};

	//������ɷ���
	blockType = 1 + rand() % 7;
	int rannum = rand() % 8;
	//��ʼ��
	for (int i = 0; i < 4; i++) {
		int value = blocks[blockType - 1][i];
		smallBlock[i].setRow(value/2);
		smallBlock[i].setColumn(value % 2);//+rannum
	}

	img = imgs[blockType - 1];//���������
	
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
		//��ת�������
		smallBlock[i].setColumn(p.getColumn()-tmp.getRow()+p.getRow());
		smallBlock[i].setRow(p.getRow()+tmp.getColumn()-p.getColumn());
	}
}

void Block::draw(int leftSide, int topSide)
{
	for (int i = 0; i < 4; i++) {//ÿ�����͵Ķ���˹��������С��
		int x = leftSide + smallBlock[i].getColumn() * size;
		int y = topSide + smallBlock[i].getRow() * size;
		putimage(x, y, img);//��С����ת��ΪͼƬ
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

//�ж�Block�Ƿ��ڵ�ͼ��
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
