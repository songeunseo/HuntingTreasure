#include "main.h"
int main(void) {
    CursorControl(false);
    srand(time(NULL));

    //음악을 재생합니다.


    getUserName();
    // 음악 재생을 멈춥니다.

    menu();

    return 0;
}

//은서 사용자 이름 받기
void getUserName() {
    system("cls");
    printArea();
    gotoxy(10, 3);
    printf("%s", "C프로그래밍 4팀 팀프로젝트 보물찾기게임");

    gotoxy(10, 4);
    printf(":*:★,:*:☆ 여왕되기 프로젝트! :*:★,:*:☆");
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

int gameStart() {
    system("cls");

    printArea();
    initializeBoard();
    printThings();

    time_t start_time = time(NULL);
    time_t last_update_time = start_time;

    for (int i = 0; i < monsterNum; i++) {
        gotoxy(monster[i][0], monster[i][1]);
        printf("◆");
    }

    gotoxy(player[0][0], player[0][1]);
    SetColor(12);
    printf("♥");

    while (1) {
        movePlayer();
        SetColor(15);

        checkFlag();
        checkobstacle();

        if (checkGameEnd())
            break;

        time_t current_time = time(NULL); // 현재 시간 가져오기

        if (current_time - last_update_time >= 1) { // 1초마다
            moveMonster();
            int elapsed_time = current_time - start_time; // 경과된 시간 계산
            int remaining_time = gametime - elapsed_time; // 남은 시간 계산

            gotoxy(0, MAP_HEIGHT);
            printf("▤ 점수 : %d\t", score);
            printf("▤ 남은 시간: %d분 %d초", remaining_time / 60, remaining_time % 60);
            recordAndEndOnTime(remaining_time);

            last_update_time = current_time;
        }
        Sleep(5);
    }
    return 0;
}

//은서 게임 설명
void gameRule() {
    system("cls");
    printf("Skip을 하려면 엔터키를 누르시오.\n\n");
    if (_kbhit()) {
        char key = _getch();
        switch (key) {
        case 27://esc키
            menu();
            return;
        case 13://enter키
            difficultyMenu();
            return;
        }
    }
    else {
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
        _getch(); // 아무 키나 입력받기
        difficultyMenu();
    }
}
//은서 메뉴 화면
void menu() {
    system("cls");
    printArea();
    printMenu(); // 메뉴내용 출력
    printSelectionBox(MENU_LEFT_ALIGN - 3, MENU_TOP_ALIGN - 1); // 메뉴박스 출력
    switchMenu(); // 메뉴 입력받기
}
//은서
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
//은서
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
//은서
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

//은서 메뉴박스 출력
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
//은서 메뉴박스 지우기
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

//은서
// 난이도 선택 메뉴
void difficultyMenu() {
    system("cls");
    printArea();
    printDifficultyMenu();
    printSelectionBox(MENU_LEFT_ALIGN - 3, MENU_TOP_ALIGN - 1);
    switchDifficultyMenu();
}
//은서
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
//은서
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
//은서
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


//은서 사용자 이동
void movePlayer() {
    if (_kbhit()) {
        char move = _getch(); // 방향키 입력받기
        gotoxy(player[0][0], player[0][1]);
        printf(" ");

        switch (move) {
        case 72: // 위쪽 방향키
            player[0][1] = player[0][1] > 1 ? player[0][1] - 1 : 1;
            gotoxy(player[0][0], player[0][1]);
            SetColor(12);
            printf("♥");
            break;
        case 80: // 아래쪽 방향키
            player[0][1] = player[0][1] < MAP_HEIGHT - 2 ? player[0][1] + 1 : MAP_HEIGHT - 2;
            gotoxy(player[0][0], player[0][1]);
            SetColor(12);
            printf("♥");
            break;
        case 75: // 왼쪽 방향키
            player[0][0] = player[0][0] > 1 ? player[0][0] - 1 : 1;
            gotoxy(player[0][0], player[0][1]);
            SetColor(12);
            printf("♥");
            break;
        case 77: // 오른쪽 방향키
            player[0][0] = player[0][0] < MAP_WIDTH - 2 ? player[0][0] + 1 : MAP_WIDTH - 2;
            gotoxy(player[0][0], player[0][1]);
            SetColor(12);
            printf("♥");
            break;
        case 27:
            menu();
            break;
        }
    }
}

//지아
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
            direction_x[i] *= -1;
        }
        else if (monster[i][0] == MAP_WIDTH - 2) {
            monster[i][0]--;
            direction_x[i] *= -1;
        }

        if (monster[i][1] == 1) {
            monster[i][1]++;
            direction_y[i] *= -1;
        }
        if (monster[i][1] == MAP_HEIGHT - 2) {
            monster[i][1]--;
            direction_y[i] *= -1;
        }

        if (rand() % 2 == 0)
            monster[i][0] += direction_x[i];
        else
            monster[i][1] += direction_y[i];

        gotoxy(monster[i][0], monster[i][1]);
        printf("◆");

    }
}

