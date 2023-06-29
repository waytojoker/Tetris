#include "Tetris.h"
#include"Block.h"
#include"fileManager.h"
#include"musicManager.h"
#include"Button.h"
#include<iostream>
#include<vector>
#include<fstream>
#include<time.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")

using namespace std;
const int SPEED_NORMAL = 400;
const int SPEED_QUICK = 30;
ExMessage msg;
int SPEEDMODEL[8] = {0,400,350,300,250,200,150,100};
int CURSPEED = SPEEDMODEL[1];
char bgmresume[50];
char bgmplay[50];
char bgmpause[50];
char bgmstop[50];
struct user {
	int score;
	int lines;
	char name[50] ;
};
Tetris::Tetris(int rows, int columns, int left, int top, int blockSize)
{
	myFilemanager = new fileManager;
	this->rows = rows;
	this->cols = columns;
	this->leftMargin = left;
	this->topMargin = top;
	this->blockSize = blockSize;

	//��0
	for (int i = 0; i < rows; i++) {
		vector<int> mapRow;
		for (int j = 0; j < cols; j++) {
			mapRow.push_back(0);
		}
		map.push_back(mapRow);
	}
	BG = 1;
}

//��ʼ��
void Tetris::init(int _mode=1)//��ʼ��
{
	whetherChangerBG = 0;
	GAMEMODE = _mode;
	clearLines = 0;
	scores = 0;
	if (_mode == 3)CURSPEED = SPEEDMODEL[7];
	delay = CURSPEED;

	//�������
	srand(time(NULL));
	sprintf_s(bg, "picture/bg/ai%d.png", BG);
	loadimage(&imgBG[0],bg);//Ŀǰ��ai 1,2,3ϵ��
	loadimage(&imgOVER, "res/over.png");
	int _height = imgBG[0].getheight();
	int _width = imgBG[0].getwidth();
	initgraph(_height, _width, EW_DBLCLKS);
	ExMessage msg;
	loadimage(0, "picture/UI/Cover1.png");

	//�������
	while (1) {		
		if (peekmessage(&msg, EM_MOUSE) && msg.message == WM_LBUTTONDOWN)break;

	}

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			map[i][j] = 0;
		}
	}

	GameOver = false;
	/*sprintf_s(bgmplay, "play auto/bgm/%d.mp3 repeat", BGM);
	mciSendString(bgmplay, 0, 0, 0);*/
	mymusicManager.musicPlay();
	highestScore = myFilemanager->hsManager(0,GAMEMODE);
}

//����Ϸ
void Tetris::play(int _mode,int _save=0)
{
	saveNumber = _save;
	//��ʼ��
	init(_mode);

	//����
	if(_save!=0)myFilemanager->readSave(*this,_save);

	nextBlock = new Block;
	curBlock = nextBlock;
	nextBlock = new Block;

	int timer = 0;
	
	if (_save != 0) {//������ȸ���һ�λ���
		//���»���
		BeginBatchDraw();
		updateWindow();
		printNecessaryMessage();
		EndBatchDraw();
	}
	//��ѭ��
	while (1) {

		//����
		keyEvent();
		/*sprintf_s(bgmresume, "resume auto/bgm/%d.mp3", BGM);
		mciSendString(bgmresume, 0, 0, 0);*/
		mymusicManager.musicResume();
		//��Ⱦ���棬Ҫ�趨��������Ⱦһ��
		timer += getDelay();
		if (timer > delay) {
			timer = 0;
			drop();
			update = 1;

		}
		if (update) {
			update = 0;
				
			//���»���
			BeginBatchDraw();
			updateWindow();
			printNecessaryMessage();
			EndBatchDraw();

			//����
			clearLine();
		}
		checkOver();
		if (GameOver) {
			//�������
			displayOver();

			//�洢name
			char tempname[50];
			InputBox(tempname, 50, "�ǳ�");
			
			myFilemanager->hsManager(scores,GAMEMODE);
			system("cls");
			myFilemanager->rankingManager( scores, clearLines,tempname, GAMEMODE);

			//�浵�ÿ�
			if (_save != 0) myFilemanager->clearsave(_save);

			/*rankingshow();*/

			int isOK = MessageBox(GetHWnd(), "�Ƿ�Ҫ���¿�ʼ��ģʽ��Ϸ", "Tetris", MB_OKCANCEL);
			if (isOK == IDOK) {
				cleardevice();
				init();
			}else{
				return;
			}
			
		}
	}

}

