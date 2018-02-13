#include <iostream>
#include <vector>
#include <array>
#include <cstdlib>
#include "cell.hpp"
#include "unit.hpp"

/*
~~~ - Water
^^^ - Hills
    - Plain
*** - Snow
PPP - Forest
... - Sands
''' - Green
    ___   ___   ___   ___   ___   ___   ___   ___   ___   ___   ___   ___   ___   ___   ___
   /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \
   \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/
 ___   ___   ___   ___   ___   ___   ___   ___   ___   ___   ___   ___   ___   ___   ___
/   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \
\___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/
    ___   ___   ___   ___   ___   ___   ___   ___   ___   ___   ___   ___   ___   ___   ___
   /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \
   \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/
 ___   ___   ___   ___   ___   ___   ___   ___   ___   ___   ___   ___   ___   ___   ___
/   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \
\___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/
    ___   ___   ___   ___   ___   ___   ___   ___   ___   ___   ___   ___   ___   ___   ___
   /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \
   \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/
 ___   ___   ___   ___   ___   ___   ___   ___   ___   ___   ___   ___   ___   ___   ___
/   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \
\___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/
    ___   ___   ___   ___   ___   ___   ___   ___   ___   ___   ___   ___   ___   ___   ___
   /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \
   \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/
 ___   ___   ___   ___   ___   ___   ___   ___   ___   ___   ___   ___   ___   ___   ___
/   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \
\___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/
    ___   ___   ___   ___   ___   ___   ___   ___   ___   ___   ___   ___   ___   ___   ___
   /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \
   \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/
 ___   ___   ___   ___   ___   ___   ___   ___   ___   ___   ___   ___   ___   ___   ___
/   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \
\___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/
    ___   ___   ___   ___   ___   ___   ___   ___   ___   ___   ___   ___   ___   ___   ___
   /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \ /   \
   \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/ \___/

*/

class TacticalGrid
{
    std::array<Cell, 14*11> battleground;
    std::vector<std::vector<Unit>> sides;
    
    void pre_generation()
    {
        for (int i = 0; i < 11; i++)
        {
            for (int j = 0; j < 14; j++)
            {
                int x;
                srand(time(0));
                Relief relief = ( (x = (rand() % 10)) == 9)? 
                                Relief::WATER : 
                                ( (x == 8 || x == 7) ? 
                                    Relief::HILLS : 
                                    Relief::PLAIN);
                srand(time(0) + 1);
                Vegetation vegetation = ( (x = (rand() % 12)) < 4)? 
                                        Vegetation::GREEN : 
                                        ( (x == 11 || x == 10) ? 
                                            Vegetation::SANDS : 
                                            ( (x == 9 || x == 8) ?
                                                Vegetation::FOREST :
                                                ( (x == 7 || x == 6) ?
                                                    Vegetation::SNOW :
                                                    Vegetation::SWAMP)));
                std::array<std::unique_ptr<Neighbour>, 6> neighbours = 
                                                        {std::unique_ptr<Neighbour>(nullptr),
                                                         std::unique_ptr<Neighbour>(nullptr),
                                                         std::unique_ptr<Neighbour>(nullptr),
                                                         std::unique_ptr<Neighbour>(nullptr),
                                                         std::unique_ptr<Neighbour>(nullptr),
                                                         std::unique_ptr<Neighbour>(nullptr)};
                battleground[14*i + j] = Cell(neighbours, i, j, nullptr, relief, vegetation);
            }
        }
    }
    
