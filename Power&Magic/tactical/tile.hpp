#include <iostream>
#include <memory>
#include <array>
#include "terrain_features.hpp"

class grid_obstacle {};
class tactical_grid;

class grid_tile
{
public:
    friend class tactical_grid;
    // Neighbour tiles with prices to move there
    std::array<grid_tile *, 6> neighbours;
    int X;
    int Y;
    int Z;
    grid_obstacle *obstacle;
    int entrance_fee;
    TERRAIN_FEATURES feature;
    bool passable;
//public:
    grid_tile
    (
        std::array<int, 6> & neighbours_,
        int X_,
        int Y_,
        int Z_,
        grid_obstacle *obstacle_,
        TERRAIN_FEATURES feature_
    ):
        neighbours(neighbours_),
        X(X_),
        Y(Y_),
        Z(Z_),
        obstacle(obstacle_),
        feature(feature_)
    {
        if (X + Y + Z != 0)
            throw "Sum of coordinates must be zero!";
        entrance_fee = terrain_features_prices[static_cast<int>(feature)];
        passable = (!obstacle && feature != TERRAIN_FEATURES::WATER)? true : false;
    }

    grid_tile() {}
    
    /*
    void reset_neighbour(int neighbour, int place)
    {
        neighbours[place] = neighbour;
    }
    */

    void show_neighbours()
    {
        for(int n : neighbours)
            if(n != -1)
                std::cout << "Tiles number: " << n << std::endl;
    }
};

