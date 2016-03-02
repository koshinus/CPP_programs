#include <iostream>
#include <iomanip>
#include <cmath>

int main()
{
	double n;
	double res=0;
	for(n = 1; n<212; n++)
	{
		res+=(1.8-n-n*n*n)/(n*n*n*(pow(n,4) + 1));
	}
	res+=(-1.8)*1.202056903+M_PI*M_PI/6;
	std::cout << std::setprecision(8) << res;
	return 0;
}