#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <dos.h>
#include <time.h>
#include <string.h>
using namespace std;
Handle console=GetStdHandle(STD_OUTPUT_HANDLE);

char *board[25][80];
void draw_board()
{
for(int i=0;i<25;i++)
{
for(int j=0;j<80;j++)
{

if( (i>2 && i<6) && (j>20 && j<60)){
board[i][j]="#";
}
else {
board[i][j]=" ";
if(i==0 || i==24){
board[i][j]="&";
}

if(j==0 || j==79){
board[i][j]="&";
}}
printf(board[i][j]);
		}
	}
}
int main()
{
   draw_board();
    return 0;
}
