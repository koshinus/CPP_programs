#include<iostream>
#include<vector>
#include<map>
using namespace std;


int main()
{
	map<int, map<char, pair<int, int> > > q_chess_board;
	for(int i = 0; i < 4; i++)
	{
		map<char, pair<int,int> > q_map;
		char a = 'a';
		for(int j = 0; j < 4; j++)
		{
			a = (char)(a+1);
			pair<int,int> p(i,j);
			q_map.insert(pair<char, pair<int,int>>(a, p));
		}
		q_chess_board.insert(pair<int, map<char, pair<int, int> > >(i, q_map));
	}
	cout << q_chess_board[1]['b'].first;
	return 0;
}