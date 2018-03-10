#include <iostream>
#include <random>
#include <map>
#include <utility>
#include <algorithm>
#include <queue>
#include "unit.hpp"
#include "tile.hpp"

std::array<int, 6> arr = {-1, -1, -1, -1, -1, -1};
grid_obstacle stone;
std::array<grid_tile, 11*14> battleground =
{
grid_tile(arr, 0, 0, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 0, 1, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 0, 2, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 0, 3, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 0, 4, &stone, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 0, 5, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 0, 6, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 0, 7, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 0, 8, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 0, 9, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 0, 10, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 0, 11, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 0, 12, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 0, 13, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),
grid_tile(arr, 1, 0, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 1, 1, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 1, 2, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 1, 3, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 1, 4, &stone, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 1, 5, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 1, 6, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 1, 7, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 1, 8, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 1, 9, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 1, 10, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 1, 11, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 1, 12, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 1, 13, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),
grid_tile(arr, 2, 0, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 2, 1, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 2, 2, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 2, 3, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 2, 4, &stone, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 2, 5, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 2, 6, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 2, 7, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 2, 8, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 2, 9, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 2, 10, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 2, 11, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 2, 12, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 2, 13, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),
grid_tile(arr, 3, 0, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 3, 1, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 3, 2, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 3, 3, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 3, 4, &stone, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 3, 5, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 3, 6, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 3, 7, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 3, 8, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 3, 9, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 3, 10, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 3, 11, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 3, 12, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 3, 13, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),
grid_tile(arr, 4, 0, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 4, 1, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 4, 2, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 4, 3, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 4, 4, &stone, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 4, 5, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 4, 6, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 4, 7, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 4, 8, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 4, 9, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 4, 10, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 4, 11, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 4, 12, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 4, 13, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),
grid_tile(arr, 5, 0, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 5, 1, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 5, 2, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 5, 3, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 5, 4, &stone, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 5, 5, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 5, 6, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 5, 7, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 5, 8, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 5, 9, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 5, 10, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 5, 11, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 5, 12, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 5, 13, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),
grid_tile(arr, 6, 0, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 6, 1, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 6, 2, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 6, 3, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 6, 4, &stone, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 6, 5, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 6, 6, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 6, 7, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 6, 8, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 6, 9, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 6, 10, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 6, 11, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 6, 12, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 6, 13, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),
grid_tile(arr, 7, 0, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 7, 1, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 7, 2, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 7, 3, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 7, 4, &stone, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 7, 5, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 7, 6, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 7, 7, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 7, 8, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 7, 9, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 7, 10, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 7, 11, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 7, 12, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 7, 13, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),
grid_tile(arr, 8, 0, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 8, 1, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 8, 2, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 8, 3, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 8, 4, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 8, 5, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 8, 6, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 8, 7, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 8, 8, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 8, 9, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 8, 10, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 8, 11, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 8, 12, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 8, 13, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),
grid_tile(arr, 9, 0, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 9, 1, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 9, 2, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 9, 3, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 9, 4, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 9, 5, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 9, 6, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 9, 7, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 9, 8, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 9, 9, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 9, 10, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 9, 11, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 9, 12, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 9, 13, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),
grid_tile(arr, 10, 0, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 10, 1, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 10, 2, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 10, 3, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 10, 4, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 10, 5, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 10, 6, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 10, 7, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 10, 8, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 10, 9, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 10, 10, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 10, 11, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 10, 12, nullptr, TERRAIN_FEATURES::GREEN_PLAIN),grid_tile(arr, 10, 13, nullptr, TERRAIN_FEATURES::GREEN_PLAIN)
};

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

