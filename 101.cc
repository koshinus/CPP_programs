#include<iostream>
#include<cstring>

class bankAccount
{
private:
	char name[30];
	char accNumber[30];
	double balance;
public:
	bankAccount(const char *clientName="",const char *clientAccNumber="",double clientBalance=0)
	{
		strcpy(name,clientName);
		strcpy(name,clientAccNumber);
		balance=clientBalance;
	};

	~bankAccount()
	{
		std::cout << "Goodbye";
	};
	
	void show()
	{
		std::cout << "Name of bank account: " << name;
		std::cout << "\nAccount number: " << accNumber;
		std::cout << "\nBalance of bank account: " << balance << std::endl;
	};
	void inc(double n)
	{
		balance+=n;
	};
	void dec(double n)
	{
		balance-=n;
	};
};

int main()
{
	bankAccount Vadim("Vad","23895",4.23);
	Vadim.show();
	Vadim.inc(5.6);
	Vadim.dec(7.6);
	Vadim.show();
	return 0;
}