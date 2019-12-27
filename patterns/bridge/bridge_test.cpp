#include <iostream>

/*
Мост - шаблон, предназначенный для уменьшения количества подклассов,
    путём разделения структуры на абстракцию и реализацию.
*/

struct sport
{
    virtual void training() = 0;
};

struct football: public sport
{
    virtual void training() override { std::cout << "Playing football for 1.5 hour." << std::endl; }
};

struct swiming: public sport
{
    virtual void training() override { std::cout << "Swim for 1.5 hour." << std::endl; }
};

struct sport_activity
{
    sport_activity(sport * sport__): sport_(sport__){}
    void activity() { sport_->training(); }
private:
    sport * sport_;
};

int main()
{
    sport * sport1 = new football(), * sport2 = new swiming();
    sport_activity act1(sport1), act2(sport2);
    act1.activity();
    act2.activity();
    delete sport1, sport2;
    return 0;
}
