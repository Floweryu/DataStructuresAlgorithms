#include<iostream>
#include<cstring>
#include<stdio.h>
#define maxsize 100
using namespace std;

typedef struct
{
    char arr[10][11];
} MazeType;       // 定义迷宫类型（二维字符数组）

struct PosType
{
	int x;
	int y;
};

struct Elemtype
{
	int ord;
	PosType seat;
	int di;
};

struct Stack
{
	Elemtype *data;
	int top;
	int listsize;
};

void InitStack(Stack &s)
{
	s.listsize = maxsize;
	s.top = 0;
	s.data = new Elemtype[s.listsize];
}

void DestroyStack(Stack &s)
{
	s.top = 0;
	s.listsize = 0;
	delete []s.data;
}

int StackEmpty(Stack s)
{
	if(s.top == 0)
	return 0;
	else
	return 1;
}

Elemtype Top(Stack s)
{
	return s.data[s.top-1];
}

int Push(Stack &s,Elemtype e)
{
	s.data[s.top] = e;
	s.top++;
	return 1;
}

int Pop(Stack &s,Elemtype &e)
{
	if(!StackEmpty(s))
	return 0;
	else
	{
		e = Top(s);
		s.top--;
		return 1;
	}
}

void FootPrint(MazeType &Maze,PosType curpos)
{
	Maze.arr[curpos.x][curpos.y] = '*';
}

void MarkPoint(MazeType &Maze,PosType s)
{
	Maze.arr[s.x][s.y] = '!';
}

int Pass(MazeType MyMaze, PosType CurPos)
{
    if (MyMaze.arr[CurPos.x][CurPos.y]==' ' || MyMaze.arr[CurPos.x][CurPos.y]=='S' || MyMaze.arr[CurPos.x][CurPos.y]=='E')
        return 1;                // 如果当前位置是可以通过，返回1
    else
        return 0;                // 其它情况返回0
}

PosType NextPos(PosType CurPos, int Dir)
{
    PosType ReturnPos;
    switch (Dir)
    {
    case 1:
        ReturnPos.x = CurPos.x;
        ReturnPos.y = CurPos.y + 1;
        break;
    case 2:
        ReturnPos.x = CurPos.x + 1;
        ReturnPos.y = CurPos.y;
        break;
    case 3:
        ReturnPos.x = CurPos.x;
        ReturnPos.y = CurPos.y - 1;
        break;
    case 4:
        ReturnPos.x = CurPos.x - 1;
        ReturnPos.y = CurPos.y;
        break;
    }
    return ReturnPos;
}

int MazePath(MazeType &Maze,PosType start,PosType end)
{
	Stack s;
	PosType curpos;
	Elemtype e;
	InitStack(s);
	curpos = start;
	int curstep = 1;
	do
	{
		if(Pass(Maze,curpos))
	    {
		FootPrint(Maze,curpos);
		e.ord = curstep;
		e.di = 1;
		e.seat.x = curpos.x;
		e.seat.y = curpos.y;
		Push(s,e);
		if(curpos.x == end.x && curpos.y == end.y)
		 return 1;
		curpos = NextPos(curpos,1);
		curstep++;
	    }
	    else
	    {
	    	if(StackEmpty(s) != 0)
	    	{
	    		Pop(s,e);
	    		while(e.di == 4 && StackEmpty(s) != 0 )
	    		{
	    			MarkPoint(Maze,e.seat);
					Pop(s,e);
				}
				if(e.di<4)
				{
					e.di ++;
					Push(s,e);
					curpos = NextPos(e.seat,e.di);
				}
			}
		}
	}while(StackEmpty(s) != 0);
	return 0;
}

int main()
{
	Stack s;
	MazeType Maze;
	PosType start;
	PosType end;
	for(int i=0;i<10;i++)
	{
		gets(Maze.arr[i]);
	}
	for(int i=0;i<10;i++)
	{
		for(int j=0;j<10;j++)
		{
			if(Maze.arr[i][j] == 'S')
			{
				start.x = i;
				start.y = j;
			}
			if(Maze.arr[i][j] == 'E')
			{
				end.x = i;
				end.y = j;
			}
		}
	}
	int ans = MazePath(Maze,start,end);
	if(ans==1)
	{
	for(int i=0;i<9;i++)
	{
		puts(Maze.arr[i]);
	}
	for(int i=0;i<10;i++)
	 printf("%c", Maze.arr[9][i]);
    }
	else
	{
	   for(int i=0;i<9;i++)
	   {
	      for(int j=0;j<10;j++)
	      {
		     if(Maze.arr[i][j] == '*')
		     Maze.arr[i][j] = '!';
		     printf("%c", Maze.arr[i][j]);
	      }
	      printf("\n");
       }
       for(int i=0;i<10;i++)
       {
       	  if(Maze.arr[9][i] == '*')
       	   Maze.arr[9][i] = '!';
       	  printf("%c", Maze.arr[9][i]);
	   }
    }
	return 0;
}
