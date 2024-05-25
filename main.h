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

#define STARTGAME 0
#define GAMELOOP 1
#define ENDGAME 2
#define GAMEEXIT 3

// Function prototypes
void Init();
void StartGame();
void UpdateGame();
void EndGame();