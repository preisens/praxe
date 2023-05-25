#include "hra.h"

int main()
{   
    HWND console = GetConsoleWindow();
    SetWindowLong(console, GWL_STYLE, GetWindowLong(console, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
    ShowWindow(console, SW_MAXIMIZE);
    

    Generate_map();

    StartPlayer();

    Welcome();

    while(1)
    {   
        Menu();
    }

    return 0;
}
