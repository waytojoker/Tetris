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

	//置0
	for (int i = 0; i < rows; i++) {
		vector<int> mapRow;
		for (int j = 0; j < cols; j++) {
			mapRow.push_back(0);
		}
		map.push_back(mapRow);
	}
	BG = 1;
}

//初始化
void Tetris::init(int _mode=1)//初始化
{
	whetherChangerBG = 0;
	GAMEMODE = _mode;
	clearLines = 0;
	scores = 0;
	if (_mode == 3)CURSPEED = SPEEDMODEL[7];
	delay = CURSPEED;

	//随机种子
	srand(time(NULL));
	sprintf_s(bg, "picture/bg/ai%d.png", BG);
	loadimage(&imgBG[0],bg);//目前有ai 1,2,3系列
	loadimage(&imgOVER, "res/over.png");
	int _height = imgBG[0].getheight();
	int _width = imgBG[0].getwidth();
	initgraph(_height, _width, EW_DBLCLKS);
	ExMessage msg;
	loadimage(0, "picture/UI/Cover1.png");

	//左键继续
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

//主游戏
void Tetris::play(int _mode,int _save=0)
{
	saveNumber = _save;
	//初始化
	init(_mode);

	//读档
	if(_save!=0)myFilemanager->readSave(*this,_save);

	nextBlock = new Block;
	curBlock = nextBlock;
	nextBlock = new Block;

	int timer = 0;
	
	if (_save != 0) {//载入后先更新一次画面
		//更新画面
		BeginBatchDraw();
		updateWindow();
		printNecessaryMessage();
		EndBatchDraw();
	}
	//主循环
	while (1) {

		//输入
		keyEvent();
		/*sprintf_s(bgmresume, "resume auto/bgm/%d.mp3", BGM);
		mciSendString(bgmresume, 0, 0, 0);*/
		mymusicManager.musicResume();
		//渲染画面，要设定多少秒渲染一次
		timer += getDelay();
		if (timer > delay) {
			timer = 0;
			drop();
			update = 1;

		}
		if (update) {
			update = 0;
				
			//更新画面
			BeginBatchDraw();
			updateWindow();
			printNecessaryMessage();
			EndBatchDraw();

			//清行
			clearLine();
		}
		checkOver();
		if (GameOver) {
			//保存分数
			displayOver();

			//存储name
			char tempname[50];
			InputBox(tempname, 50, "昵称");
			
			myFilemanager->hsManager(scores,GAMEMODE);
			system("cls");
			myFilemanager->rankingManager( scores, clearLines,tempname, GAMEMODE);

			//存档置空
			if (_save != 0) myFilemanager->clearsave(_save);

			/*rankingshow();*/

			int isOK = MessageBox(GetHWnd(), "是否要重新开始本模式游戏", "Tetris", MB_OKCANCEL);
			if (isOK == IDOK) {
				cleardevice();
				init();
			}else{
				return;
			}
			
		}
	}

}

//优化后的输入
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

			isOK = MessageBox(GetHWnd(), "ESC或P     暂停 \nA / ←        左移\nD / →        右移\nW / ↑         旋转\nS / ↓           速降\nC        切换音乐\nV        切换背景\n\n是否保存并退出？\n", "已暂停", MB_OKCANCEL);
			if (isOK == IDOK) {
				//存档
				//showMap();
				int mysave=getwhichsave();
				myFilemanager->writeSave(*this, mysave);
				exit(0);
			}
			else {
				isOK = MessageBox(GetHWnd(), "是否不保存退出？\n111", "已暂停", MB_OKCANCEL);
				if (isOK == IDOK) {
					exit(0);
				}
				else {
					MessageBox(GetHWnd(), "点下方或按下ESC以继续", "已暂停", MB_OK);//可能改动功能
				}

			}

			break;
		}
	}
}

//数字化地图，用于测试
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

//键盘读入
void Tetris::keyEvent()
{
	//时间没到30ms也能渲染，提高流畅度
	bool rotateflag = 0;
	int dx = 0;

	input2(rotateflag, dx);


	if (rotateflag) {
		//实现
		rotate();
		update = true;
	}
	if (dx != 0) {
		moveLeftRight(dx);
		update = true;
	}

}

//渲染
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
	nextBlock->draw(700, 150);//预测方块的位置
	
}

//打印必要信息
void Tetris::printNecessaryMessage()
{
	setbkmode(TRANSPARENT);
	settextstyle(30, 0, "黑体");
	outtextxy(300, 50, "press ESC to pause");
	drawdata();
	settextstyle(50, 0, "黑体");
	outtextxy(700, 580, "TETRIS");
}

