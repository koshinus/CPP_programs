#include <iostream>
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include <iomanip>
#include "support.h"

short generateNum()
{
	srand(time(NULL));
	if ((1+rand()%9)>9) return 4;
	else return 2;
}

void arrayOutput(int ar[][4], unsigned long *score)
{
	using std::cout;
	for(short i=0;i<4;i++)
	{
		for(short j=0;j<4;j++) cout << std::setw(7) << ar[i][j];
		cout << "\n\n";
	}
	cout << "\n";
	cout << "Your score is " << *score << "\n";
	cout << "You may press \'q\' to exit. \n";
}

void swap(int *a,int *b)
{
	int c;
	c=*a;
	*a=*b;
	*b=c;
}

unsigned long inputCommand(int ar[][4],unsigned long *score)
{
	short i,j;
	int input=0;
	input=getch();
	if (input=='q') return 1;
	input=getch();
	switch(input)
	{
		case(72): return move(ar,score,i,moveLineUp);
		case(80): return move(ar,score,i,moveLineDown);
		case(75): return move(ar,score,j,moveLineLeft);
		case(77): return move(ar,score,j,moveLineRight);
		default: return *score;
	}
}

short fillingArray(int ar[][4])
{
	short count=0;
	numPair zeroArray[16];
	
	zeroCheck(ar,zeroArray,&count);
	
	if (count>0) 
	{
		srand(time(NULL));
		numPair roll=zeroArray[ rand()%count ];
		ar[roll.first][roll.second]=generateNum();
		return 0;
	}
		else if (checkNeighbors(ar)>0) return 0;
			else return 1;
}
