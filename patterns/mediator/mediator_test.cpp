#include <iostream>
#include <string>

/*
Посредник - шаблон, предназначенный для того, чтобы отделить части программы
    друг от друга, тем самым уменьшив их связность, упрощая тем самым переиспользование.
    Предполагается, что теперь они должны будут общаться путём посылки друг другу
    сообщений через тот самый объект-посредник.
*/

struct mediator
{
    virtual void notify(std::string msg, std::string to) = 0;
};

class Woman
{
protected:
    mediator * sender;
    std::string last_msg;
public:
    void show_last_msg() { std::cout << last_msg << std::endl; }
    virtual void send_msg(std::string msg, std::string to) = 0;
    void set_sender(mediator * new_sender) { sender = new_sender; }
    void set_last_msg(std::string msg) { last_msg = msg; }
};

// Наследниками общего класса они сделаны для удобства, чтобы не прописывать
// 3 раза одно и то же в функциях.
struct Mary: public Woman
{
    virtual void send_msg(std::string msg, std::string to) override
    {
        sender->notify(msg, to);
        std::cout << "Wow!" << std::endl;
    }
};

struct Anna: public Woman
{
    virtual void send_msg(std::string msg, std::string to) override
    {
        sender->notify(msg, to);
        std::cout << "Wow!!" << std::endl;
    }
};

struct Elizabeth: public Woman
{
    virtual void send_msg(std::string msg, std::string to) override
    {
        sender->notify(msg, to);
        std::cout << "Wow!!!" << std::endl;
    }
};

class woman_mediator: public mediator
{
    Mary * mary;
    Anna * anna;
    Elizabeth * liz;
public:
    woman_mediator(Mary * mary_, Anna * anna_, Elizabeth * liz_):
        mediator(), mary(mary_), anna(anna_), liz(liz_) {}
    virtual void notify(std::string msg, std::string to) override
    {
        if(to == "Liz")
            liz->set_last_msg(msg + "444");
        else if(to == "Anna")
            anna->set_last_msg(msg + msg);
        else if(to == "Mary")
            mary->set_last_msg("Mary");
    }
};

int main()
{
    Mary * mary = new Mary();
    Anna * anna = new Anna();
    Elizabeth * liz = new Elizabeth();
    mediator * mediator = new woman_mediator(mary, anna, liz);
    mary->set_sender(mediator);
    anna->set_sender(mediator);
    liz->set_sender(mediator);
    mary->send_msg("Allo", "Liz");
    anna->send_msg("Hi", "Liz");
    liz->send_msg("Hi-hi", "Mary");
    mary->show_last_msg();
    anna->show_last_msg();
    liz->show_last_msg();
    delete mary, anna, liz, mediator;
}
