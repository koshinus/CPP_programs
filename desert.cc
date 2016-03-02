#include <iostream>
using namespace std;

int main()
{
	char name[20];
	char dessert[20];
	cout << "Enter your name:\n";
	cin >> name;
	cout  << "Enter your favourite dessert:\n";
	cin >> dessert;
	cout << "This " << dessert << " is for you, " << name;
return 0;
}