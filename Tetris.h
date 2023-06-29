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
	void init(int _mode);//��ʼ��
	void play(int _mode,int _save);//��ʼ��Ϸ
	void input2(bool& rotateflag, int& dx);
	//void solidify(vector<vector<int>>& map);
	void showMap();
	
private:

	//���ݳ�Ա����
	void keyEvent();
	void updateWindow();
	void printNecessaryMessage();
	int getDelay();//���ؾ�����һ�ε������������ʱ�䣬��һ�η���0
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

	//���ݳ�Ա

	int delay;
	int highestScore;
	bool update;//�Ƿ����
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
	//��ͼ��Ϣ ������ʾ�ڼ�����״
	vector<vector<int>>map;
	

	Block* curBlock;
	Block* nextBlock;//Ԥ��
	Block bakBlock;//���ݷ���

	fileManager* myFilemanager;
	musicManager mymusicManager;
};

