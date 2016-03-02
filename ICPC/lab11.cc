#include <iostream>
#include <iomanip>
#include <cmath>

int main()
{
	double n;
	double res=0;
	for(n = 1; n<4244; n++)
	{
		res+=(-1)*(1.8*pow(n,3) + n*n + 1)/(n*n*(pow(n,4) + 1));
	}
	res+=M_PI*M_PI/6;
	std::cout << std::setprecision(8) << res;
	return 0;
}