#include "UI.h"
#include"fileManager.h"
#include<iostream>
#include<graphics.h>
#include<fstream>


UI::UI()
{
	gamemode = 0;
	saveNumber = 0;
}

void UI::startUI()
{
	bool flag = 0;
	initgraph(900, 900);
	//loadimage(0, "1.png");

	ExMessage msg;
	loadimage(0, "picture/UI/Cover1.png");
	while (1) {//�������		
		if (peekmessage(&msg, EM_MOUSE) && msg.message == WM_LBUTTONDOWN)break;

	}
	//չʾͼƬ
	loadimage(0, "picture/UI/Cover2.png");
	
	settextcolor(BLACK);
	setbkcolor(RGB(240, 240, 240));
	setlinecolor(BLACK);
	setfillcolor(RGB(230, 230, 230));
	Button start(35, 185, 200, 60, "��ʼ");
	Button loadsave(35, 285, 200, 60, "����浵");
	Button intro(35, 385, 200, 60, "˵��");
	Button developer(35, 485, 200, 60, "����");
	Button exitgame(35, 585, 200, 60, "�˳�");
	Button backbutton(700,800,100, 60, "����");

	Button mode1(35, 185, 400, 60, "��ͨģʽ������ԭ���𽥼��ٵ�����");
	Button mode2(35, 285, 400, 60, "��ģʽ��������");
	Button mode3(35, 385, 400, 60, "����ģʽ�����ּ�����");
	Button mode4(35, 485, 400, 60, "��");

	
	
	//��ʾ��ʼ
	loadimage(0, "picture/UI/Cover2.png");
	{start.show();
	loadsave.show();
	intro.show();
	developer.show();
	exitgame.show();
	}

	ExMessage m;
	while (true) {
		m = getmessage(EM_MOUSE);

		//��ʼ
		if (start.click(m)) {
			//���ؿ�ʼ
			{
				start.hide();
				loadsave.hide();
				intro.hide();
				developer.hide();
				exitgame.hide();
			}
			flag = 1;

			//ѡ��ģʽ
			{
				loadimage(0, "picture/UI/Cover2.png");
				mode1.show();
				mode2.show();
				mode3.show();
				mode4.show();
				backbutton.show();
				while (1) {
					m = getmessage(EM_MOUSE);

					if (mode1.click(m)) {
						gamemode = 1;
						break;
					}
					if (mode2.click(m)) {
						gamemode = 2;
						break;
					}
					if (mode3.click(m)) {
						gamemode = 3;
						break;
					}
					if (mode4.click(m)) {
						gamemode = 4;
						break;
					}
					if (backbutton.click(m)) {
						flag = 0;
						//����ģʽ
						{mode1.hide();
						mode2.hide();
						mode3.hide();
						mode4.hide();
						backbutton.hide();
						}
						
						//��ʾ��ʼ
						loadimage(0, "picture/UI/Cover2.png");
						{start.show();
						loadsave.show();
						intro.show();
						developer.show();
						exitgame.show();
						}

						break;
					}
					
				}

				//ѡ����ģʽ���˳�UI
				if (flag) {
					closegraph();
					return;
				}
			}
		}

		//����
		if (loadsave.click(m)) {

			//���ؿ�ʼ
			{
				start.hide();
				loadsave.hide();
				intro.hide();
				developer.hide();
				exitgame.hide();
			}

			loadimage(0, "picture/UI/origin.png");

			char savetext[5][50] = {
				"","","","","",
			};
			int SAVEMODE[5];
			for (int i = 1; i <= 4; i++) {
				int s=UIfileManager.savemode(i);
				SAVEMODE[i] = s;
				if (s == 0) {
					sprintf_s(savetext[i], "�浵%d     ��", i);
				}
				else {
					sprintf_s(savetext[i], "�浵%d    ģʽ%d", i,s);
				}
			}
			Button save1(35, 185, 400, 60, savetext[1]);
			Button save2(35, 285, 400, 60, savetext[2]);
			Button save3(35, 385, 400, 60, savetext[3]);
			Button save4(35, 485, 400, 60, savetext[4]);

			Button deletesave1(550, 185, 80, 60, "ɾ��");
			Button deletesave2(550, 285, 80, 60, "ɾ��");
			Button deletesave3(550, 385, 80, 60, "ɾ��");
			Button deletesave4(550, 485, 80, 60, "ɾ��");

			Button empty1(35, 185, 400, 60, "�浵1     ��");
			Button empty2(35, 285, 400, 60, "�浵2     ��");
			Button empty3(35, 385, 400, 60, "�浵3     ��");
			Button empty4(35, 485, 400, 60, "�浵4     ��");

			save1.show();
			save2.show();
			save3.show();
			save4.show();	
			deletesave1.show();
			deletesave2.show();
			deletesave3.show();
			deletesave4.show();
			backbutton.show();
			while (1) {
				m = getmessage(EM_MOUSE);
				if (deletesave1.click(m)) {
					UIfileManager.clearsave(1);
					save1.hide();
					empty1.hide();
					empty1.show();
				}
				if (deletesave2.click(m)) {
					UIfileManager.clearsave(2);
					save2.hide();
					empty2.hide();
					empty2.show();
				}
				if (deletesave3.click(m)) {
					UIfileManager.clearsave(3);
					save3.hide();
					empty3.hide();
					empty3.show();
				}
				if (deletesave4.click(m)) {
					UIfileManager.clearsave(4);
					save4.hide();
					empty4.hide();
					empty4.show();
				}
				if (save1.click(m)) {
					if (SAVEMODE[1] != 0) {
						gamemode = SAVEMODE[1];
						saveNumber = 1;
						return;
					}			
				}
				if (save2.click(m)) {
					if (SAVEMODE[2] != 0) {
						gamemode = SAVEMODE[2];
						saveNumber = 2;
						return;
					}
				}
				if (save3.click(m)) {
					if (SAVEMODE[3] != 0) {
						gamemode = SAVEMODE[3];
						saveNumber = 3;
						return;
					}
				}
				if (save4.click(m)) {
					if (SAVEMODE[4] != 0) {
						gamemode = SAVEMODE[4];
						saveNumber = 4;
						return;
					}
				}
				if (backbutton.click(m)) {
					//���ش浵
					{save1.hide();
					save2.hide();
					save3.hide();
					save4.hide();
					backbutton.hide();
					}

					//��ʾ��ʼ
					loadimage(0, "picture/UI/Cover2.png");
					{start.show();
					loadsave.show();
					intro.show();
					developer.show();
					exitgame.show();
					}

					break;
				}

			}

			if (flag) {
				cleardevice();
				return;
			}

		}

		//����
		if (developer.click(m)) {

			//���ؿ�ʼ
			{
			start.hide();
			loadsave.hide();
			intro.hide();
			developer.hide();
			exitgame.hide();
			}		

			loadimage(0, "picture/UI/Developer.png");
			backbutton.show();
			
			while (1) {
				m = getmessage(EM_MOUSE);
				if (backbutton.click(m)) {
					backbutton.hide();

					//��ʾ��ʼ
					loadimage(0, "picture/UI/Cover2.png");
					{start.show();
					loadsave.show();
					intro.show();
					developer.show();
					exitgame.show();
					}

					break;
				}
			}
		}

		//���
		if (intro.click(m)) {
			//���ؿ�ʼ
			{
				start.hide();
				loadsave.hide();
				intro.hide();
				developer.hide();
				exitgame.hide();
			}

			loadimage(0, "picture/UI/Intro.png");
			backbutton.show();
			//settextstyle(30, 0, "����");
			settextstyle(36, 0, "����");
			setbkmode(TRANSPARENT);

			outtextxy(200, 200, "ESC��P        ��ͣ");
			outtextxy(200, 250, "A / ��        ����");
			outtextxy(200, 300, "D / ��        ����");
			outtextxy(200, 350, "W / ��        ��ת");
			outtextxy(200, 400, "S / ��        �ٽ�");
			outtextxy(200, 450, "C         �л�����");
			outtextxy(200, 500, "V         �л�����");


			while (1) {
				m = getmessage(EM_MOUSE);
				if (backbutton.click(m)) {
					backbutton.hide();

					//��ʾ��ʼ
					loadimage(0, "picture/UI/Cover2.png");			
					{start.show();
					loadsave.show();
					intro.show();
					developer.show();
					exitgame.show();
					}

					break;
				}
			}
		}

		//�˳�
		if (exitgame.click(m))exit(0);
	
	}

	
	
}

int UI::getGamemode()
{
	return gamemode;
}

int UI::getsaveNumber()
{
	return saveNumber;
}


