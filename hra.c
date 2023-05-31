#include "hra.h"

#define SIZE_Y 30
#define SIZE_X 60
#define MAX_SCORES 3
int boss = 0;
int Ecounter = 0;
int i, j, k;
int map[SIZE_Y][SIZE_X][2];
char Controller = 'V';
int x = 10;
int y = 10;
int option = 1;
char keyPressed;

typedef struct
{
    char name[100];
    float score;
} ScoreEntry;

char nickname[20];
struct stats
{
    int hp;
    int maxhp;
    int mana;
    int maxmana;
    int dmg;
    int lvl;
    int exp;
    int totalexp;
    int maxexp;
    int gold;
    int totalgold;
    int armor;
    int defense;
    int weapondmg;
    int totaldmg;
} self, monster;

void Welcome()
{
    FILE *f = fopen("title.txt", "r");
    char c;
    while ((c = fgetc(f)) != EOF)
    {
        printf("%c", c);
    }
    fclose(f);
    Sleep(2000);
    printf("\n\nWelcome to the game!\n");
    printf("What is your nickname?\n\n");

    scanf("%s", nickname);

    system("cls");
    printf("Hello %s,\n", nickname);
    Sleep(1000);
}
void StartPlayer()
{
    srand(time(NULL));
    self.maxhp = 100;
    self.hp = 100;
    self.maxmana = 100;
    self.mana = 100;
    self.dmg = rand() % 21 + 20;
    self.lvl = 0;
    self.exp = 0;
    self.maxexp = 100;
    self.totalexp = 0;
    self.gold = 0;
    self.totalgold = 0;
    self.armor = 0;
    self.weapondmg = 0;
}
char *getRandomMonster(const char *folderPath)
{
    DIR *dir;
    struct dirent *entry;
    int fileCount = 0;
    char **fileList = NULL;

    dir = opendir(folderPath);
    // Count the number of files in the directory
    while ((entry = readdir(dir)) != NULL)
    {
        // Check if it's a regular file using stat()
        struct stat fileStat;
        char filePath[PATH_MAX];
        snprintf(filePath, sizeof(filePath), "%s/%s", folderPath, entry->d_name);
        if (stat(filePath, &fileStat) == 0 && S_ISREG(fileStat.st_mode))
        {
            fileCount++;
            fileList = realloc(fileList, fileCount * sizeof(char *));
            fileList[fileCount - 1] = malloc(strlen(entry->d_name) + 1);
            strcpy(fileList[fileCount - 1], entry->d_name);
        }
    }
    closedir(dir);

    srand(time(NULL));
    int randomIndex = rand() % fileCount;

    char *filePath = malloc(strlen(folderPath) + strlen(fileList[randomIndex]) + 2);
    sprintf(filePath, "%s/%s", folderPath, fileList[randomIndex]);

    // Free memory
    for (int i = 0; i < fileCount; i++)
    {
        free(fileList[i]);
    }
    free(fileList);

    return filePath;
}
void Menu()
{

    int totalOptions = 5;

    while (1)
    {
        system("cls");
        printf("What do you want to do?\n");
        printf("-Explore%s\n", (option == 1) ? " <--" : "");
        printf("-Status/Inventory%s\n", (option == 2) ? " <--" : "");
        printf("-Shop%s\n", (option == 3) ? " <--" : "");
        printf("-Leaderboard%s\n", (option == 4) ? " <--" : "");
        printf("-Exit%s\n", (option == 5) ? " <--" : "");

        keyPressed = getch();

        if (keyPressed == 'w')
        {
            if (option > 1)
                option--;
            else
                option = totalOptions;
        }
        else if (keyPressed == 's')
        {
            if (option < totalOptions)
                option++;
            else
                option = 1;
        }

        else // Other keys
        {
            switch (option)
            {
            case 1:
            {
                system("cls");
                while (1)
                {

                    levelUp();
                    Print_map();
                    MoveControl();
                    MoveUpdate();
                    if (Controller == 'q')
                    {
                        break;
                    }
                }
            }
            break;
            case 2:
            {
                system("cls");
                printf("Your HP: %d/%d\n", self.hp, self.maxhp);
                printf("Your armor: %d\n", self.armor);
                printf("Your mana: %d/%d\n", self.mana, self.maxmana);
                printf("Your damage: %d\n", self.dmg + self.weapondmg);
                printf("Your level: %d\n", self.lvl);
                printf("Your exp: %d/%d\n", self.exp, self.maxexp);
                printf("Your gold: %d\n", self.gold);
                system("pause");
                system("cls");
                UsePotion();
                system("cls");
            }
            break;
            case 3:
            {
                system("cls");
                shop();
            }
            break;
            case 4:
            {
                system("cls");
                FILE *file = fopen("score.txt", "r");
                ScoreEntry scores[100];
                int count = 0;
                char name[100];
                float score;

                while (fscanf(file, "%[^:]: %f\n", name, &score) == 2)
                {
                    strcpy(scores[count].name, name);
                    scores[count].score = score;
                    count++;
                }

                fclose(file);

                qsort(scores, count, sizeof(ScoreEntry), compare_scores);

                int numScoresToPrint = count < 10 ? count : 10; // Select minimum of count or 10

                printf("Top %d Scores:\n", numScoresToPrint);
                for (int i = 0; i < numScoresToPrint; i++)
                {
                    printf("%d. %s: %.1f\n", i + 1, scores[i].name, scores[i].score);
                }
                system("pause");
            }
            break;
            case 5:
            {
                self.hp = 0;
                End();
            }
            break;
            default:
                printf("Wrong choice!\n");
                break;
            }
        }
    }
}
int compare_scores(const void *a, const void *b)
{
    const ScoreEntry *entryA = (const ScoreEntry *)a;
    const ScoreEntry *entryB = (const ScoreEntry *)b;
    if (entryA->score < entryB->score)
    {
        return 1;
    }
    else if (entryA->score > entryB->score)
    {
        return -1;
    }
    return 0;
}
void Combat()
{
    srand(time(NULL));
    // open a random .txt file from the folder enemies
    if (boss % 5 == 0 && boss != 0)
    {
        monster.maxhp = rand() % 201 + 100;
        monster.dmg = rand() % 31 + 70;
    }
    else
    {
        monster.maxhp = rand() % 81 + 10;
        monster.dmg = rand() % 31 + 20;
    }

    monster.hp = monster.maxhp;

    monster.exp = (monster.maxhp + monster.dmg) * 2;
    monster.gold = monster.exp / 2;
    char biomepath[50];
    if (map[y][x][0] == 1)
    {
        strcpy(biomepath, "enemies/plains");
    }
    else if (map[y][x][0] == 2)
    {
        strcpy(biomepath, "enemies/forest");
    }
    else if (map[y][x][0] == 4)
    {
        strcpy(biomepath, "enemies/mountains");
    }

    char *filePath = getRandomMonster(biomepath);
    char *fileName = strrchr(filePath, '/');
    if (fileName == NULL)
    {
        fileName = filePath;
    }
    else
    {
        fileName++;
    }

    char *nameWithoutExtension = malloc(strlen(fileName) - 3 + 1);
    strncpy(nameWithoutExtension, fileName, strlen(fileName) - 4);
    nameWithoutExtension[strlen(fileName) - 4] = '\0';
    if (boss % 5 == 0 && boss != 0)
    {
        printf("You encountered a BOSS %s!\n", nameWithoutExtension);
    }
    else
    {
        printf("You encountered a %s!\n", nameWithoutExtension);
    }
    system("pause");
    system("cls");

    FILE *file = fopen(filePath, "r");

    int c;

    if (boss % 5 == 0 && boss != 0)
        printf("\033[0;31m");

    while ((c = fgetc(file)) != EOF)
    {
        putchar(c);
    }
    printf("\033[0m");
    fclose(file);
    free(nameWithoutExtension);
    free(filePath);
    int totalOptions = 5;
    while (monster.hp > 0 && self.hp > 0)
    {
        while (1)
        {
            printf("-----------------------------------------------------------------\n");
            printf("\t\t\tENEMY STATS\t\t\t\t|\n");
            printf("-----------------------------------------------------------------\n");
            printf("\tHP: %d/%d\n", monster.hp, monster.maxhp);
            printf("-----------------------------------------------------------------\n");
            printf("\t\t\tYOUR STATS\t\t\t\t|\n");
            printf("-----------------------------------------------------------------\n");
            printf("\tHP: %d/%d\tMANA: %d/%d\tARMOR: %d\tDMG: %d\n", self.hp, self.maxhp, self.mana, self.maxmana, self.armor, self.dmg + self.weapondmg);
            printf("\nWhat do you want to do?\n");
            printf("-Attack%s\n", (option == 1 ? " <--" : ""));
            printf("-Skills%s\n", (option == 2 ? " <--" : ""));
            printf("-Defend%s\n", (option == 3 ? " <--" : ""));
            printf("-Inventory%s\n", (option == 4 ? " <--" : ""));
            printf("-Run%s\n", (option == 5 ? " <--" : ""));
            keyPressed = getch();
            if (keyPressed == 'w')
            {
                option--;
                if (option < 1)
                {
                    option = totalOptions;
                }
            }
            else if (keyPressed == 's')
            {
                option++;
                if (option > totalOptions)
                {
                    option = 1;
                }
            }

            else
                break;
            printf("\033[15A");
            printf("\033[0J");
        }

        printf("\033[6A");
        printf("\033[0J");
        self.totaldmg = self.dmg + self.weapondmg + rand() % 16 + 0;
        switch (option)
        {
        case 1:
        {
            printf("You chose to attack!\n");
            printf("You dealt %d damage to the monster!\n", self.totaldmg);
            monster.hp -= self.totaldmg;
            system("pause");
            printf("\033[3A");
            printf("\033[0J");
        }
        break;
        case 2:
        {
            int totaloptions = 2;
            int option = 1;
            while (1)
            {
                printf("You chose to use a skill!\n");
                printf("-Normal skills%s\n", (option == 1 ? " <--" : ""));
                printf("-Special skills%s\n", (option == 2 ? " <--" : ""));
                keyPressed = getch();
                if (keyPressed == 'w')
                {
                    option--;
                    if (option < 1)
                    {
                        option = totaloptions;
                    }
                }
                else if (keyPressed == 's')
                {
                    option++;
                    if (option > totaloptions)
                    {
                        option = 1;
                    }
                }
                else
                    break;
                printf("\033[3A");
                printf("\033[0J");
            }
            switch (option)
            {
            case 1:
            {
                while (1)
                {
                    printf("\033[3A");
                    printf("\033[0J");
                    printf("-Fireball%s\n", (option == 1 ? " <--" : ""));
                    printf("-Icebolt%s\n", (option == 2 ? " <--" : ""));
                    printf("-Lightning%s\n", (option == 3 ? " <--" : ""));
                    keyPressed = getch();
                    if (keyPressed == 'w')
                    {
                        option--;
                        if (option < 1)
                        {
                            option = 3;
                        }
                    }
                    else if (keyPressed == 's')
                    {
                        option++;
                        if (option > 3)
                        {
                            option = 1;
                        }
                    }
                    else
                        break;
                }
                printf("\033[3A");
                printf("\033[0J");
                switch (option)
                {
                case 1:
                {
                    if (self.mana < 10)
                    {
                        printf("The skill didn't work!\n");
                        printf("You don't have enough mana!\n");
                        break;
                    }
                    printf("You used Fireball!\n");
                    printf("You dealt %d damage to the monster!\n", self.totaldmg + 5);
                    monster.hp -= self.totaldmg + 5;
                    self.mana -= 10;
                }
                break;
                case 2:
                {
                    if (self.mana < 15)
                    {
                        printf("The skill didn't work!\n");
                        printf("You don't have enough mana!\n");
                        break;
                    }
                    printf("You used Icebolt!\n");
                    printf("You dealt %d damage to the monster!\n", self.totaldmg + 10);
                    monster.hp -= self.totaldmg + 10;
                    self.mana -= 15;
                }
                break;
                case 3:
                {
                    if (self.mana < 20)
                    {
                        printf("The skill didn't work!\n");
                        printf("You don't have enough mana!\n");
                        break;
                    }
                    printf("You used Lightning!\n");
                    printf("You dealt %d damage to the monster!\n", self.totaldmg + 15);
                    monster.hp -= self.totaldmg + 15;
                    self.mana -= 20;
                }
                break;
                }
            }
            break;
            case 2:
            {
            }
            break;
            }
            if (self.mana < 0)
            {
                self.mana = 0;
            }
            system("pause");
            printf("\033[3A");
            printf("\033[0J");
        }
        break;
        case 3:
        {
            printf("You chose to defend!\n");
            self.defense = rand() % 31 + 20;
            printf("You are blocking %d of dmg!\n", self.defense);
            system("pause");
            printf("\033[3A");
            printf("\033[0J");
        }
        break;
        case 4:
        {
            UsePotion();
        }
        break;
        case 5:
        {
            printf("You chose to run!\n");
            if (rand() % 2 == 0)
            {
                printf("You have successfully ran away!\n");
                system("pause");
                system("cls");
                return;
            }
            else
            {
                printf("You failed to run away!\n");
            }
            system("pause");
            printf("\033[3A");
            printf("\033[0J");
        }
        break;
        }
        if (monster.hp > 0)
        {
            monster.totaldmg = (monster.dmg + rand() % 16 + 0) - self.defense;
            printf("The monster attacked you!\n");
            if (monster.totaldmg >= 0)
            {
                printf("The monster dealt %d damage to you!\n", monster.totaldmg);
                self.hp -= monster.totaldmg;
            }
            else
            {
                printf("The monster dealt 0 damage to you!\n");
            }
            self.defense = 0;
            system("pause");
            printf("\033[2A");
            printf("\033[0J");
        }
        printf("\033[10A");
        printf("\033[0J");
    }
    if (self.hp > 0)
    {
        system("cls");
        printf("You have defeated the monster!\n");
        printf("You gained %d gold and %d exp!\n", monster.gold, monster.exp);
        self.gold += monster.gold;
        self.exp += monster.exp;
        self.totalgold += self.gold;
        self.totalexp += self.exp;
    }

    End();
    system("pause");
    system("cls");
}
void levelUp()
{
    if (self.exp >= self.maxexp)
    {
        self.lvl++;
        self.exp = 0;
        self.maxexp += 100;
        self.maxhp += 10;
        self.maxmana += 10;
        self.dmg += 5;
        printf("You leveled up!\n");
        printf("You are now level %d!\n", self.lvl);
        printf("You gained 10 max HP!\n");
        printf("You gained 10 max mana!\n");
        printf("You gained 5 damage!\n");

        if (self.lvl % 3 == 0)
        {
            system("cls");
            printf("Choose a special skill:\n");

            // Načtení speciálních schopností ze souboru
            FILE *file = fopen("skills/special.txt", "r");
            if (file != NULL)
            {
                const int maxSkills = 3;
                char skills[maxSkills][100]; // Max 100 znaků na řádek schopnosti

                int numSkills = 0;
                char line[100];
                while (fgets(line, sizeof(line), file) != NULL)
                {
                    if (numSkills >= maxSkills)
                    {
                        break;
                    }
                    strncpy(skills[numSkills], line, sizeof(skills[numSkills]) - 1);
                    skills[numSkills][strlen(skills[numSkills]) - 1] = '\0'; // Odstranění nového řádku
                    numSkills++;
                }

                fclose(file);

                // Výběr náhodných schopností
                srand(time(NULL));
                for (int i = 0; i < maxSkills; i++)
                {
                    int randomIndex = rand() % numSkills;
                    printf("%d. %s\n", i + 1, skills[randomIndex]);
                }

                // Zde by hráč mohl vybrat speciální schopnost a provést příslušné akce
            }
            else
            {
                printf("Error: Failed to open specials.txt\n");
            }
        }

        system("pause");
        system("cls");
    }
}
void CreateScore()
{
    FILE *file = fopen("score.txt", "a");
    float totalscore = ((float)self.totalexp + (float)self.totalgold) * (1 + ((float)self.lvl / 10));
    fprintf(file, "%s: %.1f\n", nickname, totalscore);
    fclose(file);
}
void End()
{
    if (self.hp <= 0)
    {
        system("cls");
        printf("It's Game Over for %s!\n", nickname);
        printf("You reached level %d!\n", self.lvl);
        printf("You gained a total of %d exp and %d gold!\n", self.totalexp, self.totalgold);
        printf("Thank you for playing!\n");
        system("pause");
        CreateScore();
        ResetItems();
        exit(0);
    }
}
void Generate_map()
{
    int biome_size = 0;
    int distanceY = 0;
    int distanceX = 0;
    int biome_id = 0;
    int flag = 0;

    srand(time(NULL));

    int i, j, k;

    for (i = 0; i < SIZE_Y; i++)
    {
        for (j = 0; j < SIZE_X; j++)
        {
            map[i][j][0] = 1;
            map[i][j][1] = 0;
        }
    }

    for (i = 0; i < SIZE_Y; i++)
    {
        for (j = 0; j < SIZE_X; j++)
        {
            if (map[i][j][0] != 3)
            {
                x = j;
                y = i;
                map[y][x][1] = 1;
                flag = 1;
                break;
            }
        }

        if (flag == 1)
        {
            break;
        }
    }

    for (i = 0; i < 30; i++)
    {
        distanceX = rand() % (SIZE_X - 1) + 1;
        distanceY = rand() % (SIZE_Y - 1) + 1;
        biome_id = rand() % (4 - 2 + 1) + 2;
        biome_size = rand() % (10 - 2 + 1) + 2;

        for (j = 0; j < biome_size; j++)
        {
            for (k = 0; k < biome_size; k++)
            {
                if (distanceY + j < SIZE_Y && distanceX + k < SIZE_X)
                {
                    map[distanceY + j][distanceX + k][0] = biome_id;
                }
            }
        }
    }
}
void SetCursorPosition(int x, int y)
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}

