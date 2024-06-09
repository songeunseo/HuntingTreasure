#include "main.h"

int main(void) {
    CursorControl(false);
    srand(time(NULL));
    gotoxy(10, 3);
    printf("C프로그래밍 4팀 팀프로젝트 보물찾기게임");
    gotoxy(8, 4);
    printf(":*:★,:*:☆ 여왕되기 프로젝트! :*:★,:*:☆");
    gotoxy(4, 5);
    printf("전체 화면으로 확대바랍니다!(확대 후 아무키나 누르시오)");
    _getch();
    system("cls");
    getConsoleSize(&consoleWidth, &consoleHeight);
    initBoard();

    getUserName();
    menu();

    return 0;
}
void getUserName() {

    const char* borderTop[] = {
        "+----------------------------------------------------------------------------+",
        "|  Hunting Treasure.exe                                                 [x]  |",
        "+----------------------------------------------------------------------------+"
    };

    const char* sugar2[] = {
        " _____  _   _  _____   ___  ______  _____ ",
        "/  ___|| | | ||  __ \\ / _ \\ | ___ \\/ __  \\",
        "\\ `--. | | | || |  \\// /_\\ \\| |_/ /`' / /'",
        " `--. \\| | | || | __ |  _  ||    /   / /  ",
        "/\\__/ /| |_| || |_\\ \\| | | || |\\ \\ ./ /___",
        " \\____/  \\___/  \\____/\\_| |_/\\_| \\_|\\_____/ ",
        "                                           ",
        "                                           "
    };

    const char* rune[] = {
        " ______  _   _  _   _  _____ ",
        "| ___ \\| | | || \\ | ||  ___|",
        "| |_/ /| | | ||  \\| || |__  ",
        "|    / | | | || . ` ||  __| ",
        "| |\\ \\ | |_| || |\\  || |___ ",
        "\\_| \\_| \\___/ \\_| \\_/\\____/ ",
        "                            ",
        "                            "
    };

    const char* menu[] = {
        "이름을 입력해주세요! "
    };

    const char* borderBottom[] = {
        "+----------------------------------------------------------------------------+"
    };

    system("cls");

    // 위쪽 테두리 출력
    printCentered(borderTop, sizeof(borderTop) / sizeof(borderTop[0]), -12);
    // "SUGAR²" 출력
    printCentered(sugar2, sizeof(sugar2) / sizeof(sugar2[0]), -5);
    // "RUNE" 출력
    printCentered(rune, sizeof(rune) / sizeof(rune[0]), 2);
    // 아래쪽 테두리 출력
    printCentered(borderBottom, sizeof(borderBottom) / sizeof(borderBottom[0]), 10);
    // 좌우 테두리 출력
    int leftBorderX = (consoleWidth - strlen(borderBottom[0])) / 2;
    for (int y = (consoleHeight - 20) / 2; y < (consoleHeight + 20) / 2; y++) {
        gotoxy(leftBorderX, y);
        printf("|");
        gotoxy(leftBorderX + strlen(borderBottom[0]) - 1, y);
        printf("|");
    }

    // 질문 출력
    printCentered(menu, sizeof(menu) / sizeof(menu[0]), 8);

    gotoxy((consoleWidth - strlen(menu[0])) / 2, consoleHeight + 8);
    scanf("%s", name);

    // 입력 받은 이름을 같은 위치에 출력
    gotoxy((consoleWidth - strlen(menu[0])) / 2, (consoleHeight / 2) + 8);
    printf("   %s님 안녕하세요!        ", name);
    Sleep(1000);
}

