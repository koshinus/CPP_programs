#include<iostream>
#include<string>
#include<map>
#include<algorithm>
using namespace std;
typedef std::pair<string,string> strP

class phoneBook
{
private:
	multimap<string, string> phoneData;
public:
	void add(strP val)
	{
		phoneData.insert(val);
	};
	void add(string manName, string manNumber)
	{
		phoneData.insert(strP (manName, manNumber));
	};
	void del(const string &manName)
	{
		if(phoneData.empty()) 
		{
			cout << "There is no data yet!\n";
			return;
		}
		if(phoneData.erase(manName) == 0) 
			cout << "This element is not here!\n";
	};
	void show()
	{
		for(auto val : phoneData) cout 
			<< "Name: " << val.first << ",  "
			<< "Phone number: " << val.second
			<< "\n";
	};
	void dataSearch(string str)
	{
		for(auto val : phoneData) 
		{
			if(val.first.find(str) != string::npos) cout 
				<< "Name: " << val.first << ",  "
				<< "Phone number: " << val.second
				<< "\n";
			else continue;
		}
	};
}