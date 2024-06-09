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
#include <malloc.h>

typedef struct {
    int x;
    int y;
} Pointer;

#define BAR_LENGTH 40
#define WALL 0
#define SPACE 1
#define PLAYER 2
#define TREASURE 3
#define GIFT 4
#define PENALTY 5
#define MONSTER 6
#define MENU_LEFT_ALIGN 15
#define MENU_TOP_ALIGN 9
#define MENU_LINE_SPACE 3
#define SELECTION_BOX_LEFT_ALIGN 12
#define MAP_WIDTH 60
#define MAP_HEIGHT 30
#define NUM_GIFTS 7
#define NUM_PENALTY 5
#define EASY_MONSTER 5
#define NORMAL_MONSTER 7
#define HARD_MONSTER 9
#define RAND_STORE_CHANCE 0 // 변경 필요

// 원형함수
void getUserName();
void printArea();
void printMap();
void gameRule();
void menu();
void printMenu();
void switchMenu();
void runMenu(int);
void difficultyMenu();
void printDifficultyMenu();
void switchDifficultyMenu();
void runDifficultyMenu(int);
void printSelectionBox(int, int);
void eraseSelectionBox(int, int);
int gameStart();
void printProgressBar(int, int);
void printPlayer(Pointer*, int, int);
void movePlayer();
void moveMonster(Pointer*);
void printMonster();
void initBoard();
void initRandomPosition(Pointer*);
void initGameVariables();
void drawSideBox();
void eraseSideBox();
void favorableQuestion();
void eventPrint();
void revealTreasureDirection(int);
void recordAndEndOnTime(int);
void checkFlag();
void checkTreasure();
void checkGift();
void checkPenalty();
void checkObstacle();
int checkCollision(Pointer, Pointer);
void rand_store();
void penalty_func();
void penaltyPrint(int x);
void levelUp();
void startEasyGame();
void startNormalGame();
void startHardGame();
int checkGameEnd();
void endGame(int);
void calculateScore();
//void drawPlayer();
void slowPrint(unsigned long speed, const char* s);
void SetColor(int colorNum);
void gotoxy(int x, int y);
void CursorControl(bool flag);

int item_time = 0;
int gametime = 180;
int score = 0;
double playertick;
double monstertick;
int level = 1;
int endsignal;
int treasureFound = 0;
char name[10];
time_t start_time;
int monsterNum;
int questionNum = 0;
char map[MAP_HEIGHT][MAP_WIDTH];

Pointer player;
Pointer gift[NUM_GIFTS];
Pointer penalty[NUM_PENALTY];
Pointer monster[HARD_MONSTER];
Pointer treasure;