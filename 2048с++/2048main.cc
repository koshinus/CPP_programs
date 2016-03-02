#include <iostream>
#include "support.h"

int main()
{	
	unsigned long score=0;
	int ar[4][4]={{0,0,0,0},
				  {0,0,0,0},
				  {0,0,0,0},
				  {0,0,0,0}};
	short end=0;
	end=fillingArray(ar);
	while(end!=1)
	{
		arrayOutput(ar,&score);
		score=inputCommand(ar,&score);
		if (score==1) break;
		end=fillingArray(ar);
	}
	std::cout << "Game over!";
	return 0;
}