#include <iostream>
#include <iomanip>
#include <math.h>

double maxAr(int size, double* ar)
{
	double elem = fabs(ar[0]);
	for(int i = 1; i < size; i++)
	{
		if(fabs(ar[i] > elem)) elem = ar[i];
	}
	return elem;
}	

double norm(int size, double A[][3])
{
	double ar[size];
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++) 
		{
			
			if(i != j) ar[i] += fabs(A[j][i]/A[j][j]);
		}
	}
	return maxAr(size, ar);
}

int main()
{
	double A[][3] = {
					{  1.73,  0.03,  0.2 },
					{  -0.1,  0.77, 0.46 },
					{ -0.07, -0.43, -0.5 },
					};
	int size = sizeof(A) / sizeof(*A), count = 0, i = 0;
	double b[] = { 2.39, 2.82, -2.43 }, curX[] = {1,1,1}, prevX[size], difX[size];
	double elem, normA = norm(size, A), eps = 0.00005*(1-normA)/normA;
	do
	{
		for(i = 0; i < size; i++) prevX[i] = curX[i];
		for (i = 0; i < size; i++)
		{
			elem = 0;
			for (int j = 0; j < size; j++) 
			{
				if(i != j) elem += (A[i][j] * prevX[j]);
			}
			curX[i] = (b[i] - elem) / A[i][i];
			difX[i] = curX[i]-prevX[i];
		}
		count++;
	}while( maxAr(size, difX) > eps);
	for(i = 0; i < size; i++) 	std::cout 	<< "x" << i+1 << "=" 
											<< std::setprecision(8) 
											<< curX[i] << " ";
	std::cout  << "\n" << count;
}