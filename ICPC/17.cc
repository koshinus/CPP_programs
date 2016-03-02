#include <iostream>

void genFib(unsigned long a)
{
	unsigned long fib1=0,fib2=1,temp;
	while(fib1<a)
	{
		temp  = fib1;
		fib1 += fib2;
		fib2  = temp;
	}
	if(fib1==a) std::cout << "IsFibo\n";
		else std::cout << "IsNotFibo\n";
}

int main()
{
	int n,i,b;
	std::cin >> n;
	unsigned long *a = new unsigned long [n];
	for(i=0;i<n;i++) std::cin >> a[i];
	i=0;
	for(i=0;i<n;i++) genFib(a[i]);
	return 0;
}