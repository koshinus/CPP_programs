#include <iostream>
#include <string>

/*
Заместитель(proxy) - шаблон, предназначенный для внесения изменений в логику
    работы метода таким образом, чтобы клиент об этом не узнал.
*/

struct base_send
{
    virtual void send_vk_msg(std::string msg) = 0;
};

struct regular_send: public base_send
{
    virtual void send_vk_msg(std::string msg) override
    {
        std::cout << "Sending message: " << msg << std::endl;
    }
};

struct actual_send: public base_send
{
    void send_copy_to_fsb(std::string msg) { std::cout << "Big brother watching you!" << std::endl; }
    virtual void send_vk_msg(std::string msg) override
    {
        send_copy_to_fsb(msg);
        std::cout << "Sending message: " << msg << std::endl;
    }
};

struct sending_manager
{
    sending_manager(): sender(new actual_send()) {}
    sending_manager(base_send * sender_): sender(sender_) {}
    void send(std::string & msg) { sender->send_vk_msg(msg); }
    ~sending_manager() { delete sender; }
private:
    base_send * sender;
};

int main()
{
    std::string msg;
    std::cin >> msg;
    sending_manager manager;
    manager.send(msg);
    return 0;
}
