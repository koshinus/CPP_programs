#include <iostream>
#include <string>
using namespace std;

int main()
{
	char first[30],last[15], grade;
	short age;
	
	cout << "What is your first name? ";
	cin.getline(first,30);
	cout << "What is your last name? ";
	cin.getline(last,15);
	cout << "What letter grade do you deserve? ";
	cin >> grade;
	cout << "What is your age? ";
	cin >> age;
	
	cout << "Name: " << last << ", " << first << endl;
	cout << "Age: " << age << endl;
	cout << "Grade: " << char(int(grade)+1) << endl;
return 0;
}