void initBoard() {
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            if (i == 0 || i == MAP_HEIGHT - 2 || j == 0 || j == MAP_WIDTH - 1) {
                map[i][j] = WALL;
            }
            else {
                map[i][j] = SPACE;
            }
        }
    }
    initRandomPosition(&player);
    map[player.y][player.x] = PLAYER;
    initRandomPosition(&treasure);
    map[treasure.y][treasure.x] = TREASURE;

    for (int i = 0; i < NUM_GIFTS; i++) {
        initRandomPosition(&gift[i]);
        map[gift[i].y][gift[i].x] = GIFT;
    }

    for (int i = 0; i < NUM_PENALTY; i++) {
        initRandomPosition(&penalty[i]);
        map[penalty[i].y][penalty[i].x] = PENALTY;
    }

    for (int i = 0; i < monsterNum; i++) {
        initRandomPosition(&monster[i]);
        map[monster[i].y][monster[i].x] = MONSTER;
    }
}
void initRandomPosition(Pointer* type) {
    do {
        type->x = rand() % (MAP_WIDTH - 3) + 2;
        type->y = rand() % (MAP_HEIGHT - 4) + 2;
    } while (map[type->y][type->x] != SPACE);
}
void initGameVariables() {
    playertick = 31.25;
    monstertick = 125;
    endsignal = 0;
    treasureFound = 0;
    score = 0;
    gametime = 180;
    item_time = 0;
}

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
void menu() {
    initGameVariables();
    system("cls");
    PlaySound(TEXT("sound\\gamestart.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    printArea();
    printMenu();
    printSelectionBox(MENU_LEFT_ALIGN - 3, MENU_TOP_ALIGN - 1);
    switchMenu();
}
void printMenu()
{
    gotoxy(7, 5);
    printf("메뉴 선택");
    gotoxy(7, 6);
    printf("방향키를 이용하여 선택하고 엔터키를 누르십시오.");

    gotoxy(MENU_LEFT_ALIGN, MENU_TOP_ALIGN);
    printf("Game Start");
    gotoxy(MENU_LEFT_ALIGN, MENU_TOP_ALIGN + MENU_LINE_SPACE);
    printf("Instructions");
    gotoxy(MENU_LEFT_ALIGN, MENU_TOP_ALIGN + MENU_LINE_SPACE * 2);
    printf("EXIT");
}
void switchMenu() {
    int menuNum = 1;
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
            if (key == 224) // 방향키
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
        exit(0);
    }
}
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
    int temp = 1;
    while (1) {
        if (_kbhit()) {
            key = _getch();

            if (key == 13) // 엔터키
            {
                break;
            }
            if (key == 224) // 방향키 모두
            {
                key = _getch();
                if (key == 72 && temp > 1) // 위쪽 방향키
                {
                    eraseSelectionBox(SELECTION_BOX_LEFT_ALIGN, MENU_TOP_ALIGN - 1 + ((temp - 1) * MENU_LINE_SPACE));
                    temp--;
                    printSelectionBox(SELECTION_BOX_LEFT_ALIGN, MENU_TOP_ALIGN - 1 + ((temp - 1) * MENU_LINE_SPACE));
                }
                else if (key == 80 && temp < 3) // 아래쪽 방향키
                {
                    eraseSelectionBox(SELECTION_BOX_LEFT_ALIGN, MENU_TOP_ALIGN - 1 + ((temp - 1) * MENU_LINE_SPACE));
                    temp++;
                    printSelectionBox(SELECTION_BOX_LEFT_ALIGN, MENU_TOP_ALIGN - 1 + ((temp - 1) * MENU_LINE_SPACE));
                }
            }

        }
    }
    runDifficultyMenu(temp);
}
void runDifficultyMenu(int num)
{
    switch (num)
    {
    case 1:
        startEasyGame();
        break;
    case 2:
        startNormalGame();
        break;
    case 3:
        startHardGame();
        break;
    }
}

