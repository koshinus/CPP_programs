#include <iostream>

/*
Посетитель (visitor) - шаблон, предназначенный для добавления нового однотипного
    функционала в существующую систему классов без её полноценного рефакторинга.
*/

struct visitor;

struct game_system
{
    virtual void calc(visitor * vis) = 0;
};

struct physics_system: public game_system
{
    void calculate_bodies() { std::cout << "[PHYSICS]Bodies calc." << std::endl; }
    void calculate_particles() { std::cout << "[PHYSICS]Particles calc." << std::endl; }
    virtual void calc(visitor * vis) override;
};

struct ai: public game_system
{
    void calculate_enemies() { std::cout << "[AI]Enemies calc." << std::endl; }
    void calculate_alies() { std::cout << "[AI]Alies calc." << std::endl; }
    virtual void calc(visitor * vis) override;
};

struct base_logic: public game_system
{
    void calculate_logic() { std::cout << "[LOGIC]Logic calc." << std::endl; }
    virtual void calc(visitor * vis) override;
};

struct visitor
{
    void calculate_physics(physics_system * system)
    {
        system->calculate_bodies();
        system->calculate_particles();
    }
    void calculate_ai(ai * ai_)
    {
        ai_->calculate_enemies();
        ai_->calculate_alies();
    }
    void calculate_logic(base_logic * logic)
    {
        logic->calculate_logic();
    }
};

// Определим эти функции здесь, потому что на момент объявления visitor ещё
// не представляет собой законченный класс.
void physics_system::calc(visitor * vis)
{
    vis->calculate_physics(this);
}

void ai::calc(visitor * vis)
{
    vis->calculate_ai(this);
}

void base_logic::calc(visitor * vis)
{
    vis->calculate_logic(this);
}

int main()
{
    game_system * systems[] = {new physics_system(), new ai(), new base_logic()};
    visitor * vis = new visitor();
    for(game_system * sys : systems)
        sys->calc(vis);
    for(game_system * sys : systems)
        delete sys;
    delete vis;
    return 0;
}
