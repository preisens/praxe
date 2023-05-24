#include "hra.h"
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
    int maxexp;
    int gold;
    int armor;
    int weapondmg;
} self, monster;

void Start()
{
    Welcome();
    StartPlayer();
}
void Events()
{
}

void Update()
{
    levelUp();
}

void Render()
{
    Menu();
    Combat();
}

void Welcome()
{
    printf("Welcome to the game!\n");
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
    self.mana = 20;
    self.dmg = rand() % 21 + 20;
    self.lvl = 1;
    self.exp = 0;
    self.maxexp = 100;
    self.gold = 0;
    self.armor = 0;
    self.weapondmg = 0;
}
void Menu()
{
    system("cls");
    printf("What do you want to do?\n");
    printf("1......... Explore\n");
    printf("2......... Inventory\n");
    printf("3......... Shop\n");
    printf("4......... Exit\n");
    int choice;
    scanf("%d", &choice);
    system("cls");
    switch (choice)
    {
    case 1:
    {
    }
    break;
    case 2:
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
    case 3:
    {

        // Výpis vybraného řádku
        printf("Welcome to the shop!\n");
        printf("What do you want to buy?\n");
        system("pause");
    }
    break;
    case 4:
    {
        printf("Goodbye %s!\n", nickname);
        exit(0);
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
    monster.maxhp = rand() % 100 + 1;
    monster.hp = monster.maxhp;
    monster.dmg = rand() % 10 + 1;
    monster.gold = rand() % 100 + 1;
    monster.exp = rand() % 100 + 1;
    printf("-----------------------------------------------------------------\n");
    if (enemy == 1)
    {
        printf("You have encountered a goblin!\n");
    }
    else if (enemy == 2)
    {
        printf("You have encountered a golem!\n");
    }
    else if (enemy == 3)
    {
        printf("You have encountered a slime!\n");
    }
    else if (enemy == 4)
    {
        printf("You have encountered a cyclops!\n");
    }
    printf("-----------------------------------------------------------------\n");
    while (monster.hp > 0)
    {
        switch (enemy)
        {
        case 1:
        {
            f = fopen("enemies/goblin.txt", "r");
            // open the file and print it to the console
            char c;
            while ((c = fgetc(f)) != EOF)
            {
                printf("%c", c);
            }
        }
        break;
        case 2:
        {
            f = fopen("enemies/golem.txt", "r");
            // open the file and print it to the console
            char c;
            while ((c = fgetc(f)) != EOF)
            {
                printf("%c", c);
            }
        }
        break;
        case 3:
        {
            f = fopen("enemies/slime.txt", "r");
            // open the file and print it to the console
            char c;
            while ((c = fgetc(f)) != EOF)
            {
                printf("%c", c);
            }
        }
        break;
        case 4:
        {
            f = fopen("enemies/cyclops.txt", "r");
            // open the file and print it to the console
            char c;
            while ((c = fgetc(f)) != EOF)
            {
                printf("%c", c);
            }
        }
        break;
        }
        printf("-----------------------------------------------------------------\n");
        printf("\t\t\tENEMY STATS\t\t\t\t|\n");
        printf("-----------------------------------------------------------------\n");
        printf("\tHP: %d/%d\n", monster.hp, monster.maxhp);
        printf("-----------------------------------------------------------------\n");
        printf("\t\t\tYOUR STATS\t\t\t\t|\n");
        printf("-----------------------------------------------------------------\n");
        printf("\tHP: %d/%d\tMANA: %d/%d\tARMOR: %d\n", self.hp, self.maxhp, self.mana, self.maxmana, self.armor);
        printf("\nWhat do you want to do?\n");
        printf("1......... Attack\n");
        printf("2......... Skills\n");
        printf("3......... Defend\n");
        printf("4......... Inventory\n");
        printf("5......... Run\n");
        int choice;
        scanf("%d", &choice);
        printf("\033[7A");
        printf("\033[0J");
        switch (choice)
        {
        case 1:
        {
            printf("You chose to attack!\n");
            printf("You dealt %d damage to the monster!\n", self.dmg + self.weapondmg);
            monster.hp -= self.dmg + self.weapondmg;
            system("pause");
            printf("\033[3A");
            printf("\033[0J");
        }
        break;
        case 2:
        {
            printf("You chose to use a skill!\n");
            printf("1......... Fireball\n");
            printf("2......... Icebolt\n");
            printf("3......... Lightning\n");
            int skill;
            scanf("%d", &skill);
            printf("\033[5A");
            printf("\033[0J");
            switch (skill)
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
                printf("You dealt %d damage to the monster!\n", self.dmg + self.weapondmg + 5);
                monster.hp -= self.dmg + self.weapondmg + 5;
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
                printf("You dealt %d damage to the monster!\n", self.dmg + self.weapondmg + 10);
                monster.hp -= self.dmg + self.weapondmg + 10;
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
                printf("You dealt %d damage to the monster!\n", self.dmg + self.weapondmg + 15);
                monster.hp -= self.dmg + self.weapondmg + 15;
                self.mana -= 20;
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
            self.armor += rand() % 21 + 10;
            printf("You gained %d armor!\n", self.armor);
            system("pause");
            printf("\033[3A");
            printf("\033[0J");
        }
        break;
        case 4:
        {
        }
        break;
        case 5:
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
            printf("The monster attacked you!\n");
            if (monster.dmg - self.armor >= 0)
            {
                printf("The monster dealt %d damage to you!\n", monster.dmg - self.armor);
            }
            else
            {
                printf("The monster dealt 0 damage to you!\n");
            }
            if (self.armor < monster.dmg)
            {
                self.hp -= monster.dmg - self.armor;
            }
            self.armor -= monster.dmg;
            if (self.armor < 0)
            {
                self.armor = 0;
            }
            system("pause");
            printf("\033[3A");
            printf("\033[0J");
        }
        if (self.hp <= 0)
        {
            printf("You died!\n");
            printf("Game over!\n");
            exit(0);
        }
        system("cls");
    }
    fclose(f);
    printf("You have defeated the monster!\n");
    printf("You gained %d gold and %d exp!\n", monster.gold, monster.exp);
    self.gold += monster.gold;
    self.exp += monster.exp;
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
    }
}