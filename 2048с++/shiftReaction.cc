#include <iostream>
#include <conio.h>
#include "support.h"

void rightShift(int ar[][4],short i)
{
	short j;
	short t=3;
	for(j=3;j>-1;j--)
	{
		if(ar[i][j]>0) 
		{
			swap(&ar[i][t],&ar[i][j]);
			t--;
		}
	}
}

void leftShift(int ar[][4],short i)
{
	short j;
	short t=0;
	for(j=0;j<4;j++)
	{
		if(ar[i][j]>0) 
		{
			swap(&ar[i][t],&ar[i][j]);
			t++;
		}
	}
}

void downShift(int ar[][4],short j)
{
	short i;
	short t=3;
	for(i=3;i>-1;i--)
	{
		if(ar[i][j]>0) 
		{
			swap(&ar[t][j],&ar[i][j]);
			t--;
		}
	}
}

void upShift(int ar[][4],short j)
{
	short i;
	short t=0;
	for(i=0;i<4;i++)
	{
		if(ar[i][j]>0) 
		{
			swap(&ar[t][j],&ar[i][j]);
			t++;
		}
	}
}

unsigned long moveLineRight(int ar[][4],short i, unsigned long *score)
{
	short j;
	rightShift(ar,i);
	short a;
	for(j=3;j>-1;j--)
	{
		if(ar[i][j]==ar[i][j-1]) 
		{
			if(j==a) continue;
			a=j;
			ar[i][j]*=2;
			ar[i][j-1]=0;
			*score+=ar[i][j];
		}
	}
	rightShift(ar,i);
	return *score;
}

unsigned long moveLineLeft(int ar[][4],short i, unsigned long *score)
{
	short j;
	leftShift(ar,i);
	short a;
	for(j=0;j<3;j++) 
	{
		if(ar[i][j]==ar[i][j+1]) 
		{
			if(j==a) continue;
			a=j;
			ar[i][j]*=2;
			ar[i][j+1]=0;
			score+=ar[i][j];
		}
	}
	leftShift(ar,i);
	return *score;
}

unsigned long moveLineDown(int ar[][4],short j, unsigned long *score)
{
	short i;
	downShift(ar,j);
	short a;
	for(i=3;i>-1;i--)
	{
		if(ar[i][j]==ar[i-1][j]) 
		{
			if(i==a) continue;
			a=i;
			ar[i][j]*=2;
			ar[i-1][j]=0;
			*score+=ar[i][j];
		}
	}
	downShift(ar,j);
	return *score;
}

unsigned long moveLineUp(int ar[][4],short j, unsigned long *score)
{
	short i;
	upShift(ar,j);
	short a;
	for(i=0;i<3;i++) 
	{
		if(ar[i][j]==ar[i+1][j]) 
		{
			if(i==a) continue;
			a=i;
			ar[i][j]*=2;
			ar[i+1][j]=0;
			score+=ar[i][j];
		}
	}
	upShift(ar,j);
	return *score;
}

unsigned long move(int ar[][4], unsigned long *score, short k, 
			unsigned long f(int ar[][4],short k, unsigned long *score))
{
	for(k=0;k<4;k++) f(ar,k,score);
	return *score;
}