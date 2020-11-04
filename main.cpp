#include "ogame.h"
#include <iostream>
#include <chrono>

using namespace ogame;

int main()
{
    PLAYER_OPTIONS player_options{PLAYER_CLASS::COLLECTOR, 1, false, true, false, false, false, 0};
    PLANET_OPTIONS planet_options{8, 75, 0, 0.2, 0, 0, 0};
    auto start = std::chrono::steady_clock::now();
    RES out1 = get_metal_extraction(30, planet_options, player_options);
    RES out2 = get_crystal_extraction(30, planet_options, player_options);
    RES out3 = get_deuterium_extraction(30, planet_options, player_options);
    auto end = std::chrono::steady_clock::now();
    std::cout << out1 << " " << out2 << " " << out3 << " " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << '\n';


}