void Print_map()
{
    SetCursorPosition(0, 0);
    for (i = 0; i < SIZE_Y; i++)
    {
        for (j = 0; j < SIZE_X; j++)
        {
            if (map[i][j][0] == 1 && map[i][j][1] == 0)
            {
                printf("\033[0;36m- ");
            }
            else if (map[i][j][0] == 2 && map[i][j][1] == 0)
            {
                printf("\033[0;32mT ");
            }
            else if (map[i][j][0] == 3 && map[i][j][1] == 0)
            {
                printf("\033[0;34mo ");
            }
            else if (map[i][j][0] == 4 && map[i][j][1] == 0)
            {
                printf("\033[0;37mX ");
            }
            else if (map[i][j][1] == 1)
            {
                printf("\033[0;31m$ ");
            }
        }

        printf("\n");
    }
    printf("\033[0m");
    printf("Controls: w, a, s, d\n");
    printf("Press q to quit\n");
}

void MoveControl()
{
    do
    {

        Controller = getch();

    } while (Controller != 'w' && Controller != 'a' && Controller != 's' && Controller != 'd' && Controller != 'q');
}

void MoveUpdate()
{
    if (Controller == 'w' && y - 1 >= 0 && map[y - 1][x][0] != 3)
    {
        map[y][x][1] = 0;
        y = y - 1;
        map[y][x][1] = 1;
    }
    else if (Controller == 's' && y + 1 <= SIZE_Y - 1 && map[y + 1][x][0] != 3)
    {
        map[y][x][1] = 0;
        y = y + 1;
        map[y][x][1] = 1;
    }
    else if (Controller == 'a' && x - 1 >= 0 && map[y][x - 1][0] != 3)
    {
        map[y][x][1] = 0;
        x = x - 1;
        map[y][x][1] = 1;
    }
    else if (Controller == 'd' && x + 1 <= SIZE_X - 1 && map[y][x + 1][0] != 3)
    {
        map[y][x][1] = 0;
        x = x + 1;
        map[y][x][1] = 1;
    }
    srand(time(NULL));
    Ecounter = rand() % 100 + 1;
    if (Ecounter >= 1 && Ecounter <= 30 && Controller != 'q')
    {
        boss++;
        printf("\033[0;31m");
        if (boss % 5 == 0 && boss != 0)
        {
            printf("\nA BOSS MONSTER ATTACKED YOU!!!\n");
        }
        else
        {
            printf("\nA monster attacked you!\n");
        }
        printf("\033[0m");
        Sleep(2000);
        system("cls");
        Combat();
    }
    if (Ecounter >= 31 && Ecounter <= 50 && Controller != 'q')
    {
        printf("\033[0;32m");
        printf("\nYou found a resting spot!\n");
        int hpgain = rand() % 71 + 30;
        int managain = rand() % 71 + 30;
        self.hp += hpgain;
        self.mana += managain;
        if (self.hp > self.maxhp)
        {
            self.hp = self.maxhp;
        }
        if (self.mana > self.maxmana)
        {
            self.mana = self.maxmana;
        }
        printf("You gained %d HP!\n", hpgain);
        printf("You gained %d MANA!\n", managain);
        printf("\033[0m");
        Sleep(2000);
        printf("\033[3A");
        printf("\033[0J");
    }
}

