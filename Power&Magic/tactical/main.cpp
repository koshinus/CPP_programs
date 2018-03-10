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
    std::array<TERRAIN_FEATURES, 6> ambient_relief = {TERRAIN_FEATURES::SNOW_HILLS, TERRAIN_FEATURES::SNOW_HILLS, TERRAIN_FEATURES::GREEN_HILLS,
                                                   TERRAIN_FEATURES::GREEN_PLAIN, TERRAIN_FEATURES::GREEN_PLAIN, TERRAIN_FEATURES::GREEN_PLAIN};
    tactical_grid grid(sides, ambient_relief);
    grid.draw_battleground();
    return 0;
}
