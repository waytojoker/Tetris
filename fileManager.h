#pragma once
#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<stdio.h>
#include"Tetris.h"
using namespace std;


class fileManager
{
public:
    friend class Tetris;
    struct user {     
        int score;
        int lines;
        char name[50]; 
        void createuser(int _score, int _lines, char _name[50]) {
            score = _score;
            lines = _lines;
            strcpy_s(name,_name);
        }
    }Users[25];
    struct save {
        int mode=0; 
        int score=0;
        int lines=0;
        int map[20][10];
        //¶¯Ì¬¿ªmap
    };
    void rankingManager( int _score, int _lines,char _name[50], int _mode);//ÅÅÃû
	int hsManager(int curscore,int _mode);
	void showUsers();
    void readSave(Tetris &game,int saveNumber);
    void writeSave(Tetris& game, int saveNumber);
    void clearsave(int saveNumber);
    int savemode(int saveNumber);
private:
	
	int highestscore;
	bool rankingchange;
	int gamemode;
};

