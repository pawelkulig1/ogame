#include "ogame.h"
#include <iostream>

using namespace ogame;

int main()
{
    std::cout << get_metal_extraction(1) << '\n';
    std::cout << get_fusion_reactor_production(1, 0) << '\n';
    std::cout << get_fusion_reactor_production(1, 0) << '\n';
    std::cout << power_cache::get_cache_ratio() << '\n';
}
