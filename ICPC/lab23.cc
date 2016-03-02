#include <iostream>
#include <iomanip>
#include <cmath>

double func(double x)
{
	return pow(M_E,x) - 1/(2*x);
}

double formCheckX(double xn, double x0)
{
	return (  func(xn) * (xn-x0)  )/(  func(xn) - func(x0)  );
}

int main()
{
	double x0=0.1, xn=0.5, checkX, accuracy=0.000005;
	int count=0;
	do 
	{
		checkX = formCheckX(xn,x0);
		xn = xn - checkX;
		count++;
	}
	while( fabs(checkX) > accuracy );
	std::cout << count << " " << std::setprecision(8) << xn;
	return 0;
}