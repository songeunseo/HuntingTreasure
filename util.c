#include "game.h"
#include "main.h"
#include "util.h"
#include "draw.h"
#include "input.h"
#include "sound.h"

// 이중 버퍼 초기화
void BufferReset()
{
    for (int i = 0; i < SCREEN_HEIGHT - 1; i++)
    {
        for (int j = 0; j < SCREEN_WIDTH - 1; j++)
        {
            if (map[i][j] == '0') backBuffer[i][j].Char.AsciiChar = ' ';
            else if (map[i][j] == '*')
            {
                backBuffer[i][j].Char.AsciiChar = map[i][j];
                backBuffer[i][j].Attributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
            }
            else
            {
                backBuffer[i][j].Char.AsciiChar = map[i][j];
                backBuffer[i][j].Attributes = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
            }
        }
    }
}
// backBuffer를 screenBuffer에 복사
void Render()
{
    memcpy(pScreenBuffer, backBuffer, sizeof(backBuffer));
}
// screenBuffer를 콘솔에 출력
void Present()
{
    COORD bufferSize = { SCREEN_WIDTH, SCREEN_HEIGHT };
    COORD bufferCoord = { 0, 0 };
    SMALL_RECT writeRegion = { 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1 };

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    WriteConsoleOutput(hStdOut, (CHAR_INFO*)screenBuffer, bufferSize, bufferCoord, &writeRegion);
}

void TimeSetup(ULONGLONG* startTime)
{
    // GetTickCount64 함수를 사용하여 현재 시간을 milliseconds로 가져옴
    *startTime = GetTickCount64();
}
void slowPrint(unsigned long speed, const char* s)
{
    while (*s) {
        if (_kbhit()) {
            char key = _getch();
            if (key == 27) {
                menu();
                return;
            }
            else if (key == 13) {
                while (*s) {
                    printf("%c", *s++);
                }
                difficultyMenu();
                return;
            }
        }
        printf("%c", *s++);
        fflush(stdout);
        Sleep(speed);
    }
}
void SetColor(int colorNum)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorNum);
}
void gotoxy(int x, int y)
{
    COORD POS = { 0 };
    POS.X = x;
    POS.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), POS);
}
void CursorControl(bool flag)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    GetConsoleCursorInfo(handle, &cci);
    cci.bVisible = flag;
    SetConsoleCursorInfo(handle, &cci);
}