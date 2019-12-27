#include <iostream>
#include <thread>
#include <mutex>
/*
"Майеровский" C++11-синглтон
Смысл синглтона - один объект на программу, обычно с помощью него 
    реализуют разные менеджеры-диспетчеры и т.п.
*/

struct singleton
{
    // Удаляем всевозможные функции, позволяющие создать объект, не через вызов instance
    singleton(const singleton &) = delete;
    singleton & operator=(const singleton &) = delete;
    singleton(singleton &&) = delete;
    singleton & operator=(singleton &&) = delete;
    // Магия С++-11
    static singleton & instance()
    {
        static singleton inst;
        return inst;
    }
private:
    singleton() = default;
};

int main()
{
    std::mutex m;
    singleton & single = singleton::instance();
    std::thread t1([&single, &m]()
    {
        m.lock();
        std::cout << "t1 " << &single << ' ';
        m.unlock();
        m.lock();
        std::cout << "t1 " << &singleton::instance() << std::endl;
        m.unlock();
    });
    std::thread t2([&single, &m]()
    {
        m.lock();
        std::cout << "t2 " << &single << ' ';
        m.unlock();
        m.lock();
        std::cout << "t2 " << &singleton::instance() << std::endl;
        m.unlock();
    });
    t1.join();
    t2.join();
    /*
    * Выводит
    * t1 0x55944961b132 t1 0x55944961b132
    * t2 0x55944961b132 t2 0x55944961b132
    */
    return 0;
}
