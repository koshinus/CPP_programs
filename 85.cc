#include<iostream>
#include<cstring>

template<typename Any> 
Any maxn(Any* ar, int n)
{
	Any max_elem = ar[0];
	for(int i=1;i<n;i++)
		if(ar[i]>max_elem) max_elem=ar[i];

return max_elem;
}

template<typename Any> 
const char maxn (const char** ar,int n)
{
	char max_elem[10];
	strcpy(max_elem,*ar[0]);
	int adress;
	for(int i=1;i<n;i++)
		if ( strcmp(*ar[i],max_elem)<=0 ) adress=i;
		
return ar[adress];
}

int main()
{
	int n=4;
	int ar1[]={1,2,3,4};
	double ar2[]={1.4,2.5,3.2,4.7};
	const char* ar3[]={"max","djfk","jsjs","sgad"};
	int res1 = maxn(ar1,n);
	double res2 = maxn(ar2,n);
	std::cout << res1 << ", " << res2 << "\n";
	std::cout << "& max of ar3 = " << maxn(ar3,n) << ", 1 elem of max in ar3 is " << &(maxn(ar3,n)) << "\n";
return 0;
}