void gameRule() {
    int x, y;

    PlaySound(NULL, NULL, 0); // 현재 재생 중인 사운드를 중지
    PlaySound(TEXT("sound\\gamerule.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    system("cls");

    const char* messages[] = {
        "마계에서 인간 세계로 내려온 마녀인 당신!",
        "마계의 여왕이 되기 위해서는, 인간들의 하트를 빼앗아야 합니다.",
        "인간들에게 호감을 얻고, 하트를 획득해보세요!",
        " ",
        "플레이어는 *으로 표시되며, 깃발은 F로 몬스터는 &으로 표시됩니다.",
        "플레이어는 방향키를 이용해 이동할 수 있습니다.",
        " ",
        "1단계에서는 '그린 하트'(900점), 2단계에서는 '핑크 하트'(1200점) 이상을 얻어야 다음 단계로 넘어갈 수 있습니다.",
        "3단계에서 '레드 하트'(1500점)을 얻으면 여왕이 될 수 있습니다.",
        "ESC키를 누르면 게임을 중단하고 메뉴 화면으로 돌아갑니다.",
        "게임을 시작하려면 아무 키나 누르세요..."
    };

    for (int i = 0; i < consoleHeight; i++) {
        gotoxy(0, i);
        if (i == 0) {
            printf("┌");
            for (int j = 0; j < consoleWidth - 2; j++) printf("─");
            printf("┐");
        }
        else if (i == consoleHeight - 1) {
            printf("└");
            for (int j = 0; j < consoleWidth - 2; j++) printf("─");
            printf("┘");
        }
        else {
            printf("│");
            gotoxy(consoleWidth - 1, i);
            printf("│");
        }
    }

    x = (consoleWidth - strlen("Skip을 하려면 엔터키를 누르세요.")) / 2; // 중앙 정렬
    gotoxy(x, 1);
    printf("Skip을 하려면 엔터키를 누르세요.");

    y = (consoleHeight - 7) / 2;
    for (int i = 0; i < 11; i++) {
        x = (consoleWidth - strlen(messages[i])) / 2;
        gotoxy(x, y + i);
        slowPrint(15, messages[i]);
    }
    _getch();
    PlaySound(NULL, NULL, 0);
    difficultyMenu();
}

void printArea() {
    gotoxy(0, 1);

    printf("+");
    for (int i = 1; i < MAP_WIDTH - 1; i++) {
        gotoxy(i, 1);
        printf("-");
    }
    printf("+");

    for (int i = 2; i < MAP_HEIGHT - 1; i++) {
        gotoxy(0, i);
        printf("|");
        gotoxy(MAP_WIDTH - 1, i);
        printf("|");
    }

    gotoxy(0, MAP_HEIGHT - 1);
    printf("+");
    for (int i = 1; i < MAP_WIDTH - 1; i++) {
        gotoxy(i, MAP_HEIGHT - 1);
        printf("-");
    }
    printf("+");
}
void printMap() {
    printf("\n");
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            char mark = map[i][j];
            if (mark == SPACE || mark == WALL) {
                printf(" ");
            }
            else if (mark == PLAYER) {
                SetColor(12);
                printf("*");
                SetColor(15);
            }
            else if (mark == MONSTER) {
                printf("&");
            }
            else if (mark == TREASURE)
                printf("F");
            else {
                printf("F");
            }
        }
        printf("\n");
    }
}
void updateMap(int oldX, int oldY, int newX, int newY, char type) {
    if (map[oldY][oldX] != WALL && map[oldY][oldX] != TREASURE && map[oldY][oldX] != GIFT && map[oldY][oldX] != PENALTY) {
        map[oldY][oldX] = SPACE;
        gotoxy(oldX, oldY + 1);
        printf(" ");
    }
    map[newY][newX] = type; // 새로운 위치를 업데이트
    gotoxy(newX, newY + 1);
    if (type == PLAYER) {
        SetColor(12);
        printf("*");
        SetColor(15);
    }
    else if (type == MONSTER) {
        printf("&");
    }
}

void printPlayer(Pointer* position, int dx, int dy) {
    int newX = position->x + dx;
    int newY = position->y + dy;

    if (map[newY][newX] != WALL) {
        updateMap(position->x, position->y, newX, newY, PLAYER);
        position->x = newX;
        position->y = newY;
    }
}
void movePlayer() {

    if (_kbhit()) {
        int key = _getch();
        switch (key) {
        case 72: // 위
            printPlayer(&player, 0, -1);
            break;
        case 80: // 아래
            printPlayer(&player, 0, 1);
            break;
        case 75: // 왼쪽
            printPlayer(&player, -1, 0);
            break;
        case 77: // 오른쪽
            printPlayer(&player, 1, 0);
            break;
        case 27: // ESC
            menu();
            break;
        }
    }
}
void drawPlayer() {
    gotoxy(player.x, player.y + 1);
    SetColor(12);
    printf("*");
    SetColor(15);
    if (_kbhit())
    {
        gotoxy(player.x, player.y + 1);
        printf(" ");
    }
}

