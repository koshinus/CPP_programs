#include<iostream>

int main()
{
	short day=1;
	short *a = new short[100000];
	a[0]=1;
	short hydra=1;
	std::cout << a[0] << std::endl;
	std::cout << hydra << std::endl;
	while(day<=8)
	{
		std::cout << day << std::endl;
		for(int i=0;i<hydra;i++)
		{
			switch(a[i])
			{
				case(0):continue;
				case(1):a[i]++;
				case(2):a[i]++;
				case(3):{a[hydra]=1;hydra++;a[i]++;};
				case(4):{a[hydra]=1;hydra++;a[i]=0;};
			}
		std::cout << i << std::endl;
		}
		day++;
	}
	short count=0;
	for(int i=0;i<hydra;i++)
	{
		if(a[i]!=0) count++;
	}
	std::cout << count;
	delete []a;
	return 0;
}