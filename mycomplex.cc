#include<iostream>
using namespace std;

class complex
{
private:
	double Re;
	double Im;
public:
	complex(double x = 0, double y = 0)
	{
		Re=x;
		Im=y;
	};
	complex(const complex &c)
	{
		Re=c.Re;
		Im=c.Im;
	};
	friend bool operator==(const complex &c1, const complex &c2)
	{
		return ( (c1.Re == c2.Re) && (c1.Im == c2.Im) );
	};
	complex operator+(const complex &c)
	{
		return complex(Re+c.Re,Im+c.Im);
	};
	complex operator+(const double d)
	{
		return complex(Re+d,Im);
	};
	complex operator-(const complex &c)
	{
		return complex(Re-c.Re,Im-c.Im);
	};
	complex operator-(const double d)
	{
		return complex(Re-d,Im);
	};
	complex operator*(const complex &c)
	{
		return complex(Re*c.Re-Im*c.Im,Re*c.Im+Im*c.Re);
	};
	complex operator*(const double d)
	{
		return complex(Re*d,Im*d);
	};
	complex operator/(const complex &c)
	{
		return complex(
			(Re*c.Re+Im*c.Im)/(c.Re*c.Re+c.Im*c.Im),
			(Re*c.Im-Im*c.Re)/(c.Re*c.Re+c.Im*c.Im));
	};
	complex operator/(const double d)
	{
		return complex(Re/d,Im/d);
	};
	complex operator+=(const complex &c)
	{
		return *this = *this + c;
	};
	complex operator-=(const complex &c)
	{
		return *this = *this - c;
	};
	complex operator*=(const complex &c)
	{
		return *this = *this * c;
	};
	complex operator/=(const complex &c)
	{
		return *this = *this / c;
	};
	complex operator=(const complex &c)
	{
		if(*this == c) return *this;
		Re = c.Re;
		Im = c.Im;
		return *this;
	};
	complex operator~()
	{
		return complex (Re,-Im);
	};
	friend ostream & operator<<(ostream &os, const complex &c)
	{
		if(c.Re == 0) os << c.Im << "i";
			else if(c.Im == 0) os << c.Re;
				else os << c.Re << "+" << c.Im << "i";
		return os;
	};
	friend istream & operator>>(istream &is, complex &c) 
	{
		is >> c.Re >> c.Im;
		return is;
	};
	~complex()
	{
//	cout << "\nGoodbye";
	};
};

int main()
{
	using std::cout;
	complex a(3.0,4.0);
	complex c;
	cout << "Enter the complex number (press ctrl+C for exit): ";
	while ((cin >> c))
	{
		cout << "c is " << c << '\n';
		cout << "complex union is equal to " << ~c << '\n';
		cout << "a is equal " << a << '\n';
		cout << "a + c is equal " << a + c << '\n';
		cout << "a - c is equal " << a - c << '\n';
		cout << "a * c is equal " << a * c << '\n';
		cout << "c * 2 is equal " << c * 2 << '\n';
		cout << "Enter the complex number (press ctrl+C for exit): ";
		cout << "Ready!\n";
	}
	return 0;
}