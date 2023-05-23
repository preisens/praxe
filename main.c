#include <stdio.h>
#include <windows.h>
#include <time.h>

void Start();
  void shop();
    void buy();
    void sell();
  void explore();
    void combat();
    void events();
void Update();
void Render();
int main()
{
    int running=1;
    

    Start();



    while(running==1)
    {
    int choice;
    printf("What do you want to do?\n");
    printf("1.........Explore\n");
    printf("2.........Shop\n");
    printf("3.........Exit\n");
    scanf("%d", &choice);
    switch(choice){
        case 1:
            //explore();

            break;
        case 2:
            shop();
            break;
        default:
            printf("You chose to do nothing\n");
            break;
    }
    }


    return 0;
}
void Start(){
    char nickname[20];
    srand(time(NULL));
    struct
    {
        int maxhp;
        int armor;
        int dmg;
    } player;
    player.maxhp=100;
    player.armor=50;
    player.dmg=rand()%10+10;




    printf("Welcome to the game\n");
    printf("Enter your nickname: ");
    scanf("%s", nickname);
    system("cls");
    printf("Hello %s,\n", nickname);
    
}
void shop(){
    printf("----------------------------------------\n");
    printf("Welcome traveler! What do you desire?\n");
    printf("----------------------------------------\n");
    printf("1.........Buy\n");
    printf("2.........Sell\n");
    printf("3.........Exit\n");
    int choice;
    scanf("%d", &choice);
    switch(choice){
        case 1:
            printf("You chose to buy\n");
            break;
        case 2:
            printf("You chose to sell\n");
            break;
        case 3:
            printf("You chose to exit\n");
            break;
        default:
            printf("You chose to do nothing\n");
            break;
    }

}