#include "hra.h"

#define SIZE_Y 30
#define SIZE_X 60

int i,j,k;
int map [SIZE_Y][SIZE_X][2];
char Controller;
int x=10;
int y=10;

void Start()
{
    x=10;
    y=10;
    Generate_map();

}
void Events()
{
    MoveControl();



    system("cls");
}

void Update()
{
    MoveUpdate();

}

void Render()
{
    Print_map();
   

}

/*-----------------------------------------------------------------------------------------------------------------------------*/

void Generate_map()
{
    int biome_size=0;
    int distanceY=0;
    int distanceX=0;
    int biome_id=0;

    srand(time(NULL));

    for (i = 0; i < SIZE_Y; i++)
    {
        for (j = 0; j < SIZE_X; j++)
        {
            map[i][j][0] = 1;
            map[i][j][1] = 0;
        }
    }

    map[10][10][1]=1;


    for(i=0;i<30;i++)
    {
        distanceX=rand()%(SIZE_X-1+1)+1;
        distanceY=rand()%(SIZE_Y-1+1)+1;
        biome_id=rand()%(4-2+1)+2;
        biome_size=rand()%(10-2+1)+2;

        for(j=0;j<biome_size;j++)
        {
            for(k=0;k<biome_size;k++)
            {
                map[distanceY+j][distanceX+k][0]=biome_id;
            }
        }      
    }
    

}


void Print_map()
{
    for (i = 0; i < SIZE_Y; i++)
    {
        for (j = 0; j < SIZE_X; j++)
        {
            if (map[i][j][0] == 1 && map[i][j][1] == 0)
            {
                printf("- ");
            }
            else if (map[i][j][0] == 2 && map[i][j][1] == 0)
            {
                printf("T ");
            }
            else if (map[i][j][0] == 3 && map[i][j][1] == 0)
            {
                printf("o ");
            }
            else if (map[i][j][0] == 4 && map[i][j][1] == 0)
            {
                printf("X ");
            }
            else if (map[i][j][1] == 1)
            {
                printf("$ ");
            }
        }

        printf("\n");
    }
}


void MoveControl()
{
    do
    {
    
    Controller = getch();
   

    }while(Controller!='w' && Controller!='a' && Controller!='s' && Controller!='d');
}

void MoveUpdate()
{
    if (Controller == 'w' && y-1>=0)
    {
        map[y][x][1] = 0;
        y = y - 1;
        map[y][x][1] = 1;
    }
    else if (Controller == 's' && y+1<=SIZE_Y-1)
    {
        map[y][x][1] = 0;
        y = y + 1;
        map[y][x][1] = 1;
    }
    else if (Controller == 'a' && x-1>=0)
    {
        map[y][x][1] = 0;
        x = x - 1;
        map[y][x][1] = 1;
    }
    else if (Controller == 'd' && x+1<=SIZE_X-1)
    {
        map[y][x][1] = 0;
        x = x + 1;
        map[y][x][1] = 1;
    }
}





