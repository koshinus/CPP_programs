#include <iostream>
#include "resumable.hpp"

resumable_cancelable foo()
{
    for(int i = 0; i < 10; i++)
    {
        std::cout << i << std::endl;
        co_await std::suspend_always();
    }
}

int main()
{
    auto t = foo();
    t.resume();
    t.resume();
    t.resume();
    std::cout << "Cancel point" << std::endl;
    t.cancel();
    return 0;
}
