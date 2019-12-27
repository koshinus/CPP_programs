#include <iostream>
#include <random>
#include <omp.h>

/*
Прототип - шаблон, полезный в том случае, если копирование объекта
    стоит сильно дешевле его создания и это вполне нормально иметь в 
    системе две (или больше) одинаковых копий одного объекта.
*/

void fill_double_array(double * array, std::size_t array_size)
{
    std::random_device rd;

    std::mt19937 e2(rd());
    std::uniform_real_distribution<> dist(0, 25);

    for (std::size_t i = 0; i < array_size; i++)
		array[i] = dist(e2);
}

class with_prototype
{
    double * array;
    size_t array_size;
public:
    with_prototype(): array(nullptr), array_size(0){}
    with_prototype(size_t n)
    {
        double start = omp_get_wtime();
        array = new double[n];
        array_size = n;
        fill_double_array(array, n);
        std::cout << "Full time for initialization: " << omp_get_wtime() - start << std::endl;
    }
    ~with_prototype()
    {
        delete [] array;
    }
    with_prototype * clone()
    {
        double start = omp_get_wtime();
        with_prototype * new_prot = new with_prototype();
        new_prot->array = new double[array_size];
        new_prot->array_size = array_size;
        std::copy(array, array + array_size, new_prot->array);
        std::cout << "Full time for cloning: " << omp_get_wtime() - start << std::endl;
        return new_prot;
    }
};

int main()
{
    with_prototype obj1(100000), *obj2, *obj3;
    obj2 = obj1.clone();
    obj3 = obj1.clone();
    delete obj2, obj3;
    return 0;
}
