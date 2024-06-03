#include "main.h"
//하이하이방가방가
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
        gotoxy(monster[i].x, monster[i].y);
        printf("◆");
    }

    gotoxy(player.x, player.y);
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


//은서 사용자 이동
void movePlayer() {
    if (_kbhit()) {
        char move = _getch(); // 방향키 입력받기
        gotoxy(player.x, player.y);
        printf(" ");

        switch (move) {
        case 72: // 위쪽 방향키
            player.y = player.y > 1 ? player.y - 1 : 1;
            gotoxy(player.x, player.y);
            SetColor(12);
            printf("♥");
            break;
        case 80: // 아래쪽 방향키
            player.y = player.y < MAP_HEIGHT - 2 ? player.y + 1 : MAP_HEIGHT - 2;
            gotoxy(player.x, player.y);
            SetColor(12);
            printf("♥");
            break;
        case 75: // 왼쪽 방향키
            player.x = player.x > 1 ? player.x - 1 : 1;
            gotoxy(player.x, player.y);
            SetColor(12);
            printf("♥");
            break;
        case 77: // 오른쪽 방향키
            player.x = player.x < MAP_WIDTH - 2 ? player.x + 1 : MAP_WIDTH - 2;
            gotoxy(player.x, player.y);
            SetColor(12);
            printf("♥");
            break;
        case 27:
            menu();
            break;
        }
    }
}

//지아 몬스터 이동
void moveMonster() {
    for (int i = 0; i < monsterNum; i++) {
        //gotoxy(monster[i].x, monster[i].y);
        //printf(" ");
        //if (rand() % 2 == 0)
        //    monster[i].x += monster[i].dx;
        //else
        //    monster[i].y += monster[i].dy;

        //if (monster[i].x == 1 || monster[i].x == MAP_WIDTH - 2)
        //    monster[i].dx *= -1;

        //if (monster[i].y == 1 || monster[i].y == MAP_HEIGHT - 2)
        //    monster[i].dy *= -1;

        //gotoxy(monster[i].x, monster[i].y);
        //printf("◆");

        gotoxy(monster[i].x, monster[i].y);
        printf(" ");
        monster[i].x += monster[i].dx;
        if (monster[i].x <= boundary_monster1[i].x || monster[i].x >= boundary_monster2[i].x)
            monster[i].dx *= -1;
        gotoxy(monster[i].x, monster[i].y);
        printf("◆");
    }
}

//맵 초기화
void initializeBoard() {
    player.x = rand() % (MAP_WIDTH - 2) + 1;
    player.y = rand() % (MAP_HEIGHT - 2) + 1;

    treasure.x = rand() % (MAP_WIDTH - 2) + 1;
    treasure.y = rand() % (MAP_HEIGHT - 2) + 1;

    for (int i = 0; i < giftNum; i++) {
        gift[i].x = rand() % (MAP_WIDTH - 2) + 1;
        gift[i].y = rand() % (MAP_HEIGHT - 2) + 1;
    }

    for (int i = 0; i < penaltyNum; i++) {
        penalty[i].x = rand() % (MAP_WIDTH - 2) + 1;
        penalty[i].y = rand() % (MAP_HEIGHT - 2) + 1;
    }

    for (int i = 0; i < monsterNum; i++) {
        monster[i].x = rand() % (MAP_WIDTH - 2) + 1;
        monster[i].y = rand() % (MAP_HEIGHT - 2) + 1;
        monster[i].dx = (rand() % 2 == 0) ? -1 : 1;
        boundary_monster1[i].x = monster[i].x - 2;
        boundary_monster2[i].x = monster[i].x + 2;
    }
}

