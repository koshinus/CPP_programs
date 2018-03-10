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
    std::array<int, 6> neighbours;
    double coordinate_X;
    double coordinate_Y;
    grid_obstacle *obstacle;
    int entrance_fee;
    TERRAIN_FEATURES feature;
    bool passable;
//public:
    grid_tile
    (
        std::array<int, 6> & neighbours_,
        double X,
        double Y,
        grid_obstacle *obstacle_,
        TERRAIN_FEATURES feature_
    ):
        neighbours(neighbours_),
        coordinate_X(X),
        coordinate_Y(Y),
        obstacle(obstacle_),
        feature(feature_)
    {
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

