#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

int x = 0;
mutex m;

int func1()
{
    while(true)
    {
        m.lock();
        x +=1;
        m.unlock();
    }
}

int func2()
{
    m.lock();
    while(true)
    { 
        if (x % 1000 == 0) 
        std::cout << x << std::endl;
        m.unlock();
    }
}

int main()
{
thread tr1(func1);
thread tr2(func2);
tr1.join();
tr2.join();
}
