#include<iostream>
#include<Windows.h>
#include<conio.h>
#include<time.h>
using namespace std;
#ifndef _console_header
#define _console_header
#define ColorCode_Back			0
#define ColorCode_DarkBlue		1
#define ColorCode_DarkGreen		2
#define ColorCode_DarkCyan		3
#define ColorCode_DarkRed		4
#define ColorCode_DarkPink		5
#define ColorCode_DarkYellow	6
#define ColorCode_DarkWhite		7
#define ColorCode_Grey			8
#define ColorCode_Blue			9
#define ColorCode_Green			10
#define ColorCode_Cyan			11
#define ColorCode_Red			12
#define ColorCode_Pink			13
#define ColorCode_Yellow		14
#define ColorCode_White			15
#define default_ColorCode		7
#define key_Up		1072
#define key_Down	1080
#define key_Left	1075
#define key_Right	1077
#define key_none	-1
#include <windows.h>
int inputKey();
void clrscr();
void gotoXY (int column, int line);
void TextColor (int color);
void clrscr()
{
	CONSOLE_SCREEN_BUFFER_INFO	csbiInfo;
	HANDLE	hConsoleOut;
	COORD	Home = {0,0};
	DWORD	dummy;
	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut,&csbiInfo);
	FillConsoleOutputCharacter(hConsoleOut,' ',csbiInfo.dwSize.X * csbiInfo.dwSize.Y,Home,&dummy);
	csbiInfo.dwCursorPosition.X = 0;
	csbiInfo.dwCursorPosition.Y = 0;
	SetConsoleCursorPosition(hConsoleOut,csbiInfo.dwCursorPosition);
}
void gotoXY (int column, int line)
{
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
void TextColor (int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , color);
}
#endif
#define consoleWidth 40
#define consoleHeight 20
enum TrangThai { UP,DOWN,LEFT,RIGHT };
struct moto
{
    int mau;
    char kitu;
};

moto buffer[consoleHeight][consoleWidth+1];

void vemoto(int dong,int cot,int kitu,int mau)
{
    buffer[dong][cot].kitu=kitu;
    buffer[dong][cot].mau=mau;
}

struct ToaDo
{
    int x,y;
};

struct Snake
{
    ToaDo dot[31];
    int n;
    TrangThai tt;
    int diem;
};

struct HoaQua
{
    ToaDo td;
};

void Khoitao(Snake &snake, HoaQua &hq)
{
    snake.n=3;
    snake.diem=0;
    snake.dot[0].x=3;
    snake.dot[0].y=5;
    snake.dot[1].x=2;
    snake.dot[1].y=5;
    snake.dot[2].x=1;
    snake.dot[2].x=5;
    snake.tt=RIGHT;
    snake.dot[0].x++;
    hq.td.x=10;
    hq.td.y=10;
    for(int i=0;i<consoleHeight;i++)
    {
        for(int j=0;j<consoleWidth;j++)
         {
            buffer[i][j].kitu=' ';
            buffer[i][j].mau=8;
         }
    }
}

void HienThi(Snake snake, HoaQua hq)
{
    for(int i=0;i<consoleHeight+1;i++)
        vemoto(i,consoleWidth,186,14);
    for(int i=0;i<consoleWidth+1;i++)
        vemoto(consoleHeight-1,i,205,14);
    for(int i=0;i<consoleWidth+1;i++)
        vemoto(0,i,205,14);
    for(int i=0;i<consoleHeight;i++)
        vemoto(i,0,186,14);
    vemoto(hq.td.y,hq.td.x,'+',12);
    vemoto(snake.dot[0].y,snake.dot[0].x,'@',11);
    for(int i=1;i<snake.n;i++)
        vemoto(snake.dot[i].y,snake.dot[i].x,'*',11);
    gotoXY(0,0);
    for(int i=0;i<consoleHeight;i++)
    {
        for(int j=0;j<=consoleWidth;j++)
        {
            TextColor(buffer[i][j].mau);
            cout << buffer[i][j].kitu;
            buffer[i][j].kitu=' ';
        }
        if(i<consoleHeight-1)
            cout << "\n";
    }
    TextColor(10);
	gotoXY(consoleWidth+2,1);
	cout << "Diem = " << snake.diem*10;
}

void DieuKhien_DiChuyen(Snake &snake)
{
    for(int i=snake.n-1;i>0;i--)
        snake.dot[i]=snake.dot[i-1];

    if(kbhit())
    {
        int key=_getch();
        if(key=='A'||key=='a')
            snake.tt=LEFT;
        else if(key=='D'||key=='d')
            snake.tt=RIGHT;
        else if(key=='W'||key=='w')
            snake.tt=UP;
        else if(key=='S'||key=='s')
            snake.tt=DOWN;
        else if(key=='4')
            snake.tt=LEFT;
        else if(key=='6')
            snake.tt=RIGHT;
        else if(key=='8')
            snake.tt=UP;
        else if(key=='5')
            snake.tt=DOWN;

    }
    if(snake.tt==UP)
        snake.dot[0].y--;
    else if(snake.tt==DOWN)
        snake.dot[0].y++;
    else if(snake.tt==RIGHT)
        snake.dot[0].x++;
    else if(snake.tt==LEFT)
        snake.dot[0].x--;
}
int XuLy(Snake &snake, HoaQua &hq,int &ThoiGianSleep)
{
    if(snake.dot[0].x<1||snake.dot[0].x>=consoleWidth||
       snake.dot[0].y<1||snake.dot[0].y>=consoleHeight-1)
        return -1;
    for(int i=2;i<snake.n;i++)
        if(snake.dot[0].x==snake.dot[i].x&&
           snake.dot[0].y==snake.dot[i].y)
           return -1;
    if(snake.dot[0].x==hq.td.x&&snake.dot[0].y==hq.td.y)
    {
        for(int i=snake.n;i>0;i--)
            snake.dot[i]=snake.dot[i-1];
        snake.n++;
        snake.diem++;
        if(snake.tt==UP)
            snake.dot[0].y--;
        else if(snake.tt==DOWN)
            snake.dot[0].y++;
        else if(snake.tt==RIGHT)
            snake.dot[0].x++;
        else if(snake.tt==LEFT)
            snake.dot[0].x--;
        hq.td.x=1+rand()%(consoleWidth-1);
        hq.td.y=1+rand()%(consoleHeight-2);
        if(ThoiGianSleep>30)
            ThoiGianSleep-=20;
    }
}

int main()
{
    srand(time(NULL));
    Snake snake;
    HoaQua hq;
    Khoitao(snake,hq);
    int ma=0;
    int ThoiGianSleep=400;
    while(1)
    {
        HienThi(snake,hq);
        DieuKhien_DiChuyen(snake);
        ma= XuLy(snake, hq,ThoiGianSleep);
        if(ma==-1)
        {
            gotoXY((consoleWidth-3)/2,(consoleHeight-2)/2);
            TextColor(5);
            cout << char(157)<< "  "<<"GAMEOVER"<<"  "<<char(157);
            while(_getch()!=13);
            break;
        }
         Sleep(ThoiGianSleep);
    }
    return 0;
}

