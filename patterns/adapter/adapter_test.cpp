#include <iostream>

/*
Адаптер - шаблон, позволяющий натянуть сову на глобус.
    Есть существующая система классов глобусов разных расцветок и
    размеров, есть полезный класс сбоку - сова, но его интерфейс 
    категорически не годится для использования. Выход - создать 
    класс-обёртку для совы, с интерфейсом глобуса. 
*/

class owl
{
public:
    void * reverse_matrix_calc(void * matrix)
    {
        // Сложные вычисления, которые мне лень писать
        // Случайно попавший ультраважный вывод, который нельзя
        //      просто так взять и повторить
        std::cout << "Useless output" << std::endl;
        // Не спрашивайте, почему сова решила вычислять 
        //      обратную матрицу и возвращать указатель
        //      на неё, приведённый к "void *": я тоже не
        //      в курсе, возможно, она - старый Си-программер
        return NULL;
    }
};

class base_globe
{
public:
    virtual void f() { std::cout << "base" << std::endl; }
};

class globe: public base_globe
{
    virtual void f() override { std::cout << "globe" << std::endl; }
};

class owl_on_globe_puller: public base_globe
{
    virtual void f() override
    {
        owl owll;
        owll.reverse_matrix_calc(nullptr);
    }
};

int main()
{
    base_globe * globe1 = new base_globe();
    base_globe * globe2 = new globe();
    base_globe * globe3 = new owl_on_globe_puller();
    globe1->f(); globe2->f(); globe3->f();
    delete globe1, globe2, globe3;
    return 0;
}
