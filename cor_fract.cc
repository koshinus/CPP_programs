#include <iostream>
using namespace std;

class correct_fraction
{
private:
	typedef unsigned long type;
	type numerator;
	type denominator;
public:
	correct_fraction(double &num)
	{
		int_part = (type)num; 
		
}
int main()
{
	double ar[] = {3.4,2.3,4.555};
	double *i = ar;
	cout << sizeof(ar) << endl;
	cout << sizeof(i) << endl;
return 0;
}