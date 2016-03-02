#include <iostream>
#include <string>
using namespace std;

int main()
{
	string str1 = "hgfhgfhgfh";
	string str2 = "dfxvhgfjh";
	str1+str2;
	double ar[] = {3.4,2.3,4.555};
	double *i = ar;
	cout << sizeof(ar) << endl;
	cout << sizeof(i) << endl;
return 0;
}
/*for(i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++) std::cout << A[i][j] << " ";
		std::cout << "\n";

double max(double a, double b)
{
	return (a>b)?a:b;
}	
*/