#include <iostream>
#include <cctype>

struct Likes
{
	char name[30];
	char likes[30];
}

void calc(int from, int to, int *common, Likes *arr, int i)
{
int count=0;
	for(int j=from;j<to;j++)
	{
		for(int k=0; k<30; k++)
		{
		char symbol = arr[j].likes[k];
		if( isdigit(symbol) )
			{
				if(symbol==arr[i].likes[k])
				count++;
			}
		}
		common[j]=count;
	}
}

int main()
{
using namespace std;

	int n;
	
	cout << "Enter number of people: ";
	cin >> n;
	
	Likes arr[n];
	
	for(int i=0;i<n;i++)
	{
		cout << "Enter the name of person: ";
		cin >> arr[i].name;
		cout << "Enter what he(she) likes: ";
		cin >> arr[i].likes;
	}
	
	int common[n];
	
	cout << "Enter № of man, which you want to recommend what to watch: "
	cin >> i;
	
	common[i-1]=0;
	calc(0,i-2,common,arr,i-1);
	calc(i,n,common,arr,i-1);
	