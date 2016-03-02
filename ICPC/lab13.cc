#include <iostream>
#include <iomanip>
#include <cmath>

double sum(double i)
{
	double res=0;
	for(double n = 1; n<i; n++)
	{
		res+=(n*n-1.8*n-1)/((pow(n,4) + 1));
	}
	return res;
}

int main()
{
	std::cout << std::setprecision(8) << sum(2000001) << "\n";
	std::cout << std::setprecision(8) << sum(4244) << "\n";
	std::cout << std::setprecision(8) << sum(212) << "\n";
	return 0;
}