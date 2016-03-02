#include<iostream>

struct CandyBar
	{
	std::string name;
	double weight;
	int price;
	};

int main()
{
	CandyBar snack = {"Mocha Munch",2.3,350};
	std::cout << snack.name << " have " << snack.weight 
	<< " weight and " << snack.price << " price." << std::endl;
return 0;
}