#pragma once
#include<iostream>
#include<graphics.h>
#include"Button.h"
#include"fileManager.h"
class UI
{
public:
	UI();
	void startUI();
	int getGamemode();
	int getsaveNumber();
private:
	IMAGE imgCOVER;
	IMAGE imgSTARTUI;
	int gamemode;
	int saveNumber;//0´ú±í²»¶Áµµ
	fileManager UIfileManager;
};