//�Ż��������
void Tetris::input2(bool& rotateflag, int& dx)
{
	int isOK;
	while (peekmessage(&msg, EM_KEY) && msg.message == WM_KEYDOWN) {
		switch (msg.vkcode) {
		case 'V':
			changeBackground();
			break;
		case 'C':
			mymusicManager.musicChange();
			break;
		case 'W':
		case VK_UP:
			rotateflag = 1;
			break;
		case 'S':
		case VK_DOWN:
			delay = SPEED_QUICK;
			break;
		case 'A':
		case VK_LEFT:
			dx = -1;
			break;
		case 'D':
		case VK_RIGHT:
			dx = 1;
			break;
		case VK_ESCAPE:
		case 'P':
			mymusicManager.musicPause();

			isOK = MessageBox(GetHWnd(), "ESC��P     ��ͣ \nA / ��        ����\nD / ��        ����\nW / ��         ��ת\nS / ��           �ٽ�\nC        �л�����\nV        �л�����\n\n�Ƿ񱣴沢�˳���\n", "����ͣ", MB_OKCANCEL);
			if (isOK == IDOK) {
				//�浵
				//showMap();
				int mysave=getwhichsave();
				myFilemanager->writeSave(*this, mysave);
				exit(0);
			}
			else {
				isOK = MessageBox(GetHWnd(), "�Ƿ񲻱����˳���\n111", "����ͣ", MB_OKCANCEL);
				if (isOK == IDOK) {
					exit(0);
				}
				else {
					MessageBox(GetHWnd(), "���·�����ESC�Լ���", "����ͣ", MB_OK);//���ܸĶ�����
				}

			}

			break;
		}
	}
}

//���ֻ���ͼ�����ڲ���
void Tetris::showMap()
{
	cout << '\n';
	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[i].size(); j++) {
			cout << map[i][j];
		}
		cout << '\n';
	}
	cout << '\n';
}

//���̶���
void Tetris::keyEvent()
{
	//ʱ��û��30msҲ����Ⱦ�����������
	bool rotateflag = 0;
	int dx = 0;

	input2(rotateflag, dx);


	if (rotateflag) {
		//ʵ��
		rotate();
		update = true;
	}
	if (dx != 0) {
		moveLeftRight(dx);
		update = true;
	}

}

//��Ⱦ
void Tetris::updateWindow()
{
	putimage(0, 0, &imgBG[0]);
	
	IMAGE** imgs = Block::getImages();
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (map[i][j] == 0)continue;//

			int x = j * blockSize + leftMargin;
			int y = i * blockSize + topMargin;
			putimage(x, y, imgs[map[i][j] - 1]);
			//FlushBatchDraw();
		}
	}

	curBlock->draw(leftMargin, topMargin);
	nextBlock->draw(700, 150);//Ԥ�ⷽ���λ��
	
}

//��ӡ��Ҫ��Ϣ
void Tetris::printNecessaryMessage()
{
	setbkmode(TRANSPARENT);
	settextstyle(30, 0, "����");
	outtextxy(300, 50, "press ESC to pause");
	drawdata();
	settextstyle(50, 0, "����");
	outtextxy(700, 580, "TETRIS");
}

//�����ӳٴ�С����һ�ε��úͱ��ε��õ�ʱ����
int Tetris::getDelay()
{
	static unsigned long long lastTime = 0;
	unsigned long long currentTime = GetTickCount();
	if (lastTime == 0) {
		lastTime = currentTime;
		return 0;
	}
	else {
		int ret = (currentTime - lastTime);
		lastTime = currentTime;
		return ret;
	}


}

