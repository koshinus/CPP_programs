#include <iostream>
#include <vector>
#include "tactical_grid.hpp"

int main()
{
    std::vector<std::vector<Unit>> sides =
    {
        {Unit("Unit1", 15, 7, 2, 5, 5, 10, 7, 0)},
        {Unit("Unit1", 15, 7, 2, 5, 5, 10, 7, 0)}
    };
    std::array<GLOBAL_RELIEF, 6> ambient_relief = {GLOBAL_RELIEF::PLAIN_GREEN, GLOBAL_RELIEF::PLAIN_GREEN, GLOBAL_RELIEF::PLAIN_GREEN,
                                                   GLOBAL_RELIEF::PLAIN_GREEN, GLOBAL_RELIEF::PLAIN_GREEN, GLOBAL_RELIEF::PLAIN_GREEN};
    tactical_grid grid(sides, ambient_relief);
    grid.draw_battleground();
    return 0;
}
