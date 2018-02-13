#include <iostream>
#include <memory>
#include <utility>
#include <array>

enum Relief { HILLS, PLAIN, WATER };
enum Vegetation { FOREST, SANDS, SNOW, GREEN, SWAMP };
class Obstacle;
class TacticalGrid;

int terrain_features_price[3][5] = 
        /*Vegetation*/
/*R*/{
/*e*/   {3, 3, 4, 2, 100},
/*l*/   {2, 2, 3, 1, 3},
/*i*/   {100, 100, 100, 100, 100}
/*e*/};
/*f*/

struct Neighbour
{
    int cell_number;
    int entrance_fee;
};


class Cell
{
    friend class TacticalGrid;
    // Neighbour cells with prices to move there
    std::array<std::unique_ptr<Neighbour>, 6> neighbours;
    double coordinate_X;
    double coordinate_Y;
    Obstacle *obstacle;
    Relief relief;
    Vegetation vegetation;
    bool passable;
public:
    Cell
    (
        std::array<std::unique_ptr<Neighbour>, 6> &neighbours_,
        double X,
        double Y,
        Obstacle *obstacle_,
        Relief relief_,
        Vegetation vegetation_
    ):
        coordinate_X(X),
        coordinate_Y(Y),
        obstacle(obstacle_),
        relief(relief_),
        vegetation(vegetation_)
    {
        for (size_t i = 0; i < neighbours.size(); i++)
            neighbours[i] = std::move(neighbours_[i]);
        passable = (!obstacle && relief != Relief::WATER)? true : false;
    }

    Cell() {}
    
    void reset_neighbour(Neighbour neighbour, int place)
    {
        neighbours[place].reset(new Neighbour(neighbour));
    }
    
    void show_neighbours()
    {
        for(auto & n : neighbours)
            if(n)
                std::cout << "Cells number: " << n->cell_number << ", entrance fee: " << n->entrance_fee << std::endl;
    }
    /*
    ~Cell()
    {
        for(auto & n : neighbours)
            delete n;
    }
    */
};

