#include "main.h"
int main(void) {
    CursorControl(false);
    srand(time(NULL));

    getUserName();
    menu();

    return 0;
}

void getUserName() {
    system("cls");
    printArea();
    gotoxy(10, 3);
    printf("0:23 ━━■━━━━━━ 3:09");
    gotoxy(10, 4);
    printf("        ◀ ■■ ▶    ");
    gotoxy(10, 6);
    printf("당신의 이름은 무엇인가요? ");
    scanf("%s", &name);
    gotoxy(10, 9);
    printf("%s님 안녕하세요!", &name);
    Sleep(1000);
}
void printArea()
{
    system("cls");
    gotoxy(0, 0);
    printf("┌");
    for (int i = 0; i < MAP_WIDTH - 2; i++) {
        printf("─");
    }
    printf("┐\n");

    for (int i = 0; i < MAP_HEIGHT - 2; i++) {
        printf("│");
        for (int j = 0; j < MAP_WIDTH - 2; j++) {
            printf(" ");
        }
        printf("│\n");
    }

    printf("└");
    for (int i = 0; i < MAP_WIDTH - 2; i++) {
        printf("─");
    }
    printf("┘");

}

//게임 설명
void gameRule() {
    PlaySound(NULL, NULL, 0); // 현재 재생 중인 사운드를 중지
    PlaySound(TEXT("sound\\gamerule.wav"), NULL, SND_FILENAME | SND_ASYNC);
    system("cls");
    printf("Skip을 하려면 엔터키를 누르시오.\n\n");
    slowPrint(50, "게임 설명\n");
    slowPrint(50, "이 게임은 플레이어가 미로 속에서 보물을 찾아나가는 게임입니다.\n");
    slowPrint(50, "플레이어는 ♥으로 표시되며, 보물은 ★으로 표시됩니다.\n");
    slowPrint(50, "플레이어는 ↑, ↓, ←, → 키를 사용하여 이동할 수 있습니다.\n");
    slowPrint(50, "이득 깃발(G)을 획득하면 점수가 100점 증가하고, 벌칙 깃발(P)에 닿으면 점수가 1점 감소합니다.\n");
    slowPrint(50, "점수가 일정 수준 이상이 되면 게임을 클리어할 수 있습니다.\n");
    slowPrint(50, "게임은 시간 제한이 있으며, 시간이 다 되면 게임 오버됩니다.\n");
    slowPrint(50, "게임 시작 전에 메뉴를 통해 게임 시작 또는 게임 설명을 선택할 수 있습니다.\n");
    slowPrint(50, "게임 중간에도 메뉴를 통해 게임을 나갈 수 있습니다.\n\n");
    slowPrint(50, "게임을 시작하려면 아무 키나 누르세요...");
}

