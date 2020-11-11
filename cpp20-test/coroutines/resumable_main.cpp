#include <iostream>
#include "resumable.hpp"

resumable foo()
{
  std::cout << "Hello" << std::endl;
  co_await std::suspend_always();
  std::cout << "World" << std::endl;
}

int main()
{
    auto t = foo();
    t.resume();
    std::cout << " coroutine " << std::endl;
    t.resume();
    return 0;
}
