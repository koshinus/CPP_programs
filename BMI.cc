#include <iostream>
using namespace std;

int main()
{
	int foot, inch, pound;
	cout << "Enter your weight: ";
	cin >> pound;
	cout << "Enter your growth in foot and inch: ";
	cin >> foot >> inch;
	cout << "Your weight is " << pound << " lb.\n";
	cout << "Your growth is " << foot << " ft. and " << inch << " in.\n";
	float growth = (foot*12+inch)*0.0254;
	float weight = pound/2.2;
	float index = weight/(growth*growth);
	cout << index;
	
	return 0;
}