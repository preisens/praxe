#include "hra.h"

#define SIZE_Y 30
#define SIZE_X 60

int i,j,k;
int map [SIZE_Y][SIZE_X][2];
char Controller;
int x=10;
int y=10;

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
    int weapondmg;
} self, monster;

void Start()
{
    Welcome();
    x=10;
    y=10;
    Generate_map();
    StartPlayer();
}

void Render()
{
    Menu();
}

void Events()
{
    
}

void Update()
{
    

    levelUp();
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
    self.totalexp = 0;
    self.gold = 0;
    self.totalgold = 0;
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
    char choice = getch();
    system("cls");
    switch (choice)
    {
    case '1':
    {
        while(1)
        {
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
    monster.maxhp = rand() % 100 + 1;
    monster.hp = monster.maxhp;
    monster.dmg = rand() % 31 + 20;
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
    while (monster.hp > 0 && self.hp > 0)
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
        char choice = getch();
        printf("\033[6A");
        printf("\033[0J");
        switch (choice)
        {
        case '1':
        {
            printf("You chose to attack!\n");
            printf("You dealt %d damage to the monster!\n", self.dmg + self.weapondmg);
            monster.hp -= self.dmg + self.weapondmg;
            system("pause");
            printf("\033[3A");
            printf("\033[0J");
        }
        break;
        case '2':
        {
            printf("You chose to use a skill!\n");
            printf("1......... Fireball\n");
            printf("2......... Icebolt\n");
            printf("3......... Lightning\n");
            char skill = getch();
            printf("\033[4A");
            printf("\033[0J");
            switch (skill)
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
                printf("You dealt %d damage to the monster!\n", self.dmg + self.weapondmg + 5);
                monster.hp -= self.dmg + self.weapondmg + 5;
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
                printf("You dealt %d damage to the monster!\n", self.dmg + self.weapondmg + 10);
                monster.hp -= self.dmg + self.weapondmg + 10;
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
        case '3':
        {
            printf("You chose to defend!\n");
            self.armor += rand() % 21 + 10;
            printf("You gained %d armor!\n", self.armor);
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
            printf("\033[2A");
            printf("\033[0J");
        }
       
        system("cls");
    }
    if(self.hp>0)
    {
    printf("You have defeated the monster!\n");
    printf("You gained %d gold and %d exp!\n", monster.gold, monster.exp);
    self.gold += monster.gold;
    self.exp += monster.exp;
    self.totalgold += self.gold;
    self.totalexp += self.exp;
    }
    if (f != NULL)  fclose(f);
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
    }
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
        exit(0);
    }
}
void Generate_map()
{
    int biome_size=0;
    int distanceY=0;
    int distanceX=0;
    int biome_id=0;
    srand(time(NULL));

    for (i = 0; i < SIZE_Y; i++)
    {
        for (j = 0; j < SIZE_X; j++)
        {
            map[i][j][0] = 1;
            map[i][j][1] = 0;
        }
    }

    map[10][10][1]=1;


    for(i=0;i<30;i++)
    {
        distanceX=rand()%(SIZE_X-1+1)+1;
        distanceY=rand()%(SIZE_Y-1+1)+1;
        biome_id=rand()%(4-2+1)+2;
        biome_size=rand()%(10-2+1)+2;

        for(j=0;j<biome_size;j++)
        {
            for(k=0;k<biome_size;k++)
            {
                map[distanceY+j][distanceX+k][0]=biome_id;
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
                printf("- ");
            }
            else if (map[i][j][0] == 2 && map[i][j][1] == 0)
            {
                printf("T ");
            }
            else if (map[i][j][0] == 3 && map[i][j][1] == 0)
            {
                printf("o ");
            }
            else if (map[i][j][0] == 4 && map[i][j][1] == 0)
            {
                printf("X ");
            }
            else if (map[i][j][1] == 1)
            {
                printf("$ ");
            }
        }

        printf("\n");
    }
}


void MoveControl()
{
    do
    {
    
    Controller = getch();
   

    }while(Controller!='w' && Controller!='a' && Controller!='s' && Controller!='d');
}

void MoveUpdate()
{
    if (Controller == 'w' && y-1>=0)
    {
        map[y][x][1] = 0;
        y = y - 1;
        map[y][x][1] = 1;
    }
    else if (Controller == 's' && y+1<=SIZE_Y-1)
    {
        map[y][x][1] = 0;
        y = y + 1;
        map[y][x][1] = 1;
    }
    else if (Controller == 'a' && x-1>=0)
    {
        map[y][x][1] = 0;
        x = x - 1;
        map[y][x][1] = 1;
    }
    else if (Controller == 'd' && x+1<=SIZE_X-1)
    {
        map[y][x][1] = 0;
        x = x + 1;
        map[y][x][1] = 1;
    }
}






