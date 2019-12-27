#include <iostream>
#include <ctime>

/*
Команда - шаблон, предназначенный для того, чтобы создать буфер между вызывающим кодом
    и вызываемым кодом, тем самым уменьшив связность кода и упростив добавление новой
    функциональности в обе его части.
*/

struct request_handler
{
    virtual void handle() = 0;
};

struct request_1xx_handler: public request_handler
{
    virtual void handle() override { std::cout << "Got 1xx. Wait a moment..." << std::endl; }
};

struct request_2xx_handler: public request_handler
{
    virtual void handle() override { std::cout << "Got 2xx. Everything is OK." << std::endl; }
};

struct request_3xx_handler: public request_handler
{
    virtual void handle() override { std::cout << "Got 3xx. Redirecting..." << std::endl; }
};

struct request_4xx_handler: public request_handler
{
    virtual void handle() override { std::cout << "Got 4xx. Your net configuration have some issues." << std::endl; }
};

struct request_5xx_handler: public request_handler
{
    virtual void handle() override { std::cout << "Got 5xx. Server is not availible." << std::endl; }
};

int main()
{
    request_handler * handler;
    srand(time(NULL));
    // Как правило, код, подбирающий нужную команду
    // выносят в отдельный класс
    switch( (rand() % 5) + 1 )
    {
        case 1:
        {
            handler = new request_1xx_handler();
            break;
        }
        case 2:
        {
            handler = new request_2xx_handler();
            break;
        }
        case 3:
        {
            handler = new request_3xx_handler();
            break;
        }
        case 4:
        {
            handler = new request_4xx_handler();
            break;
        }
        case 5:
        {
            handler = new request_5xx_handler();
            break;
        }
    }
    handler->handle();
    delete handler;
    return 0;
}