//���������
void Tetris::drop()
{
	bakBlock = *(curBlock);
	curBlock->drop();
	if (curBlock->blockInMap(map) == 0) {

		//����̻�
		bakBlock.solidify(map);

		delete curBlock;
		curBlock = nextBlock;
		nextBlock = new Block;

	}
	if (GAMEMODE == 2)CURSPEED = SPEEDMODEL[1];
	if (GAMEMODE == 3)CURSPEED = SPEEDMODEL[7];
	delay = CURSPEED;
}

//����
void Tetris::clearLine()
{
	int lines = 0;
	int k = rows - 1;
	for (int i = rows - 1; i > 0; i--) {

		int count = 0;
		for (int j = 0; j < cols; j++) {
			if (map[i][j]) {
				count++;
			}
			map[k][j] = map[i][j];//��ɨ�ߴ�
		}
		if (count < cols)k--;
		else {
			lines++;
		}
	}
	if (lines > 0) {
		//����÷�
		int addScore[4] = { 10,25,45,70 };
		clearLines += lines;
		scores += addScore[lines - 1];
		//��BG
		whetherChangerBG += lines;
		if (whetherChangerBG >= 10) {
			whetherChangerBG -= 10;
			changeBackground();
		}
		//��Ч
		mciSendString("play res/damage.mp3", 0, 0, 0);
		update = true;
		if (GAMEMODE == 1) {
			levels = clearLines / 10+1;
				if (levels > 7)levels = 7;
			CURSPEED = SPEEDMODEL[levels];
		}
		if (GAMEMODE == 2) {
			levels = 1;
			CURSPEED = 400;
		}
		if (GAMEMODE == 3) {
			levels = 7;
			CURSPEED = 100;
		}
		if (GAMEMODE == 4) {
			levels++;
			if (levels > 7) {
				levels = 1;
			}
			CURSPEED = SPEEDMODEL[levels];
		}
	}
}

//�����ƶ�
void Tetris::moveLeftRight(int offset)
{
	bakBlock = *curBlock;
	curBlock->moveLeftOrRight(offset);

	if (!curBlock->blockInMap(map)) {//���Ծͻ�ԭ
		*curBlock = bakBlock;
	}
}

//��ת
void Tetris::rotate()
{
	if (curBlock->getBlockType() == 7)return;

	bakBlock = *curBlock;//����
	curBlock->rotate();//��ת

	if (!curBlock->blockInMap(map)) {//���Ծͻ�ԭ
		*curBlock = bakBlock;
	}

}

//������
void Tetris::checkOver()
{
	GameOver =( curBlock->blockInMap(map) == false);

}

//��������
void Tetris::drawdata()
{
	char scoreText[32],clearlineText[32],speedText[32],levelText[32],hsText[32];
	sprintf_s(scoreText, sizeof(scoreText), "%d", scores);
	sprintf_s(clearlineText, sizeof(clearlineText), "%d", clearLines);
	sprintf_s(speedText, sizeof(speedText), "%d", CURSPEED);
	sprintf_s(levelText, sizeof(levelText), "%d", levels);
	sprintf_s(hsText, sizeof(levelText), "%d", highestScore);
	settextstyle(30, 0, "����");
	setbkmode(TRANSPARENT);
	outtextxy(700, 350, "score");
	outtextxy(700, 380, "lines");
	outtextxy(700, 410, "speeds");
	outtextxy(700, 440, "levels");
	outtextxy(650, 500, "highestScore");
	outtextxy(800, 350, scoreText);
	outtextxy(800, 380, clearlineText);
	outtextxy(800, 410, speedText);
	outtextxy(800, 440, levelText);
	outtextxy(830, 500, hsText);
}

//��������
void Tetris::displayOver()
{
	/*sprintf_s(bgmstop, "stop auto/bgm/%d.mp3", BGM);
	mciSendString(bgmstop, 0, 0, 0);*/
	mymusicManager.musicStop();
	putimage(262, 361, &imgOVER);
	mciSendString("play res/tie.mp3", 0, 0, 0);

}

