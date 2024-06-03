#pragma once
#pragma comment(lib, "winmm.lib")

#define _CRT_SECURE_NO_WARNINGS

//헤더파일
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <stdbool.h>
#include <stddef.h>
#include <mmsystem.h>
#include <process.h>
#include <wchar.h>
#include <locale.h>

//기호상수
#define MENU_LEFT_ALIGN 15
#define MENU_TOP_ALIGN 9
#define MENU_LINE_SPACE 3
#define SELECTION_BOX_LEFT_ALIGN 12

#define MAP_WIDTH 60
#define MAP_HEIGHT 30
#define NUM_GIFTS 10
#define NUM_PENALTY 5
#define NUM_MONSTER 3

#define EASY_GIFT 5
#define EASY_PENALTY 3
#define EASY_MONSTER 3

#define NORMAL_GIFT 7
#define NORMAL_PENALTY 5
#define NORMAL_MONSTER 5

#define HARD_GIFT 9
#define HARD_PENALTY 7
#define HARD_MONSTER 7

#define PLAYTIME 180
#define rand_store_chance 5

// 원형함수
void printArea();
void getUserName();
void gameRule();
void menu();
void printMenu();
void switchMenu();
void runMenu(int menuNum);
void difficultyMenu();
void printDifficultyMenu();
void switchDifficultyMenu();
void runDifficultyMenu(int level);
void printSelectionBox(int x, int y);
void eraseSelectionBox(int x, int y);
void movePlayer();
void moveMonster();

void recordAndEndOnTime(int x);
void option();
void rand_store();
void penalty_func();
int checkGameEnd();
void endGame(int result);
void initializeBoard();
void printThings();
void checkobstacle();
void checkFlag();
void calculateScore();
void levelUp();
void startEasyGame();
void startNormalGame();
void startHardGame();
void checkErasing(int x, int y);
void drawFavorable();
void eraseFavorable();

//API
void slowPrint(unsigned long speed, const char* s);
void SetColor(int colorNum);
void gotoxy(int x, int y);
void CursorControl(bool flag);

// 변수
int gametime = 180;//게임 시간
int score = 0;
double playertick;
double monstertick;
int level = 1;
int endsignal;
char name[10]; // 사용자 이름 입력받기
bool gameRunning = true;
time_t start_time;

int monsterNum;
int giftNum;
int penaltyNum;

int player[1][2] = { 0 };
int treasure[1][2] = { 0 };
int gift[HARD_GIFT][2] = { 0 };
int penalty[HARD_PENALTY][2] = { 0 };
int monster[HARD_MONSTER][2] = { 0 };

int questionNum = 0;