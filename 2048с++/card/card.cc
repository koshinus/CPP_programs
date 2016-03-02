#include <iostream>
#include <cstdlib>
#include <ctime>
#include <list>
using namespace std;
typedef std::pair<int,int> p;

p myCardGenerator()
{
	srand(time(NULL));
	p card = p(rand()%16, rand()%3);
	return card;
}

int main()
{
	p ar[] = new p [48];
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 16; j++) ar[i*16+j] = new p(j, i);
	char ch;
	int count = 48;
	do
	{
		std::cout << "Enter \"n\" or anything else";
		std::cin >> ch;
		srand(time(NULL));
		p pa = ar[rand()%count];
		std::cout << pa.first << " " << pa.second << "\n";
		lst->DelItem(count);
		count--;
	}while(ch != 'n');
}

