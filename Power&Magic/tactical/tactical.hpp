#include <iostream>
#include <vector>

std::vector<std::vector<Cell>> cells;
int side = 0;

class Cell;

class Unit
{
    friend class Cell;
    int max_health;
    int health;
    int attack;
    int defence;
    int amount;
    int side;    

public:
    Unit(int max_health_, int health_, int attack_, int defence_, int amount_, int side_): 
        max_health(max_health_),
        health(health_),
        lives(lives_), 
        attack(attack_), 
        defence(defence_),
        amount(amount_), 
        side(side_)
    {}
};

class Cell
{
public:
    Unit unit;
    bool is_free = true;
    
    Cell(Unit unit_): unit(unit_)
    {
        if (unit.amount != 0)
        is_free = false;
    }
};

void fill_cells()
{
    for(int i = 0; i < 10; i++)
    {
        std::vector<Cell> cells_row;
        for(int j = 0; j < 10; j++)
        {
            switch(j)
            {
                case 0:
                {
                    cells_row.push_back(Unit(10,2,1,8,0));
                    break;
                }
                case 9:
                {
                    cells_row.push_back(Unit(10,2,1,8,1));
                    break;
                }
                default:
                {
                    cells_row.push_back(Unit(0,0,0,0,10));
                    break;
                }
            }
        }
        cells.push_back(cells_row);
    }
}

bool is_within(int value)
{
    return value >= 0 && value <= 9;
}

/*
bool verify_step(int row_old, int col_old, int row_new, int col_new)
{
    if (!(is_within(row_old) && is_within(col_old) && is_within(row_new) && is_within(col_new)) || (row_old == row_new && col_old == col_new))
    if (!(is_within(row_old) && is_within(col_old) && is_within(row_new) && is_within(col_new)) || (cells[row_new][col_new].unit.side != side))
        return false;
    return cells[row_new][col_new].is_free || (!cells[row_new][col_new].is_free && cells[row_new][col_new].unit.side != cells[row_old][col_old].unit.side)
}
*/

bool verify_step(int row_old, int col_old, int row_new, int col_new)
{
    return  is_within(row_old) && 
            is_within(col_old) && 
            is_within(row_new) && 
            is_within(col_new) && 
            cells[row_new][col_new].unit.side == side && 
            cells[row_new][col_new].is_free;
}

double my_max(double fst, double snd) { return (fst >= snd)? fst : snd; }

void calculate_damage(Unit &unit1, Unit &unit2)
{
    double damage = my_max(amount*((unit1.attack >= unit2.defence)? 
                            1+(unit1.attack - unit2.defence)*0.05 :
                            1-(unit2.defence - unit1.attack)*0.05), 1);
    unit2.amount -= int(damage)/unit2.max_health;
    if (unit2.amount <= 0)
    {
        unit2.max_health = 0;
        unit2.health     = 0;
        unit2.attack     = 0;
        unit2.defence    = 0;
        unit2.amount     = 0;
        unit2.side       = 10;
        return;
    }
    unit2.health  = int(damage)%unit2.max_health;
    damage = my_max(amount*((unit2.attack >= unit1.defence)?
                     1+(unit2.attack - unit1.defence)*0.05 :
                     1-(unit1.defence - unit2.attack)*0.05), 1);
    unit1.amount -= int(damage)/unit1.max_health;
    if (unit1.amount <= 0)
    {
        unit1.max_health = 0;
        unit1.health     = 0;
        unit1.attack     = 0;
        unit1.defence    = 0;
        unit1.amount     = 0;
        unit1.side       = 10;
        return;
    }
    unit1.health  = int(damage)%unit1.max_health;
}

void make_step(int row_old, int col_old, int row_new, int col_new)
{
    
}

int main()
{
    fill_cells();
    
    return 0;
}
