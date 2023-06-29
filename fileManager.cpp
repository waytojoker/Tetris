#include "fileManager.h"
#include<iostream>
#include<fstream>
#include<vector>
#include<stdio.h>
#include<iomanip>
#include<cstring>
#include"Button.h"
using namespace std;

//vector<user> users;



//����
void fileManager::rankingManager( int _score, int _lines,char _name[50], int _mode)
{
    char new_name[50];
    strcpy_s(new_name, _name);
    user tempuser;
    tempuser.createuser(_score, _lines, _name);
    //cout << "\n������û���";
    //cout << tempuser.score << " " << tempuser.lines << " " << tempuser.name << '\n';

    int filestart = (_mode - 1) * 5;//0,5,10,15
    int fileend = _mode * 5 - 1;
    gamemode = _mode;
    
    char filename[5][50];
    strcpy_s(filename[1], "ranking/ranking1.dat");
    strcpy_s(filename[2], "ranking/ranking2.dat");
    strcpy_s(filename[3], "ranking/ranking3.dat");
    strcpy_s(filename[4], "ranking/ranking4.dat");
   
    ///��ǰд��,1�μ���
    /*{
        for (int i = 0; i <= 20; i++) {
            Users[i].lines = 0;
            Users[i].score = 0;
            strcpy_s(Users[i].name,"Unknown player");
        }

        fstream fout(filename[1], ios::out | ios::binary);
        if (!fout.is_open()) {
            cerr << filename[1] << "��ʧ��" << endl;
        }
        for (int i = 0; i <= 4; i++)fout.write((const char*)&Users[i], sizeof(Users[i]));
        fout.close();


        fout.open(filename[2], ios::out | ios::binary);
        if (!fout.is_open()) {
            cerr << filename[2] << "��ʧ��" << endl;
        }
        for (int i = 0; i <= 4; i++)fout.write((const char*)&Users[i+5], sizeof(Users[i+5]));
        fout.close();


        fout.open(filename[3], ios::out | ios::binary);
        if (!fout.is_open()) {
            cerr << filename[3] << "��ʧ��" << endl;
        }
        for (int i = 0; i <= 4; i++)fout.write((const char*)&Users[i + 10], sizeof(Users[i + 10]));
        fout.close();


        fout.open(filename[4], ios::out | ios::binary);
        if (!fout.is_open()) {
            cerr << filename[4] << "��ʧ��" << endl;
        }
        for (int i = 0; i <= 4; i++)fout.write((const char*)&Users[i + 15], sizeof(Users[i + 15]));
        fout.close();
    }*/

    //�鿴�Ƿ��ʼ�����
    //showUsers();
    

    ifstream file_in(filename[_mode], ios::in |ios::binary);//�ļ���
    if (!file_in.is_open()) {
        cerr << "file_in��ʧ��\n";
    }

    //��ȡ5��
    for (int i = 0; i <= 4;i++) {
        file_in.read((char*)&Users[filestart + i], sizeof(Users[filestart + i]));
    }
    file_in.close();
    //showUsers();
    //�鿴�Ƿ�������
    //showUsers();

    //����
    for (int i = 0; i <= 4; i++) {
        if (Users[filestart + i].score < tempuser.score) {
            for (int j = 4; j >= i+1; j--) {
                Users[filestart + j] = Users[filestart + j - 1];
            }
            Users[filestart + i] = tempuser;
            break;
        }
    }

    //�鿴�Ƿ��������
    //showUsers();

    //�ƶ�ָ�뵽ָ��ģʽ����Ŀ�ʼ
    //file.seekp(sizeof(user) * filestart);
    
    ofstream file_out(filename[_mode], ios::out | ios::binary);
    if (!file_out.is_open()) {
        cerr << "file_out��ʧ��\n";
    }
    //д��5��
    for (int i = 0; i <= 4; i++) {
        file_out.write((const char*)&Users[filestart + i], sizeof(Users[filestart + i]));
    }

    file_out.close();

    //showUsers();

    loadimage(0, "picture/UI/origin.png");
    //�������
    settextcolor(BLACK);
    setbkcolor(RGB(240, 240, 240));
    setlinecolor(BLACK);
    setfillcolor(RGB(230, 230, 230));
    Button backbutton(700, 800, 100, 60, "����");
    backbutton.show();

    char ch_user[5][4][50];//number,score,lines,name
    /*string s1;
    char s2[50]="\0";
    s1 = s2;*/
   
    char name1[50] = "?";
    char name2[50] = "?";
    char name3[50] = "?";
    char name4[50] = "?";
    char name5[50] = "?";
    strcpy_s(name1, Users[filestart+0].name);
    strcpy_s(name2, Users[filestart + 1].name);
    strcpy_s(name3, Users[filestart + 2].name);
    strcpy_s(name4, Users[filestart + 3].name);
    strcpy_s(name5, Users[filestart + 4].name);
    for (int i = 0; i <= 4; i++) {
            sprintf_s(ch_user[i][0], sizeof(ch_user[i][0]), "%d", i+1);
            sprintf_s(ch_user[i][1], sizeof(ch_user[i][1]), "%d", Users[filestart+i].score);
            sprintf_s(ch_user[i][2], sizeof(ch_user[i][2]), "%d", Users[filestart + i].lines);
            //ch_user[i][2] = Users[filestart + i].name;
    }
    settextstyle(48, 0, "����");

    outtextxy(300,130,"���а�");
    int x = 100, y = 200;
    for (int i = 0; i <= 4; i++) {
        	for (int j = 0; j <= 2; j++) {
        		outtextxy(x+j*135,y+i*70,ch_user[i][j]);
        	}      		
    }
    outtextxy(x + 3 * 135, y + 0 * 70, name1);
    outtextxy(x + 3 * 135, y + 1 * 70, name2);
    outtextxy(x + 3 * 135, y + 2 * 70, name3);
    outtextxy(x + 3 * 135, y + 3 * 70, name4);
    outtextxy(x + 3 * 135, y + 4 * 70, name5);

    ExMessage m;
    while (1) {
        		m = getmessage(EM_MOUSE);
        		if (backbutton.click(m)) {
        			backbutton.hide();
        			cleardevice();
        			break;
        		}
    }
}

