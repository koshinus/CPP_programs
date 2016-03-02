#include<iostream>
#include<iomanip>
#include<cmath>

double func(double point)
{
	return sin(1+point*point);
}

double simpson(double left, double right, double step)
{
	double point = left;
	double n = (right - left)/step;
	double result = 0;
	for(int i = 0; i <= (int)n-1; i++)
	{
		result += func(point) + 4*func(point+step/2) + func(point+step);
		point += step;
	}
	return result *= step/6;
}

double middle(double left, double right, double step)
{
	double point = left;
	double n = (right - left)/step;
	double result = 0;
	for(int i = 0; i < (int)n; i++)
	{
		result += func(point + step/2);
		point += step;
	}
	return result *= step;
}

double gauss(double left, double right, double step)
{
	double point = left;
	double n = (right - left)/step;
	double result = 0;
	for(int i = 0; i < (int)n; i++)
	{
		result += step/2 
			* ( func( (2*point + step)/2 - step/(2*sqrt(3)) ) 
			+ func( (2*point + step)/2 + step/(2*sqrt(3)) ) );
		point += step;
	}
	return result;
}

int main()
{
	using namespace std;
	double left = 2;
	double right = 3;
	double step = 0.1;
	double n = (right - left)/step;
	cout 	
			<< "Simpson with step=0.1 is " << setprecision(12) << simpson(left, right, step)
			<< ", middle with step=0.1 is " << setprecision(12) << middle(left, right, step) 
			<< ", gauss with step=0.1 is " << setprecision(12) << gauss(left, right, step) 
			<< "\n";
	step = 0.05;
	cout 	
			<< "Simpson with step=0.05 is "  << setprecision(12) << simpson(left, right, step)
			<< ", middle with step=0.05 is " << setprecision(12) << middle(left, right, step) 
			<< ", gauss with step=0.05 is " << setprecision(12) << gauss(left, right, step) 
			<< "\n";
	step = 0.025;
	cout 	
			<< "Simpson with step=0.025 is " << setprecision(12) << simpson(left, right, step)
			<< ", middle with step=0.025 is " << setprecision(12) << middle(left, right, step)
			<< ", gauss with step=0.025 is " << setprecision(12) << gauss(left, right, step)  
			<< "\n";
	return 0;
}