void shop()
{
    char koupe[4];

    printf("Welcome to shop \n");
    Sleep(500);
    printf("This is what we offer\n\n");
    Sleep(1500);
    system("cls");

    do
    {
        printf("POTIONS \n \n");

        printf("1) HEALTH POTION - 30 gold \n");
        printf("gives you 25 hp \n\n");

        printf("2) MANA POTION - 30 gold \n");
        printf("gives you 30 mana power \n\n");

        printf("ARMORS \n \n");

        printf("3) LEATHER ARMOR - 150 \n");
        printf("gives you 50 armor \n\n");

        printf("4) IRON ARMOR - 300 \n");
        printf("gives you 150 armor \n\n");

        printf("5) STEEL ARMOR - 900 \n");
        printf("gives you 300 armor \n\n");

        printf("6) DRAGON ARMOR - 1200 \n");
        printf("gives you 400 armor \n\n");

        printf("7) PLATINUM ARMOR - 1700 \n");
        printf("gives you 550 armor \n\n");

        printf("SHIELDS \n \n");

        printf("8) LEATHER SHIELD - 150 \n");
        printf("gives you 50 armor \n\n");

        printf("9) IRON SHIELD - 300 \n");
        printf("gives you 150 armor \n\n");

        printf("10) STEEL SHIELD - 900 \n");
        printf("gives you 300 armor \n\n");

        printf("11) DRAGON SHIELD - 1200 \n");
        printf("gives you 400 armor \n\n");

        printf("12) PLATINUM SHIELD - 1700 \n");
        printf("gives you 550 armor \n\n");

        printf("WEAPONS \n \n");

        printf("13) WOODEN SWORD - 150 \n");
        printf("gives you 25 damage \n\n");

        printf("14) IRON SWORD - 300 \n");
        printf("gives you 75 damage \n\n");

        printf("15) STEEL SWORD - 900 \n");
        printf("gives you 150 damage \n\n");

        printf("16) DRAGON SWORD - 1200 \n");
        printf("gives you 200 damage \n\n");

        printf("17) PLATINUM SWORD - 1700 \n");
        printf("gives you 275 damage \n\n");

        printf("Press q to leave \n\n");

        scanf("%s",koupe);

        if ((strcmp(koupe, "1")==0))
        {
            if (self.gold >= 30)
            {
                self.gold = self.gold - 30;
                printf("\n");
                printf("you spent 30 gold on health potion \n");
                UpdateItemNumber("health potion");
                Sleep(1200);
                system("cls");
            }
            else
            {
                printf("\n");
                printf("you are too poor :( \n");
                Sleep(1200);
                system("cls");
            }
        }

        if ((strcmp(koupe, "2")==0))
        {
            if (self.gold >= 30)
            {
                self.gold = self.gold - 30;
                printf("\n");
                printf("you spent 30 gold on mana potion \n");
                UpdateItemNumber("mana potion");
                Sleep(1200);
                system("cls");
            }
            else
            {
                printf("\n");
                printf("you are too poor :( \n");
                Sleep(1200);
                system("cls");
            }
        }

        if(strcmp(koupe, "3") == 0 || strcmp(koupe, "4") == 0 || strcmp(koupe, "5") == 0 || strcmp(koupe, "6") == 0 || strcmp(koupe, "7") == 0 || strcmp(koupe, "8") == 0 || strcmp(koupe, "9") == 0 || strcmp(koupe, "10") == 0 || strcmp(koupe, "11") == 0 || strcmp(koupe, "12") == 0 || strcmp(koupe, "13") == 0 || strcmp(koupe, "14") == 0 || strcmp(koupe, "15") == 0 || strcmp(koupe, "16") == 0 || strcmp(koupe, "17") == 0)
        {
            UpdateEquipment(koupe);
        }

        system("cls");

    } while (strcmp(koupe, "q") != 0);
}

