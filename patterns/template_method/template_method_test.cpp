#include <iostream>

/*
Шаблонный метод - шаблон, предназначенный для того, чтобы дать возможность
    изменения поведения некоторого алгоритма, чтобы получить большую гибкость.
*/

struct base
{
    virtual void step1() { std::cout << "Step one for base class" << std::endl; }
    virtual void step2() { std::cout << "Step two for base class" << std::endl; }
    virtual void step3() { std::cout << "Step three for base class" << std::endl; }
    void templ_method()
    {
        step1();
        step2();
        step3();
    }
};

struct derived1: public base
{
    virtual void step1() override { std::cout << "Step one for derived class" << std::endl; }
};

struct derived2: public base
{
    virtual void step3() override { std::cout << "Step three for derived class" << std::endl; }
};

int main()
{
    base * d1 = new derived1(), * d2 = new derived2();
    d1->templ_method();
    d2->templ_method();
    delete d1, d2;
}
