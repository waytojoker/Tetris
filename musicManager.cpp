#include<iostream>
#include<graphics.h>
#include"musicManager.h"
#include<stdio.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")
musicManager::musicManager()
{
	BGM = 1;
}

void musicManager::musicPause()
{
	sprintf_s(bgmpause, "pause auto/bgm/%d.mp3", BGM);
	mciSendString(bgmpause, 0, 0, 0);
}

void musicManager::musicResume()
{
	sprintf_s(bgmresume, "resume auto/bgm/%d.mp3", BGM);
	mciSendString(bgmresume, 0, 0, 0);
}

void musicManager::musicStop()
{
	sprintf_s(bgmstop, "stop auto/bgm/%d.mp3", BGM);
	mciSendString(bgmstop, 0, 0, 0);
}

void musicManager::musicPlay()
{
	sprintf_s(bgmplay, "play auto/bgm/%d.mp3 repeat", BGM);
	mciSendString(bgmplay, 0, 0, 0);
}

void musicManager::musicChange()
{
	sprintf_s(bgmstop, "stop auto/bgm/%d.mp3", BGM);
	mciSendString(bgmstop, 0, 0, 0);
	BGM++;
	if (BGM > 4)BGM = 1;
	sprintf_s(bgmplay, "play auto/bgm/%d.mp3 repeat", BGM);
	mciSendString(bgmplay, 0, 0, 0);
}
