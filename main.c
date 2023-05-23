#include <stdio.h>
#include <windows.h>

void Start();
void Events();
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
    scanf("%d", &choice);
    switch(choice){
        case 1:
            //explore();
            break;
        case 2:
            //shop();
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
    printf("Welcome to the game\n");
    printf("Enter your nickname: ");
    scanf("%s", nickname);
    system("cls");
    printf("Hello %s,\n", nickname);
    

}