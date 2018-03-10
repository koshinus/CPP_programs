#include <iostream>
#include <cstdint>
#include <vector>

int main()
{
    int64_t n, m;
    std::vector<int64_t> a;
    std::vector<int64_t> b;
    std::cin >> n;
    int64_t num, sum = 0;
    for (int64_t i = 0; i < n; i++)
    {
        std::cin >> num;
        a.push_back(num);
    }
    std::cin >> m;
    for (int64_t i = 0; i < m; i++)
    {
        std::cin >> num;
        b.push_back(num);
    }
    for (int64_t i = 0; i < n; i++)
        for (int64_t j = 0; j < m; j++)
        {
            //int64_t step = (i-j)*std::abs(a[i] - b[j]);
            //std::cout << step << std::endl;
            sum += (i-j)*std::abs(a[i] - b[j]);            
        }
    std::cout << sum << std::endl;
}