    void fill_angles()
    {
        // Re-set upper left corner
        battleground[0]->reset_neighbour(Neighbour{.cell_number = 1 , .entrance_fee = terrain_features_price[battleground[1 ].relief][battleground[1 ].vegetation]}, 1);
        battleground[0]->reset_neighbour(Neighbour{.cell_number = 15, .entrance_fee = terrain_features_price[battleground[15].relief][battleground[15].vegetation]}, 2);
        battleground[0]->reset_neighbour(Neighbour{.cell_number = 14, .entrance_fee = terrain_features_price[battleground[14].relief][battleground[14].vegetation]}, 3);
        // Re-set lower left corner
        battleground[14*10]->reset_neighbour(Neighbour{.cell_number = 14*9+1 , .entrance_fee = terrain_features_price[battleground[14*9+1 ].relief][battleground[14*9+1 ].vegetation]}, 0);
        battleground[14*10]->reset_neighbour(Neighbour{.cell_number = 14*10+1, .entrance_fee = terrain_features_price[battleground[14*10+1].relief][battleground[14*10+1].vegetation]}, 1);
        battleground[14*10]->reset_neighbour(Neighbour{.cell_number = 14*9   , .entrance_fee = terrain_features_price[battleground[14*9   ].relief][battleground[14*9   ].vegetation]}, 5);
        // Re-set upper right corner
        battleground[13]->reset_neighbour(Neighbour{.cell_number = 14*1+13, .entrance_fee = terrain_features_price[battleground[14*1+13].relief][battleground[14*1+13].vegetation]}, 3);
        battleground[13]->reset_neighbour(Neighbour{.cell_number = 12     , .entrance_fee = terrain_features_price[battleground[12     ].relief][battleground[12     ].vegetation]}, 4);
        // Re-set lower right corner
        battleground[14*10+13]->reset_neighbour(Neighbour{.cell_number = 14*10+12, .entrance_fee = terrain_features_price[battleground[14*10+12].relief][battleground[14*10+12].vegetation]}, 4);
        battleground[14*10+13]->reset_neighbour(Neighbour{.cell_number = 14*9+12 , .entrance_fee = terrain_features_price[battleground[14*9+12 ].relief][battleground[14*9+12 ].vegetation]}, 5);
    }