void draw_battleground(std::vector<int> & travelled_path)
{
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
        {
            if (std::find(travelled_path.begin(), travelled_path.end(), 14*i+j) != travelled_path.end())
                std::cout << "/---\\ ";
            else if (!battleground[14*i+j].obstacle)
                draw_feature[static_cast<int>(battleground[14*i+j].feature)](false);
            else
                std::cout << "/OOO\\ ";
        }
        std::cout << std::endl;
        if ( i % 2 == 0 )
            std::cout << "   ";
        for (size_t j = 0; j < 14; j++)
        {
            if (!battleground[14*i+j].obstacle)
                draw_feature[static_cast<int>(battleground[14*i+j].feature)](true);
            else
                std::cout << "\\OOO/ ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

/*
template<typename T, typename priority_t>
struct PriorityQueue {
  typedef std::pair<priority_t, T> PQElement;
  std::priority_queue<PQElement, std::vector<PQElement>,
                 std::greater<PQElement>> elements;

  inline bool empty() const {
     return elements.empty();
  }

  inline void put(T item, priority_t priority) {
    elements.emplace(priority, item);
  }

  T get() {
    T best_item = elements.top().second;
    elements.pop();
    return best_item;
  }
};

template<typename Location>
std::vector<Location> reconstruct_path(
   Location start, Location goal,
   std::map<Location, Location> came_from
) {
  std::vector<Location> path;
  Location current = goal;
  while (current != start) {
    path.push_back(current);
    current = came_from[current];
  }
  path.push_back(start); // optional
  std::reverse(path.begin(), path.end());
  return path;
}

inline double heuristic(GridLocation a, GridLocation b) {
  return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}
template<typename Location, typename Graph>
void a_star_search
  (Graph graph,
   Location start,
   Location goal,
   std::map<Location, Location>& came_from,
   std::map<Location, double>& cost_so_far)
{
  PriorityQueue<Location, double> frontier;
  frontier.put(start, 0);

  came_from[start] = start;
  cost_so_far[start] = 0;

  while (!frontier.empty()) {
    Location current = frontier.get();

    if (current == goal) {
      break;
    }

    for (Location next : graph.neighbors(current)) {
      double new_cost = cost_so_far[current] + graph.cost(current, next);
      if (cost_so_far.find(next) == cost_so_far.end()
          || new_cost < cost_so_far[next]) {
        cost_so_far[next] = new_cost;
        double priority = new_cost + heuristic(next, goal);
        frontier.put(next, priority);
        came_from[next] = current;
      }
    }
  }
}
*/

/*
inline double heuristic(int from, int to)
{
    return  std::sqrt
            (
                (battleground[from].coordinate_X - battleground[to].coordinate_X) *
                (battleground[from].coordinate_X - battleground[to].coordinate_X) +
                (battleground[from].coordinate_Y - battleground[to].coordinate_Y) *
                (battleground[from].coordinate_Y - battleground[to].coordinate_Y)
            );
}
*/
inline double heuristic(int from, int to)
{
    return  std::abs(battleground[from].coordinate_X - battleground[to].coordinate_X) +
            std::abs(battleground[from].coordinate_Y - battleground[to].coordinate_Y);
}

///*
void A_star_search(int start, int goal, std::map<int, int> & came_from, std::map<int, double> cost_so_far)
{
    using elem = std::pair<int, double>;
    auto comp = [](elem fst, elem snd) { return fst.second >= snd.second; };

    std::priority_queue<elem, std::vector<elem>, decltype(comp)> frontier(comp);
    frontier.emplace(elem(start, 0.0));

    came_from[start] = start;
    cost_so_far[start] = 0.0;

    while (!frontier.empty())
    {
        int current = frontier.top().first;
        frontier.pop();

        if (current == goal)
            break;

        for (int neighbour : battleground[current].neighbours)
        {
            if (neighbour == -1 || !battleground[neighbour].passable)
                continue;
            double new_cost = cost_so_far[current] + double(battleground[neighbour].entrance_fee);//cost(battleground[current], battleground[neighbour]);
            if (cost_so_far.find(neighbour) == cost_so_far.end() || new_cost < cost_so_far[neighbour])
            {
                cost_so_far[neighbour] = new_cost;
                double priority = new_cost + heuristic(neighbour, goal);
                frontier.emplace(neighbour, priority);
                came_from[neighbour] = current;
            }
        }
    }
}
//*/

std::vector<int> reconstruct_path(
   int start, int goal,
   std::map<int, int> & came_from
) {
  std::vector<int> path;
  int current = goal;
  while (current != start) {
    path.push_back(current);
    current = came_from[current];
  }
  path.push_back(start); // optional
  std::reverse(path.begin(), path.end());
  return path;
}

int main()
{
    fill_angles();
    fill_edges();
    fill_middle();
    std::map<int, int> came_from;
    std::map<int, double> cost_so_far;
    std::vector<int> path;
    draw_battleground(path);
    A_star_search(0, 5, came_from, cost_so_far);
    path = reconstruct_path(0, 5, came_from);
    draw_battleground(path);
    /*
    std::array<TERRAIN_FEATURES, 6> ambient_relief = {TERRAIN_FEATURES::GREEN_PLAIN, TERRAIN_FEATURES::GREEN_HILLS, TERRAIN_FEATURES::GREEN_HILLS,
                                                      TERRAIN_FEATURES::GREEN_PLAIN, TERRAIN_FEATURES::GREEN_PLAIN, TERRAIN_FEATURES::SNOW_PLAIN};
    std::random_device rd;
    std::mt19937 gen(rd());
    std::vector<std::pair<TERRAIN_FEATURES, int>> features_and_frequencies = {std::make_pair(TERRAIN_FEATURES::WATER, 1)};
    for (size_t i = 0; i < 6; i++)
    {
        auto it = find_if(features_and_frequencies.begin(), features_and_frequencies.end(),
                        [&ambient_relief, i](std::pair<TERRAIN_FEATURES, int> & p){return p.first == ambient_relief[i];});
        if(it == features_and_frequencies.end())
            features_and_frequencies.push_back(std::make_pair(ambient_relief[i], 1));
        else
            it->second++;
    }
    std::vector<int> frequencies;
    for (size_t i = 0; i < features_and_frequencies.size(); i++)
        frequencies.push_back(features_and_frequencies[i].second);
    std::discrete_distribution<> d(frequencies.begin(), frequencies.end());
    std::cout << features_and_frequencies[d(gen)].first << ' ' << frequencies.size() << ' ' << features_and_frequencies.size() << std::endl;
    */
    return 0;
}
