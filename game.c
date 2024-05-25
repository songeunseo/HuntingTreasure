#include "game.h"
#include "main.h"
#include "util.h"
#include "draw.h"
#include "input.h"
#include "sound.h"

//하이하이
// 바이바이

// 인게임으로 진입했을 때 시간
ULONGLONG gameLoopStartTime;
// FPS 제어 // 계속 갱신됨
ULONGLONG startTime;
extern int gameMode;

/// 메뉴 선택
void StartGame()
{

	PlaySoundEffect(SOUND_GEN);

	/// 메뉴 선택
	TitleDraw();
	int menuCode = MenuDraw();

	/// 게임 시작
	if (menuCode == 0)
	{
		system("cls");
		MapDraw();
		Render();
		Present();
		TimeSetup(&gameLoopStartTime);
		gameMode = GAMELOOP;
	}

	/// 게임 정보
	else if (menuCode == 1)
	{
		RankingDraw();
	}

	/// 게임 종료
	else if (menuCode == 2)
	{
		gameMode = GAMEEXIT;
	}
}

/// 게임 진행
void UpdateGame()
{
	/// 버퍼 초기화
	BufferReset();

	//-------------------------------

	/// 캐릭터 조작
	CharacterMove();

	/// 당근(두더지) 생성 
	CarrotManagement();

	/// UI
	ScoreAndTimeUI();

	//-------------------------------

	/// 화면 출력
	Render();
	Present();
}

/// 랭킹 등록 후 메인 화면으로 돌아가기
void EndGame()
{
	PlaySoundEffect(SOUND_GEN);

	// 타임오버, 랭킹등록
	TimeOverDraw();

	// 맵 동적할당 해제
	MapDie();

	// 값 초기화
	GameReset();

	// StartGame으로 돌아가기
	gameMode = STARTGAME;
}