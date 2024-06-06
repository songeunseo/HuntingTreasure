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

#define NUM_GIFTS 7
#define NUM_PENALTY 5
#define EASY_MONSTER 5
#define NORMAL_MONSTER 7
#define HARD_MONSTER 9

#define PLAYTIME 180
#define rand_store_chance 5

// 원형함수
void getUserName();
void printArea();

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
void movePlayer();
void moveMonster();

void initBoard();
void initRandomPosition(int position[2]);
void initTick();
void initGameVariables();

void printThings();
void checkErasing(int x, int y);

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

//void rand_store();
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

//API
void slowPrint(unsigned long speed, const char* s);
void SetColor(int colorNum);
void gotoxy(int x, int y);
void CursorControl(bool flag);

// 변수
int gametime = 180;//게임 시간
int score = 0;
double playertick = 31.25;
double monstertick = 125;
int level = 1;
int endsignal;
int treasureFound = 0;
char name[10]; // 사용자 이름 입력받기
bool gameRunning = true;
time_t start_time;
int monsterNum;
int direction_x[HARD_MONSTER];
int direction_y[HARD_MONSTER];
int monster_x_perc[HARD_MONSTER] = { 0 };
int monster_y_perc[HARD_MONSTER] = { 0 };

int monsterNum;
int giftNum;
int penaltyNum;

int player[1][2] = { 0 };
int treasure[1][2] = { 0 };
int gift[NUM_GIFTS][2] = { 0 };
int penalty[NUM_PENALTY][2] = { 0 };
int monster[HARD_MONSTER][2] = { 0 };
int questionNum = 0;

char* heart =
"                              \n"
"         ....    ....         \n"
"       .......  .......       \n"
"      ..................      \n"
"      ..................      \n"
"      ..................      \n"
"      ..................      \n"
"      ..................      \n"
"      ..................      \n"
"      ..................      \n"
"      ..................      \n"
"       ................       \n"
"        ..............        \n"
"         ............         \n"
"          ..........          \n"
"           ........           \n"
"            ......            \n"
"              ...             \n"
"                              \n";