#include <iostream>
using namespace std;

double toAstronomic(double lightYears)
{
	return 63240*lightYears;
}

int main()
{
	double astroUnits, lightYears;;
	cout << "Enter the number of light years : ";
	cin >> lightYears;
	astroUnits = toAstronomic(lightYears);
	cout << lightYears << " light years = " 
	<< astroUnits << " astronomical units.";
}