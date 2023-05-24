#include "hra.h"
char nickname[20];
struct
{
    int hp;
    int maxhp;
    int mana;
    int maxmana;
    int dmg;
    int lvl;
    int exp;
    int gold;
    int armor;
    int weapon;
} self, monster;

void Start()
{
    Welcome();
}
void Events()
{
}

void Update()
{
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
    self.mana = 100;
    self.dmg = rand() % 10 + 1;
    self.lvl = 1;
    self.exp = 0;
    self.gold = 0;
    self.armor = 0;
    self.weapon = 0;
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
    StartPlayer();
    srand(time(NULL));
    FILE *f;
    // open a random .txt file from the folder enemies
    int enemy = rand() % 4 + 1;
    monster.maxhp = rand() % 100 + 1;
    monster.hp = monster.maxhp;
    monster.dmg = rand() % 10 + 1;
    monster.gold = rand() % 100 + 1;
    monster.exp = rand() % 100 + 1;
    while (monster.hp > 0)
    {
        printf("--------------------------------------------------------\n");
        switch (enemy)
        {
        case 1:
        {
            f = fopen("enemies/goblin.txt", "r");
            printf("You have encountered a goblin!\n");
            // open the file and print it to the console
            char c;
            while ((c = fgetc(f)) != EOF)
            {
                printf("%c", c);
            }
            fclose(f);
        }
        break;
        case 2:
        {
            f = fopen("enemies/golem.txt", "r");
            printf("You have encountered a golem!\n");
            // open the file and print it to the console
            char c;
            while ((c = fgetc(f)) != EOF)
            {
                printf("%c", c);
            }
            fclose(f);
        }
        break;
        case 3:
        {
            f = fopen("enemies/slime.txt", "r");
            printf("You have encountered a slime!\n");
            // open the file and print it to the console
            char c;
            while ((c = fgetc(f)) != EOF)
            {
                printf("%c", c);
            }
            fclose(f);
        }
        break;
        case 4:
        {
            f = fopen("enemies/cyclops.txt", "r");
            printf("You have encountered a cyclops!\n");
            // open the file and print it to the console
            char c;
            while ((c = fgetc(f)) != EOF)
            {
                printf("%c", c);
            }
            fclose(f);
        }
        break;
        }
        printf("--------------------------------------------------------\n");
        printf("Enemy HP: %d/%d\n", monster.hp, monster.maxhp);
        printf("--------------------------------------------------------\n");
        printf("What do you want to do?\n");
        printf("1......... Attack\n");
        printf("2......... Skills\n");
        printf("3......... Defend\n");
        printf("4......... Inventory\n");
        printf("5......... Run\n");
        int choice;
        scanf("%d", &choice);
        system("cls");
        switch (choice)
        {
        case 1:
        {
            printf("You chose to attack!\n");
            printf("You dealt %d damage to the monster!\n", self.dmg + self.weapon);
            monster.hp -= self.dmg + self.weapon;
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
            switch (skill)
            {
            case 1:
            {
                printf("You used Fireball!\n");
                printf("You dealt %d damage to the monster!\n", self.dmg + self.weapon + 5);
                monster.hp -= self.dmg + self.weapon + 5;
                self.mana -= 10;
            }
            break;
            case 2:
            {
                printf("You used Icebolt!\n");
                printf("You dealt %d damage to the monster!\n", self.dmg + self.weapon + 10);
                monster.hp -= self.dmg + self.weapon + 10;
                self.mana -= 15;
            }
            break;
            case 3:
            {
                printf("You used Lightning!\n");
                printf("You dealt %d damage to the monster!\n", self.dmg + self.weapon + 15);
                monster.hp -= self.dmg + self.weapon + 15;
                self.mana -= 20;
            }
            break;
            }
            printf("Your mana: %d/%d\n", self.mana, self.maxmana);
        }
        break;
        case 3:
        {
            printf("You chose to defend!\n");
            self.armor += rand() % 21 + 10;
            printf("You gained %d armor!\n", self.armor);
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
                return;
            }
            else
            {
                printf("You failed to run away!\n");
            }
        }
        break;
        }
        system("pause");
        system("cls");
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
        }

        printf("Your HP: %d/%d\n", self.hp, self.maxhp);
        printf("Your armor: %d\n", self.armor);
        printf("Your mana: %d/%d\n", self.mana, self.maxmana);
        system("pause");
        system("cls");
        if (self.hp <= 0)
        {
            printf("You died!\n");
            printf("Game over!\n");
            exit(0);
        }
    }
    printf("You have defeated the monster!\n");
    printf("You gained %d gold and %d exp!\n", monster.gold, monster.exp);
    self.gold += monster.gold;
    self.exp += monster.exp;
    system("pause");
}