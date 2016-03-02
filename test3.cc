#include<iostream>

int main()
{
	short n,i,j;
	std::cin >> n;
	
	short **a = new short*[n];
		for(i=0;i<n;i++) a[i] = new short [n];
		
	for(i=0;i<n;i++)
		for(j=0;j<n;j++) std::cin >> a[i][j];
	
	for(short line=0;line<2*n-1;line++)
	{
		if(line<n) 
			for(i=line,j=0;i>-1;i--,j++) std::cout << a[i][j] << " ";
			
			else 
				for(i=n-1,j=line-n+1;i>line-n;i--,j++) std::cout << a[i][j] << " ";
	}

	for(i=0;i<n;i++) delete []a[i];
	return 0;
}