//메뉴 화면
void menu() {
    initializeGameVariables(); // 게임 변수 초기화
    system("cls");
    PlaySound(TEXT("sound\\gamestart.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    printArea();
    printMenu(); // 메뉴내용 출력
    printSelectionBox(MENU_LEFT_ALIGN - 3, MENU_TOP_ALIGN - 1); // 메뉴박스 출력
    switchMenu(); // 메뉴 입력받기
}
void printMenu()
{
    gotoxy(10, 3);
    printf("C프로그래밍 4팀 팀프로젝트 보물찾기게임");
    gotoxy(10, 4);
    printf(":*:★,:*:☆ 여왕되기 프로젝트! :*:★,:*:☆");
    gotoxy(10, 6);
    printf("※ 방향키를 이용하여 선택하고 엔터키를 누르십시오.");

    gotoxy(MENU_LEFT_ALIGN, MENU_TOP_ALIGN);
    printf("Game Start");
    gotoxy(MENU_LEFT_ALIGN, MENU_TOP_ALIGN + MENU_LINE_SPACE);
    printf("Instructions");
    gotoxy(MENU_LEFT_ALIGN, MENU_TOP_ALIGN + MENU_LINE_SPACE * 2);
    printf("EXIT");
}
void switchMenu() {
    int menuNum = 1; //1:게임시작, 2:게임설명, 3:EXIT
    int key;

    while (1)
    {
        if (_kbhit() != 0)
        {
            key = _getch();

            if (key == 13) // 엔터키
            {
                break;
            }
            if (key == 224) // 방향키 모두
            {
                key = _getch();
                if (key == 72 && menuNum > 1) // 위쪽 방향키
                {
                    eraseSelectionBox(SELECTION_BOX_LEFT_ALIGN, MENU_TOP_ALIGN - 1 + ((menuNum - 1) * MENU_LINE_SPACE));
                    menuNum--;
                    printSelectionBox(SELECTION_BOX_LEFT_ALIGN, MENU_TOP_ALIGN - 1 + ((menuNum - 1) * MENU_LINE_SPACE));
                }
                else if (key == 80 && menuNum < 3) // 아래쪽 방향키
                {
                    eraseSelectionBox(SELECTION_BOX_LEFT_ALIGN, MENU_TOP_ALIGN - 1 + ((menuNum - 1) * MENU_LINE_SPACE));
                    menuNum++;
                    printSelectionBox(SELECTION_BOX_LEFT_ALIGN, MENU_TOP_ALIGN - 1 + ((menuNum - 1) * MENU_LINE_SPACE));
                }
            }

        }
        Sleep(200);
    }
    runMenu(menuNum);
}
void runMenu(int menuNum)
{
    switch (menuNum)
    {
    case 1:
        difficultyMenu();
        break;
    case 2:
        gameRule();
        break;
    case 3:
        system("cls");
        printf("종료되었습니다.");
        break;
    }
}
//메뉴박스 출력
void printSelectionBox(int x, int y)
{
    gotoxy(x, y);
    puts("┌───────────────────────────────┐");
    gotoxy(x, y + 1);
    puts("│");
    gotoxy(x + 32, y + 1);
    puts("│");
    gotoxy(x, y + 2);
    puts("└───────────────────────────────┘");
}
//메뉴박스 지우기
void eraseSelectionBox(int x, int y)
{
    gotoxy(x, y);
    puts("                                 ");
    gotoxy(x, y + 1);
    puts(" ");
    gotoxy(x + 32, y + 1);
    puts(" ");
    gotoxy(x, y + 2);
    puts("                                 ");
}
// 난이도 선택 메뉴
void difficultyMenu() {
    system("cls");
    printArea();
    printDifficultyMenu();
    printSelectionBox(MENU_LEFT_ALIGN - 3, MENU_TOP_ALIGN - 1);
    switchDifficultyMenu();
}
void printDifficultyMenu()
{
    gotoxy(13, 5);
    printf("난이도 설정\n");

    gotoxy(MENU_LEFT_ALIGN, MENU_TOP_ALIGN);
    printf("초급 Easy Mode");
    gotoxy(MENU_LEFT_ALIGN, MENU_TOP_ALIGN + MENU_LINE_SPACE);
    printf("중급 Normal Mode");
    gotoxy(MENU_LEFT_ALIGN, MENU_TOP_ALIGN + MENU_LINE_SPACE * 2);
    printf("고급 Hard Mode");
}
void switchDifficultyMenu() {
    int key;

    while (1)
    {
        if (_kbhit() != 0)
        {
            key = _getch();

            if (key == 13) // 엔터키
            {
                break;
            }
            if (key == 224) // 방향키 모두
            {
                key = _getch();
                if (key == 72 && level > 1) // 위쪽 방향키
                {
                    eraseSelectionBox(SELECTION_BOX_LEFT_ALIGN, MENU_TOP_ALIGN - 1 + ((level - 1) * MENU_LINE_SPACE));
                    level--;
                    printSelectionBox(SELECTION_BOX_LEFT_ALIGN, MENU_TOP_ALIGN - 1 + ((level - 1) * MENU_LINE_SPACE));
                }
                else if (key == 80 && level < 3) // 아래쪽 방향키
                {
                    eraseSelectionBox(SELECTION_BOX_LEFT_ALIGN, MENU_TOP_ALIGN - 1 + ((level - 1) * MENU_LINE_SPACE));
                    level++;
                    printSelectionBox(SELECTION_BOX_LEFT_ALIGN, MENU_TOP_ALIGN - 1 + ((level - 1) * MENU_LINE_SPACE));
                }
            }

        }
        Sleep(200);
    }
    runDifficultyMenu(level);
}
void runDifficultyMenu(int level)
{
    switch (level)
    {
    case 1:
        // PlaySound(NULL, 0, 0);
        startEasyGame();
        break;
    case 2:
        //PlaySound(NULL, 0, 0);
        startNormalGame();
        break;
    case 3:
        // PlaySound(NULL, 0, 0);
        startHardGame();
        break;
    }
}

// 게임 함수
int gameStart() {
    system("cls");
    PlaySound(NULL, NULL, 0);
    PlaySound(TEXT("sound\\gaming.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

    printArea();
    initializeBoard();
    printThings();

    time_t start_time = time(NULL);

    for (int i = 0; i < monsterNum; i++) {
        gotoxy(monster[i][0], monster[i][1]);
        printf("◆");
    }

    clock_t player_std_time, monster_std_time, player_time, monster_time;
    double player_duration, monster_duration;
    player_std_time = clock();
    monster_std_time = clock();

    while (1) {
        player_time = clock();
        monster_time = clock();

        player_duration = (double)(player_time - player_std_time);
        monster_duration = (double)(monster_time - monster_std_time);

        checkFlag();

        time_t current_time = time(NULL); // ���� �ð� ��������

        if (player_duration >= playertick) { // playertick마다
            movePlayer();
            player_std_time = clock();
        }

        if (monster_duration >= monstertick) { // monstertick마다
            moveMonster();
            monster_std_time = clock();
        }

        if (current_time - start_time >= 1) {// 1초마다
            int elapsed_time = current_time - start_time; // 경과된 시간 계산
            int remaining_time = gametime - elapsed_time; // 남은 시간 계산
            gotoxy(0, MAP_HEIGHT);
            printf("▤ 점수 : %d\t", score);
            printf("▤ 남은 시간: %d분 %d초", remaining_time / 60, remaining_time % 60);
            recordAndEndOnTime(remaining_time);
        }

        if (checkGameEnd())
            break;
        Sleep(5); // 과도한 반복 방지
    }
    return 0;
}

//사용자 이동
void movePlayer() {
    if (_kbhit()) {
        char move = _getch(); // 방향키 입력받기
        gotoxy(player[0][0], player[0][1]);
        printf(" ");
        SetColor(12);
        switch (move) {
        case 72: // 위쪽 방향키
            player[0][1] = player[0][1] > 1 ? player[0][1] - 1 : 1;
            gotoxy(player[0][0], player[0][1]);
            printf("♥");
            break;
        case 80: // 아래쪽 방향키
            player[0][1] = player[0][1] < MAP_HEIGHT - 2 ? player[0][1] + 1 : MAP_HEIGHT - 2;
            gotoxy(player[0][0], player[0][1]);
            printf("♥");
            break;
        case 75: // 왼쪽 방향키
            player[0][0] = player[0][0] > 1 ? player[0][0] - 1 : 1;
            gotoxy(player[0][0], player[0][1]);
            printf("♥");
            break;
        case 77: // 오른쪽 방향키
            player[0][0] = player[0][0] < MAP_WIDTH - 2 ? player[0][0] + 1 : MAP_WIDTH - 2;
            gotoxy(player[0][0], player[0][1]);
            printf("♥");
            break;
        case 27:
            menu();
            break;
        }
        SetColor(15);
    }
}
//몬스터 이동
void moveMonster() {
    for (int i = 0; i < monsterNum; i++) {
        direction_x[i] = ((rand() % 10) + 1) > monster_x_perc[i] ? 1 : -1;
        direction_y[i] = ((rand() % 10) + 1) > monster_x_perc[i] ? 1 : -1;
    }

    for (int i = 0; i < monsterNum; i++) {
        gotoxy(monster[i][0], monster[i][1]);
        printf(" ");
        checkErasing(monster[i][0], monster[i][1]);
        if (monster[i][0] == 1) {
            monster[i][0]++;
            monster_x_perc[i] = 2;
        }
        else if (monster[i][0] == MAP_WIDTH - 2) {
            monster[i][0]--;
            monster_x_perc[i] = 8;
        }

        if (monster[i][1] == 1) {
            monster[i][1]++;
            monster_y_perc[i] = 2;
        }
        if (monster[i][1] == MAP_HEIGHT - 2) {
            monster[i][1]--;
            monster_y_perc[i] = 8;
        }

        if (rand() % 2 == 0)
            monster[i][0] += direction_x[i];
        else
            monster[i][1] += direction_y[i];

        gotoxy(monster[i][0], monster[i][1]);
        printf("◆");

    }
}

//맵 초기화
void initializeBoard() {
    srand(time(NULL));
    initRandomPosition(player[0]);
    initRandomPosition(treasure[0]);

    for (int i = 0; i < NUM_GIFTS; i++) {
        initRandomPosition(gift[i]);
    }

    for (int i = 0; i < NUM_PENALTY; i++) {
        initRandomPosition(penalty[i]);
    }

    for (int i = 0; i < monsterNum; i++) {
        initRandomPosition(monster[i]);
        direction_x[i] = (rand() % 2) ? 1 : -1;
        direction_y[i] = (rand() % 2) ? 1 : -1;
    }
}
// 랜덤 위치 초기화 함수
void initRandomPosition(int position[2]) {
    position[0] = rand() % (MAP_WIDTH - 2) + 1;
    position[1] = rand() % (MAP_HEIGHT - 2) + 1;
}
//몬스터 제외 맵에 그리기
void printThings() {
    gotoxy(player[0][0], player[0][1]);
    SetColor(12);
    printf("♥");
    SetColor(15);

    gotoxy(treasure[0][0], treasure[0][1]);
    printf("▶");

    for (int i = 0; i < NUM_GIFTS; i++) {
        gotoxy(gift[i][0], gift[i][1]);
        printf("▶");
    }

    for (int i = 0; i < NUM_PENALTY; i++) {
        gotoxy(penalty[i][0], penalty[i][1]);
        printf("▶");
    }
}
//몬스터가 맵 지우면 다시 그리기
void checkErasing(int x, int y) {
    if (x == treasure[0][0] && y == treasure[0][1]) {
        gotoxy(treasure[0][0], treasure[0][1]);
        if (treasureFound == 0) {
            printf("▶");
        }
        else if (treasureFound == 1) {
            printf("★");
        }
    }
    for (int i = 0; i < NUM_GIFTS; i++) {
        if (x == gift[i][0] && y == gift[i][1])
        {
            gotoxy(gift[i][0], gift[i][1]);
            printf("▶");
        }
    }
    for (int i = 0; i < NUM_PENALTY; i++) {
        if (x == penalty[i][0] && y == penalty[i][1])
        {
            gotoxy(penalty[i][0], penalty[i][1]);
            printf("▶");
        }
    }
}

//남은 게임시간 감소 
void recordAndEndOnTime(int x)
{
    if (x <= 0) {
        endsignal = -1;
    }
}

//깃발 접촉
void checkFlag()
{
    checkTreasure();
    checkGift();
    checkPenalty();
    checkObstacle();
}
//보물 접촉
void checkTreasure() {
    if (player[0][0] == treasure[0][0] && player[0][1] == treasure[0][1])
    {
        //PlaySound(TEXT("sound\\jump02.wav"), NULL, SND_FILENAME | SND_ASYNC);
        treasureFound = 1;
        MessageBox(NULL, TEXT("보물을 발견하셨습니다!"), TEXT("TREASURE"), MB_OK);
        int temp1 = MessageBox(NULL, TEXT("점수를 계산하시겠습니까?"), TEXT("TREASURE"), MB_YESNO);
        if (temp1 == IDYES) {
            system("cls");
            endsignal = 1; //checkGameEnd()함수에서 endsingnal값으로 게임 종료 여부 확인
        }
        else {
            endsignal = 0;
            gotoxy(treasure[0][0], treasure[0][1]);
            printf("★");
            player[0][0]++;
            player[0][1]++;
        }
    }
}
//이득깃발 접촉
void checkGift() {
    for (int i = 0; i < 3; i++)
    {
        if (player[0][0] == gift[i][0] && player[0][1] == gift[i][1])
        {
            initializeTick();
            //PlaySound(TEXT("sound\\jump02.wav"), NULL, SND_FILENAME | SND_ASYNC);
            gift[i][0] = 0, gift[i][1] = 0; //접촉한 깃발 제거
            drawSideBox();
            favorableQuestion();
            eraseSideBox();
            //if ((rand() % 10) > rand_store_chance)//확률적으로 상점 열림
            //    rand_store();
        }
    }
    for (int i = 3; i < 5; i++) {
        if (player[0][0] == gift[i][0] && player[0][1] == gift[i][1]) {
            initializeTick();
            gift[i][0] = 0, gift[i][1] = 0;
            score += 300;
            eventPrint();
        }
    }

    if (player[0][0] == gift[5][0] && player[0][1] == gift[5][1]) {
        initializeTick();
        gift[5][0] = 0, gift[5][1] = 0;
        // 보물 위아래 방향 알려줌
        drawSideBox();
        gotoxy(MAP_WIDTH + 5, 5);
        printf("엿보기 안경 획득!");
        gotoxy(MAP_WIDTH + 5, 6);
        if (player[0][1] > treasure[0][1]) {
            printf("보물이 현재 위치보다 위에 있습니다.");
        }
        else if (player[0][1] == treasure[0][1])
            printf("보물은 현재 위치의 y축과 동일합니다.");
        else {
            printf("보물이 현재 위치보다 아래에 있습니다.");
        }
        Sleep(1000);
        eraseSideBox();
    }
    if (player[0][0] == gift[6][0] && player[0][1] == gift[6][1]) {
        initializeTick();
        gift[6][0] = 0, gift[6][1] = 0;
        // 보물 좌우 방향 알려줌
        drawSideBox();
        gotoxy(MAP_WIDTH + 5, 5);
        printf("엿보기 안경 획득!");
        gotoxy(MAP_WIDTH + 5, 6);
        if (player[0][0] < treasure[0][0])
            printf("보물이 현재 위치보다 오른쪽에 있습니다.");
        else if (player[0][0] == treasure[0][0])
            printf("보물은 현재 위치의 x축과 동일합니다.");
        else
            printf("보물이 현재 위치보다 왼쪽에 있습니다.");
        Sleep(1000);
        eraseSideBox();
    }
}
//벌칙깃발 접촉
void checkPenalty() {
    for (int i = 0; i < NUM_PENALTY; i++)
    {
        if (player[0][0] == penalty[i][0] && player[0][1] == penalty[i][1])
        {
            //PlaySound(TEXT("sound\\jump02.wav"), NULL, SND_FILENAME | SND_ASYNC);
            penalty[i][0] = 0, penalty[i][1] = 0;// 접촉한 깃발 제거
            penalty_func();
        }
    }
}
//장애물 접촉
void checkObstacle()
{
    for (int i = 0; i < monsterNum; i++)
    {
        if (player[0][0] == monster[i][0] && player[0][1] == monster[i][1])
        {
            //PlaySound(TEXT("sound\\jump02.wav"), NULL, SND_FILENAME | SND_ASYNC);
            if (score >= 100)
                score -= 100; // 점수감소
            else
                score = 0;
            player[0][0]--;
        }

    }
}

//벌칙 깃발과 접촉시 생기는 패널티
void penalty_func()
{
    int temp1 = rand() % 2; //랜덤으로 패널티가 결정됨
    switch (temp1)
    {
    case 0:
        monstertick *= 0.5;
        break;
    case 1:
        playertick *= 1.5;
        break;
    }
    penaltyPrint(temp1);
}

//호감도 선택지 박스 그리기
void drawSideBox() {
    gotoxy(MAP_WIDTH + 3, 3);
    puts("┌────────────────────────────────────────────────────┐");
    for (int i = 0; i <= 15; i++) {
        gotoxy(MAP_WIDTH + 3, 4 + i);
        puts("│");
        gotoxy(MAP_WIDTH + 56, 4 + i);
        puts("│");
    }
    gotoxy(MAP_WIDTH + 3, 19);
    puts("└────────────────────────────────────────────────────┘");
}
//호감도 선택지 박스 지우기
void eraseSideBox() {
    for (int i = 0; i <= 16; i++) {
        gotoxy(MAP_WIDTH + 3, 3 + i);
        puts("                                                         ");
    }
}
//질문&선택지 출력 함수
void favorableQuestion() {
    char* question[] = {
    "Q. '나 살찐 것 같지?’에 대한 가장 적절한 대답은?",
    "Q. '내 어디가 좋아?’에 대한 가장 적절한 대답은?",
    "Q. '더 이상 연락하지 마’의 속뜻은?",
    "Q. 예쁜 디저트를 먹으러 갔을 때",
    "Q. '어떤 옷이 나아?’에 대한 가장 적절한 대답은?",
    "Q. 세젤예랑 만나고 10억 받기 VS 나랑 만나기",
    "Q. 아까 지나간 사람 엄청 예쁘지?",
    "Q. 전 여자친구랑 나랑 누가 더 나아?",
    "Q. 나 이거 먹고 싶은데, 너도 먹을 거야?"
    };
    char* favorableSelection1[] = {
        "1) 별로 안 먹던데 왜 찌지?",
        "1) 착해서 좋아",
        "1) 연락하지 마",
        "1) 맛있겠다며 먼저 먹여주기",
        "1) 아무거나 입어도 다 예쁜데?",
        "1) 10억 받고 너랑 만나야지!",
        "1) 아까 누가 지나갔어?",
        "1) 전 여자친구가 참 착한 애긴 했어",
        "1) 난 안 먹을래"
    };

    char* favorableSelection2[] = {
        "2) 하나도 안 쪘어",
        "2) 그런 게 어디 있어~ 너라서 좋아",
        "2) 화 풀릴 때까지 계속 연락해",
        "2) 사진 찍고 싶을 수 있으니 기다리기",
        "2) 처음보단 두 번째 거가 낫다!",
        "2) 세상에서 제일 예쁜 사람이랑 만날게",
        "2) 응 예쁘더라",
        "2) 당연히 너가 제일 좋지!",
        "2) 너 먹고 싶으면 먹어"
    };

    char* favorableSelection3[] = {
        "3) 살찐 건 모르겠고 예뻐",
        "3) 예뻐서 좋아",
        "3) 평생 볼 생각도 하지마",
        "3) 맛있는지 먹어보겠다며 먼저 먹어보기",
        "3) 둘 다 예쁜데 더 편한 옷이 낫지 않을까?",
        "3) 이미 만나고 있는데 10억 어딨지?",
        "3) 하나도 안 예뻤는데?",
        "3) 난 전 여자친구 없는데?",
        "3) 나도 먹고 싶었는데! 같이 먹자"
    };

    time_t pause_start_time = time(NULL);
    gotoxy(MAP_WIDTH + 5, 5);
    printf("%s", question[questionNum]);
    gotoxy(MAP_WIDTH + 5, 6);
    printf("%s", favorableSelection1[questionNum]);
    gotoxy(MAP_WIDTH + 5, 7);
    printf("%s", favorableSelection2[questionNum]);
    gotoxy(MAP_WIDTH + 5, 8);
    printf("%s", favorableSelection3[questionNum]);
    gotoxy(MAP_WIDTH + 5, 9);
    printf("답: ");
    int answer;
    scanf("%d", &answer);

    if (questionNum == 6) {
        switch (answer) {
        case 1:
            score += 300;
            break;
        case 2:
        case 3:
            break;
        }
    }
    if (questionNum == 2 || questionNum == 3) {
        switch (answer) {
        case 1:
            break;
        case 2:
            score += 300;
        case 3:
            break;
        }
    }
    if (questionNum == 0 || questionNum == 1 || questionNum == 4 || questionNum == 5 || questionNum == 7 || questionNum == 8 || questionNum == 9) {
        switch (answer) {
        case 1:
        case 2: break;
        case 3:
            score += 300;
            break;
        }
    }
    questionNum++;
    if (questionNum == 9)
        questionNum = 0;
}
//이득 출력
void eventPrint() {
    drawSideBox();
    gotoxy(MAP_WIDTH + 5, 5);
    printf("이득 깃발 발견!");
    gotoxy(MAP_WIDTH + 5, 6);
    printf("호감도 +300");
    Sleep(1000);
    eraseSideBox();
}
//페널티 출력 함수
void penaltyPrint(int x) {
    drawSideBox();
    gotoxy(MAP_WIDTH + 5, 5);
    printf("벌칙 깃발 발견!");
    gotoxy(MAP_WIDTH + 5, 6);
    switch (x)
    {
    case 0:
        printf("몬스터의 속도가 2배 빨라졌습니다!");
        break;
    case 1:
        printf("플레이어의 속도가 1.5배 느려졌습니다!");
        break;
    }
    Sleep(1000);
    eraseSideBox();
}

// 게임 변수 초기화
void initializeGameVariables() {
    playertick = 31.25;
    monstertick = 125;
    endsignal = 0;
    treasureFound = 0;
    score = 0;
    gametime = 180;
}
void initializeTick() {
    playertick = 31.25;
    monstertick = 125;
}

//게임 종료 조건 검사, 게임 종료 확인
int checkGameEnd() {
    // 보물을 찾았는지 확인
    if (endsignal == 1) {
        endGame(1);
        return 1;
    }
    // 시간초과 확인
    else if (endsignal == -1) {
        endGame(0);
        return 1;
    }
    else
        return 0;
}
//게임 종료 화면
void endGame(int result) {
    if (result) {
        calculateScore();
    }
    else {
        system("cls");
        PlaySound(NULL, NULL, 0);
        PlaySound(TEXT("sound\\gameover.wav"), NULL, SND_FILENAME | SND_ASYNC);
        printf("GAME OVER!\n");
        printf("시간이 종료되었습니다.");
    }
}
// 점수 계산
void calculateScore() {
    PlaySound(NULL, NULL, 0);
    PlaySound(TEXT("sound\\levelup.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    system("cls");
    printArea();
    gotoxy(10, 3);
    printf("당신의 score는 %d점입니다.", score);
    Sleep(2000);
    system("cls");
    if (score < 300) {
        printf("You failed\n\n");
        Sleep(2000);
        menu();
    }
    else if (300 <= score && score < 600) {
        printf("벌꿀색 하트\n");
        SetColor(14);
        printf("%s", heart);
        SetColor(15);
        printf("\n깜짝 놀랐을 때 나오는 하트.\n");
        Sleep(2000);
        printf("You failed");
        Sleep(2000);
        menu();
    }
    else if (600 <= score && score < 900) {
        printf("오렌지 하트\n");
        SetColor(4);
        printf("%s", heart);
        SetColor(15);
        printf("\n설레이거나 호감이 생기기 시작할 때 생기는 하트.\n");
        Sleep(2000);
        printf("You failed");
        Sleep(2000);
        menu();
    }
    else if (900 <= score && score < 1200) {
        printf("그린 하트\n");
        SetColor(10);
        printf("%s", heart);
        SetColor(15);
        printf("친구들 사이의 우정의 하트.\n");
        Sleep(2000);
        levelUp();
    }
    else if (1200 <= score && score < 1500) {
        printf("핑크 하트\n");
        SetColor(13);
        printf("%s", heart);
        SetColor(15);
        printf("사랑이 시작할 때 나오는 하트.");
        Sleep(2000);
        levelUp();
    }
    else {
        printf("레드 하트\n");
        SetColor(12);
        printf("%s", heart);
        SetColor(15);
        printf("진실한 사랑의 하트.");
        Sleep(2000);
        levelUp();
    }
}

// 난이도별로 조작
void levelUp() {
    initializeGameVariables();
    system("cls");

    if (level != 3) {
        printf(" _                         _   _   _         _ \n");
        printf("| |                       | | | | | |       | |\n");
        printf("| |      ___ __   __  ___ | | | | | | _ __  | |\n");
        printf("| |     / _ \\\\ \\ / / / _ \\| | | | | || '_ \\ | |\n");
        printf("| |____|  __/ \\ V / |  __/| | | |_| || |_) ||_|\n");
        printf("\\_____/ \\___|  \\_/   \\___||_|  \\___/ | .__/ (_)\n");
        printf("                                     | |       \n");
        printf("                                     |_|       \n");
        Sleep(2000);
        printf("\n다음 레벨로 이동합니다...");
        printf("\n이동하려면 아무 키나 누르세요.");
        _getch();

        switch (level) {
        case 1:
            level++;
            startNormalGame();
            break;
        case 2:
            level++;
            startHardGame();
            break;
        }
    }
    else {
        PlaySound(TEXT("sound\\gameclear.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
        printf(" _____                           _____  _                     _ \n");
        printf("|  __ \\                         /  __ \\| |                   | |\n");
        printf("| |  \\/  __ _  _ __ ___    ___  | /  \\/| |  ___   __ _  _ __ | |\n");
        printf("| | __  / _` || '_ ` _ \\  / _ \\ | |    | | / _ \\ / _` || '__|| |\n");
        printf("| |_\\ \\| (_| || | | | | ||  __/ | \\__/\\| ||  __/| (_| || |   |_|\n");
        printf(" \\____/ \\__,_||_| |_| |_| \\___|  \\____/|_| \\___| \\__,_||_|   (_)\n");
        printf("                                                                \n");
        printf("                                                                \n");
        printf("당신은 마계의 여왕이 되는데 성공하셨습니다.");
        Sleep(2000);
        printf("\n\n메뉴로 다시 돌아갑니다...");
        printf("\n이동하려면 아무 키나 누르세요.");
        _getch();
        menu();
    }
}
void startEasyGame() {
    monsterNum = EASY_MONSTER;
    gameStart();
}
void startNormalGame() {
    monsterNum = NORMAL_MONSTER;
    gameStart();
}
void startHardGame() {
    monsterNum = HARD_MONSTER;
    gameStart();
}

//API
void slowPrint(unsigned long speed, const char* s)
{
    while (*s) {
        if (_kbhit()) {
            char key = _getch();
            if (key == 27) {
                PlaySound(NULL, NULL, 0);
                menu();
                return;
            }
            else if (key == 13) {
                while (*s) {
                    printf("%c", *s++);
                }
                PlaySound(NULL, NULL, 0);
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