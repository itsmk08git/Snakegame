#include <iostream>
#include <conio.h>
using namespace std;

bool gameover;
const int width = 60;
const int height = 20;

int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100], ntail;

enum edirection{ STOP=0, LEFT, RIGHT, UP, DOWN};
edirection dir;

void setup()
{
    gameover = false;
    dir = STOP;
    x= width /2;
    y= height /2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}
void Draw()
{
    system("cls");
    int i, j;
    for( i=0; i<width+2; i++)
    {
        cout<<"#";
    }
    cout<<endl;

    for( i=0; i<height ; i++)
    {
        for( j=0; j<width ; j++)
        {
            if(j==0 )
            {
                cout<<"#";
            }
            if(i==y && j==x)
            {
                cout<<"O";
            }
            else if(i==fruitY && j==fruitX)
            {
                cout<<"F";
            }
            else
            {
                bool Print=false;

                for(int k=0; k<ntail; k++)
                {
                    if(i==tailY[k] && j==tailX[k])
                    {
                        cout<<"o";
                        Print=true;
                    }
                }if(!Print)
                {
                    cout<<" ";
                }
            }

            if(j==width-1)
            {
                cout<<"#";
            }
        }
        cout<<endl;
    }

    for( i=0; i<width+2; i ++)
    {
        cout<<"#";
    }
    cout<<endl;
    cout<<"Score:"<<score;
}

void Input()
{
    if(kbhit())
    {
        switch(_getch())
        {
            case 'w':
                dir = UP;
                break;
            case 's':
                dir = DOWN;
                break;
            case 'a':
                dir = LEFT;
                break;
            case 'd':
                dir = RIGHT;
                break;
            default :
                gameover= true;
                break;
        }
    }
}

void Logic()
{
    int prevX= tailX[0];
    int prevY= tailY[0];
    tailX[0]=x;
    tailY[0]=y;
    int prev2X, prev2Y;

    for(int i=1; i<ntail; i++)
    {
        prev2X=tailX[i];
        prev2Y=tailY[i];
        tailX[i]=prevX;
        tailY[i]=prevY;
        prevX=prev2X;
        prevY=prev2Y;
    }   
    switch (dir)
    {
        case UP:
            y--;
            break;
        case DOWN:
             y++;
            break;
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        default:
            break;
    }
    if(x > width || x < 0 || y > height || y < 0)
        gameover = true;
    
    for(int i=0; i<ntail; i++)
    {
        if(x==tailX[i] && y==tailY[i])
        {
            gameover=true;
        }
    }
    if(x == fruitX && y == fruitY)
    {
        score +=10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        ntail++;
    }
}

int main()
{
    system("cls");
    setup();
    while (!gameover)
    {
        Draw();
        Input();
        Logic();
    }
}