#include <iostream>
#include <cmath>
#include <omp.h>

std::uint64_t regular_fib(int n)
{
	std::uint64_t fib_1 = 1, fib_2 = 1, tmp;
	if (n == 0)
		return 0;
	if (n == 1 || n == 2)
		return 1;
	for (int i = 2; i < n; i++)
	{
		tmp = fib_2;
		fib_2 += fib_1;
		fib_1 = tmp;
	}
	return fib_2;
}

double power_fib(int n)
{
	std::uint64_t fib_1 = 1, fib_2 = 1, tmp;
	if (n == 0)
		return 0;
	if (n == 1 || n == 2)
		return 1;
	long double golden_section = (1. + sqrt(5)) / 2., golden_section_conj = (1. - sqrt(5)) / 2.;
	return ( (pow(golden_section, n) - pow(golden_section_conj, n)) / sqrt(5) );
}

int main()
{
	double start, finish;
	start = omp_get_wtime();
	regular_fib(70);
	finish = omp_get_wtime();
	std::cout << finish - start << std::endl;
	start = omp_get_wtime();
	power_fib(70);
	finish = omp_get_wtime();
	std::cout << finish - start << std::endl;
	std::cout << regular_fib(0) << ' ' << regular_fib(1) << ' ' << regular_fib(2) << ' ' << regular_fib(70) << std::endl;
	std::cout << power_fib(0) << ' ' << power_fib(1) << ' ' << power_fib(2) << ' ' << power_fib(70) << std::endl;
	return 0;
}