void PrintItems()
{
    FILE *file = fopen("items.txt", "r");
    if (file == NULL)
    {
        printf("Failed to open the file.\n");
        return;
    }

    int ch;
    while ((ch = fgetc(file)) != EOF)
    {
        putchar(ch);
    }

    if (ferror(file))
    {
        printf("Error occurred while reading the file.\n");
    }

    fclose(file);
}

void UpdateItemNumber(const char *itemName)
{
    const char *filePath = "items.txt";

    // Read the contents of the file
    FILE *file = fopen(filePath, "r");
    if (file == NULL)
    {
        printf("Failed to open the file.\n");
        return;
    }

    char line[100];
    char modifiedContent[500] = "";
    int foundItem = 0;

    while (fgets(line, sizeof(line), file))
    {
        // Check if the line contains the specified item name
        if (strstr(line, itemName) != NULL)
        {
            foundItem = 1;

            // Extract the item ID and quantity from the line
            int id, quantity;
            sscanf(line, "%d)%*[^0-9]%d", &id, &quantity);

            // Increment the quantity by 1
            quantity++;

            // Generate the modified line with the updated quantity
            char modifiedLine[100];
            snprintf(modifiedLine, sizeof(modifiedLine), "%d) %s %d\n", id, itemName, quantity);

            // Append the modified line to the content string
            strcat(modifiedContent, modifiedLine);
        }
        else
        {
            // Append the original line to the content string
            strcat(modifiedContent, line);
        }
    }

    fclose(file);

    if (!foundItem)
    {
        printf("Item not found in the file.\n");
        return;
    }

    // Write the modified contents back to the file
    file = fopen(filePath, "w");
    if (file == NULL)
    {
        printf("Failed to open the file for writing.\n");
        return;
    }

    fputs(modifiedContent, file);

    fclose(file);
}

