#include<iostream>
#include<string>
#include<algorithm>
#include<list>
using namespace std;

std::string X = "rrrgggggbbbb";
//std::string X = "rrrggy";
int N = 12;
//int N = 6;

bool isValid(string s)
{
	for(int i = 1; i < N; i++)
	{
		if(s[i]=='b' && s[i]==s[i-1]) return false;
		//if(s[i]=='r' && s[i]==s[i-1]) return false;
	}
	return true;
}

void Swap(int a,int b)
{
    char t=X[a];
    X[a]=X[b];
    X[b]=t;
}

void Generate(int k, list<string> *lst)
{
    if (k==N)
    {
		if(isValid(X) && find(lst->begin(), lst->end(), X) == lst->end()) lst->push_front(X);
		/*{
			for(int i=0;i<N;i++)
				std::cout<<X[i]<<" ";
			std::cout<<"\n";
		}*/
    }
    else
    { 
        for(int j=k;j<N;j++)
        {
            Swap(k,j);
            Generate(k+1, lst);
            Swap(k,j);
        }
    }
}
 
int main()
{
	list<string> lst;
	/*long count = 0;
    std::cout<<"N=";
    std::cin>>N;
    for(int i=0;i<N;i++)
        X[i]=(char)('a'+i);*/
    Generate(0, &lst);
    cout << lst.size();
}