#include "main.h"
//�������̹氡�氡
int main(void) {
    CursorControl(false);
    srand(time(NULL));

    //������ ����մϴ�.

    getUserName();
    // ���� ����� ����ϴ�.

    menu();

    return 0;
}

//���� ����� �̸� �ޱ�
void getUserName() {
    printArea();
    gotoxy(10, 3);
    printf("%s", "C���α׷��� 4�� ��������Ʈ ����ã�����");

    gotoxy(10, 4);
    printf(":*:��,:*:�� ���յǱ� ������Ʈ! :*:��,:*:��");
    gotoxy(10, 6);
    printf("����� �̸��� �����ΰ���? ");
    scanf("%s", &name);

    gotoxy(10, 9);
    printf("%s�� �ȳ��ϼ���!", &name);
    Sleep(1000);
}

void printArea()
{
    gotoxy(0, 0);
    printf("��");
    for (int i = 0; i < MAP_WIDTH - 2; i++) {
        printf("��");
    }
    printf("��\n");

    for (int i = 0; i < MAP_HEIGHT - 2; i++) {
        printf("��");
        for (int j = 0; j < MAP_WIDTH - 2; j++) {
            printf(" ");
        }
        printf("��\n");
    }

    printf("��");
    for (int i = 0; i < MAP_WIDTH - 2; i++) {
        printf("��");
    }
    printf("��");

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
        printf("��");
    }

    gotoxy(player.x, player.y);
    SetColor(12);
    printf("��");

    while (1) {
        movePlayer();
        SetColor(15);

        checkFlag();
        checkobstacle();

        if (checkGameEnd())
            break;

        time_t current_time = time(NULL); // ���� �ð� ��������

        if (current_time - last_update_time >= 1) { // 1�ʸ���
            moveMonster();
            int elapsed_time = current_time - start_time; // ����� �ð� ���
            int remaining_time = gametime - elapsed_time; // ���� �ð� ��� 

            gotoxy(0, MAP_HEIGHT);
            printf("�� ���� : %d\t", score);
            printf("�� ���� �ð�: %d�� %d��", remaining_time / 60, remaining_time % 60);
            recordAndEndOnTime(remaining_time);

            last_update_time = current_time;
        }
        Sleep(5);
    }
    return 0;
}

