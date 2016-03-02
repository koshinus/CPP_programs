#include <iostream>
#include <string>
#include <cstring>
using namespace std;

int main()
{
	char first[30],last[30];
	
	cout << "What is your first name? ";
	cin.getline(first,30);
	cout << "What is your last name? ";
	cin.getline(last,30);
	
	char res[62];
	strcpy(res,first);
	strcat(strcat(res,", "),last);
	cout << "Here's the information in a single string: " << res << endl;
return 0;
}