//������
void Tetris::changeBackground()
{
	BG++;
	if (BG > 3)BG = 1;//�ɸı�BG������
	sprintf_s(bg, "picture/bg/ai%d.png", BG);
	loadimage(&imgBG[0], bg);//Ŀǰ��ai 1,2,3ϵ��
}

bool Tetris::gamefinish()
{
	return finish;
}

//��ȡҪ��ڼ����浵
int Tetris::getwhichsave()
{
	settextcolor(BLACK);
	setbkcolor(RGB(240, 240, 240));
	setlinecolor(BLACK);
	setfillcolor(RGB(230, 230, 230));
	loadimage(0, "picture/UI/origin.png");

	char savetext[5][50] = {
		"","","","","",
	};
	int SAVEMODE[5];
	for (int i = 1; i <= 4; i++) {
		int s = myFilemanager->savemode(i);
		SAVEMODE[i] = s;
		if (s == 0) {
			sprintf_s(savetext[i], "�浵%d     ��", i);
		}
		else {
			sprintf_s(savetext[i], "�浵%d    ģʽ%d", i, s);
		}
	}
	Button save1(35, 185, 400, 60, savetext[1]);
	Button save2(35, 285, 400, 60, savetext[2]);
	Button save3(35, 385, 400, 60, savetext[3]);
	Button save4(35, 485, 400, 60, savetext[4]);

	save1.show();
	save2.show();
	save3.show();
	save4.show();

	ExMessage m;
	while (1) {
		m = getmessage(EM_MOUSE);

		if (save1.click(m))return 1;
		if (save2.click(m))return 2;
		if (save3.click(m))return 3;
		if (save4.click(m))return 4;
	}
}

void Tetris::rankingshow()
{
	int filestart = (GAMEMODE - 1) * 5;//0,5,10,15
	loadimage(0, "picture/UI/origin.png");
	//�������
	settextcolor(BLACK);
	setbkcolor(RGB(240, 240, 240));
	setlinecolor(BLACK);
	setfillcolor(RGB(230, 230, 230));
	Button backbutton(700, 800, 100, 60, "����");
	backbutton.show();
 
	settextstyle(70, 0, "����");
	outtextxy(150, 300, "���ڿ���̨�鿴����");

	ExMessage m;
	while (1) {
		m = getmessage(EM_MOUSE);
		if (backbutton.click(m)) {
			backbutton.hide();			
			break;
		}
	}
	
}

//void Tetris::rankingshow()
//{
//	loadimage(0, "picture/UI/origin.png");
//	char ch_user[5][4][50];//number,score,lines,name
//	user tempusers[5];
//	int filestart = (GAMEMODE - 1) * 5;//0,5,10,15
//	int fileend = GAMEMODE * 5 - 1;
//	string filename;
//	filename = "ranking/rank.txt";
//
//	//�ļ�����
//	fstream file(filename, ios::in | ios::out);//�ļ���
//	if (!file.is_open()) {
//		cerr << "file��ʧ��\n";
//	}
//	//�ƶ�ָ�뵽ָ��ģʽ����Ŀ�ʼ
//	file.seekp(sizeof(user) * filestart);
//	//��ȡ
//	for (int i = 0; i <= 4; i++) {
//		file.read((char*)&tempusers[i], sizeof(tempusers[i]));
//	}
//	file.close();
//
//
//	
//	settextstyle(70, 0, "����");
//	int x = 200, y = 200;
//	for (int i = 0; i <= 4; i++) {
//		for (int j = 0; j <= 2; j++) {
//			outtextxy(x+j*135,y+i*70,ch_user[i][j]);
//		}
//		
//	}
//
//	//�������
//	settextcolor(BLACK);
//	setbkcolor(RGB(240, 240, 240));
//	setlinecolor(BLACK);
//	setfillcolor(RGB(230, 230, 230));
//	Button backbutton(700, 800, 100, 60, "����");
//	backbutton.show();
//	ExMessage m;
//	while (1) {
//		m = getmessage(EM_MOUSE);
//		if (backbutton.click(m)) {
//			backbutton.hide();
//			cleardevice();
//			break;
//		}
//	}
//	
//	return;
//}


