#include <iostream>
#include <string>
#include <cstdint>
#include <exception>

class Cell;
class Obstacle {};

class Unit: public Obstacle
{
    friend class Cell;
    std::string name;
    int max_health;
    int health;
    int damage;
    int damage_dispersion;
    int attack;
    int defence;
    int amount;
    int speed;
    int side;

public:
    Unit(std::string name_, int max_health_, int damage_, int dispersion, int attack_, int defence_, int amount_, int speed_, int side_)
    {
        if ( max_health_ <= 0 || damage_ <= 0 || dispersion < 0 || attack_ <= 0 || defence_ < 0 || amount_ <= 0 || speed_ <= 0 || side_ < 0 )
        {
            //std::cout << "ERROR: wrong parameters for unit." << std::endl;
            throw std::runtime_error("ERROR: wrong parameters for unit.\n");
        }
        name                = name_;
        max_health          = max_health_;
        health              = max_health_;
        damage              = damage_;
        damage_dispersion   = dispersion;
        attack              = attack_;
        defence             = defence_;
        amount              = amount_;
        speed               = speed_;
        side                = side_;
    }

    void show_characteristics()
    {
        std::cout << "____________________________" << std::endl;
        std::cout << "| " << name << "s of " << amount << " |" << std::endl;
        std::cout << "____________________________" << std::endl;
        std::cout << "|Max Health: " << max_health << " |" << std::endl;
        std::cout << "|Cur Health: " << health << " |" << std::endl;
        std::cout << "|Damage: " << damage << '-' << damage + damage_dispersion << "|" << std::endl;
        std::cout << "|Attack: " << attack << " |" << std::endl;
        std::cout << "|Defence: " << defence << " |" << std::endl;
        std::cout << "|Speed: " << speed << " |" << std::endl;
        std::cout << "________________" << std::endl;
    }
};
