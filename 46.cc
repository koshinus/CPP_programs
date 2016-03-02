#include<iostream>
using namespace std;

struct CandyBar
	{
	string name;
	double weight;
	int price;
	};

int main()
{
	CandyBar arr[3];
	int i;
	for(i=0;i<3;i++)
		{
		cout << "Enter next element: ";
		cin >> arr[i].name >> arr[i].weight >> arr[i].price;
		}
	for(i=0;i<3;i++)
	cout << arr[i].name << " have " << arr[i].weight 
	<< " weight and " << arr[i].price << " price." << endl;
return 0;
}