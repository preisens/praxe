#include <stdio.h>
#include "hra.h"

int main()
{
    int Encounter=0;

    Generate_map();

    StartPlayer();

    Welcome();

    Menu();

    while(1)
    {
        Print_map();
        MoveControl();
        MoveUpdate();
        system("cls");
        Encounter=rand()%(100-1+1)+1;
        if(Encounter==-5)
        {
            Combat();
        }

    }


    




    return 0;
}
