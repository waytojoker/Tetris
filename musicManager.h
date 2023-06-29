#pragma once
#include<iostream>
#include<stdio.h>
#include<mmsystem.h>
#include<graphics.h>
#pragma comment(lib,"winmm.lib")
class musicManager
{
public:
	musicManager();
	void musicPause();
	void musicResume();
	void musicStop();
	void musicPlay();
	void musicChange();
private:
	int BGM;
	char bgmresume[50];
	char bgmplay[50];
	char bgmpause[50];
	char bgmstop[50];
};

