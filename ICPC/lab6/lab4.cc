#include<iostream>
#include<iomanip>
#include<cmath>

double func(double point)
{
	return cos(point+point*point);
}

double simpson(double a, double b, double h)
{
	double point = a;
	double n = (b - a)/h;
	double result = 0;
	for(int i = 0; i <= (int)n-1; i++)
	{
		result += func(point) + 4*func(point+h/2) + func(point+h);
		point += h;
	}
	return result *= h/6;
}

double Gregory(double a, double b, double h)
{
	double point = a;
	double n = (b - a)/h;
	double result = 0;
	for(int i = 1; i <= (int)n-1; i++)
	{
		point += h;
		result += h * func(point);
	}
	return result = h*result + (h/2) * (func(a) + func(b)) + 
                       (h/24) * (-3*func(a) + 4*func(a+h) - func(a + 2*h) - func(b - 2*h) + 4*func(b-h) - 3*func(b));;
}


int main()
{
	using namespace std;
	double a = 2;
	double b = 3;
	double h = 0.1;
	cout 	
			<< "Simpson with h=0.1 is " << setprecision(12) << simpson(a, b, h)
			<< ", gregory with h=0.1 is " << setprecision(12) << Gregory(a, b, h) 
			<< "\n";
	h = 0.05;
	cout 	
			<< "Simpson with h=0.05 is "  << setprecision(12) << simpson(a, b, h)
			<< ", gregory with h=0.05 is " << setprecision(12) << Gregory(a, b, h) 
			<< "\n";
	h = 0.2;
	cout 	
			<< "Simpson with h=0.2 is " << setprecision(12) << simpson(a, b, h)
			<< ", gregory with h=0.2 is " << setprecision(12) << Gregory(a, b, h)
			<< "\n";
	return 0;
}
