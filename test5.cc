#include <iostream>
#include <string>
//#include <regex>
using namespace std;
int main()
{
	/*std::string s("sfdghfda as ajdh ajsh");
	std::regex e(".\s.");
	std::cout << std::regex_replace(s,e,"");*/
	unsigned char s = 100;
	unsigned char a = 1;
	unsigned char j = (unsigned char) (s+a);
	cout << (int)j;
	return 0;
}