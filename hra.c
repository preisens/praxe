#include "hra.h"

int i,j,k;
int map [20][20][2];
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

    for (i = 0; i < 20; i++)
    {
        for (j = 0; j < 20; j++)
        {
            map[i][j][0] = 1;
            map[i][j][1] = 0;
        }
    }

    map[10][10][1]=1;


    for(i=0;i<15;i++)
    {
        distanceX=rand()%(20-1+1)+1;
        distanceY=rand()%(20-1+1)+1;
        biome_id=rand()%(4-2+1)+2;
        biome_size=rand()%(5-2+1)+2;

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
    for (i = 0; i < 20; i++)
    {
        for (j = 0; j < 20; j++)
        {
            if (map[j][i][0] == 1 && map[j][i][1] == 0)
            {
                printf("- ");
            }
            else if (map[j][i][0] == 2 && map[j][i][1] == 0)
            {
                printf("T ");
            }
            else if (map[j][i][0] == 3 && map[j][i][1] == 0)
            {
                printf("? ");
            }
            else if (map[j][i][0] == 4 && map[j][i][1] == 0)
            {
                printf("! ");
            }
            else if (map[j][i][1] == 1)
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
    
    scanf(" %c",&Controller);
    if(Controller=='w')
    {

    }
    else if(Controller=='a')
    {
        
    }
    else if(Controller=='s')
    {
        
    }
    else if(Controller=='d')
    {
        
    }

    }while(Controller!='w' && Controller!='a' && Controller!='s' && Controller!='d');
}

void MoveUpdate()
{
    if (Controller == 'w' && x-1>=0)
    {
        map[y][x][1] = 0;
        x = x - 1;
        map[y][x][1] = 1;
    }
    else if (Controller == 's' && x+1<=19)
    {
        map[y][x][1] = 0;
        x = x + 1;
        map[y][x][1] = 1;
    }
    else if (Controller == 'a' && y-1>=0)
    {
        map[y][x][1] = 0;
        y = y - 1;
        map[y][x][1] = 1;
    }
    else if (Controller == 'd' && y+1<=19)
    {
        map[y][x][1] = 0;
        y = y + 1;
        map[y][x][1] = 1;
    }
}