    void fill_edges()
    {
        /*
            14 - number of elements in row
            11 - number of elements in column
            14*j+13 - last element in j-th row
        */
        // Re-set upper row
        for (size_t j = 1; j < 13; i++)
        {
            battleground[j]->reset_neighbour(Neighbour{.cell_number = j+1     , .entrance_fee = terrain_features_price[battleground[j+1     ].relief][battleground[j+1     ].vegetation]}, 1);
            battleground[j]->reset_neighbour(Neighbour{.cell_number = 14*1+j+1, .entrance_fee = terrain_features_price[battleground[14*1+j+1].relief][battleground[14*1+j+1].vegetation]}, 2);
            battleground[j]->reset_neighbour(Neighbour{.cell_number = 14*1+j  , .entrance_fee = terrain_features_price[battleground[14*1+j  ].relief][battleground[14*1+j  ].vegetation]}, 3);
            battleground[j]->reset_neighbour(Neighbour{.cell_number = j-1     , .entrance_fee = terrain_features_price[battleground[j-1     ].relief][battleground[j-1     ].vegetation]}, 4);
        }
        // Re-set lower row
        for (size_t j = 1; j < 13; i++)
        {
            battleground[14*10+j]->reset_neighbour(Neighbour{.cell_number = 14*9+j+1 , .entrance_fee = terrain_features_price[battleground[14*9+j+1 ].relief][battleground[14*9+j+1 ].vegetation]}, 0);
            battleground[14*10+j]->reset_neighbour(Neighbour{.cell_number = 14*10+j+1, .entrance_fee = terrain_features_price[battleground[14*10+j+1].relief][battleground[14*10+j+1].vegetation]}, 1);
            battleground[14*10+j]->reset_neighbour(Neighbour{.cell_number = 14*9+j   , .entrance_fee = terrain_features_price[battleground[14*9+j   ].relief][battleground[14*9+j   ].vegetation]}, 4);
            battleground[14*10+j]->reset_neighbour(Neighbour{.cell_number = 14*10+j-1, .entrance_fee = terrain_features_price[battleground[14*10+j-1].relief][battleground[14*10+j-1].vegetation]}, 5);
        }
        // Re-set left column
        for (size_t j = 1; j < 10; j++)
        {
            if ( j % 2 == 0 )
            {
                battleground[14*j]->reset_neighbour(Neighbour{.cell_number = 14*(j-1)  , .entrance_fee = terrain_features_price[battleground[14*(j-1)  ].relief][battleground[14*(j-1)  ].vegetation]}, 0);
                battleground[14*j]->reset_neighbour(Neighbour{.cell_number = 14*(j-1)+1, .entrance_fee = terrain_features_price[battleground[14*(j-1)+1].relief][battleground[14*(j-1)+1].vegetation]}, 1);
                battleground[14*j]->reset_neighbour(Neighbour{.cell_number = 14*j+1    , .entrance_fee = terrain_features_price[battleground[14*j+1    ].relief][battleground[14*j+1    ].vegetation]}, 2);
                battleground[14*j]->reset_neighbour(Neighbour{.cell_number = 14*(j+1)+1, .entrance_fee = terrain_features_price[battleground[14*(j+1)+1].relief][battleground[14*(j+1)+1].vegetation]}, 3);
                battleground[14*j]->reset_neighbour(Neighbour{.cell_number = 14*(j+1)  , .entrance_fee = terrain_features_price[battleground[14*(j+1)  ].relief][battleground[14*(j+1)  ].vegetation]}, 5);
            }
            else
            {
                battleground[14*j]->reset_neighbour(Neighbour{.cell_number = 14*(j-1), .entrance_fee = terrain_features_price[battleground[14*(j-1)].relief][battleground[14*(j-1)].vegetation]}, 0);
                battleground[14*j]->reset_neighbour(Neighbour{.cell_number = 14*j+1  , .entrance_fee = terrain_features_price[battleground[14*j+1  ].relief][battleground[14*j+1  ].vegetation]}, 1);
                battleground[14*j]->reset_neighbour(Neighbour{.cell_number = 14*(j+1), .entrance_fee = terrain_features_price[battleground[14*(j+1)].relief][battleground[14*(j+1)].vegetation]}, 2);

            }
        }
        // Re-set right column
        for (size_t j = 1; j < 10; j++)
        {
            if ( j % 2 == 1 )
            {
                battleground[14*j+13]->reset_neighbour(Neighbour{.cell_number = 14*(j-1)+13, .entrance_fee = terrain_features_price[battleground[14*(j-1)+13].relief][battleground[14*(j-1)+13].vegetation]}, 0);
                battleground[14*j+13]->reset_neighbour(Neighbour{.cell_number = 14*(j+1)+13, .entrance_fee = terrain_features_price[battleground[14*(j+1)+13].relief][battleground[14*(j+1)+13].vegetation]}, 2);
                battleground[14*j+13]->reset_neighbour(Neighbour{.cell_number = 14*(j+1)+12, .entrance_fee = terrain_features_price[battleground[14*(j+1)+12].relief][battleground[14*(j+1)+12].vegetation]}, 3);
                battleground[14*j+13]->reset_neighbour(Neighbour{.cell_number = 14*j+12    , .entrance_fee = terrain_features_price[battleground[14*j+12    ].relief][battleground[14*j+12    ].vegetation]}, 4);
                battleground[14*j+13]->reset_neighbour(Neighbour{.cell_number = 14*(j-1)+12, .entrance_fee = terrain_features_price[battleground[14*(j-1)+12].relief][battleground[14*(j-1)+12].vegetation]}, 5);
            }
            else
            {
                battleground[14*j+13]->reset_neighbour(Neighbour{.cell_number = 14*(j+1)+13, .entrance_fee = terrain_features_price[battleground[14*(j+1)+13].relief][battleground[14*(j+1)+13].vegetation]}, 3);
                battleground[14*j+13]->reset_neighbour(Neighbour{.cell_number = 14*j+12    , .entrance_fee = terrain_features_price[battleground[14*j+12    ].relief][battleground[14*j+12    ].vegetation]}, 4);
                battleground[14*j+13]->reset_neighbour(Neighbour{.cell_number = 14*(j-1)+13, .entrance_fee = terrain_features_price[battleground[14*(j-1)+13].relief][battleground[14*(j-1)+13].vegetation]}, 5);

            }
        }
    }

