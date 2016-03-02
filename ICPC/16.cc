#include <iostream>
#include <cmath>

int main()
{
	double x1,y1,x2,y2;	
	int r1=0,r2=0,rm=0;
	std::cin >> x1 >> y1 >> x2 >> y2;
	
	r1=floor(sqrt(x1*x1+y1*y1));
	r2=floor(sqrt(x2*x2+y2*y2));
	
	rm=floor(sqrt((((y2-y1)-(x2-x1))/((y2-y1)+(x2-x1)))*(((y2-y1)-(x2-x1))/((y2-y1)+(x2-x1))) + 
	(((y2-y1)+(x2-x1))/((y2-y1)-(x2-x1)))*(((y2-y1)+(x2-x1))/((y2-y1)-(x2-x1)))));
	
	std::cout << r1+r2-rm;
return 0;
}