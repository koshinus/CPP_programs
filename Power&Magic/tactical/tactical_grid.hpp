#include <iostream>
#include <vector>
#include <array>
#include <chrono>
#include <thread>
#include "tile.hpp"
#include "unit.hpp"

/*
~~~ - Water
^^^ - Hills
    - Plain
*** - Snow
PPP - Forest
... - Sands
    - Green
''' - Swamp
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

class tactical_grid
{
    std::array<grid_tile, 14*11> battleground;
    std::vector<std::vector<Unit>> sides;
    
    void pre_generation(std::array<GLOBAL_RELIEF, 6> & ambient_relief)
    {
        for (int i = 0; i < 11; i++)
        {
            for (int j = 0; j < 14; j++)
            {
                //srand(time(0));
                //int x = rand() % 100;
                //terrain_features feature = static_cast<terrain_features>(x % 10);
                terrain_features feature = generate_feature(ambient_relief);
                std::array<int, 6> neighbours = {-1, -1, -1, -1, -1, -1};
                battleground[14*i + j] = grid_tile(neighbours, i, j, nullptr, feature);
                std::this_thread::sleep_for(std::chrono::milliseconds(5));
            }
        }
    }

    void reset_neighbours(size_t tile, std::vector<size_t> tiles_neighbours, std::vector<size_t> neighbours_places)
    {
        //if (cells_neighbours.size() != neighbours_places.size())
        for (size_t i = 0; i < tiles_neighbours.size(); i++)
            battleground[tile].neighbours[neighbours_places[i]] = tiles_neighbours[i];
    }    

    void fill_angles()
    {
        // Re-set upper left, lower left, upper right and lower right corners
        reset_neighbours(0       , std::vector<size_t>{1       , 15     ,   14}, std::vector<size_t>{1, 2, 3});
        reset_neighbours(14*10   , std::vector<size_t>{14*9+1  , 14*10+1, 14*9}, std::vector<size_t>{0, 1, 5});
        reset_neighbours(13      , std::vector<size_t>{14*1+13 , 12           }, std::vector<size_t>{3, 4   });
        reset_neighbours(14*10+13, std::vector<size_t>{14*10+12, 14*9+12      }, std::vector<size_t>{4, 5   });
    }

    void fill_edges()
    {
        /*
            14 - number of elements in row
            11 - number of elements in column
            14*j+13 - last element in j-th row
        */
        // Re-set upper and lower rows
        for (size_t j = 1; j < 13; j++)
        {
            reset_neighbours(j      , std::vector<size_t>{j+1     , 14*1+j+1 , 14*1+j, j-1      }, std::vector<size_t>{1, 2, 3, 4});
            reset_neighbours(14*10+j, std::vector<size_t>{14*9+j+1, 14*10+j+1, 14*9+j, 14*10+j-1}, std::vector<size_t>{0, 1, 4, 5});
        }
        // Re-set left and right column
        for (size_t j = 1; j < 10; j++)
        {
            if ( j % 2 == 0 )
            {
                reset_neighbours(14*j   , std::vector<size_t>{14*(j-1), 14*(j-1)+1, 14*j+1, 14*(j+1)+1, 14*(j+1)}, std::vector<size_t>{0, 1, 2, 3, 5});
                reset_neighbours(14*j+13, std::vector<size_t>{14*(j+1)+13, 14*j+12, 14*(j-1)+13}                 , std::vector<size_t>{3, 4, 5});
            }
            else
            {
                reset_neighbours(14*j   , std::vector<size_t>{14*(j-1), 14*j+1, 14*(j+1)}                                 , std::vector<size_t>{0, 1, 2});
                reset_neighbours(14*j+13, std::vector<size_t>{14*(j-1)+13, 14*(j+1)+13, 14*(j+1)+12, 14*j+12, 14*(j-1)+12}, std::vector<size_t>{0, 2, 3, 4, 5});
            }
        }
    }

    void fill_middle()
    {
        for (size_t i = 1; i < 10; i++)
            for (size_t j = 1; j < 13; j++)
                reset_neighbours(14*i+j, std::vector<size_t>{14*(i-1)+j, 14*i+j+1, 14*(i+1)+j, 14*(i+1)+j-1, 14*i+j-1, 14*(i-1)+j-1}, std::vector<size_t>{0, 1, 2, 3, 4, 5});
    }

public:
    tactical_grid(std::vector<std::vector<Unit>> & sides_, std::array<GLOBAL_RELIEF, 6> & ambient_relief):
    sides(sides_)
    {
        pre_generation(ambient_relief);
        fill_angles();
        fill_edges();
        fill_middle();
    }
    
    void draw_battleground()
    {
        ///*
        for (size_t i = 0; i < 11; i++)
        {
            if ( i % 2 == 0 )
                std::cout << "   ";
            for (size_t j = 0; j < 14; j++)
                std::cout << " ___  ";
            std::cout << std::endl;
            if ( i % 2 == 0 )
                std::cout << "   ";
            for (size_t j = 0; j < 14; j++)
                draw_feature[static_cast<int>(battleground[14*i+j].feature)](false);
            std::cout << std::endl;
            if ( i % 2 == 0 )
                std::cout << "   ";
            for (size_t j = 0; j < 14; j++)
                draw_feature[static_cast<int>(battleground[14*i+j].feature)](true);
            std::cout << std::endl;
        }
        std::cout << std::endl;
        //*/
        /*
        int i = 0;
        for (auto & tile : battleground)
        {
            std::cout << "_____________________" << std::endl << i << std::endl;
            tile.show_neighbours();
            i++;
        }
        //*/
    }
};