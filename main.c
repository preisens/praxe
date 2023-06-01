#include "hra.h"

void main()
{   
    HWND console = GetConsoleWindow();
    SetWindowLong(console, GWL_STYLE, GetWindowLong(console, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
    ShowWindow(console, SW_MAXIMIZE);
    srand(time(NULL));

    Welcome();

    while(1)
    {   
        Menu();
    }
}
