#include "main.h"
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
    system("cls");
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
    system("cls");
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
        gotoxy(monster[i][0], monster[i][1]);
        printf("��");
    }

    gotoxy(player[0][0], player[0][1]);
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
    if (_kbhit()) {
        char key = _getch();
        switch (key) {
        case 27://escŰ
            menu();
            return;
        case 13://enterŰ
            difficultyMenu();
            return;
        }
    }
    else {
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


//���� ����� �̵�
void movePlayer() {
    if (_kbhit()) {
        char move = _getch(); // ����Ű �Է¹ޱ�
        gotoxy(player[0][0], player[0][1]);
        printf(" ");

        switch (move) {
        case 72: // ���� ����Ű
            player[0][1] = player[0][1] > 1 ? player[0][1] - 1 : 1;
            gotoxy(player[0][0], player[0][1]);
            SetColor(12);
            printf("��");
            break;
        case 80: // �Ʒ��� ����Ű
            player[0][1] = player[0][1] < MAP_HEIGHT - 2 ? player[0][1] + 1 : MAP_HEIGHT - 2;
            gotoxy(player[0][0], player[0][1]);
            SetColor(12);
            printf("��");
            break;
        case 75: // ���� ����Ű
            player[0][0] = player[0][0] > 1 ? player[0][0] - 1 : 1;
            gotoxy(player[0][0], player[0][1]);
            SetColor(12);
            printf("��");
            break;
        case 77: // ������ ����Ű
            player[0][0] = player[0][0] < MAP_WIDTH - 2 ? player[0][0] + 1 : MAP_WIDTH - 2;
            gotoxy(player[0][0], player[0][1]);
            SetColor(12);
            printf("��");
            break;
        case 27:
            menu();
            break;
        }
    }
}

//����
//���� �̵�
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
        printf("��");

    }
}

//����
// //�� �ʱ�ȭ
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

//����
//���� ���� �ʿ� �׸���
void printThings() {
    gotoxy(player[0][0], player[0][1]);
    SetColor(12);
    printf("��");

    SetColor(15);
    gotoxy(treasure[0][0], treasure[0][1]);
    printf("��");

    for (int i = 0; i < NUM_GIFTS; i++) {
        gotoxy(gift[i][0], gift[i][1]);
        printf("G");
    }

    for (int i = 0; i < NUM_PENALTY; i++) {
        gotoxy(penalty[i][0], penalty[i][1]);
        printf("P");
    }
}

