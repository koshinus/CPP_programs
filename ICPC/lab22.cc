#include <iostream>
#include <iomanip>
#include <cmath>

double func(double x)
{
	return 1/(  2 * pow(M_E,x)  );
}

int main()
{
	double prevX, curX=0.5, accuracy=0.000005;
	int count=0;
	do 
	{
		prevX=curX;
		curX=func(curX);
		count++;
	}
	while( fabs(curX-prevX) > accuracy );
	std::cout << count << " " << std::setprecision(8) << curX;
	return 0;
}