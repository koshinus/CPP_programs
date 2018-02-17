#include <iostream>
#include <memory>
#include <functional>
#include <array>

enum terrain_features           {FOREST_HILLS, SAND_HILLS, SNOW_HILLS, GREEN_HILLS, FOREST_PLAIN, SAND_PLAIN, SNOW_PLAIN, GREEN_PLAIN, SWAMP_PLAIN, WATER};
int terrain_features_prices[] = {           3,          3,          4,           2,            2,          2,          3,           1,           3,   100};
std::function<void (bool)> draw_feature[] =
{
    [](bool last)
    {
        if(!last)
            std::cout << "/^P^\\ ";
        else
            std::cout << "\\P^P/ ";
    },
    [](bool last)
    {
        if(!last)
            std::cout << "/^.^\\ ";
        else
            std::cout << "\\.^./ ";
    },
    [](bool last)
    {
        if(!last)
            std::cout << "/^*^\\ ";
        else
            std::cout << "\\*^*/ ";
    },
    [](bool last)
    {
        if(!last)
            std::cout << "/^'^\\ ";
        else
            std::cout << "\\'^'/ ";
    },
    [](bool last)
    {
        if(!last)
            std::cout << "/ P \\ ";
        else
            std::cout << "\\P P/ ";
    },
    [](bool last)
    {
        if(!last)
            std::cout << "/ . \\ ";
        else
            std::cout << "\\. ./ ";
    },
    [](bool last)
    {
        if(!last)
            std::cout << "/ * \\ ";
        else
            std::cout << "\\* */ ";
    },
    [](bool last)
    {
        if(!last)
            std::cout << "/   \\ ";
        else
            std::cout << "\\___/ ";
    },
    [](bool last)
    {
        if(!last)
            std::cout << "/ ' \\ ";
        else
            std::cout << "\\'_'/ ";
    },
    [](bool last)
    {
        if(!last)
            std::cout << "/~~~\\ ";
        else
            std::cout << "\\~~~/ ";
    }
}; 
class grid_obstacle;
class tactical_grid;

struct tile_neighbour
{
    int tile_number;
    int entrance_fee;
};


class grid_tile
{
    friend class tactical_grid;
    // Neighbour cells with prices to move there
    std::array<std::unique_ptr<tile_neighbour>, 6> neighbours;
    double coordinate_X;
    double coordinate_Y;
    grid_obstacle *obstacle;
    terrain_features feature;
    bool passable;
public:
    grid_tile
    (
        std::array<std::unique_ptr<tile_neighbour>, 6> &neighbours_,
        double X,
        double Y,
        grid_obstacle *obstacle_,
        terrain_features feature_
    ):
        coordinate_X(X),
        coordinate_Y(Y),
        obstacle(obstacle_),
        feature(feature_)
    {
        for (size_t i = 0; i < neighbours.size(); i++)
            neighbours[i] = std::move(neighbours_[i]);
        passable = (!obstacle && feature != terrain_features::WATER)? true : false;
    }

    grid_tile() {}
    
    void reset_neighbour(tile_neighbour neighbour, int place)
    {
        neighbours[place].reset(new tile_neighbour(neighbour));
    }
    
    void show_neighbours()
    {
        for(auto & n : neighbours)
            if(n)
                std::cout << "Cells number: " << n->tile_number << ", entrance fee: " << n->entrance_fee << std::endl;
    }
    
    /*
	int number = 9999;
	std::string name = (40 - (std::to_string(number) + "| of |").size(), "Elfs");
	std::string all_together = std::string() + "| " + name + " of " + std::to_string(number) + " |";
	std::string header = std::string() + "| " + std::string((40 - all_together.size())/2, ' ') + 
                                    name + " of " + std::to_string(number) + 
                                    std::string((40 - all_together.size())/2, ' ') + " |";
	std::cout << header << std::endl;
    */
};

