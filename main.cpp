#include"Tetris.h"
#include<iostream>
#include <stdio.h>
#include<conio.h>
#include<graphics.h>
#include <mmsystem.h>
#include"fileManager.h"
#include"UI.h"
#include"Button.h"
#pragma comment (lib,"winmm.lib")//���ؾ�̬��
using namespace std;

//while (peekmessage(&msg, EM_MOUSE) && msg.message == WM_LBUTTONDOWN) //������
//while (peekmessage(&msg, EM_KEY) && msg.message == WM_KEYDOWN)         //����

int main() {
	Tetris game(20, 10, 263, 133, 36);//���������ݺ��ڸĿ��Ա����С
	UI myUI;
	while (1) {

		cleardevice();
		myUI.startUI();
		int mode=myUI.getGamemode();

		game.play(mode,myUI.getsaveNumber());
	}
	

	return 0;
}