void moveMonster(Pointer* monster) {
    int direction = rand() % 4;
    int dx = 0, dy = 0;

    switch (direction) {
    case 0: dy = -1; break; // 위
    case 1: dy = 1; break;  // 아래
    case 2: dx = -1; break; // 왼쪽
    case 3: dx = 1; break;  // 오른쪽
    }

    int newX = monster->x + dx;
    int newY = monster->y + dy;

    if (map[newY][newX] != WALL && map[newY][newX] != TREASURE && map[newY][newX] != GIFT && map[newY][newX] != PENALTY) {
        updateMap(monster->x, monster->y, newX, newY, MONSTER);
        monster->x = newX;
        monster->y = newY;
    }
}
void moveMonsters() {
    for (int i = 0; i < monsterNum; i++) {
        int oldX = monster[i].x;
        int oldY = monster[i].y;
        moveMonster(&monster[i]);
    }
}

void checkFlag()
{
    checkTreasure();
    checkGift();
    checkPenalty();
    checkObstacle();
}
void checkTreasure() {
    if (checkCollision(player, treasure))
    {
        treasureFound = 1;
        MessageBox(NULL, TEXT("보물을 발견하셨습니다!"), TEXT("TREASURE"), MB_OK);
        int box = MessageBox(NULL, TEXT("점수를 계산하시겠습니까?"), TEXT("TREASURE"), MB_YESNO);
        if (box == IDYES) {
            system("cls");
            endsignal = 1; //checkGameEnd()함수에서 endsingnal값으로 게임 종료 여부 확인
        }
        else {
            endsignal = 0;
            gotoxy(treasure.x, treasure.y + 1);
            printf("!");
            map[treasure.y][treasure.x] = TREASURE;

            if (player.x > MAP_WIDTH / 2)
                player.x--;
            else
                player.x++;
            drawPlayer();
        }
    }
}
void checkGift() {
    for (int i = 0; i < 7; i++) {
        if (checkCollision(player, gift[i])) {
            gift[i].x = 0, gift[i].y = 0; // 접촉한 깃발 제거
            if (i < 3) { // 3개의 깃발은 favorableQuestion을 호출
                favorableQuestion();
            }
            else if (i < 5) { // 2개의 깃발은 점수 증가
                score += 300;
                eventPrint();
            }
            else { // 엿보기 안경 획득
                revealTreasureDirection(i);
            }
            if (rand() % 10 + 1 > RAND_STORE_CHANCE) // 확률 따라서 랜덤 상점
                rand_store();
        }
    }
}
void checkPenalty() {
    for (int i = 0; i < NUM_PENALTY; i++)
    {
        if (checkCollision(player, penalty[i]))
        {
            penalty[i].x = 0, penalty[i].y = 0;
            penalty_func();
        }
    }
}
void checkObstacle()
{
    for (int i = 0; i < monsterNum; i++)
    {
        if (checkCollision(player, monster[i]))
        {
            if (score >= 100)
                score -= 100;
            else
                score = 0;
            if (player.x > MAP_WIDTH / 2)
                player.x--;
            else
                player.x++;
            drawPlayer();
        }

    }
}
int checkCollision(Pointer position1, Pointer position2) {
    return (position1.x == position2.x && position1.y == position2.y);
}

