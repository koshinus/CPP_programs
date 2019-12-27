#include <iostream>
#include <string>
#include <string_view>
#include <cstdio>

/*
Интерпретатор - шаблон, предназначенный для того, чтобы предоставить стороннему
    пользователю вносить изменения в логику программы без изменения исходного
    кода и пересборки самой программы.
*/

struct interpreter
{
    void handle_input()
    {
        // TODO: обработать ввод нормально.
        std::cin >> command >> x >> y;
        if(command == "ADD")
        {
            add(x, y);
            return;
        }
        else if(command == "SUB")
        {
            sub(x, y);
            return;
        }
    }
    void add(int x, int y) { std::cout << x + y << std::endl; }
    void sub(int x, int y) { std::cout << x - y << std::endl; }
private:
    std::string command;
    int x = 0, y = 0;
};

int main()
{
    interpreter interp;
    try
    {
        while(true)
        {
            interp.handle_input();
        }
    }
    catch(...) {}
    return 0;
}
