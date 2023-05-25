#include "hra.h"

int main()
{
    int Encounter=0;

    Generate_map();

    StartPlayer();

    Welcome();

    while(1)
    {
         Menu();
    }

    return 0;
}
