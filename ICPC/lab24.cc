#include <iostream>
#include <iomanip>
#include <cmath>

double func1(double x)
{
	return log(x) - 1.6 + x*x;
}

double func2(double x)
{
	return 1/x + 2*x;
}

double formNextX(double xn)
{
	return xn - func1(xn)/func2(xn);
}

int main()
{
	double xCur = 1.5, xPrev = 1.5, accuracy = 0.00005;
	int count=0;
	do 
	{
		xPrev = xCur;
		xCur = formNextX(xPrev);
		count++;
	}
	while( fabs(xCur-xPrev) > accuracy );
	std::cout << count << " " << std::setprecision(8) << xCur;
	return 0;
}