//���� ���� ����
void gameRule() {
    system("cls");
    printf("Skip�� �Ϸ��� ����Ű�� �����ÿ�.\n\n");

    slowPrint(50, "���� ����\n");
    slowPrint(50, "�� ������ �÷��̾ �̷� �ӿ��� ������ ã�Ƴ����� �����Դϴ�.\n");
    slowPrint(50, "�÷��̾�� ������ ǥ�õǸ�, ������ ������ ǥ�õ˴ϴ�.\n");
    slowPrint(50, "�÷��̾�� ��, ��, ��, �� Ű�� ����Ͽ� �̵��� �� �ֽ��ϴ�.\n");
    slowPrint(50, "�̵� ���(G)�� ȹ���ϸ� ������ 100�� �����ϰ�, ��Ģ ���(P)�� ������ ������ 1�� �����մϴ�.\n");
    slowPrint(50, "������ ���� ���� �̻��� �Ǹ� ������ Ŭ������ �� �ֽ��ϴ�.\n");
    slowPrint(50, "������ �ð� ������ ������, �ð��� �� �Ǹ� ���� �����˴ϴ�.\n");
    slowPrint(50, "���� ���� ���� �޴��� ���� ���� ���� �Ǵ� ���� ������ ������ �� �ֽ��ϴ�.\n");
    slowPrint(50, "���� �߰����� �޴��� ���� ������ ���� �� �ֽ��ϴ�.\n\n");
    slowPrint(50, "������ �����Ϸ��� �ƹ� Ű�� ��������...");
    _getch(); // �ƹ� Ű�� �Է¹ޱ�
    difficultyMenu();
}
//���� �޴� ȭ��
void menu() {
    system("cls");
    printArea();
    printMenu(); // �޴����� ���
    printSelectionBox(MENU_LEFT_ALIGN - 3, MENU_TOP_ALIGN - 1); // �޴��ڽ� ���
    switchMenu(); // �޴� �Է¹ޱ�
}
//����
void printMenu()
{
    gotoxy(10, 3);
    printf("C���α׷��� 4�� ��������Ʈ ����ã�����");
    gotoxy(10, 4);
    printf(":*:��,:*:�� ���յǱ� ������Ʈ! :*:��,:*:��");
    gotoxy(10, 6);
    printf("�� ����Ű�� �̿��Ͽ� �����ϰ� ����Ű�� �����ʽÿ�.");

    gotoxy(MENU_LEFT_ALIGN, MENU_TOP_ALIGN);
    printf("Game Start");
    gotoxy(MENU_LEFT_ALIGN, MENU_TOP_ALIGN + MENU_LINE_SPACE);
    printf("Instructions");
    gotoxy(MENU_LEFT_ALIGN, MENU_TOP_ALIGN + MENU_LINE_SPACE * 2);
    printf("EXIT");
}
//����
void switchMenu() {
    int menuNum = 1; //1:���ӽ���, 2:���Ӽ���, 3:EXIT
    int key;

    while (1)
    {
        if (_kbhit() != 0)
        {
            key = _getch();

            if (key == 13) // ����Ű
            {
                break;
            }
            if (key == 224) // ����Ű ���
            {
                key = _getch();
                if (key == 72 && menuNum > 1) // ���� ����Ű
                {
                    eraseSelectionBox(SELECTION_BOX_LEFT_ALIGN, MENU_TOP_ALIGN - 1 + ((menuNum - 1) * MENU_LINE_SPACE));
                    menuNum--;
                    printSelectionBox(SELECTION_BOX_LEFT_ALIGN, MENU_TOP_ALIGN - 1 + ((menuNum - 1) * MENU_LINE_SPACE));
                }
                else if (key == 80 && menuNum < 3) // �Ʒ��� ����Ű
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
//����
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
        printf("����Ǿ����ϴ�.");
        break;
    }
}

//���� �޴��ڽ� ���
void printSelectionBox(int x, int y)
{
    gotoxy(x, y);
    puts("������������������������������������������������������������������");
    gotoxy(x, y + 1);
    puts("��");
    gotoxy(x + 32, y + 1);
    puts("��");
    gotoxy(x, y + 2);
    puts("������������������������������������������������������������������");
}
//���� �޴��ڽ� �����
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

//����
// ���̵� ���� �޴�
void difficultyMenu() {
    system("cls");
    printArea();
    printDifficultyMenu();
    printSelectionBox(MENU_LEFT_ALIGN - 3, MENU_TOP_ALIGN - 1);
    switchDifficultyMenu();
}
//����
void printDifficultyMenu()
{
    gotoxy(13, 5);
    printf("���̵� ����\n");

    gotoxy(MENU_LEFT_ALIGN, MENU_TOP_ALIGN);
    printf("�ʱ� Easy Mode");
    gotoxy(MENU_LEFT_ALIGN, MENU_TOP_ALIGN + MENU_LINE_SPACE);
    printf("�߱� Normal Mode");
    gotoxy(MENU_LEFT_ALIGN, MENU_TOP_ALIGN + MENU_LINE_SPACE * 2);
    printf("��� Hard Mode");
}
//����
void switchDifficultyMenu() {
    int key;

    while (1)
    {
        if (_kbhit() != 0)
        {
            key = _getch();

            if (key == 13) // ����Ű
            {
                break;
            }
            if (key == 224) // ����Ű ���
            {
                key = _getch();
                if (key == 72 && level > 1) // ���� ����Ű
                {
                    eraseSelectionBox(SELECTION_BOX_LEFT_ALIGN, MENU_TOP_ALIGN - 1 + ((level - 1) * MENU_LINE_SPACE));
                    level--;
                    printSelectionBox(SELECTION_BOX_LEFT_ALIGN, MENU_TOP_ALIGN - 1 + ((level - 1) * MENU_LINE_SPACE));
                }
                else if (key == 80 && level < 3) // �Ʒ��� ����Ű
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
//����
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


//���� ����� �̵�
void movePlayer() {
    if (_kbhit()) {
        char move = _getch(); // ����Ű �Է¹ޱ�
        gotoxy(player.x, player.y);
        printf(" ");

        switch (move) {
        case 72: // ���� ����Ű
            player.y = player.y > 1 ? player.y - 1 : 1;
            gotoxy(player.x, player.y);
            SetColor(12);
            printf("��");
            break;
        case 80: // �Ʒ��� ����Ű
            player.y = player.y < MAP_HEIGHT - 2 ? player.y + 1 : MAP_HEIGHT - 2;
            gotoxy(player.x, player.y);
            SetColor(12);
            printf("��");
            break;
        case 75: // ���� ����Ű
            player.x = player.x > 1 ? player.x - 1 : 1;
            gotoxy(player.x, player.y);
            SetColor(12);
            printf("��");
            break;
        case 77: // ������ ����Ű
            player.x = player.x < MAP_WIDTH - 2 ? player.x + 1 : MAP_WIDTH - 2;
            gotoxy(player.x, player.y);
            SetColor(12);
            printf("��");
            break;
        case 27:
            menu();
            break;
        }
    }
}

//���� ���� �̵�
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
        //printf("��");

        gotoxy(monster[i].x, monster[i].y);
        printf(" ");
        monster[i].x += monster[i].dx;
        if (monster[i].x <= boundary_monster1[i].x || monster[i].x >= boundary_monster2[i].x)
            monster[i].dx *= -1;
        gotoxy(monster[i].x, monster[i].y);
        printf("��");
    }
}

//�� �ʱ�ȭ
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

//���� ���� �ʿ� �׸���
void printThings() {
    gotoxy(player.x, player.y);
    SetColor(12);
    printf("��");

    SetColor(15);
    gotoxy(treasure.x, treasure.y);
    printf("��");

    for (int i = 0; i < giftNum; i++) {
        gotoxy(gift[i].x, gift[i].y);
        printf("G");
    }

    for (int i = 0; i < penaltyNum; i++) {
        gotoxy(penalty[i].x, penalty[i].y);
        printf("P");
    }
}

//����
// ���� ���ӽð� ���� 
void recordAndEndOnTime(int x)
{
    if (x <= 0) {
        endsignal = -1;
    }
}

//����
//��� ����
void checkFlag()
{
    //���� ���
    if (player.x == treasure.x && player.y == treasure.y)//�÷��̾� ��ġ�� ������� ��ġ�� ����
    {
        MessageBox(NULL, TEXT("������ �߰��ϼ̽��ϴ�!"), TEXT("TREASURE"), MB_OK);
        int temp1 = MessageBox(NULL, TEXT("������ ����Ͻðڽ��ϱ�?"), TEXT("TREASURE"), MB_YESNO);
        if (temp1 == IDYES) {
            system("cls");
            endsignal = 1; //checkGameEnd()�Լ����� endsingnal������ ���� ���� ���� Ȯ��
        }
        else {
            endsignal = 0;
            gotoxy(treasure.x, treasure.y);
            printf("��");

            do {
                player.x = rand() % (MAP_WIDTH - 2) + 1;
                player.y = rand() % (MAP_HEIGHT - 2) + 1;
            } while (player.x != treasure.x && player.y != treasure.y);
        }
    }
    //�̵� ���
    for (int i = 0; i < EASY_GIFT; i++)
    {
        if (player.x == gift[i].x && player.y == gift[i].y)
        {
            gift[i].x = 0, gift[i].y = 0; //������ ��� ����
            score += 300;
            //option(); //������ ��� �� ���ÿ� ���� ���� ����
            //if ((rand() % 10) > rand_store_chance)//Ȯ�������� ���� ����
            //    rand_store();
        }
    }
    //��Ģ ���
    for (int i = 0; i < EASY_PENALTY; i++)
    {
        if (player.x == penalty[i].x && player.y == penalty[i].y)
        {
            penalty[i].x = 0, penalty[i].y = 0;// ������ ��� ����
            score -= 10;
            penalty_func();
        }
    }
}

//����
//��ֹ� ����
void checkobstacle()
{
    for (int i = 0; i < EASY_MONSTER; i++)
    {
        if (player.x == monster[i].x && player.y == monster[i].y)
        {
            score -= 100; //��������
            Sleep(2000); // 2�� ����
        }
    }
}

// ����
//��� ���˽� ������ ����,���� ����
void option()
{
    char benefit_str[5][100] = { "aaa","bbb","ccc","ddd","eee" };//������ ���� ���� �ʿ�, ������ �Է� �ʿ�
    int benefit_str_score[5] = { 100, 200, 300, 400, 500 }; // �������� ��ġ ���� �ʿ�
    int a[3] = { 0 };
    int temp1;

    for (int i = 0; i < 3; i++) //�ߺ� ���� 0~4���� ���� 3�� ����
    {
        a[i] = (rand() % 5);
        for (int j = 0; j < i; j++)
        {
            if (a[i] == a[j])
                i--;
        }
    }
    gotoxy(20, 41); // ������ ��� ��ġ ���� �ʿ�
    printf("1.%s\n2.%s\n3.%s\n", benefit_str[a[0]], benefit_str[a[1]], benefit_str[a[2]]);//������ ���
    scanf("%d", &temp1);//������ ���� �� �Է�
    switch (temp1)//�� �������� �ش��ϴ� ������ �� ������ ���ϱ�
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

//����
//����Ȯ���� ������ ����
void rand_store()
{
    int temp1;
    gotoxy(21, 41); //������ ��� ��ġ ���� �ʿ�
    printf("1.���� �ӵ� ����");
    gotoxy(21, 42);
    printf("2.�÷��̾� �ӵ� ����");
    gotoxy(21, 43);
    printf("3.���� �ð� ����");
    scanf("%d", &temp1);//���ð� �Է�
    switch (temp1)// ���ð��� ���� �ٸ� ȿ��
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

//����
//��Ģ ��߰� ���˽� ����� �г�Ƽ
void penalty_func()
{
    int temp1 = rand() % 3;//�������� �г�Ƽ�� ������
    switch (temp1)
    {
    case 0:
        monstertick *= 0.5;
        break;
    case 1:
        playertick *= 2;
        break;
    case 2:
        //3�� �г�Ƽ ���� �� ����
        break;
    }
}

//����
//���� ���� ���� �˻�, ���� ���� Ȯ��
bool checkGameEnd() {
    // ������ ã�Ҵ��� Ȯ�� 
    if (endsignal == 1) {
        endGame(true);
        return true;
    }
    // �ð��ʰ� Ȯ��
    else if (endsignal == -1) {
        endGame(false);
        return true;
    }
    else
        return false;
}

//���� ���� ȭ��
void endGame(bool result) {
    if (result) {
        calculateScore();
    }
    else {
        system("cls");
        printf("GAME OVER!\n");
        printf("�ð��� ����Ǿ����ϴ�.");
    }
}

// ���� ���
void calculateScore() {
    system("cls");
    printf("����� score�� %d���Դϴ�.\n\n", score);

    if (score < 100) {
        printf("You failed\n\n");
    }
    else if (100 <= score && score < 300) {
        printf("���ܻ� ��Ʈ\n");
        printf("��¦ ����� �� ������ ��Ʈ.\n\n");
        printf("You failed\n\n");
        menu();
    }
    else if (300 <= score && score < 500) {
        printf("������ ��Ʈ\n");
        printf("�����̰ų� ȣ���� ����� ������ �� ����� ��Ʈ.\n\n");
        printf("You failed\n\n");
        menu();
    }
    else if (500 <= score && score < 1000) {
        printf("�׸� ��Ʈ\n");
        printf("ģ���� ������ ������ ��Ʈ.\n\n");
        printf("You failed\n\n");
        menu();
    }
    else if (1000 <= score && score < 3000) {
        printf("��ũ ��Ʈ\n");
        printf("����� ������ �� ������ ��Ʈ.\n\n");
        levelUp();
    }
    else {
        printf("���� ��Ʈ\n");
        printf("������ ����� ��Ʈ.\n\n");
        levelUp();
    }
}

// ���̵����� ����
void levelUp() {
    score = 0; // ���� �ʱ�ȭ
    endsignal = 0;

    if (level != 3) {
        printf("Level Up!");
        Sleep(2000);
        printf("\n���� ������ �̵��մϴ�...");
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
        printf("�޴��� �ٽ� ���ư��ϴ�...");
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