#pragma once
void BufferReset();
void Render();
void Present();
void SetConsole();
void TimeSetup(ULONGLONG* startTime);
void SetColor(int colorNum);
void gotoxy(int x, int y);
void CursorControl(bool flag);