void ResetItems()
{
    const char *filePath = "items.txt";
    const char *resetLines[] = {"broken sword", "broken armor", "broken shield"};

    // Open the file for writing
    FILE *file = fopen(filePath, "w");
    if (file == NULL)
    {
        printf("Failed to open the file.\n");
        return;
    }

    // Write the new lines for the first three items
    for (int i = 0; i < 3; i++)
    {
        fprintf(file, "%s\n", resetLines[i]);
    }

    // Write 0 for all other items
    fprintf(file, "\n1) health potion 0\n2) mana potion 0\n");

    fclose(file);
}

void UsePotion()
{
    char input;

    do
    {
        printf("ITEMS:\n \n");
        PrintItems();
        printf("\n");
        printf("mate %d / %d HP \n",self.hp,self.maxhp);
        printf("mate %d / %d HP \n\n",self.mana,self.maxmana);     
        printf("press q to leave \n");
        input = getch();

        if (input == '1' || input == '2')
        {
            DecreaseItemCount(input);
            printf("\033[2A");
            printf("\033[0J");

        }

        printf("\033[13A");
        printf("\033[0J");

    } while (input != 'q');
}

void DecreaseItemCount(char input)
{
    FILE *file, *tempFile;
    int ccount = 0;
    const char *filename = "items.txt";
    const char *tempFilename = "temp_items.txt";
    const int bufferSize = 100;
    char buffer[bufferSize];
    int itemID = input - '0'; // Convert input character to integer ID

    // Open the original file for reading
    file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Failed to open the file %s\n", filename);
        return;
    }

    // Create a temporary file for writing
    tempFile = fopen(tempFilename, "w");
    if (tempFile == NULL)
    {
        printf("Failed to create the temporary file %s\n", tempFilename);
        fclose(file);
        return;
    }

    // Copy the first 3 lines from the original file to the temporary file
    for (int i = 0; i < 3; i++)
    {
        fgets(buffer, bufferSize, file);
        fputs(buffer, tempFile);
    }

    // Find and update the item ccount
    int currentItemID;
    while (fgets(buffer, bufferSize, file) != NULL)
    {
        if (sscanf(buffer, "%d) ", &currentItemID) == 1 && currentItemID == itemID)
        {
            char itemName[bufferSize];
            sscanf(buffer, "%*d) %[^0-9] %d", itemName, &ccount);

            if (input == '1' && ccount != 0)
            {
                printf("\n");
                printf("you drunk health potion and got 25 HP \n");
                Sleep(1100);
                self.hp = self.hp + 25;
                if (self.hp > self.maxhp)
                {
                    self.hp = self.maxhp;
                }
            }
            else if (input == '2' && ccount != 0)
            {
                printf("\n");
                printf("you drunk health potion and got 30 mana power \n");
                Sleep(1100);
                self.mana = self.mana + 30;
                if (self.mana > self.maxmana)
                {
                    self.mana = self.maxmana;
                }
            }

            if (ccount > 0)
            {
                ccount--;
                fprintf(tempFile, "%d) %s%d\n", itemID, itemName, ccount);
            }
            else
            {
                fprintf(tempFile, "%d) %s%d\n", itemID, itemName, ccount); // Write the line as is
            }
        }
        else
        {
            fprintf(tempFile, "%s", buffer); // Write other lines as is
        }
    }

    fclose(file);
    fclose(tempFile);
    // Replace the original file with the temporary file
    if (remove(filename) != 0)
    {
        printf("Failed to remove the original file %s\n", filename);
        return;
    }
    if (rename(tempFilename, filename) != 0)
    {
        printf("Failed to rename the temporary file\n");
    }
}