//지아
// //맵 초기화
void initializeBoard() {
    player[0][0] = rand() % (MAP_WIDTH - 2) + 1;
    player[0][1] = rand() % (MAP_HEIGHT - 2) + 1;

    treasure[0][0] = rand() % (MAP_WIDTH - 2) + 1;
    treasure[0][1] = rand() % (MAP_HEIGHT - 2) + 1;

    for (int i = 0; i < NUM_GIFTS; i++) {
        gift[i][0] = rand() % (MAP_WIDTH - 2) + 1;
        gift[i][1] = rand() % (MAP_HEIGHT - 2) + 1;
    }

    for (int i = 0; i < NUM_PENALTY; i++) {
        penalty[i][0] = rand() % (MAP_WIDTH - 2) + 1;
        penalty[i][1] = rand() % (MAP_HEIGHT - 2) + 1;
    }

    for (int i = 0; i < monsterNum; i++) {
        monster[i][0] = rand() % (MAP_WIDTH - 2) + 1;
        monster[i][1] = rand() % (MAP_HEIGHT - 2) + 1;
    }
}

//지아
//몬스터 제외 맵에 그리기
void printThings() {
    gotoxy(player[0][0], player[0][1]);
    SetColor(12);
    printf("♥");

    SetColor(15);
    gotoxy(treasure[0][0], treasure[0][1]);
    printf("★");

    for (int i = 0; i < NUM_GIFTS; i++) {
        gotoxy(gift[i][0], gift[i][1]);
        printf("G");
    }

    for (int i = 0; i < NUM_PENALTY; i++) {
        gotoxy(penalty[i][0], penalty[i][1]);
        printf("P");
    }
}

//지아
//몬스터가 맵 지우면 다시 그리기
void checkErasing(int x, int y) {
    if (x == treasure[0][0] && y == treasure[0][1]) {
        gotoxy(treasure[0][0], treasure[0][1]);
        SetColor(15);
        printf("★");
    }
    for (int i = 0; i < NUM_GIFTS; i++) {
        if (x == gift[i][0] && y == gift[i][1])
        {
            gotoxy(gift[i][0], gift[i][1]);
            printf("G");
        }
    }
    for (int i = 0; i < NUM_PENALTY; i++) {
        if (x == penalty[i][0] && y == penalty[i][1])
        {
            gotoxy(penalty[i][0], penalty[i][1]);
            printf("P");
        }
    }
}

//지아
//호감도 선택지 박스 그리기
void drawFavorable() {
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

//지아
//호감도 선택지 박스 지우기
void eraseFavorable() {
    for (int i = 0; i <= 16; i++) {
        gotoxy(MAP_WIDTH + 3, 3 + i);
        puts("                                                         ");
    }
}

//지아
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

//지혁
// 남은 게임시간 감소 
void recordAndEndOnTime(int x)
{
    if (x <= 0) {
        endsignal = -1;
    }
}

//지혁
//깃발 접촉
void checkFlag()
{
    //보물 깃발
    if (player[0][0] == treasure[0][0] && player[0][1] == treasure[0][1]) //플레이어 위치와 보물깃발 위치가 같음
    {
        //PlaySound(TEXT("sound\\jump02.wav"), NULL, SND_FILENAME | SND_ASYNC);
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

            do {
                player[0][0] = rand() % (MAP_WIDTH - 2) + 1;
                player[0][1] = rand() % (MAP_HEIGHT - 2) + 1;
            } while (player[0][0] != treasure[0][0] && player[0][1] != treasure[0][1]);
        }
    }
    //이득 깃발
    for (int i = 0; i < 3; i++)
    {
        if (player[0][0] == gift[i][0] && player[0][1] == gift[i][1])
        {
            //PlaySound(TEXT("sound\\jump02.wav"), NULL, SND_FILENAME | SND_ASYNC);
            gift[i][0] = 0, gift[i][1] = 0; //접촉한 깃발 제거
            drawFavorable();
            favorableQuestion();
            eraseFavorable();
            //if ((rand() % 10) > rand_store_chance)//확률적으로 상점 열림
            //    rand_store();
        }
    }
    for (int i = 3; i < 5; i++) {
        if (player[0][0] == gift[i][0] && player[0][1] == gift[i][1]) {
            gift[i][0] = 0, gift[i][1] = 0;
            score += 300;
        }
    }

    if (player[0][0] == gift[5][0] && player[0][1] == gift[5][1]) {
        gift[5][0] = 0, gift[5][1] = 0;
        // 보물 위아래 방향 알려줌
        drawFavorable();
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
        eraseFavorable();
    }
    if (player[0][0] == gift[6][0] && player[0][1] == gift[6][1]) {
        gift[6][0] = 0, gift[6][1] = 0;
        // 보물 좌우 방향 알려줌
        drawFavorable();
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
        eraseFavorable();
    }


    //벌칙 깃발
    for (int i = 0; i < NUM_PENALTY; i++)
    {
        if (player[0][0] == penalty[i][0] && player[0][1] == penalty[i][1])
        {
            //PlaySound(TEXT("sound\\jump02.wav"), NULL, SND_FILENAME | SND_ASYNC);
            penalty[i][0] = 0, penalty[i][1] = 0;// 접촉한 깃발 제거
            score -= 100;
            penalty_func();
        }
    }


    // 몬스터와 접촉시 다시 출력
    for (int i = 0; i < monsterNum; i++)
    {
        if (monster[i][0] == treasure[0][0] && monster[i][1] == treasure[0][1]) {
            gotoxy(treasure[0][0], treasure[0][1]);
            SetColor(15);
            printf("★");
        }
        for (int j = 0; j < NUM_GIFTS; j++) {
            if (monster[i][0] == gift[j][0] && monster[i][1] == gift[j][1])
            {
                gotoxy(gift[j][0], gift[j][1]);
                printf("G");
            }
        }

    }
}

