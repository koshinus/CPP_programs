#include <iostream>

int main()
{
	int n,k,x,y;
	std::cin >> n >> k >> x;
	y=x;
	for(int i=0;i<k-1;i++)
	{
		y--;
		std::cout << y << " ";
	}
	y=x;
	std::cout << y << " ";
	for(int i=0;i<n-k;i++)
	{
		y++;
		std::cout << y << " ";
	}
	
return 0;
}