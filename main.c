#include <stdio.h>
#include "hra.h"

int main()
{
    int running=1;

    Start();
    printf("Start\n");


    while(running)
    {
        Events();
        Update();
        Render();
    }


    return 0;
}