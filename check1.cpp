#include<iostream>

class High
{
public:
	virtual void show()
	{
		std::cout << "High";
	}
};
class Low : public High
{
public:
	virtual void show()
	{
		std::cout << "Low";
	}
	void be()
	{
		std::cout << "be";
	}
};

int main()
{
	High *h1 = new High;
	High *h2 = new Low;
	Low *h3 = new Low;
	//Low *h4 = new High;
	High bar;
	Low blow;
	High * pb = static_cast <High *> ( &blow ) ;
	Low  * pl = static_cast < Low *> ( &bar ) ;
}