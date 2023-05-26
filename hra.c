#include "hra.h"

#define SIZE_Y 30
#define SIZE_X 60

int Ecounter = 0;
int i, j, k;
int map[SIZE_Y][SIZE_X][2];
char Controller = 'V';
int x = 10;
int y = 10;

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
    printf("What is your nickname?\n");

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
        if (entry->d_type == DT_REG)
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
    Controller = 'V';
    system("cls");
    printf("What do you want to do?\n");
    printf("1......... Explore\n");
    printf("2......... Status/Inventory\n");
    printf("3......... Shop\n");
    printf("4......... Exit\n");
    char choice = getch();
    system("cls");
    switch (choice)
    {
    case '1':
    {

        while (Controller != 'q')
        {
            levelUp();
            Print_map();
            MoveControl();
            MoveUpdate();
            system("cls");
        }
    }
    break;
    case '2':
    {
        printf("Your HP: %d/%d\n", self.hp, self.maxhp);
        printf("Your armor: %d\n", self.armor);
        printf("Your mana: %d/%d\n", self.mana, self.maxmana);
        printf("Your damage: %d\n", self.dmg + self.weapondmg);
        printf("Your level: %d\n", self.lvl);
        printf("Your exp: %d/%d\n", self.exp, self.maxexp);
        printf("Your gold: %d\n", self.gold);
        system("pause");
        system("cls");
        printf("Items:\n");
        system("pause");
        system("cls");
    }
    break;
    case '3':
    {

        // Výpis vybraného řádku
        printf("Welcome to the shop!\n");
        printf("What do you want to buy?\n");
        system("pause");
    }
    break;
    case '4':
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
void Combat()
{
    srand(time(NULL));
    FILE *f;
    // open a random .txt file from the folder enemies
    int enemy = rand() % 4 + 1;
    monster.maxhp = rand() % 81 + 10;
    monster.hp = monster.maxhp;
    monster.dmg = rand() % 31 + 20;
    monster.exp = monster.maxhp + monster.dmg;
    monster.gold = monster.exp / 2;
    char *filePath = getRandomMonster("enemies");
    char *fileName = strrchr(filePath, '/');
    if (fileName == NULL)
    {
        fileName = filePath;
    }
    else
    {
        fileName++;
    }
    char *nameWithoutExtension = malloc(strlen(fileName) - 3);
    strncpy(nameWithoutExtension, fileName, strlen(fileName) - 4);
    nameWithoutExtension[strlen(fileName) - 4] = '\0';

    printf("You encountered a %s!\n", nameWithoutExtension);
    system("pause");
    system("cls");
    while (monster.hp > 0 && self.hp > 0)
    {
        FILE *file = fopen(filePath, "r");
        int c;
        while ((c = fgetc(file)) != EOF)
        {
            putchar(c);
        }
        printf("-----------------------------------------------------------------\n");
        printf("\t\t\tENEMY STATS\t\t\t\t|\n");
        printf("-----------------------------------------------------------------\n");
        printf("\tHP: %d/%d\n", monster.hp, monster.maxhp);
        printf("-----------------------------------------------------------------\n");
        printf("\t\t\tYOUR STATS\t\t\t\t|\n");
        printf("-----------------------------------------------------------------\n");
        printf("\tHP: %d/%d\tMANA: %d/%d\tARMOR: %d\tDMG: %d\n", self.hp, self.maxhp, self.mana, self.maxmana, self.armor, self.dmg + self.weapondmg);
        printf("\nWhat do you want to do?\n");
        printf("1......... Attack\n");
        printf("2......... Skills\n");
        printf("3......... Defend\n");
        printf("4......... Inventory\n");
        printf("5......... Run\n");
        char choice = getch();
        printf("\033[6A");
        printf("\033[0J");
        self.totaldmg = self.dmg + self.weapondmg + rand() % 16 + 0;
        switch (choice)
        {
        case '1':
        {
            printf("You chose to attack!\n");
            printf("You dealt %d damage to the monster!\n", self.totaldmg);
            monster.hp -= self.totaldmg;
            system("pause");
            printf("\033[3A");
            printf("\033[0J");
        }
        break;
        case '2':
        {
            printf("You chose to use a skill!\n");
            printf("1.......... Normal skills\n");
            printf("2.......... Special skills\n");
            char skill = getch();
            printf("\033[3A");
            printf("\033[0J");
            switch (skill)
            {
            case '1':
            {
                printf("1.......... Fireball\n");
                printf("2.......... Icebolt\n");
                printf("3.......... Lightning\n");
                char normal = getch();
                printf("\033[3A");
                printf("\033[0J");
                switch (normal)
                {
                case '1':
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
                case '2':
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
                case '3':
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
            case '2':
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
        case '3':
        {
            printf("You chose to defend!\n");
            self.defense = rand() % 31 + 20;
            printf("You are blocking %d of dmg!\n", self.defense);
            system("pause");
            printf("\033[3A");
            printf("\033[0J");
        }
        break;
        case '4':
        {
        }
        break;
        case '5':
        {
            printf("You chose to run!\n");
            if (rand() % 2 == 0)
            {
                printf("You have successfully ran away!\n");
                system("pause");
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

        system("cls");
        if (monster.hp <= 0 || self.hp <= 0)
        {
            fclose(file);
            free(filePath);
            free(nameWithoutExtension);
        }
    }
    if (self.hp > 0)
    {
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
        system("pause");
        system("cls");
    }
}
void CreateScore()
{
    char filepath[100];
    sprintf(filepath, "score/%s.txt", nickname);
    FILE *file = fopen(filepath, "w");
    fprintf(file, "Level: %d\n", self.lvl);
    fprintf(file, "Total Experience: %d\n", self.totalexp);
    fprintf(file, "Total Gold: %d\n", self.totalgold);
    fclose(file);
}
void End()
{
    if (self.hp <= 0)
    {
        printf("It's Game Over for %s!\n", nickname);
        printf("You reached level %d!\n", self.lvl);
        printf("You gained a total of %d exp and %d gold!\n", self.totalexp, self.totalgold);
        printf("Thank you for playing!\n");
        system("pause");
        CreateScore();
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

void Print_map()
{
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
        printf("\033[0;31m");
        printf("\na monster attacked you!\n");
        printf("\033[0m");
        Sleep(1000);
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
        system("cls");
    }
}