//��߷�
int fileManager::hsManager(int curscore,int _mode)
{
    string filename;
    if (_mode == 1)filename = "highest_score/hs1.dat";
    if (_mode == 2)filename = "highest_score/hs2.dat";
    if (_mode == 3)filename = "highest_score/hs3.dat";
    if (_mode == 4)filename = "highest_score/hs4.dat";

    fstream fin(filename,ios::in|ios::binary);
    if (!fin.is_open()) {
        cerr << filename << "��߷�д���ʧ��" << endl;
        highestscore = 0;
    }
    else {
        fin >> highestscore;
        if (curscore > highestscore)highestscore=curscore;
        
    }
    fin.close();

    fstream fout(filename, ios::out | ios::binary);
    if (!fout.is_open()) {
        cerr << filename << "��߷ֶ�ȡ��ʧ��" << endl;
        highestscore = 0;
    }
    fout<< highestscore;
    fout.close();

    return highestscore;
}

//����̨չʾ
void fileManager::showUsers()
{
    
    cout << "ģʽ��" << gamemode <<" "<< '\n';
    cout << setw(10) << "����" << setw(10) << "����" << "   " << "�û���" << '\n';
    for (int i = 0; i <= 4; i++) {
       cout <<setw(10)<< Users[(gamemode - 1) * 5 + i].score << setw(10) << Users[(gamemode - 1) * 5 + i].lines << "   " << Users[(gamemode - 1) * 5 + i].name << '\n';
    }
    cout << '\n';
}

