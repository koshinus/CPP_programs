/*
#include <iostream>
#include <range/v3/all.hpp> // get everything
#include <string>
using std::cout;
int
main()
{
    std::string s{"hello"};
    // output: h e l l o
    ranges::for_each(s, [](char c) { cout << c << ' '; });
    cout << '\n';
}
*/
// Remove all non-unique elements from a container.
#include <iostream>
#include <vector>
#include <range/v3/action/sort.hpp>
#include <range/v3/action/unique.hpp>
#include <range/v3/view/all.hpp>
using std::cout;
int main()
{
    std::vector<int> vi{9, 4, 5, 2, 9, 1, 0, 2, 6, 7, 4, 5, 6, 5, 9, 2, 7,
                        1, 4, 5, 3, 8, 5, 0, 2, 9, 3, 7, 5, 7, 5, 5, 6, 1,
                        4, 3, 1, 8, 4, 0, 7, 8, 8, 2, 6, 5, 3, 4, 5};
    using namespace ranges;
    vi |= action::sort | action::unique;
    // prints: [0,1,2,3,4,5,6,7,8,9]
    cout << view::all(vi) << '\n';
    for(int i : vi)
        cout << i << ' '; 
}
