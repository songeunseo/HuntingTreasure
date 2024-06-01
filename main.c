#include "game.h"
#include "main.h"
#include "util.h"
#include "draw.h"
#include "input.h"
#include "sound.h"

extern ULONGLONG startTime;
int gameMode = STARTGAME;

int main()
{
	/// Init
	Init();

	while (1)
	{
		/// Title & Menu Select
		if (gameMode == STARTGAME) {
			StartGame();
		}

		/// Loop
		if (gameMode == GAMELOOP) {
			UpdateGame();
			startTime = GetTickCount64();
		}

		if (gameMode == ENDGAME) {
			EndGame();
		}

		/// EXIT
		if (gameMode == GAMEEXIT){
			// 사운드 해제
			ReleaseSound();
			break;
		}
	}
	return 0;
}

/// 초기 세팅
void Init()
{
	// 랜덤 시드 설정
	srand(time(NULL));
	// 시작 시간 저장
	TimeSetup(&startTime);
	// 콘솔 셋업
	SetConsole();

	/// 사운드 초기화
	CreateSoundInit();
	AllocateSound();
	PlayBGM();
}//test