//返回延迟大小，上一次调用和本次调用的时间间隔
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

//方块的下落
void Tetris::drop()
{
	bakBlock = *(curBlock);
	curBlock->drop();
	if (curBlock->blockInMap(map) == 0) {

		//方块固化
		bakBlock.solidify(map);

		delete curBlock;
		curBlock = nextBlock;
		nextBlock = new Block;

	}
	if (GAMEMODE == 2)CURSPEED = SPEEDMODEL[1];
	if (GAMEMODE == 3)CURSPEED = SPEEDMODEL[7];
	delay = CURSPEED;
}

//清行
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
			map[k][j] = map[i][j];//边扫边存
		}
		if (count < cols)k--;
		else {
			lines++;
		}
	}
	if (lines > 0) {
		//计算得分
		int addScore[4] = { 10,25,45,70 };
		clearLines += lines;
		scores += addScore[lines - 1];
		//换BG
		whetherChangerBG += lines;
		if (whetherChangerBG >= 10) {
			whetherChangerBG -= 10;
			changeBackground();
		}
		//音效
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

//左右移动
void Tetris::moveLeftRight(int offset)
{
	bakBlock = *curBlock;
	curBlock->moveLeftOrRight(offset);

	if (!curBlock->blockInMap(map)) {//不对就还原
		*curBlock = bakBlock;
	}
}

//旋转
void Tetris::rotate()
{
	if (curBlock->getBlockType() == 7)return;

	bakBlock = *curBlock;//备份
	curBlock->rotate();//旋转

	if (!curBlock->blockInMap(map)) {//不对就还原
		*curBlock = bakBlock;
	}

}

//检测结束
void Tetris::checkOver()
{
	GameOver =( curBlock->blockInMap(map) == false);

}

//绘制数据
void Tetris::drawdata()
{
	char scoreText[32],clearlineText[32],speedText[32],levelText[32],hsText[32];
	sprintf_s(scoreText, sizeof(scoreText), "%d", scores);
	sprintf_s(clearlineText, sizeof(clearlineText), "%d", clearLines);
	sprintf_s(speedText, sizeof(speedText), "%d", CURSPEED);
	sprintf_s(levelText, sizeof(levelText), "%d", levels);
	sprintf_s(hsText, sizeof(levelText), "%d", highestScore);
	settextstyle(30, 0, "黑体");
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

//结束界面
void Tetris::displayOver()
{
	/*sprintf_s(bgmstop, "stop auto/bgm/%d.mp3", BGM);
	mciSendString(bgmstop, 0, 0, 0);*/
	mymusicManager.musicStop();
	putimage(262, 361, &imgOVER);
	mciSendString("play res/tie.mp3", 0, 0, 0);

}

//换背景
void Tetris::changeBackground()
{
	BG++;
	if (BG > 3)BG = 1;//可改变BG的上限
	sprintf_s(bg, "picture/bg/ai%d.png", BG);
	loadimage(&imgBG[0], bg);//目前有ai 1,2,3系列
}

bool Tetris::gamefinish()
{
	return finish;
}

//获取要存第几个存档
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
			sprintf_s(savetext[i], "存档%d     空", i);
		}
		else {
			sprintf_s(savetext[i], "存档%d    模式%d", i, s);
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
	//左键继续
	settextcolor(BLACK);
	setbkcolor(RGB(240, 240, 240));
	setlinecolor(BLACK);
	setfillcolor(RGB(230, 230, 230));
	Button backbutton(700, 800, 100, 60, "返回");
	backbutton.show();
 
	settextstyle(70, 0, "黑体");
	outtextxy(150, 300, "请在控制台查看排名");

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
//	//文件操作
//	fstream file(filename, ios::in | ios::out);//文件打开
//	if (!file.is_open()) {
//		cerr << "file打开失败\n";
//	}
//	//移动指针到指定模式区域的开始
//	file.seekp(sizeof(user) * filestart);
//	//读取
//	for (int i = 0; i <= 4; i++) {
//		file.read((char*)&tempusers[i], sizeof(tempusers[i]));
//	}
//	file.close();
//
//
//	
//	settextstyle(70, 0, "黑体");
//	int x = 200, y = 200;
//	for (int i = 0; i <= 4; i++) {
//		for (int j = 0; j <= 2; j++) {
//			outtextxy(x+j*135,y+i*70,ch_user[i][j]);
//		}
//		
//	}
//
//	//左键继续
//	settextcolor(BLACK);
//	setbkcolor(RGB(240, 240, 240));
//	setlinecolor(BLACK);
//	setfillcolor(RGB(230, 230, 230));
//	Button backbutton(700, 800, 100, 60, "返回");
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