//지혁
//장애물 접촉
void checkobstacle()
{
    for (int i = 0; i < monsterNum; i++)
    {
        if (player[0][0] == monster[i][0] && player[0][1] == monster[i][1])
        {
            //PlaySound(TEXT("sound\\jump02.wav"), NULL, SND_FILENAME | SND_ASYNC);
            score -= 100; //점수감소
            Sleep(2000); // 2초 정지
        }
    }
}

//지혁
//일정확률로 나오는 상점
void rand_store()
{
    int temp1;
    gotoxy(21, 41); //선택지 출력 위치 조절 필요
    printf("1.몬스터 속도 감소");
    gotoxy(21, 42);
    printf("2.플레이어 속도 증가");
    gotoxy(21, 43);
    printf("3.남은 시간 증가");
    scanf("%d", &temp1);//선택값 입력
    switch (temp1)// 선택값에 따라 다른 효과
    {
    case 1:
        gametime -= 10;
        break;
    case 2:
        gametime -= 10;
        break;
    case 3:
        gametime += 30;
        break;
    }
}

//지혁
//벌칙 깃발과 접촉시 생기는 패널티
void penalty_func()
{
    int temp1 = rand() % 3;//랜덤으로 패널티가 결정됨
    switch (temp1)
    {
    case 0:
        monstertick *= 0.5;
        break;
    case 1:
        playertick *= 2;
        break;
    case 2:
        //3번 패널티 몬스터 수 증가
        break;
    }
}

//민재
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
        printf("GAME OVER!\n");
        printf("시간이 종료되었습니다.");
    }
}

// 점수 계산
void calculateScore() {
    system("cls");
    printf("당신의 score는 %d점입니다.\n\n", score);

    if (score < 100) {
        printf("You failed\n\n");
        Sleep(2000);
        endsignal = 0;
        score = 0;
        menu();
    }
    else if (100 <= score && score < 300) {
        printf("벌꿀색 하트\n");
        printf("깜짝 놀랐을 때 나오는 하트.\n\n");
        printf("You failed\n\n");
        Sleep(2000);
        endsignal = 0;
        score = 0;
        menu();
    }
    else if (300 <= score && score < 500) {
        printf("오렌지 하트\n");
        printf("설레이거나 호감이 생기기 시작할 때 생기는 하트.\n\n");
        printf("You failed\n\n");
        Sleep(2000);
        endsignal = 0;
        score = 0;
        menu();
    }
    else if (500 <= score && score < 1000) {
        printf("그린 하트\n");
        printf("친구들 사이의 우정의 하트.\n\n");
        printf("You failed\n\n");
        Sleep(2000);
        endsignal = 0;
        score = 0;
        menu();
    }
    else if (1000 <= score && score < 3000) {
        printf("핑크 하트\n");
        printf("사랑이 시작할 때 나오는 하트.\n\n");
        levelUp();
    }
    else {
        printf("레드 하트\n");
        printf("진실한 사랑의 하트.\n\n");
        levelUp();
    }
}

// 난이도별로 조작
void levelUp() {
    score = 0; // 점수 초기화
    endsignal = 0;

    if (level != 3) {
        printf("Level Up!");
        Sleep(2000);
        printf("\n다음 레벨로 이동합니다...");
        Sleep(2000);

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
        printf("GAME CLEAR!\n");
        Sleep(2000);
        printf("메뉴로 다시 돌아갑니다...");
        Sleep(2000);
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