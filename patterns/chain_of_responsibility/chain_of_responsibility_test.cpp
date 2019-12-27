#include <iostream>
#include <string>

/*
Цепочка обязанностей - шаблон, подразумевающий последовательный вызов (один из другого)
    ряда обработчиков, производящих определённые вычисления и принимающих решения: стоит
    ли переложить решение некоторой проблемы на следующего в цепочке или можно справиться
    самостоятельно. Обычно используется при проверке, чтобы не писать много if-else. Все
    обработчики должны иметь единый интерфейс.
По идее, для решения FizzBuzz можно было бы и не извращаться, но мне хочется написать это именно так.
*/

struct divide_3
{
    static std::string is_divide(int num)
    {
        return num % 3 == 0 ? "Fizz" : "";
    }
};

struct divide_5
{
    static std::string is_divide(int num)
    {
        return num % 5 == 0 ? "Buzz" : divide_3::is_divide(num);
    }
};

struct divide_15
{
    static std::string is_divide(int num)
    {
        return num % 15 == 0 ? "FizzBuzz" : divide_5::is_divide(num);
    }
};

int main()
{
    int n;
    std::cin >> n;
    std::cout << divide_15::is_divide(n) << std::endl;
}
