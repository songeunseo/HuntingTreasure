#include "game.h"
#include "main.h"
#include "util.h"
#include "draw.h"
#include "input.h"
#include "sound.h"

//��������
// ���̹���

// �ΰ������� �������� �� �ð�
ULONGLONG gameLoopStartTime;
// FPS ���� // ��� ���ŵ�
ULONGLONG startTime;
extern int gameMode;

/// �޴� ����
void StartGame()
{

	PlaySoundEffect(SOUND_GEN);

	/// �޴� ����
	TitleDraw();
	int menuCode = MenuDraw();

	/// ���� ����
	if (menuCode == 0)
	{
		system("cls");
		MapDraw();
		Render();
		Present();
		TimeSetup(&gameLoopStartTime);
		gameMode = GAMELOOP;
	}

	/// ���� ����
	else if (menuCode == 1)
	{
		RankingDraw();
	}

	/// ���� ����
	else if (menuCode == 2)
	{
		gameMode = GAMEEXIT;
	}
}

/// ���� ����
void UpdateGame()
{
	/// ���� �ʱ�ȭ
	BufferReset();

	//-------------------------------

	/// ĳ���� ����
	CharacterMove();

	/// ���(�δ���) ���� 
	CarrotManagement();

	/// UI
	ScoreAndTimeUI();

	//-------------------------------

	/// ȭ�� ���
	Render();
	Present();
}

/// ��ŷ ��� �� ���� ȭ������ ���ư���
void EndGame()
{
	PlaySoundEffect(SOUND_GEN);

	// Ÿ�ӿ���, ��ŷ���
	TimeOverDraw();

	// �� �����Ҵ� ����
	MapDie();

	// �� �ʱ�ȭ
	GameReset();

	// StartGame���� ���ư���
	gameMode = STARTGAME;
}