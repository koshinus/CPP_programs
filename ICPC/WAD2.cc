#include<iostream>
#include<utility>
#include<algorithm>
#include<vector>
typedef std::pair<int,int> p;

bool myfunc(p pair1, p pair2)
{
	return (pair1.second > pair2.second);
}

int main()
{
	unsigned short N;
	std::cin >> N;
	std::vector<p> ar(N, p(0,0));
	for(int i = 0; i < N; i++) 
	{
		std::cin >> ar[i].first;
		std::cin >> ar[i].second;
	}
	std::sort(ar.begin(), ar.end(), myfunc);
	for(int i = 0; i < N; i++) 
	{
		std::cout << ar[i].first << " ";
		std::cout << ar[i].second << "\n";
	}
	return 0;
}