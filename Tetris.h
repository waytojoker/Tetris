#pragma once
#include<iostream>
#include<vector>
#include<graphics.h>
#include<stdio.h>
#include"Block.h"
#include"musicManager.h"
#include"fileManager.h"
using namespace std;
class Tetris
{
	friend class fileManager;
public:
	//constructor
	Tetris(int rows,int columns,int left,int top,int blockSize);
	void init(int _mode);//初始化
	void play(int _mode,int _save);//开始游戏
	void input2(bool& rotateflag, int& dx);
	//void solidify(vector<vector<int>>& map);
	void showMap();
	
private:

	//数据成员函数
	void keyEvent();
	void updateWindow();
	void printNecessaryMessage();
	int getDelay();//返回距离上一次调用这个函数的时间，第一次返回0
	void drop();
	void clearLine();
	void moveLeftRight(int offset);
	void rotate();
	void checkOver();
	void drawdata();
	void displayOver();
	void changeBackground();
	bool gamefinish();
	int getwhichsave();
	void rankingshow();

	//数据成员

	int delay;
	int highestScore;
	bool update;//是否更新
	int rows, cols, leftMargin, topMargin, blockSize;
	int clearLines;
	int scores;
	int levels;
	int GAMEMODE;
	int saveNumber;
	int whetherChangerBG;
	IMAGE imgBG[3];
	IMAGE imgOVER;
	int BG;
	bool GameOver;
	bool finish;
	char bg[50];
	//地图信息 整数表示第几种形状
	vector<vector<int>>map;
	

	Block* curBlock;
	Block* nextBlock;//预告
	Block bakBlock;//备份方块

	fileManager* myFilemanager;
	musicManager mymusicManager;
};

