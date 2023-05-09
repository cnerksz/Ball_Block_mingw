#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <string.h>
#include <dos.h>
#include <conio.h>
#include<unistd.h>
#include <string>

#define SCREEN_WIDTH 79
#define SCREEN_HEIGHT 25


using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;
int rktx=32;
int rkty=22;
int resume=1;
int life=5;
int move_rkt=2;
int ballx=40;
int bally=10;
int move_ballx=0;
int move_bally=1;
char *board[80][25];
void draw_board();
int score=0;
void gotoxy(int x, int y)
{
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);
}

void setcursor(bool visible, DWORD size)
{
    if(size == 0)
    {
        size = 20;
    }
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = size;
    SetConsoleCursorInfo(console,&lpCursor);
}

void drawBorder()
{
    gotoxy(0,0);
    cout<<"==================================BALLS-BLOCK==================================";
    gotoxy(0,SCREEN_HEIGHT);
    cout<<"==================================BALLS-BLOCK==================================";

    for(int i=0; i<SCREEN_HEIGHT; i++)
    {
        gotoxy(0,i+1);
        cout<<"#";
        gotoxy(SCREEN_WIDTH-1,i+1);
        cout<<"#";
    }
}
void clear_rkt()
{
    gotoxy(rktx,rkty);
    string rkt="           ";
    cout<<rkt;
}
void draw_rkt()
{
    gotoxy(rktx,rkty);
    string  rkt="=========";
    cout<<rkt;
}
void clear_ball()
{
    gotoxy(ballx,bally);
    cout<<" ";
}
void draw_ball()
{
    gotoxy(ballx,bally);
    cout<<"O";
}

void update_board(int x,int y)
{
    while(board[x][y]!=" ")
    {
        board[x][y]=" ";
        if(board[x][y-1]=="#")y=y-1;
        else if(board[x][y+1]=="#")y=y+1;
        else if(board[x+1][y]=="#")x=x+1;
        else if(board[x+2][y]=="#")x=x+2;
        else if(board[x-1][y]=="#")x=x-1;
        else if(board[x-2][y]=="#")x=x-2;
    }

}
void update_ball()
{
    clear_ball();
    bally=bally+move_bally;
    ballx=ballx+move_ballx;
    draw_ball();


    if(bally+1==rkty)
    {
        if((ballx==rktx)||(ballx+1==rktx&&move_ballx!=0))
        {
            move_bally=-move_bally;
            move_ballx=-2;
        }
        if((ballx==rktx+3)||(ballx==rktx+4)||(ballx==rktx+5))
        {
            move_bally=-move_bally;
            move_ballx=0;
        }
        if((ballx==rktx+1)||(ballx==rktx+2))
        {
            move_bally=-move_bally;
            move_ballx=-1;
        }
        if((ballx==rktx+6)||(ballx==rktx+7))
        {
            move_bally=-move_bally;
            move_ballx=1;
        }
        if((ballx==rktx+8)||(ballx-1==rktx+8&&move_ballx!=0))
        {
            move_bally=-move_bally;
            move_ballx=2;
        }
    }
    if(board[ballx][bally]=="#")
    {
        score+=10;
        gotoxy(85,2);
        cout<<"Score :";
        gotoxy(95,2);
        cout<<score;
        update_board(ballx,bally);
        draw_board();
        move_bally=-move_bally;


    }




    if(ballx<=2 || ballx>=76)
    {

        move_ballx= -move_ballx;

    }

    if(bally==1)
    {
        move_bally=-move_bally;

    }
    Sleep(150);
}

void init_board()
{
    int locx=5;
    int locy=2;
    {
        for(int i=0; i<4; i++)
        {
            for(int j=0; j<80; j+=2)
            {

                if(j%8==0&&j!=0)
                {
                    locx=locx+4;
                    continue;
                }


                if(i==1)
                {
                    locy=3;
                }
                if(i==2)
                {
                    locy=6;
                }
                if(i==3)
                {
                    locy=7;
                }
                gotoxy(locx,locy);
                if(j!=0)
                {
                    board[locx][locy]="#";
                    cout<<board[locx][locy];
                }
                locx++;
            }
            locx=5;
        }
    }
}

void draw_board()
{

    int locx=5;
    int locy=2;
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<80; j+=2)
        {

            if(j%8==0&&j!=0)
            {
                locx=locx+4;
                continue;
            }


            if(i==1)
            {
                locy=3;
            }
            if(i==2)
            {
                locy=6;
            }
            if(i==3)
            {
                locy=7;
            }
            gotoxy(locx,locy);
            if(j!=0)
            {
                cout<<board[locx][locy];
            }
            locx++;
        }
        locx=5;
    }
}






