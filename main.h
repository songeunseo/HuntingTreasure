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

//기호상수
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

#define PLAYTIME 180
#define RAND_STORE_CHANCE 0 // 변경 필요

char map[MAP_HEIGHT][MAP_WIDTH];
Pointer player;
Pointer gift[NUM_GIFTS];
Pointer penalty[NUM_PENALTY];
Pointer monster[HARD_MONSTER];
Pointer treasure;

// 원형함수
void getUserName();
void printArea();
void printMap();

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

int gameStart();
void printProgressBar(int elapsed, int total);
void printPlayer(Pointer* pos, int dx, int dy);
void movePlayer();
void moveMonster(Pointer* monster);
void printMonster();

void initBoard();
void initRandomPosition(Pointer* object);
void initTick();
void initGameVariables();

//void printThings();


void drawSideBox();
void eraseSideBox();
void favorableQuestion();
void eventPrint();
void revealTreasureDirection(int i);

void recordAndEndOnTime(int x);

void checkFlag();
void checkTreasure();
void checkGift();
void checkPenalty();
void checkObstacle();
int checkCollision(Pointer pos1, Pointer pos2);
void checkErasing(int x, int y);

void rand_store();
void penalty_func();
void penaltyPrint(int x);

void levelUp();
void startEasyGame();
void startNormalGame();
void startHardGame();

int checkGameEnd();
void endGame(int result);

//void printAtPosition(int position[2], const char* symbol, int color);
void calculateScore();
void printCentered(const char* text[], int numLines, int yOffset);

//API
void slowPrint(unsigned long speed, const char* s);
void SetColor(int colorNum);
void gotoxy(int x, int y);
void CursorControl(bool flag);
void getConsoleSize(int* width, int* height);

// 변수
int item_time = 0;
int gametime = 180;//게임 시간
int score = 0;
double playertick;
double monstertick;
int level = 1;
int endsignal;
int treasureFound = 0;
char name[10]; // 사용자 이름 입력받기
bool gameRunning = true;
time_t start_time;

int direction_x[HARD_MONSTER];
int direction_y[HARD_MONSTER];
int monster_x_perc[HARD_MONSTER] = { 0 };
int monster_y_perc[HARD_MONSTER] = { 0 };

int monsterNum;
int giftNum;
int penaltyNum;
int questionNum = 0;
int consoleWidth, consoleHeight;