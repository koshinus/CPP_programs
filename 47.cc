#include<iostream>
using namespace std;

struct Pizza
	{
	std::string name;
	int size;
	int weight;
	};

int main()
{
	Pizza ex;
	cout << "Enter the name of pizza company: ";
	getline(cin,ex.name);
	cout << "Enter pizza's size and weight: ";
	cin	>> ex.size >> ex.weight;

	cout << ex.name << " have " << ex.size 
	<< " size and " << ex.weight << " weight." << endl;
return 0;
}