//����
void fileManager::readSave(Tetris &game, int saveNumber)
{
    cout << "����save" << saveNumber << '\n';
    /*char filename1[50];
    sprintf_s(filename1, "save/1.txt");*/

    //string filename;
    char filename[50];
    sprintf_s(filename,"save/%d.dat",saveNumber );
    
    fstream file(filename, ios::in |ios::binary ); // �ļ���
    if (!file.is_open()) {
        cerr << "��ȡ��ʧ��\n";
    }
    save tempsave;
    file.read((char *)&tempsave,sizeof(tempsave));
    cout << "mode:" << tempsave.mode << " " << tempsave.score << " " << tempsave.lines << '\n';
    int rows = game.map.size();
    int cols = game.map[0].size();
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {

            cout << tempsave.map[i][j];
            game.map[i][j] = tempsave.map[i][j];
        }
        cout << '\n';
    }
    file.close();
}

//�浵
void fileManager::writeSave(Tetris& game, int saveNumber=0)//0,1,2,3
{
    cout << "����save" << saveNumber<<'\n';
    /*char filename[50];
    sprintf_s(filename, "save/%d.txt",saveNumber);*/

    //��ʼ����
    /*{
        save abc;
        abc.score = 0; abc.lines = 0; abc.mode = 0;
        for (int i = 0; i < 20; i++) {
            for(int j = 0; j < 10;j++){ 
                abc.map[i][j] = 0;
            }
        }
        string filename1 = "save/1.dat";
        fstream(filename1, ios::out);

    }*/
    char filename[50];
    sprintf_s(filename, "save/%d.dat", saveNumber);
    
    fstream file(filename,  ios::out|ios::binary );//�ļ���
    
    if (!file.is_open()) {
        cerr << "д���ʧ��\n";
    }

    
    save tempsave;
    tempsave.lines = game.clearLines;
    tempsave.mode = game.GAMEMODE;
    tempsave.score = game.scores;

    //copy(game.map.begin(), game.map.end() + 1, tempsave.map.begin());���ܴ�vector
    int rows=game.map.size();
    int cols = game.map[0].size();
   /* tempsave.map = new int* [rows];
    for (int i = 0; i < rows; i++) {
        tempsave.map[i] = new int[cols];
    }*/
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            tempsave.map[i][j]=0;
        }
    }
    cout << "mode:"<<tempsave.mode << " " << tempsave.score << " " << tempsave.lines << '\n';
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            tempsave.map[i][j]=game.map[i][j];
        }
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {

            cout << tempsave.map[i][j];
        }
        cout << '\n';
    }
    //�����ͼ������ȷ����֪��Ϊʲôû���ȥ
    file.write((const char*)&tempsave,sizeof(tempsave));

    file.close();
}

//��մ浵
void fileManager::clearsave(int saveNumber=1)
{
    char filename[50];
    sprintf_s(filename, "save/%d.dat", saveNumber);
    
    save temp;
    temp.mode = 0;
    temp.score = 0;
    temp.lines = 0;
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 10; j++) {
            temp.map[i][j] = 0;
        }
    }

    fstream file(filename, ios::out | ios::binary);//�ļ���
    if (!file.is_open()) {
        cerr << "��մ浵��ʧ��\n";
    }
    file.write((const char*)&temp, sizeof(temp));
    file.close();
}

//�鿴�浵ģʽ
int fileManager::savemode(int saveNumber)
{
    char filename[50];
    sprintf_s(filename, "save/%d.dat", saveNumber);

    fstream file(filename, ios::in | ios::binary); // �ļ���
    if (!file.is_open()) {
        cerr << "��ȡ��ʧ��\n";
    }
    save tempsave;
    file.read((char*)&tempsave, sizeof(tempsave));
    file.close();
    return tempsave.mode;
}


//�������쳣: ��ȡ����Ȩ�޳�ͻ��
//** std::vector<fileManager::user, std::allocator<fileManager::user> >::operator[] * *(...) ���� 0x1BED25DDA10��