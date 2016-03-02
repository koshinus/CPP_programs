#include <iostream>

const char* word(short n)
{
	switch(n)
	{
		case 1 : return "alpha";
		case 2 : return "beta";
		case 3 : return "gamma";
		case 4 : return "delta";
		case 5 : return "epsilon";
		case 6 : return "zeta";
		case 7 : return "eta";
		case 8 : return "theta";
		case 9 : return "iota";
		case 10 : return "kappa";
		case 11 : return "lambda";
		case 12 : return "mu";
		case 13 : return "nu";
		case 14 : return "xi";
		case 15 : return "omicron";
		case 16 : return "pi";
		case 17 : return "rho";
		case 18 : return "sigma";
		case 19 : return "tau";
		case 20 : return "upsilon";
		case 21 : return "phi";
		case 22 : return "chi";
		case 23 : return "psi";
		case 24 : return "omega";
	}
}


int main()
{
	short n;
	std::cin >> n;
	std::cout << word(n);
	
return 0;
}