    void fill_middle()
    {
        for (size_t i = 1; i < 10; i++)
        {
            for (size_t j = 1; j < 13; j++)
            {
                battleground[14*i+j]->reset_neighbour(Neighbour{.cell_number = 14*(i-1)+j  , .entrance_fee = terrain_features_price[battleground[14*(i-1)+j  ].relief][battleground[14*(i-1)+j  ].vegetation]}, 0);
                battleground[14*i+j]->reset_neighbour(Neighbour{.cell_number = 14*i+j+1    , .entrance_fee = terrain_features_price[battleground[14*i+j+1    ].relief][battleground[14*i+j+1    ].vegetation]}, 1);
                battleground[14*i+j]->reset_neighbour(Neighbour{.cell_number = 14*(i+1)+j  , .entrance_fee = terrain_features_price[battleground[14*(i+1)+j  ].relief][battleground[14*(i+1)+j  ].vegetation]}, 2);
                battleground[14*i+j]->reset_neighbour(Neighbour{.cell_number = 14*(i+1)+j-1, .entrance_fee = terrain_features_price[battleground[14*(i+1)+j-1].relief][battleground[14*(i+1)+j-1].vegetation]}, 3);
                battleground[14*i+j]->reset_neighbour(Neighbour{.cell_number = 14*i+j-1    , .entrance_fee = terrain_features_price[battleground[14*i+j-1    ].relief][battleground[14*i+j-1    ].vegetation]}, 4);
                battleground[14*i+j]->reset_neighbour(Neighbour{.cell_number = 14*(i-1)+j-1, .entrance_fee = terrain_features_price[battleground[14*(i-1)+j-1].relief][battleground[14*(i-1)+j-1].vegetation]}, 5);
            }
        }
    }

public:
    TacticalGrid(std::vector<std::vector<Unit>> & sides_):
    sides(sides_)
    {
        pre_generation();
        fill_angles();
    }
};

int main()
{
    std::vector<std::vector<Unit>> sides =
    {
        {Unit("Unit1", 15, 3, 2, 9, 5, 10, 7, 0)},
        {Unit("Unit2", 15, 3, 2, 9, 5, 10, 7, 1)}
    };
    return 0;
}