void play()
{




            while(resume==1)
            {
                update_ball();
                if(bally==rkty+1)
                {
                    life--;
                    gotoxy(85,4);
                    cout<<"Life :";
                    gotoxy(95,4);
                    cout<<life;
                    clear_ball();
                    ballx=40;
                    bally=10;
                    move_ballx=0;
                    move_bally=1;
                    clear_rkt();
                    rktx=32;
                    rkty=22;
                    draw_rkt();
                    if(life==0){

                    system("cls");
                    gotoxy(50,14);
                    cout<<"Uzgunuz Kaybettiniz..";
                    gotoxy(50,16);
                    cout<<"Total Score :";
                    gotoxy(65,16);
                    cout<<score;
                        resume=0;
                        continue;
                    }
                }
                if(score==200){
                    system("cls");
                         gotoxy(50,14);
                    cout<<"Tebrikler Kazandiniz..";
                    gotoxy(50,16);
                    cout<<"Total Score :";
                    gotoxy(65,16);
                    cout<<score;
                 resume=0;
                        continue;

                }
                    if(_kbhit()){
                    char ch=_getch();
                    switch(ch)
                    {
                    case 'd':
                    case 'D':

                        if(rktx<66)
                        {

                            clear_rkt();

                            rktx=rktx+move_rkt;

                            draw_rkt();
                        }
                        break;

                    case 'a':
                    case 'A':

                        if(rktx>4)
                        {
                            clear_rkt();
                            rktx=rktx-move_rkt;

                            draw_rkt();
                        }
                    }
                    }
                }

        }




void instructions()
{

    system("cls");
    cout<<"Instructions";
    cout<<"\n-----------------";
    cout<<"\n\nUse 'a' key to move racket to left";
    cout<<"\n\nUse 'd' key to move racket to right";
    cout<<"\n\nPress spacebar to start game";
    cout<<"\n\nPress any key to go back to menu";
    _getch();
}
void menu()
{
    system("cls");
gotoxy(5,0);cout<<" _     _ _______ ___     _______ _______ __   __ _______    _______ _______ ";
gotoxy(5,1);cout<<"| | _ | |       |   |   |       |       |  |_|  |       |  |       |       |";
gotoxy(5,2);cout<<"| || || |    ___|   |   |       |   _   |       |    ___|  |_     _|   _   |";
gotoxy(5,3);cout<<"|       |   |___|   |   |       |  | |  |       |   |___     |   | |  | |  |";
gotoxy(5,4);cout<<"|       |    ___|   |___|      _|  |_|  |       |    ___|    |   | |  |_|  |";
gotoxy(5,5);cout<<"|   _   |   |___|       |     |_|       | ||_|| |   |___     |   | |       |";
gotoxy(5,6);cout<<"|__| |__|_______|_______|_______|_______|_|   |_|_______|    |___| |_______|";
gotoxy(0,9);cout<<"  _______ _______ ___     ___     _______    _______ ___     _______ _______ ___   _ _______ ";
gotoxy(0,10);cout<<"|  _    |   _   |   |   |   |   |       |  |  _    |   |   |       |       |   | | |       |";
gotoxy(0,11);cout<<"| |_|   |  |_|  |   |   |   |   |  _____|  | |_|   |   |   |   _   |       |   |_| |  _____|";
gotoxy(0,12);cout<<"|       |       |   |   |   |   | |_____   |       |   |   |  | |  |       |      _| |_____ ";
gotoxy(0,13);cout<<"|  _   ||       |   |___|   |___|_____  |  |  _   ||   |___|  |_|  |      _|     |_|_____  |";
gotoxy(0,14);cout<<"| |_|   |   _   |       |       |_____| |  | |_|   |       |       |     |_|    _  |_____| |";
gotoxy(0,15);cout<<"|_______|__| |__|_______|_______|_______|  |_______|_______|_______|_______|___| |_|_______|";

    gotoxy(5,18);
    cout<<"Use '1' key to play game";
    gotoxy(5,20);
    cout<<"Use '2' key to see instructions";

    char ch=_getch();
    if(ch=='1')
    {
        system("cls");
        draw_ball();

        drawBorder();
        draw_rkt();
        init_board();
        gotoxy(85,4);
                    cout<<"Life :";
                    gotoxy(95,4);
                    cout<<life;
        gotoxy(85,2);
        cout<<"Score :";
        gotoxy(95,2);
        cout<<score;
         char che =_getch();
        if(che==32){
        while(1)
            play();

    }
    if(ch=='2')
    {
        system("cls");
        instructions();


    }
}
}

int main()
{

    setcursor(0,0);

    while(1)
        menu();


    return 0;

}
