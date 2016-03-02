#include<iostream>
#include<cstring>

class Plorg
{
private:
	char name[20];
	int CI;
public:

	Plorg(char *plorgName="Plorg",int plorgCI=50)
	{
		strcpy(name,plorgName);
		CI=plorgCI;
	}
	
	void add(int n)
	{
	CI+=n;
	};
	void sub(int n)
	{
	CI-=n;
	};
	void mul(int n)
	{
	CI*=n;
	};
	
	void show()
	{
		std::cout << "\nPlorg's name is " << name << ", Plorg's CI is " << CI;
	}
};
	
int main()
{

	Plorg one("hsdgf",45);
	
	one.show();
	one.add(7);
	one.sub(8);
	one.mul(2);
	one.show();
	
	return 0;
}