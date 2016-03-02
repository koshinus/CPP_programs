#include <iostream>

int main()
{
	long long v=0,g=0,n,k,x1,y1,x2,y2;
	std::cin >> n;
	for(k=0;k<n;k++)
	{
		std::cin >> x1 >> y1 >> x2 >> y2;
		if(x1==x2) v++;
			else g++;
	}
	std::cout << v*g;
	
return 0;
}