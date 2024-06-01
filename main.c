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
			// ���� ����
			ReleaseSound();
			break;
		}
	}
	return 0;
}

/// �ʱ� ����
void Init()
{
	// ���� �õ� ����
	srand(time(NULL));
	// ���� �ð� ����
	TimeSetup(&startTime);
	// �ܼ� �¾�
	SetConsole();

	/// ���� �ʱ�ȭ
	CreateSoundInit();
	AllocateSound();
	PlayBGM();
}//test