void UpdateEquipment(char input[4]) {
    int lineCount = 0;
    char line[256];
    char* token;
    char name[20];
    char tool[20];
    int price;
    int value;
    char function[20];
    char temp[256];

    FILE* file = fopen("shop_items.txt", "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    int targetLine = atoi(input);

    while (fgets(line, sizeof(line), file) != NULL) {
        lineCount++;
        if (lineCount == targetLine) {
            char tempLine[256];
            strcpy(tempLine, line);

            token = strtok(tempLine, " \t");

            strcpy(name, token);
            token = strtok(NULL, " \t");
            strcpy(tool, token);
            token = strtok(NULL, " \t");
            price = atoi(token);
            token = strtok(NULL, " \t");
            value = atoi(token);
            token = strtok(NULL, " \t");
            strcpy(function, token);

            if(price>self.gold)
            {
                printf("you are too poor :( \n");
                Sleep(1500);
                return;
            }

            if(strcmp(tool,"armor")==0)
            {
                self.armor=value;
            }
            else if(strcmp(tool,"sword")==0)
            {
                self.weapondmg=value;
            }
            else if(strcmp(tool,"shield")==0)
            {
                self.defense=value;
            }

            printf("item bought \n");

            break;
        }
    }

    fclose(file);

    file = fopen("items.txt", "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        sleep(3);
        return;
    }

    FILE* tempFile = fopen("temporary.txt", "w");
    if (tempFile == NULL) {
        printf("Failed to create the temporary file.\n");
        sleep(3);
        fclose(file);
        return;
    }

    int lineNum = 1;
    int matchLineNum = -1;
    char word1[100], word2[100];

    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%s %s", word1, word2) == 2) {
            if (strcmp(word2, tool) == 0)
            {

                matchLineNum = lineNum;
            }
        }
        if (matchLineNum != lineNum) {
            fputs(line, tempFile);
        }
        else if (matchLineNum == lineNum)
        {
            char concatenated[100];
            strcpy(concatenated, name);
            strcat(concatenated, " ");
            strcat(concatenated, tool);
            fputs(concatenated, tempFile);
            fputs("\n",tempFile);
        }
        lineNum++;
    }



    fclose(file);
    fclose(tempFile);

    if (remove("items.txt") == 0) {
        printf("Original file deleted successfully.\n");
    } else {
        printf("Failed to delete the original file.\n");
        return;
    }

    if (rename("temporary.txt", "items.txt") == 0) {

    } else {

        return;
    }
}


