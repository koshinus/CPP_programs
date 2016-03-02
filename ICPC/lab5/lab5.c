#include <stdio.h>

double exactSolution(double x)
{
	return 2/(x*x) - 1;
}

double func(double yn, double xn)
{
	return (-20)*yn*yn*(xn - 0.4);
}

double myAbs(x)
{
	return (x>0)? x : -x;
}

void explicitEuler(double step, double limit, double xn, double yn)
{
	FILE *fp = fopen("exEuler.txt", "a+");
	for(xn; xn <= limit; xn+=step) 
	{
		fprintf(fp, "(%lf;", xn);
		fprintf(fp, "%lf)\n", yn);
		yn += step * func(yn, xn);
	}
	fprintf(fp, "\n\n\n");
	fclose(fp);
}

void implicitEuler(double step, double limit, double xn, double yn)
{
	FILE *fp = fopen("imEuler.txt", "a+");
		fprintf(fp, "(%lf;", xn);
		fprintf(fp, "%lf)\n", yn);
	xn+=step;
	for(xn; xn <= limit; xn+=step) 
	{
		fprintf(fp, "(%lf;", xn);
		yn = (yn*xn - 2*step)/(xn + 2*step);
		fprintf(fp, "%lf)\n", yn);
	}
	fprintf(fp, "\n\n\n");
	fclose(fp);
}

void twoStepAdams(double step, double limit, double xn, double yn)
{
	FILE *fp = fopen("twoStepAdams.txt", "a+");
		fprintf(fp, "(%lf;", xn);
		fprintf(fp, "%lf)\n", yn);
	double k1 = step*func(yn,xn);
	double k2 = step*func(yn + k1, xn + step);
	double k3 = step*func(yn + 1/4*k1 + 1/4*k2, xn + step/2);
	double yl = yn;
	double ym = yn + 1/6*k1 + 1/6*k2 + 4/6*k3;
	for(xn+=step; xn <= limit; xn+=step) 
	{
		fprintf(fp, "(%lf;", xn);
		yn = ym + step/2*(3*func(ym, xn) - func(yl, xn-step));
		yl = ym;
		ym = yn;
		fprintf(fp, "%lf)\n", ym);
	}
	fprintf(fp, "\n\n\n");
	fclose(fp);
}

void Simpson(double step, double limit, double xi, double yi)
{
	FILE *fp = fopen("Simpson.txt", "a+");
		fprintf(fp, "(%lf;", xi);
		fprintf(fp, "%lf)\n", yi);
		double k1 = step*func(yi,xi);
		double k2 = step*func(yi + k1/2.0, xi + step/2.0);
		double k3 = step*func(yi + k2/2.0, xi + step/2.0);
		double k4 = step*func(yi + k3, xi + step);
	double yl = yi;
	double ym = 1.0/6*k1 + 2.0/6*k2 + 2.0/6*k3 + 1.0/6*k4 + yl;
	xi+=step;
		fprintf(fp, "(%lf;", xi);
		fprintf(fp, "%lf)\n", ym);
	double yn;
	for(xi+=step; xi <= limit; xi+=step) 
	{
		fprintf(fp, "(%lf;", xi);
		double prevY;
		while(myAbs(yn - prevY) > 0.000001)
		{
			prevY = yn;
			yn = yl + step/3*(func(prevY, xi + step) + 4*func(ym, xi) + func(yl, xi-step));
		}
		fprintf(fp, "%lf)\n", yn);
		yl = ym;
		ym = yn;
	}
	fprintf(fp, "\n\n\n");
	fclose(fp);
}

void calcExactSolution(double step, double limit, double xn, double yn)
{
	FILE *fp = fopen("exactSolution.txt", "a+");
	for(xn; xn <= limit; xn+=step) 
	{
		fprintf(fp, "(%lf;", xn);
		yn = exactSolution(xn);
		fprintf(fp, "%lf)\n", yn);
	}
	fprintf(fp, "\n\n\n");
	fclose(fp);
}

int main()
{
	double xi = 0.0; 
	double yi = 0.5;
	double limit = 1.0;
	double step = 0.1;
	//explicitEuler(step, limit, xn, yn);
	//implicitEuler(step, limit, xn, yn);
	//twoStepAdams(step, limit, xn, yn);
	//calcExactSolution(step, limit, xn, yn);
	Simpson(step, limit, xi, yi);
	step = 0.05;
	//explicitEuler(step, limit, xn, yn);
	//implicitEuler(step, limit, xn, yn);
	//twoStepAdams(step, limit, xn, yn);
	//calcExactSolution(step, limit, xn, yn);
	Simpson(step, limit, xi, yi);
	step = 0.025;
	//explicitEuler(step, limit, xn, yn);
	//implicitEuler(step, limit, xn, yn);
	//twoStepAdams(step, limit, xn, yn);
	//calcExactSolution(step, limit, xn, yn);
	Simpson(step, limit, xi, yi);
	
	return 0;
}