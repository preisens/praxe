#include <stdio.h>
#include "hra.h"

int main()
{
    int running=1;

    Start();
    

    while(running)
    {
        Events();
        Update();
        Render();
    }


    return 0;
}