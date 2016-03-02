#include <iostream>
#include <string>
using namespace std;

int main()
{
	string first,last,res;
	
	cout << "What is your first name? ";
	cin >> first;
	cout << "What is your last name? ";
	cin >> last;
	
	res = last;
	res+=", ";
	res+=first;
	cout << "Here's the information in a single string: " << res << endl;
return 0;
}