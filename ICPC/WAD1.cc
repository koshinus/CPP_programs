#include<iostream>
#include<string>
#include<algorithm>

int main()
{
	std::string str, subs;
	short i,j;
	std::cin >> str;
	std::cin >> i >> j; 
	subs = str.substr(i-1,j-i+1);
	reverse(subs.begin(),subs.end());
	std::cout << str.replace(i-1,j-i+1,subs);
	return 0;
}