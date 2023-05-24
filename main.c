#include <stdio.h>
#include "hra.h"

int main()
{
    int running=1;

    Start();
    

    while(running)
    {
        Render();
        Events();
        Update();
        
    }


    return 0;
}
