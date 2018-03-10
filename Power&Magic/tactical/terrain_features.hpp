#include <iostream>
#include <functional>
#include <map>
#include <cstdlib>
//#include "../global/terrain_features.hpp"

enum TERRAIN_FEATURES           {FOREST_HILLS, SAND_HILLS, SNOW_HILLS, GREEN_HILLS, FOREST_PLAIN, SAND_PLAIN, SNOW_PLAIN, GREEN_PLAIN, SWAMP_PLAIN, WATER};
int terrain_features_prices[] = {           3,          3,          4,           2,            2,          2,          3,           1,           3,   100};
std::function<void (bool)> draw_feature[] =
{
    [](bool last)// Forest & Hills
    {
        if(!last)
            std::cout << "/^P^\\ ";
        else
            std::cout << "\\P^P/ ";
    },
    [](bool last)// Sand & Hills
    {
        if(!last)
            std::cout << "/^.^\\ ";
        else
            std::cout << "\\.^./ ";
    },
    [](bool last)// Snow & Hills
    {
        if(!last)
            std::cout << "/^*^\\ ";
        else
            std::cout << "\\*^*/ ";
    },
    [](bool last)// Green & Hills
    {
        if(!last)
            std::cout << "/^'^\\ ";
        else
            std::cout << "\\'^'/ ";
    },
    [](bool last)// Forest & Plain
    {
        if(!last)
            std::cout << "/ P \\ ";
        else
            std::cout << "\\P P/ ";
    },
    [](bool last)// Sand & Plain
    {
        if(!last)
            std::cout << "/ . \\ ";
        else
            std::cout << "\\. ./ ";
    },
    [](bool last)// Snow & Plain
    {
        if(!last)
            std::cout << "/ * \\ ";
        else
            std::cout << "\\* */ ";
    },
    [](bool last)// Green & Plain
    {
        if(!last)
            std::cout << "/   \\ ";
        else
            std::cout << "\\___/ ";
    },
    [](bool last)// Swamp & Plain
    {
        if(!last)
            std::cout << "/ ' \\ ";
        else
            std::cout << "\\' '/ ";
    },
    [](bool last)// Water
    {
        if(!last)
            std::cout << "/~~~\\ ";
        else
            std::cout << "\\~~~/ ";
    }
};

/*
terrain_features generate_feature(std::array<TERRAIN_FEATURES, 6> & ambient_relief)
{
    std::map<GLOBAL_RELIEF, int> frequencies;
    for (size_t i = 0; i < 6; i++)
    {
        if(frequencies.find(ambient_relief[i]) != frequencies.end())
            frequencies[ambient_relief[i]]++;
        else
            frequencies.insert(std::pair<GLOBAL_RELIEF, int>(ambient_relief[i], 1));
    }
    srand(time(0));
    int x = rand() % (ambient_relief.size() + 1);
    if (x == 6)
        return terrain_features::WATER;
//    if (frequencies.size() == 1)
//        return ambient_relief[0];
    int left_barier = 0;
    for (auto & relief_freq : frequencies)
    {
        if (left_barier <= x && x <= left_barier + relief_freq.second)
            return relief_freq.first;
        left_barier += relief_freq.second;
    }
}
*/
