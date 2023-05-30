#include "hra.h"

void main()
{   
    HWND console = GetConsoleWindow();
    SetWindowLong(console, GWL_STYLE, GetWindowLong(console, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
    ShowWindow(console, SW_MAXIMIZE);
    
    readSkills();
    printRandomSkills();
    Generate_map();

    StartPlayer();

    Welcome();

    while(1)
    {   
        Menu();
    }
}
