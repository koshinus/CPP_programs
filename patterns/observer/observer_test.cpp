#include <iostream>
#include <vector>

/*
Наблюдатель(observer) - шаблон предназначен для адресной рассылки некоего сообщения
    для строго определённого круга лиц.
*/

struct subscriber
{
    virtual void update() = 0;
};

struct adequate_subscriber: public subscriber
{
    virtual void update() override { std::cout << "Mmm... New WH'40000 book..." << std::endl; }
};

struct waha_fan: public subscriber
{
    virtual void update() override { std::cout << "Waaaaaaggghhhhh!!!!!!" << std::endl; }
};

struct publisher
{
    void add_subscriber(subscriber * sub) { subscribers.push_back(sub); }
    // Прости, неизвестный подписчик, мне лень писать адекватную логику,
    // поэтому огребёшь в любом случае ты - тот, кто оказался последним в списке.
    void rm_subscriber() { subscribers.pop_back(); }
    void notify_all() { for(auto sub : subscribers) sub->update(); }
private:
    std::vector<subscriber *> subscribers;
};

int main()
{
    publisher publisher;
    subscriber * sub1 = new adequate_subscriber(), * sub2 = new waha_fan();
    publisher.add_subscriber(sub1); publisher.add_subscriber(sub2);
    publisher.notify_all();
    delete sub1, sub2;
    return 0;
}
