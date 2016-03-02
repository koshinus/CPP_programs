#include <iostream>
#include <iomanip>
#include <cmath>

int sign(double x)
{
	return x>0? 1: -1; // функция сигнум
}

double func(double x)
{
	return pow(M_E,x) - 1/(2*x);
}

int main()
{
	double left=0.1, right=0.5, accuracy=0.000005, middle=0;
	int count=0;
	while( (right - left) > accuracy )
	{
		middle = (right+left)/2;
		if( sign(func(left)) != sign(func(middle)) ) right = middle;
			else left = middle;
		count++;
	}	
	std::cout << count << " " << std::setprecision(8) << middle;
	return 0;
}