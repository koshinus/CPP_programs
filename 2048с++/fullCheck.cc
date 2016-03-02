#include <iostream>
#include "support.h"

void zeroCheck(int ar[][4], numPair *zeroArray, short *count)
{
	for(short i=0;i<4;i++)
		for(short j=0;j<4;j++)
			if(ar[i][j]==0) 
			{
				zeroArray[*count].first=i;
				zeroArray[*count].second=j;
				(*count)++;
			}
}

short checkNeighbor(int ar[][4],short i,short j, int elem)
{
	try
	{	ar[i][j]==elem;	}
	catch(...)
	{	return 0;	}
	if (ar[i][j]!=elem) return 0;
	else return 1;
}

short checkNeighbors(int ar[][4])
{
	short neighborCount;
	for(short i=0;i<4;i++)
		for(short j=0;j<4;j++)
		{
			neighborCount = checkNeighbor(ar,--i,j,ar[i][j])+
							checkNeighbor(ar,++i,j,ar[i][j])+
							checkNeighbor(ar,i,--j,ar[i][j])+
							checkNeighbor(ar,i,++j,ar[i][j]);
		}
	return neighborCount;
}