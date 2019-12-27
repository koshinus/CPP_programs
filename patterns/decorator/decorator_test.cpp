#include <iostream>

/*
Декоратор/обёртка - шаблон, предназначенный для добавления функциональности
    в некоторый класс, без изменений в самом этом классе.
*/

struct base
{
    virtual void about() { std::cout << "This is the base class." << std::endl; }
};

struct derived: public base
{
    virtual void about() override
    {
        base::about();
        std::cout << "And it's derived class." << std::endl;
    }
};

int main()
{
    base * not_base = new derived();
    not_base->about();
    delete not_base;
    return 0;
}
