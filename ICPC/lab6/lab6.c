#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#define a 2.23
#define euler 2.7182818284

double func(double yn, double xn)
{
	return yn + a*(2.0+xn-xn*xn) + 2.0;
}

double make_qi(double xi)
{
	return a*(2.0+xi-xi*xi) + 2.0;
}

void shooting(double step, double left, double right)
{
	FILE *fp = fopen("shooting.txt", "a+");
	int n = (right-left)/step;
	double mu = 0.0;
	double newMu = 2.0;
	double *shootingX = (double *)malloc(sizeof(double)*n);
	double *shootingY = (double *)malloc(sizeof(double)*n);
	double *shootingZ = (double *)malloc(sizeof(double)*n);
	shootingX[0] = left;
	for(int i = 1; i < n; i++) shootingX[i] = shootingX[i-1] + step;
	while(fabs(newMu - mu) > 0.0000001)
	{
		mu = newMu;
		printf("%.12lf\n", mu);
		getch();
		shootingY[0] = mu;
		shootingZ[0] = mu - a;
		for(int i = 1; i < n; i++)
		{
			shootingY[i] = shootingY[i-1] + step/2.0*shootingZ[i-1];
			shootingZ[i] = 
					shootingZ[i-1] 
						+ step/2.0*(3.0*func(shootingY[i], shootingX[i]) 
							- func(shootingY[i-1], shootingX[i-1]));
		}
		newMu = mu - (2.0*mu*euler - 2.0*euler - a + 2.0)/(2.0*euler);
	}
	for(int i = 0; i < n; i++)
	{
		fprintf(fp,"(%lf;",shootingX[i]);
		fprintf(fp,"%lf)\n",shootingY[i]);
	}
	free(shootingX);
	free(shootingY);
	free(shootingZ);
	fprintf(fp, "\n\n\n");
	fclose(fp);
}
	/*
	 * n - число уравнений (строк матрицы)
	 * upDiag - диагональ, лежащая над главной (нумеруется: [0;n-2])
	 * mainDiag - главная диагональ матрицы A (нумеруется: [0;n-1])
	 * downDiag - диагональ, лежащая под главной (нумеруется: [1;n-1])
	 * x - правая часть (столбец)
	 * y - решение, массив y будет содержать ответ
	 */
void shuttle(double step, double left, double right)
{
	int n = (int)((right-left)/step);
	FILE *fp = fopen("shuttle.txt", "a+");
	double *upDiag   = (double *)malloc(sizeof(double)*n);
	double *mainDiag = (double *)malloc(sizeof(double)*n);
	double *downDiag = (double *)malloc(sizeof(double)*n);
	double *x = (double *)malloc(sizeof(double)*n);
	double *y = (double *)malloc(sizeof(double)*n);
	downDiag[0] = upDiag[n-1] = 0;
	mainDiag[0] = mainDiag[n-1] = -(2+2*step+step*step);
	downDiag[n-1] = upDiag[0] = 2;
	for(int i = 1; i < n-1; i ++)
	{
		downDiag[i] = upDiag[i] = 1;
		mainDiag[i] = -(2+step*step);
	}
	double m, xi;
	xi = left;
	x[0] = step*step*make_qi(xi) - 2.0*step*a;
	for (int i = 1; i < n; i++)
	{
		xi += step;
		if(i != n-1) x[i] = step*step*make_qi(xi);
			else x[i] = step*step*make_qi(xi) - 2*step*(2*euler + a - 2);
		m = downDiag[i]/mainDiag[i-1];
		mainDiag[i] -= m*upDiag[i-1];
		x[i] -= m*x[i-1];
	}
	
 
	y[n-1] = x[n-1]/mainDiag[n-1];
 
	for (int i = n - 2; i >= 0; i--) 
		y[i]=(x[i]-upDiag[i]*y[i+1])/mainDiag[i];
	
	xi = left;
	for(int i = 0; i < n; i++)
	{
		fprintf(fp, "(%lf;", xi);
		xi+=step;
		fprintf(fp, "%lf)\n", y[i]);
	}
	free(upDiag);	
	free(mainDiag);
	free(downDiag);
	free(x);
	free(y);
	fprintf(fp, "\n\n\n");
	fclose(fp);
}

int main()
{
	double left = 0.0; 
	double right = 1.0;
	double step = (right - left)/10;
	shuttle(step, left, right);
	shooting(step, left, right);
	step = (right - left)/20;
	shuttle(step, left, right);
	shooting(step, left, right);
	
	return 0;
}