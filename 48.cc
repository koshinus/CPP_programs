#include<iostream>
using namespace std;

struct Pizza
	{
	char name[30];
	int size;
	int weight;
	};

int main()
{
	Pizza *ex = new Pizza;
	cout << "Enter pizza's size: ";
	cin	>> ex->size;
	cout << "Enter pizza's weight: ";
	cin >> ex->weight;
	cin.get();
	cout << "Enter the name of pizza company: ";
	cin.get(ex->name,30);

	cout << (*ex).name << " have " << ex->size 
	<< " size and " << ex->weight << " weight." << endl;
	delete ex;
return 0;
}