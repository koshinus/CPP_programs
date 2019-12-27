#include <iostream>

/*
Итератор - даёт возможность более абстрактно работать с коллекциями/контейнерами.
*/

template<typename T>
class array_like
{
    T * array;
    size_t arr_size;
public:
    array_like(): array(nullptr), arr_size(0){}
    array_like(size_t n): arr_size(n)
    {
        array = new T[n];
    }
    ~array_like()
    {
        delete [] array;
    }
    size_t size(){ return arr_size; }
    T & operator[](size_t i){ return array[i]; }
    struct iterator
    {
        iterator(): elem_ptr(nullptr){}
        iterator(T * ptr): elem_ptr(ptr){}
        iterator operator++(int){ return elem_ptr++; }
        T & operator*(){ return *elem_ptr; }
        bool operator!=(const iterator & other){ return elem_ptr != other.elem_ptr; }
    private:
        T * elem_ptr;
    };
    iterator begin() { return iterator(array); }
    iterator end() { return iterator(array + arr_size); }
};

int main()
{
    array_like<size_t> ar(8);
    for(auto i = 0; i < ar.size(); i++)
        ar[i] = i;
    for(auto it = ar.begin(); it != ar.end(); it++)
        std::cout << *it << ' ';
    return 0;
}
