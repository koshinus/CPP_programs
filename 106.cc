#include<iostream>

class Move
{
private:
	double x;
	double y;
public:
	Move (double a=0, double b=0)
	{
		x=a;
		y=b;
	};
	void showmove() const
	{
		std::cout << "x = " << x << "y = " << y << std::endl;
	};
	void add(const Move &m)
	{
		x+=m.x;
		y+=m.y;
	};
	//reset (double а=0, double b=0);
	~Move()
	{
	std::cout << "\nGoodbye";
	};
};
	
int main()
{

	Move one(3,4);
	one.showmove();
	Move two(6,5);
	one.add(two);
	one.showmove();

	return 0;
}