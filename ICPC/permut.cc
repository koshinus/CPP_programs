#include<iostream>
#include<string>

std::string X = "rrrgggggbbbb";
int N = 12;

void Swap(int a,int b)
{
    char t=X[a];
    X[a]=X[b];
    X[b]=t;
}

void Generate(int k, long *count)
{
    if (k==N)
    {
		(*count)++;
        /*for(int i=0;i<N;i++)
            std::cout<<X[i]<<" ";
        std::cout<<"\n";*/
    }
    else
    { 
        for(int j=k;j<N;j++)
        {
            Swap(k,j);
            Generate(k+1, count);
            Swap(k,j);
        }
    }
}
 
int main()
{
	long count = 0;/*
    std::cout<<"N=";
    std::cin>>N;
    for(int i=0;i<N;i++)
        X[i]=(char)('a'+i);*/
    Generate(0, &count);
    std::cout << count;
}