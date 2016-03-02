#include <iostream>

struct intPair
{
	int fst;
	int snd;
};

double fabs(double a)
{
	return (a>0)?a:-a;
}

intPair findMaxElem(double A[][3], int i)
{
	int n = sizeof(*A)/sizeof(**A);
	double maxElem = fabs(A[i][i]);
	intPair indexes = {i,i};
	for(int k = i; k < n; k++)
	{
		for(int j = i; j < n; j++)
		{
			if(fabs(A[k][j]) > maxElem)
			{
				maxElem = fabs(A[k][j]);
				indexes.fst = k;
				indexes.snd = j;
			}
		}
	}
	return indexes;
}

void exchange(intPair indexes, double A[][3], int j, double *b)
{
	int i;
	double exch;
	int n = sizeof(*A)/sizeof(**A);
	for(i = 0; i < n; i++)
	{
		exch = A[i][j];
		A[i][j] = A[i][indexes.snd];
		A[i][indexes.snd] = exch;
	}
	for(i = 0; i < n; i++)
	{
		exch = A[j][i];
		A[j][i] = A[indexes.fst][i];
		A[indexes.fst][i] = exch;
	}
	exch = b[j];
	b[j] = b[indexes.fst];
	b[indexes.fst] = exch;
}

int main()
{
	int i, j;
	double elem;
	double A[][3] = {
					{  1.73,  0.03,  0.2 },
					{  -0.1,  0.77, 0.46 },
					{ -0.07, -0.43, -0.5 },
					};
	double b[] = { 2.39, 2.82, -2.43 };
	int size = sizeof(b) / sizeof(*b);
	for (i = 0; i < size; i++)
	{
		exchange(findMaxElem(A, i), A, i, b);
		j = i;
		elem = A[i][j];
		b[i] /= elem;
		for (j; j < size; j++) A[i][j] /= elem;
		int k, s;
		k = i + 1;
		s = i;
		for (k; k < size; k++)
		{
			elem = A[k][s];
			b[k] -= b[i] * elem;
			for (s; s < size; s++) A[k][s] -= A[i][s] * elem;
			s = i;
		}
	}
	j--;
	for (j; j > 0; j--)
	{
		i = j;
		elem = b[j];
		for (i; i > 0; i--)
		{
			b[i-1] -= A[i-1][j]*elem;
			A[i-1][j] = 0;
		}
	}
	for (i = 0; i < size; i++) std::cout << "x" << i+1 << "=" << b[i] << " ";
	return 0;
}