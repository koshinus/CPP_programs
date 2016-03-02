#include<iostream>

class VectorND
{
private:
	unsigned int size = new unsigned int;
	double *array = new double [size];
public:
	VectorND() 
	{
		int size = 0;
		double *array = new double [0];
	};
	VectorND(const unsigned int &n) 
	{
		int size = n;
		double *array = new double [n];
	};
	VectorND(const double &xi, const unsigned int &n) 
	{
		double *array = new double [n];
		for(int i = 0; i < n; i++) array[i] = xi;
	};
	int size()
	{
		return size;
	};
	double & operator[](const unsigned int &i)
	{
		return array[i];
	};
	VectorND(const VectorND &v) 
	{
		if(size != v.size) 
		{
			~VectorND();
			VectorND(v.size);
		}
		for(int i = 0; i < *this.size; i++) *this[i] = v[i];
	};
	VectorND & operator=(const VectorND &v)
	{
		if(this == &v) return *this;
		VectorND(const VectorND &v);
	};
	VectorND & operator+(const VectorND &v)
	{
		if(*this.size != v.size) 
		{
			std::cout << "Vectors must have the same size!";
			retutn *this;
		}
		for(int i = 0; i < *this.size; i++) *this[i] += v[i];
	};
	VectorND & operator-(const VectorND &v)
	{
		if(*this.size != v.size) 
		{
			std::cout << "Vectors must have the same size!";
			retutn *this;
		}
		for(int i = 0; i < *this.size; i++) *this[i] -= v[i];
	};
	bool operator==(const VectorND &v)
	{
		if(*this.size != v.size) 
		{
			std::cout << "Vectors must have the same size!";
			retutn false;
		}
		if(this == &v) 
		{
			std::cout << "It's not the two different vectors."
			return true;
		}
		for(int i = 0; i < v.size; i++) if(*this[i] != v[i]) return false;
		return true;
	};
	double scalar(const VectorND &v)
	{
		double scal = 0.0;
		if(*this.size != v.size) 
		{
			std::cout << "Vectors must have the same size!";
			retutn *this;
		}
		for(int i = 0; i < *this.size; i++) scal += *this[i]*v[i];
		return scal;
	};
	double get_xi(const unsigned int &i)
	{
		return *this[i];
	};
	VectorND & multiple(const double &num)
	{
		for(int i = 0; i < *this.size; i++) *this[i] *= num;
	};
	~VectorND()
	{
		delete [] array;
		delete size;
	};