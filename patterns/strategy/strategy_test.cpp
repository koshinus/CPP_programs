#include <iostream>

/*
Стратегия - шаблон, предназначенный для изменения поведения алгоритма, в зависимости
    от контекста.
*/

struct strategy
{
    virtual void spend_free_time() = 0;
};

struct walking_strategy: public strategy
{
    virtual void spend_free_time() { std::cout << "Go for a walk." << std::endl; }
};

struct playing_strategy: public strategy
{
    virtual void spend_free_time() { std::cout << "Stay at home and play." << std::endl; }
};

struct day_schedule
{
    // В качестве альтернативы, стратегию можно задавать при вызове
    //      основной функции, подавая её в качестве аргумента, а не
    //      задавая отдельно
    void set_strategy(strategy * strat_) { strat = strat_; }
    void schedule()
    {
        std::cout << "Waking up. Go to work. Working. Spend free time as: ";
        strat->spend_free_time();
    }
private:
    strategy * strat;
};

int main()
{
    strategy * walk = new walking_strategy();
    strategy * play = new playing_strategy();
    day_schedule schedule;
    schedule.set_strategy(walk);
    schedule.schedule();
    schedule.set_strategy(play);
    schedule.schedule();
    delete walk, play;
    return 0;
}