/*

 /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  
|~~||~~||~~||~~||~~||~~||~~||~~||~~||~~||~~||~~||~~||~~||~~|
 \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/ 

 /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  
|~~||~~||~~||~~||~~||~~||~~||~~||~~||~~||~~||~~||~~||~~||~~|
 \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/ 

 /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  
|~~||~~||~~||~~||~~||~~||~~||~~||~~||~~||~~||~~||~~||~~||~~|
 \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/ 

 /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  
|~~||~~||~~||~~||~~||~~||~~||~~||~~||~~||~~||~~||~~||~~||~~|
 \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/ 

 /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  
|~~||~~||~~||~~||~~||~~||~~||~~||~~||~~||~~||~~||~~||~~||~~|
 \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/ 

 /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  
|~~||~~||~~||~~||~~||~~||~~||~~||~~||~~||~~||~~||~~||~~||~~|
 \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/ 

 /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  
|~~||~~||~~||~~||~~||~~||~~||~~||~~||~~||~~||~~||~~||~~||~~|
 \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/ 

 /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  
|~~||~~||~~||~~||~~||~~||~~||~~||~~||~~||~~||~~||~~||~~||~~|
 \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/ 

 /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  
|~~||~~||~~||~~||~~||~~||~~||~~||~~||~~||~~||~~||~~||~~||~~|
 \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/ 

 /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  
|~~||~~||~~||~~||~~||~~||~~||~~||~~||~~||~~||~~||~~||~~||~~|
 \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/ 

 /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  
|~~||~~||~~||~~||~~||~~||~~||~~||~~||~~||~~||~~||~~||~~||~~|
 \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/ 

     ___  ___  ___  ___  ___  ___  ___  ___  ___  ___  ___  ___  ___  ___  ___
    /   \/   \/   \/   \/   \/   \/   \/   \/   \/   \/   \/   \/   \/   \/   \
    \___/\___/\___/\___/\___/\___/\___/\___/\___/\___/\___/\___/\___/\___/\___/
 ___  ___  ___  ___  ___  ___  ___  ___  ___  ___  ___  ___  ___  ___  ___
/   \/   \/   \/   \/   \/   \/   \/   \/   \/   \/   \/   \/   \/   \/   \
\___/\___/\___/\___/\___/\___/\___/\___/\___/\___/\___/\___/\___/\___/\___/
     ___  ___  ___  ___  ___  ___  ___  ___  ___  ___  ___  ___  ___  ___  ___
    /   \/   \/   \/   \/   \/   \/   \/   \/   \/   \/   \/   \/   \/   \/   \
    \___/\___/\___/\___/\___/\___/\___/\___/\___/\___/\___/\___/\___/\___/\___/
 ___  ___  ___  ___  ___  ___  ___  ___  ___  ___  ___  ___  ___  ___  ___
/   \/   \/   \/   \/   \/   \/   \/   \/   \/   \/   \/   \/   \/   \/   \
\___/\___/\___/\___/\___/\___/\___/\___/\___/\___/\___/\___/\___/\___/\___/
     ___  ___  ___  ___  ___  ___  ___  ___  ___  ___  ___  ___  ___  ___  ___
    /   \/   \/   \/   \/   \/   \/   \/   \/   \/   \/   \/   \/   \/   \/   \
    \___/\___/\___/\___/\___/\___/\___/\___/\___/\___/\___/\___/\___/\___/\___/
 ___  ___  ___  ___  ___  ___  ___  ___  ___  ___  ___  ___  ___  ___  ___
/   \/   \/   \/   \/   \/   \/   \/   \/   \/   \/   \/   \/   \/   \/   \
\___/\___/\___/\___/\___/\___/\___/\___/\___/\___/\___/\___/\___/\___/\___/
     ___  ___  ___  ___  ___  ___  ___  ___  ___  ___  ___  ___  ___  ___  ___
    /   \/   \/   \/   \/   \/   \/   \/   \/   \/   \/   \/   \/   \/   \/   \
    \___/\___/\___/\___/\___/\___/\___/\___/\___/\___/\___/\___/\___/\___/\___/
 ___  ___  ___  ___  ___  ___  ___  ___  ___  ___  ___  ___  ___  ___  ___
/   \/   \/   \/   \/   \/   \/   \/   \/   \/   \/   \/   \/   \/   \/   \
\___/\___/\___/\___/\___/\___/\___/\___/\___/\___/\___/\___/\___/\___/\___/
     ___  ___  ___  ___  ___  ___  ___  ___  ___  ___  ___  ___  ___  ___  ___
    /   \/   \/   \/   \/   \/   \/   \/   \/   \/   \/   \/   \/   \/   \/   \
    \___/\___/\___/\___/\___/\___/\___/\___/\___/\___/\___/\___/\___/\___/\___/
 ___  ___  ___  ___  ___  ___  ___  ___  ___  ___  ___  ___  ___  ___  ___
/   \/   \/   \/   \/   \/   \/   \/   \/   \/   \/   \/   \/   \/   \/   \
\___/\___/\___/\___/\___/\___/\___/\___/\___/\___/\___/\___/\___/\___/\___/
     ___  ___  ___  ___  ___  ___  ___  ___  ___  ___  ___  ___  ___  ___  ___
    /   \/   \/   \/   \/   \/   \/   \/   \/   \/   \/   \/   \/   \/   \/   \
    \___/\___/\___/\___/\___/\___/\___/\___/\___/\___/\___/\___/\___/\___/\___/

vector<Cell> battleground = 
{
    Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(),
    Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(),
    Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(),
    Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(),
    Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(),
    Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(),
    Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(),
    Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(),
    Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(),
    Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(),
    Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell(), Cell()
};

void print_grid()
{
    for(int i = 0; i < 11; i++)
    {    
        std::cout << " ___  ___  ___  ___  ___  ___  ___  ___  ___  ___  ___  ___  ___  ___  ___" << std::endl;
        std::cout << "/   \\/   \\/   \\/   \\/   \\/   \\/   \\/   \\/   \\/   \\/   \\/   \\/   \\/   \\/   \\" << std::endl;
        std::cout << "\\___/\\___/\\___/\\___/\\___/\\___/\\___/\\___/\\___/\\___/\\___/\\___/\\___/\\___/\\___/" << std::endl;
    }
}

*/