void rand_store()
{
    drawSideBox();
    gotoxy(MAP_WIDTH + 6, 5);
    printf("1.몬스터 속도 감소(게임 시간 30초 소모)");
    gotoxy(MAP_WIDTH + 6, 6);
    printf("2.플레이어 속도 증가(게임 시간 30초 소모)");
    gotoxy(MAP_WIDTH + 6, 7);
    printf("3.남은 시간 증가(게임 시간 30초 증가)");
    gotoxy(MAP_WIDTH + 6, 8);
    printf("선택: ");
    gotoxy(MAP_WIDTH + 11, 8);
    int choose;
    scanf("%d", &choose);
    switch (choose)
    {
    case 1:
        item_time += 30;
        monstertick *= 2;
        break;
    case 2:
        item_time += 30;
        playertick *= 0.5;
        break;
    case 3:
        item_time -= 30;
        break;
    }
    eraseSideBox();
}
void penalty_func()
{
    int penalty_rand = rand() % 2; //랜덤으로 패널티가 결정됨
    switch (penalty_rand)
    {
    case 0:
        monstertick *= 0.5;
        break;
    case 1:
        playertick *= 1.5;
        break;
    }
    penaltyPrint(penalty_rand);
}
void drawSideBox() {
    gotoxy(MAP_WIDTH + 3, 3);
    puts("=============================================================================");

    gotoxy(MAP_WIDTH + 3, 19);
    puts("=============================================================================");
}
void eraseSideBox() {
    for (int i = 0; i <= 16; i++) {
        gotoxy(MAP_WIDTH + 3, 3 + i);
        puts("                                                                                                     ");
    }
}
void favorableQuestion() {
    char* question[] = {
    "나 요즘 너무 살찐 것 같지? ㅠㅠ",
    "넌 내 어디가 좋아? 장난치지 말구!",
    "더 이상 연락하지 마, 라는 말을 들었다! 속뜻은?",
    "이 디저트 너무 예쁘고 맛있어 보인다, 라는 말을 들었다! 어떻게 행동할 것인가?",
    "어떤 옷이 제일 나아? 너가 골라주는 거 입을래!",
    "세젤잘이랑 만나고 10억 받을래, 아님 나랑 만날래?",
    "아까 지나간 사람 진짜 엄청 멋있지!!",
    "혹시 전 남자친구랑 나랑 누가 더 나아?",
    "나 이 케이크 먹고 싶은데, 너도 먹을래?"
    };
    char* favorableSelection1[] = {
        "1) 그니까 별로 먹지도 않는데 왜 찌지?",
        "1) 착해서 좋아하지~",
        "1) 연락하지 마",
        "1) 맛있겠다며 먼저 먹여주기",
        "1) 아무거나 입어도 다 예쁜데?",
        "1) 에이, 너랑 만나야지!",
        "1) 아까 누구 지나갔어?",
        "1) 으으음.... 아 왜 그런 걸 물어봐~",
        "1) 난 단 거 싫어서.. 안 먹을래"
    };

    char* favorableSelection2[] = {
        "2) 안 찐 거 같은데..? 쪘어?",
        "2) 아 그런 게 어디 있어~ 좋으면 좋은 거지~",
        "2) 화 풀릴 때까지 계속 연락해",
        "2) 사진 찍고 싶을 수 있으니 기다리기",
        "2) 처음보단 두 번째 거가 낫다!",
        "2) 이건 너무 밸붕인데..? 미안하다 ㅎㅎ",
        "2) 멋있긴 하더라 ㅎㅎ",
        "2) 당연히 너가 제일 좋지!",
        "2) 너 먹고 싶으면 많이 먹어~"
    };

    char* favorableSelection3[] = {
        "3) 살찐 건 모르겠고 멋있기만 한데?",
        "3) 너무 너무 멋있어서 좋아하지~",
        "3) 평생 볼 생각도 하지마",
        "3) 맛있는지 확인해보겠다며 먼저 먹어보기",
        "3) 둘 다 너무 멋있는데 더 편한 바지가 낫지 않을까?",
        "3) 이미 만나고 있는데 10억 어딨지?",
        "3) 하나도 안 잘생겼는데?",
        "3) 난 전남친 같은 거 없는데?",
        "3) 나도 먹고 싶었는데! 다른 거 더 먹고 싶은 건 없어??"
    };
    drawSideBox();
    gotoxy(MAP_WIDTH + 6, 5);
    printf("%s아(야), %s", name, question[questionNum]);
    gotoxy(MAP_WIDTH + 6, 6);
    printf("%s", favorableSelection1[questionNum]);
    gotoxy(MAP_WIDTH + 6, 7);
    printf("%s", favorableSelection2[questionNum]);
    gotoxy(MAP_WIDTH + 6, 8);
    printf("%s", favorableSelection3[questionNum]);
    gotoxy(MAP_WIDTH + 6, 9);
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
        case 2:
            break;
        case 3:
            score += 300;
            break;
        }
    }
    questionNum++;
    if (questionNum == 9)
        questionNum = 0;
    eraseSideBox();
}
void eventPrint() {
    drawSideBox();
    gotoxy(MAP_WIDTH + 5, 5);
    printf("이득 깃발 발견!");
    gotoxy(MAP_WIDTH + 5, 6);
    printf("호감도 +300");
    Sleep(500);
    eraseSideBox();
}
void revealTreasureDirection(int i) {
    drawSideBox();
    gotoxy(MAP_WIDTH + 5, 5);
    printf("엿보기 안경 획득!");
    gotoxy(MAP_WIDTH + 5, 6);
    if (i == 5) { // 보물의 위아래 방향 알려줌
        if (player.y > treasure.y) {
            printf("보물이 현재 위치보다 위에 있습니다.");
        }
        else if (player.y == treasure.y) {
            printf("보물은 현재 위치의 y축과 동일합니다.");
        }
        else {
            printf("보물이 현재 위치보다 아래에 있습니다.");
        }
    }
    else if (i == 6) { // 보물의 좌우 방향 알려줌
        if (player.x < treasure.x) {
            printf("보물이 현재 위치보다 오른쪽에 있습니다.");
        }
        else if (player.x == treasure.x) {
            printf("보물은 현재 위치의 x축과 동일합니다.");
        }
        else {
            printf("보물이 현재 위치보다 왼쪽에 있습니다.");
        }
    }
    Sleep(1000);
    eraseSideBox();
}
void penaltyPrint(int penalty_rand) {
    drawSideBox();
    gotoxy(MAP_WIDTH + 5, 5);
    printf("벌칙 깃발 발견!");
    gotoxy(MAP_WIDTH + 5, 6);
    switch (penalty_rand)
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

void levelUp() {
    initGameVariables();

    if (level != 3) {
        const char* levelUpMessage[] = {
            " _                         _   _   _         _ ",
            "| |                       | | | | | |       | |",
            "| |      ___ __   __  ___ | | | | | | _ __  | |",
            "| |     / _ \\\\ \\ / / / _ \\| | | | | || '_ \\ | |",
            "| |____|  __/ \\ V / |  __/| | | |_| || |_) ||_|",
            "\\_____/ \\___|  \\_/   \\___||_|  \\___/ | .__/ (_)",
            "                                     | |       ",
            "                                     |_|       "
        };
        printCentered(levelUpMessage, sizeof(levelUpMessage) / sizeof(levelUpMessage[0]), -2);

        const char* nextLevelMessage1 = "다음 레벨로 이동합니다...";
        const char* nextLevelMessage2 = "이동하려면 아무 키나 누르세요.";
        printCentered(&nextLevelMessage1, 1, 2);
        printCentered(&nextLevelMessage2, 1, 3);

        while (_kbhit()) _getch(); // 버퍼를 비움
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

        const char* gameClearMessage[] = {
            " _____                           _____  _                     _ ",
            "|  __ \\                         /  __ \\| |                   | |",
            "| |  \\/  __ _  _ __ ___    ___  | /  \\/| |  ___   __ _  _ __ | |",
            "| | __  / _` || '_ ` _ \\  / _ \\ | |    | | / _ \\ / _` || '__|| |",
            "| |_\\ \\| (_| || | | | | ||  __/ | \\__/\\| ||  __/| (_| || |   |_|",
            " \\____/ \\__,_||_| |_| |_| \\___|  \\____/|_| \\___| \\__,_||_|   (_)",
            "                                                                ",
            "                                                                "
        };

        const char* queenMessage = "당신은 마계의 여왕이 되는데 성공하셨습니다.";

        printCentered(gameClearMessage, sizeof(gameClearMessage) / sizeof(gameClearMessage[0]), -2);
        printCentered(&queenMessage, 1, 1);

        Sleep(1000);
        const char* menuMessage1 = "메뉴로 다시 돌아갑니다...";
        const char* menuMessage2 = "이동하려면 아무 키나 누르세요.";
        printCentered(&menuMessage1, 1, 3);
        printCentered(&menuMessage2, 1, 4);

        _getch();
        menu();
    }
}
void startEasyGame() {
    level = 1;
    monsterNum = EASY_MONSTER;
    gameStart();
}
void startNormalGame() {
    level = 2;
    monsterNum = NORMAL_MONSTER;
    gameStart();
}
void startHardGame() {
    level = 3;
    monsterNum = HARD_MONSTER;
    gameStart();
}

void gameStart() {
    system("cls");
    PlaySound(NULL, NULL, 0);
    PlaySound(TEXT("sound\\gaming.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    initBoard();
    printMap();

    time_t start_time = time(NULL);
    clock_t player_std_time, monster_std_time, player_time, monster_time;

    double player_duration, monster_duration;
    player_std_time = clock();
    monster_std_time = clock();

    while (1) {
        printArea();
        player_time = clock();
        monster_time = clock();

        player_duration = (double)(player_time - player_std_time);
        monster_duration = (double)(monster_time - monster_std_time);


        checkFlag();

        time_t current_time = time(NULL);

        if (player_duration >= playertick) { // playertick마다
            movePlayer();
            player_std_time = clock();
        }

        if (monster_duration >= monstertick) { // monstertick마다
            moveMonsters();
            monster_std_time = clock();
        }

        if (current_time - start_time >= 1) {// 1초마다
            int elapsed_time = current_time - start_time + item_time;// 경과된 시간
            int remaining_time = gametime - elapsed_time; // 남은 시간
            gotoxy(4, 0);
            printProgressBar(elapsed_time, gametime);
            gotoxy(0, MAP_HEIGHT + 1);
            printf("▤ 점수 : %04d\t", score);
            printf("▤ 현재 레벨: %d", level);

            if (remaining_time <= 0) {
                endsignal = -1;
            }
        }
        if (checkGameEnd())
            break;

        Sleep(5); // 과도한 반복 방지
    }
}
void printProgressBar(int elapsed_time, int gametime) {
    int position = (int)(((double)elapsed_time / gametime) * BAR_LENGTH);
    if (elapsed_time > 0)
    {

        gotoxy(57, 0);
        printf("           ");
        gotoxy(4, 0);
        printf("%02d:%02d ", elapsed_time / 60, elapsed_time % 60);  // 경과 시간
    }
    else
    {
        gotoxy(57, 0);
        printf("+%2d", -elapsed_time);
        gotoxy(4, 0);
        printf("00:00 ");
    }
    for (int i = 0; i < BAR_LENGTH; i++) {
        if (i == position) {
            printf("#");
        }
        else if (i < position) {
            printf("=");
        }
        else {
            printf("-");
        }
    }
    printf(" %2d:%02d", gametime / 60, gametime % 60);  // 총 시간
    fflush(stdout);
}

int checkGameEnd() { //게임 종료 조건 검사, 게임 종료 확인
    if (endsignal == 1) { // 보물 도달
        endGame(1);
        return 1;
    }

    else if (endsignal == -1) { // 시간초과
        endGame(0);
        return 1;
    }
    else
        return 0;
}
void endGame(int result) {
    system("cls");

    PlaySound(NULL, NULL, 0);
    int screenWidth, screenHeight;
    getConsoleSize(&screenWidth, &screenHeight);

    if (result) {
        calculateScore();
    }
    else {
        PlaySound(TEXT("sound\\gameover.wav"), NULL, SND_FILENAME | SND_ASYNC);

        const char* gameOverMessage[] = {
            " _____                           _____                     _ ",
            "|  __ \\                         |  _  |                   | |",
            "| |  \\/  __ _  _ __ ___    ___  | | | |__   __  ___  _ __ | |",
            "| | __  / _` || '_ ` _ \\  / _ \\ | | | |\\ \\ / / / _ \\| '__|| |",
            "| |_\\ \\| (_| || | | | | ||  __/ \\ \\_/ / \\ V / |  __/| |   |_|",
            " \\____/ \\__,_||_| |_| |_| \\___|  \\___/   \\_/   \\___||_|   (_)",
            "                                                             ",
            "                                                             "
        };
        const char* gameOverMessage2 = "시간이 종료되었습니다.";

        printCentered(gameOverMessage, sizeof(gameOverMessage) / sizeof(gameOverMessage[0]), -2);
        printCentered(&gameOverMessage2, 1, 3);
        Sleep(7000);
        menu();
    }
}
void calculateScore() {
    int consoleWidth, consoleHeight;
    getConsoleSize(&consoleWidth, &consoleHeight);

    const int requiredScore[] = { 900, 1200, 1500 }; // 각 레벨에서 요구되는 점수
    const char* heartColors[] = { "벌꿀색 하트", "오렌지 하트", "그린 하트", "핑크 하트", "레드 하트" };
    const int heartColorsCode[] = { 14, 4, 10, 13, 12 };
    const char* heartDescriptions[] = {
        "깜짝 놀랐을 때 나오는 하트.\n",
        "설레이거나 호감이 생기기 시작할 때 생기는 하트.\n",
        "친구들 사이의 우정의 하트.\n",
        "사랑이 시작할 때 나오는 하트.\n",
        "진실한 사랑의 하트.\n"
    };
    bool levelUpCondition = score >= requiredScore[level - 1];

    int heartIndex = score / 300 - 1;
    if (score == 0)
        heartIndex = 0;

    PlaySound(NULL, NULL, 0);
    PlaySound(TEXT("sound\\levelup.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    system("cls");

    const char* heartColor = heartColors[heartIndex];
    printCentered(&heartColor, 1, -2);

    // 하트 심볼을 중앙에 배치
    const char* heartSymbol[] = { "♥" };
    SetColor(heartColorsCode[heartIndex]);
    printCentered(heartSymbol, 1, 0);
    SetColor(15);

    const char* heartDescription = heartDescriptions[heartIndex];
    printCentered(&heartDescription, 1, 2);
    Sleep(5000);
    system("cls");
    if (!levelUpCondition) {
        const char* failedMessage[] = {
                    "__   __                ______         _  _            _ ",
                    "\\ \\ / /                |  ___|       (_)| |          | |",
                    " \\ V /   ___   _   _   | |_     __ _  _ | |  ___   __| |",
                    "  \\ /   / _ \\ | | | |  |  _|   / _` || || | / _ \\ / _` |",
                    "  | |  | (_) || |_| |  | |    | (_| || || ||  __/| (_| |",
                    "  \\_/   \\___/  \\__,_|  \\_|     \\__,_||_||_| \\___| \\__,_|",
                    "                                                        ",
                    "                                                        "
        };
        printCentered(failedMessage, sizeof(failedMessage) / sizeof(failedMessage[0]), -2);
        Sleep(5000);
        menu();
    }
    else {
        levelUp();
    }
}

// 콘솔 크기에 맞춰 중앙에 텍스트 출력하는 함수
void printCentered(const char* text[], int numLines, int yOffset) {
    // 각 줄의 길이와 콘솔의 중앙 좌표를 계산하여 출력
    int consoleWidth, consoleHeight;
    getConsoleSize(&consoleWidth, &consoleHeight);

    for (int i = 0; i < numLines; i++) {
        int lineLength = strlen(text[i]);
        int x = (consoleWidth - lineLength) / 2;
        int y = (consoleHeight - numLines) / 2 + i + yOffset;
        gotoxy(x, y);
        printf("%s", text[i]);
    }
}

//API
void getConsoleSize(int* width, int* height) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int cols, rows;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    *width = cols;
    *height = rows;
}
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