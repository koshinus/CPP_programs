#ifndef SUPPORT_H_
#define SUPPORT_H_

struct numPair { short first; short second; };

void swap(int *a,int *b);

short fillingArray(int ar[][4]);

void arrayOutput(int ar[][4], unsigned long *score);

short generateNum();

void rightShift(int ar[][4],short i);

void leftShift(int ar[][4],short i);

void downShift(int ar[][4],short j);

void upShift(int ar[][4],short j);

unsigned long moveLineRight(int ar[][4],short i, unsigned long *score);

unsigned long moveLineLeft(int ar[][4],short i, unsigned long *score);

unsigned long moveLineDown(int ar[][4],short j, unsigned long *score);

unsigned long moveLineUp(int ar[][4],short j, unsigned long *score);

unsigned long move(int ar[][4], unsigned long *score, short k, 
			unsigned long f(int ar[][4],short k, unsigned long *score));

unsigned long inputCommand(int ar[][4], unsigned long *score);

void zeroCheck(int ar[][4], numPair *zeroArray, short *count);

short checkNeighbor(int ar[][4],short i,short j, int elem);

short checkNeighbors(int ar[][4]);

#endif