//����
//���Ͱ� �� ����� �ٽ� �׸���
void checkErasing(int x, int y) {
    if (x == treasure[0][0] && y == treasure[0][1]) {
        gotoxy(treasure[0][0], treasure[0][1]);
        SetColor(15);
        printf("��");
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

//����
//ȣ���� ������ �ڽ� �׸���
void drawFavorable() {
    gotoxy(MAP_WIDTH + 3, 3);
    puts("������������������������������������������������������������������������������������������������������������");
    for (int i = 0; i <= 15; i++) {
        gotoxy(MAP_WIDTH + 3, 4 + i);
        puts("��");
        gotoxy(MAP_WIDTH + 56, 4 + i);
        puts("��");
    }
    gotoxy(MAP_WIDTH + 3, 19);
    puts("������������������������������������������������������������������������������������������������������������");
}

//����
//ȣ���� ������ �ڽ� �����
void eraseFavorable() {
    for (int i = 0; i <= 16; i++) {
        gotoxy(MAP_WIDTH + 3, 3 + i);
        puts("                                                         ");
    }
}

//����
//����&������ ��� �Լ�
void favorableQuestion() {
    char* question[] = {
    "Q. '�� ���� �� ����?���� ���� ���� ������ �����?",
    "Q. '�� ��� ����?���� ���� ���� ������ �����?",
    "Q. '�� �̻� �������� ������ �Ӷ���?",
    "Q. ���� ����Ʈ�� ������ ���� ��",
    "Q. '� ���� ����?���� ���� ���� ������ �����?",
    "Q. �������� ������ 10�� �ޱ� VS ���� ������",
    "Q. �Ʊ� ������ ��� ��û ������?",
    "Q. �� ����ģ���� ���� ���� �� ����?",
    "Q. �� �̰� �԰� ������, �ʵ� ���� �ž�?"
    };
    char* favorableSelection1[] = {
        "1) ���� �� �Դ��� �� ����?",
        "1) ���ؼ� ����",
        "1) �������� ��",
        "1) ���ְڴٸ� ���� �Կ��ֱ�",
        "1) �ƹ��ų� �Ծ �� ���۵�?",
        "1) 10�� �ް� �ʶ� ��������!",
        "1) �Ʊ� ���� ��������?",
        "1) �� ����ģ���� �� ���� �ֱ� �߾�",
        "1) �� �� ������"
    };

    char* favorableSelection2[] = {
        "2) �ϳ��� �� �Ⱦ�",
        "2) �׷� �� ��� �־�~ �ʶ� ����",
        "2) ȭ Ǯ�� ������ ��� ������",
        "2) ���� ��� ���� �� ������ ��ٸ���",
        "2) ó������ �� ��° �Ű� ����!",
        "2) ���󿡼� ���� ���� ����̶� ������",
        "2) �� ���ڴ���",
        "2) �翬�� �ʰ� ���� ����!",
        "2) �� �԰� ������ �Ծ�"
    };

    char* favorableSelection3[] = {
        "3) ���� �� �𸣰ڰ� ����",
        "3) ������ ����",
        "3) ��� �� ������ ������",
        "3) ���ִ��� �Ծ�ڴٸ� ���� �Ծ��",
        "3) �� �� ���۵� �� ���� ���� ���� ������?",
        "3) �̹� ������ �ִµ� 10�� �����?",
        "3) �ϳ��� �� �����µ�?",
        "3) �� �� ����ģ�� ���µ�?",
        "3) ���� �԰� �;��µ�! ���� ����"
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
    printf("��: ");
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
    if (player[0][0] == treasure[0][0] && player[0][1] == treasure[0][1]) //�÷��̾� ��ġ�� ������� ��ġ�� ����
    {
        //PlaySound(TEXT("sound\\jump02.wav"), NULL, SND_FILENAME | SND_ASYNC);
        MessageBox(NULL, TEXT("������ �߰��ϼ̽��ϴ�!"), TEXT("TREASURE"), MB_OK);
        int temp1 = MessageBox(NULL, TEXT("������ ����Ͻðڽ��ϱ�?"), TEXT("TREASURE"), MB_YESNO);
        if (temp1 == IDYES) {
            system("cls");
            endsignal = 1; //checkGameEnd()�Լ����� endsingnal������ ���� ���� ���� Ȯ��
        }
        else {
            endsignal = 0;
            gotoxy(treasure[0][0], treasure[0][1]);
            printf("��");

            do {
                player[0][0] = rand() % (MAP_WIDTH - 2) + 1;
                player[0][1] = rand() % (MAP_HEIGHT - 2) + 1;
            } while (player[0][0] != treasure[0][0] && player[0][1] != treasure[0][1]);
        }
    }
    //�̵� ���
    for (int i = 0; i < 3; i++)
    {
        if (player[0][0] == gift[i][0] && player[0][1] == gift[i][1])
        {
            //PlaySound(TEXT("sound\\jump02.wav"), NULL, SND_FILENAME | SND_ASYNC);
            gift[i][0] = 0, gift[i][1] = 0; //������ ��� ����
            drawFavorable();
            favorableQuestion();
            eraseFavorable();
            //if ((rand() % 10) > rand_store_chance)//Ȯ�������� ���� ����
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
        // ���� ���Ʒ� ���� �˷���
        drawFavorable();
        gotoxy(MAP_WIDTH + 5, 5);
        printf("������ �Ȱ� ȹ��!");
        gotoxy(MAP_WIDTH + 5, 6);
        if (player[0][1] > treasure[0][1]) {
            printf("������ ���� ��ġ���� ���� �ֽ��ϴ�.");
        }
        else if (player[0][1] == treasure[0][1])
            printf("������ ���� ��ġ�� y��� �����մϴ�.");
        else {
            printf("������ ���� ��ġ���� �Ʒ��� �ֽ��ϴ�.");
        }
        Sleep(1000);
        eraseFavorable();
    }
    if (player[0][0] == gift[6][0] && player[0][1] == gift[6][1]) {
        gift[6][0] = 0, gift[6][1] = 0;
        // ���� �¿� ���� �˷���
        drawFavorable();
        gotoxy(MAP_WIDTH + 5, 5);
        printf("������ �Ȱ� ȹ��!");
        gotoxy(MAP_WIDTH + 5, 6);
        if (player[0][0] < treasure[0][0])
            printf("������ ���� ��ġ���� �����ʿ� �ֽ��ϴ�.");
        else if (player[0][0] == treasure[0][0])
            printf("������ ���� ��ġ�� x��� �����մϴ�.");
        else
            printf("������ ���� ��ġ���� ���ʿ� �ֽ��ϴ�.");
        Sleep(1000);
        eraseFavorable();
    }


    //��Ģ ���
    for (int i = 0; i < NUM_PENALTY; i++)
    {
        if (player[0][0] == penalty[i][0] && player[0][1] == penalty[i][1])
        {
            //PlaySound(TEXT("sound\\jump02.wav"), NULL, SND_FILENAME | SND_ASYNC);
            penalty[i][0] = 0, penalty[i][1] = 0;// ������ ��� ����
            score -= 100;
            penalty_func();
        }
    }


    // ���Ϳ� ���˽� �ٽ� ���
    for (int i = 0; i < monsterNum; i++)
    {
        if (monster[i][0] == treasure[0][0] && monster[i][1] == treasure[0][1]) {
            gotoxy(treasure[0][0], treasure[0][1]);
            SetColor(15);
            printf("��");
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

//����
//��ֹ� ����
void checkobstacle()
{
    for (int i = 0; i < monsterNum; i++)
    {
        if (player[0][0] == monster[i][0] && player[0][1] == monster[i][1])
        {
            //PlaySound(TEXT("sound\\jump02.wav"), NULL, SND_FILENAME | SND_ASYNC);
            score -= 100; //��������
            Sleep(2000); // 2�� ����
        }
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
int checkGameEnd() {
    // ������ ã�Ҵ��� Ȯ��
    if (endsignal == 1) {
        endGame(1);
        return 1;
    }
    // �ð��ʰ� Ȯ��
    else if (endsignal == -1) {
        endGame(0);
        return 1;
    }
    else
        return 0;
}

//���� ���� ȭ��
void endGame(int result) {
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
        Sleep(2000);
        endsignal = 0;
        score = 0;
        menu();
    }
    else if (100 <= score && score < 300) {
        printf("���ܻ� ��Ʈ\n");
        printf("��¦ ����� �� ������ ��Ʈ.\n\n");
        printf("You failed\n\n");
        Sleep(2000);
        endsignal = 0;
        score = 0;
        menu();
    }
    else if (300 <= score && score < 500) {
        printf("������ ��Ʈ\n");
        printf("�����̰ų� ȣ���� ����� ������ �� ����� ��Ʈ.\n\n");
        printf("You failed\n\n");
        Sleep(2000);
        endsignal = 0;
        score = 0;
        menu();
    }
    else if (500 <= score && score < 1000) {
        printf("�׸� ��Ʈ\n");
        printf("ģ���� ������ ������ ��Ʈ.\n\n");
        printf("You failed\n\n");
        Sleep(2000);
        endsignal = 0;
        score = 0;
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