//몬스터 제외 맵에 그리기
void printThings() {
    gotoxy(player.x, player.y);
    SetColor(12);
    printf("♥");

    SetColor(15);
    gotoxy(treasure.x, treasure.y);
    printf("★");

    for (int i = 0; i < giftNum; i++) {
        gotoxy(gift[i].x, gift[i].y);
        printf("G");
    }

    for (int i = 0; i < penaltyNum; i++) {
        gotoxy(penalty[i].x, penalty[i].y);
        printf("P");
    }
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
    if (player.x == treasure.x && player.y == treasure.y)//플레이어 위치와 보물깃발 위치가 같음
    {
        MessageBox(NULL, TEXT("보물을 발견하셨습니다!"), TEXT("TREASURE"), MB_OK);
        int temp1 = MessageBox(NULL, TEXT("점수를 계산하시겠습니까?"), TEXT("TREASURE"), MB_YESNO);
        if (temp1 == IDYES) {
            system("cls");
            endsignal = 1; //checkGameEnd()함수에서 endsingnal값으로 게임 종료 여부 확인
        }
        else {
            endsignal = 0;
            gotoxy(treasure.x, treasure.y);
            printf("★");

            do {
                player.x = rand() % (MAP_WIDTH - 2) + 1;
                player.y = rand() % (MAP_HEIGHT - 2) + 1;
            } while (player.x != treasure.x && player.y != treasure.y);
        }
    }
    //이득 깃발
    for (int i = 0; i < EASY_GIFT; i++)
    {
        if (player.x == gift[i].x && player.y == gift[i].y)
        {
            gift[i].x = 0, gift[i].y = 0; //접촉한 깃발 제거
            score += 300;
            //option(); //선택지 출력 후 선택에 따라 점수 변경
            //if ((rand() % 10) > rand_store_chance)//확률적으로 상점 열림
            //    rand_store();
        }
    }
    //벌칙 깃발
    for (int i = 0; i < EASY_PENALTY; i++)
    {
        if (player.x == penalty[i].x && player.y == penalty[i].y)
        {
            penalty[i].x = 0, penalty[i].y = 0;// 접촉한 깃발 제거
            score -= 10;
            penalty_func();
        }
    }
}

//지혁
//장애물 접촉
void checkobstacle()
{
    for (int i = 0; i < EASY_MONSTER; i++)
    {
        if (player.x == monster[i].x && player.y == monster[i].y)
        {
            score -= 100; //점수감소
            Sleep(2000); // 2초 정지
        }
    }
}

// 지혁
//깃발 접촉시 선택지 제공,점수 증가
void option()
{
    char benefit_str[5][100] = { "aaa","bbb","ccc","ddd","eee" };//선택지 갯수 조절 필요, 선택지 입력 필요
    int benefit_str_score[5] = { 100, 200, 300, 400, 500 }; // 점수증가 수치 조절 필요
    int a[3] = { 0 };
    int temp1;

    for (int i = 0; i < 3; i++) //중복 없는 0~4사이 난수 3개 생성
    {
        a[i] = (rand() % 5);
        for (int j = 0; j < i; j++)
        {
            if (a[i] == a[j])
                i--;
        }
    }
    gotoxy(20, 41); // 선택지 출력 위치 조절 필요
    printf("1.%s\n2.%s\n3.%s\n", benefit_str[a[0]], benefit_str[a[1]], benefit_str[a[2]]);//선택지 출력
    scanf("%d", &temp1);//선택지 선택 값 입력
    switch (temp1)//각 선택지에 해당하는 점수를 총 점수에 더하기
    {
    case 1:
        score += benefit_str_score[a[0]];
        break;
    case 2:
        score += benefit_str_score[a[1]];
        break;
    case 3:
        score += benefit_str_score[a[2]];
        break;
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
bool checkGameEnd() {
    // 보물을 찾았는지 확인 
    if (endsignal == 1) {
        endGame(true);
        return true;
    }
    // 시간초과 확인
    else if (endsignal == -1) {
        endGame(false);
        return true;
    }
    else
        return false;
}

//게임 종료 화면
void endGame(bool result) {
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
    }
    else if (100 <= score && score < 300) {
        printf("벌꿀색 하트\n");
        printf("깜짝 놀랐을 때 나오는 하트.\n\n");
        printf("You failed\n\n");
        menu();
    }
    else if (300 <= score && score < 500) {
        printf("오렌지 하트\n");
        printf("설레이거나 호감이 생기기 시작할 때 생기는 하트.\n\n");
        printf("You failed\n\n");
        menu();
    }
    else if (500 <= score && score < 1000) {
        printf("그린 하트\n");
        printf("친구들 사이의 우정의 하트.\n\n");
        printf("You failed\n\n");
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
    giftNum = EASY_GIFT;
    penaltyNum = EASY_PENALTY;
    monsterNum = HARD_PENALTY;
    gameStart();
}
void startNormalGame() {
    giftNum = NORMAL_GIFT;
    penaltyNum = NORMAL_PENALTY;
    monsterNum = NORMAL_PENALTY;
    gameStart();
}
void startHardGame() {
    giftNum = HARD_GIFT;
    penaltyNum = HARD_PENALTY;
    monsterNum = HARD_PENALTY;
    gameStart();
}

//API
void slowPrint(unsigned long speed, const char* s)
{

    int i = 0;

    while (s[i] != 0) {
        printf("%c", s[i++]);
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