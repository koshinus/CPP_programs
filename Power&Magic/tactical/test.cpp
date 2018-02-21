#include <iostream>
#include <memory>
#include "unit.hpp"
#include "cell.hpp"

int main()
{
    /*
    std::cout << std::endl;
    for(int i = 0; i < 11; i++)
    {
        std::cout << " ___  ___  ___  ___  ___  ___  ___  ___  ___  ___  ___  ___  ___  ___  ___" << std::endl;
        std::cout << "/   \\/   \\/   \\/   \\/   \\/   \\/   \\/   \\/   \\/   \\/   \\/   \\/   \\/   \\/   \\" << std::endl;
        std::cout << "\\___/\\___/\\___/\\___/\\___/\\___/\\___/\\___/\\___/\\___/\\___/\\___/\\___/\\___/\\___/" << std::endl;
    }
| Elfs numbering in 999999 |
    */
    Unit *elf;
    try
    {
        elf = new Unit("Elf", 15, 3, 2, 9, 5, 999999, 7, 0);
        elf->show_characteristics();
    }
    catch(std::exception &e)
    {
        std::cout << e.what();
    }
    
    std::array<std::unique_ptr<Neighbour>, 6> neighbours = 
                                            {std::unique_ptr<Neighbour>(nullptr),
                                             std::unique_ptr<Neighbour>(nullptr),
                                             std::unique_ptr<Neighbour>(nullptr),
                                             std::unique_ptr<Neighbour>(nullptr),
                                             std::unique_ptr<Neighbour>(nullptr),
                                             std::unique_ptr<Neighbour>(nullptr)};
    Cell cell(neighbours, 0, 0, elf, Relief::HILLS, Vegetation::GREEN);
    cell.reset_neighbour(Neighbour{.cell_number = 3, .entrance_fee = 2}, 1);
    cell.show_neighbours();
    cell.reset_neighbour(Neighbour{.cell_number = 5, .entrance_fee = 3}, 2);
    cell.reset_neighbour(Neighbour{.cell_number = 3, .entrance_fee = 4}, 3);
    cell.show_neighbours();
    delete elf;
    return 0;
}
