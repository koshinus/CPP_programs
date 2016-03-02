#include <iostream>

int main()
{
	int x,y;
	std::cin >> x >> y;
	x+=y;
	if(x>=360) x-=360;
		else if(x<0) x+=360;
	std::cout << x;
	
return 0;
}