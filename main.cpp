#include "ogame.h"
#include <iostream>
#include <chrono>
#include <cassert>

using namespace ogame;

int main()
{
    PLAYER_OPTIONS player_options{PLAYER_CLASS::COLLECTOR, 1, true, true, false, false, false, 0};
    PLANET_OPTIONS planet_options{8, 75, 0, 0.2, 0.2, 0.2, 0.2};
    auto start = std::chrono::steady_clock::now();
    RES out1 = get_metal_extraction(30, planet_options, player_options);
    RES out2 = get_crystal_extraction(30, planet_options, player_options);
    RES out3 = get_deuterium_extraction(30, planet_options, player_options);
    RES out4 = get_solar_plant_production(30, planet_options, player_options);
    RES out5 = get_fusion_reactor_production(30, planet_options, player_options);
    RES out6 = get_solar_satelite_production(planet_options, player_options);
    RES out7 = get_fusion_deuterium_consumption(30);
    auto end = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << '\n';
	
	assert(out1 == 32901);
	assert(out2 == 16242);
	assert(out3 == 9249); //9250 enchancement_bonus option rounding error?
	assert(out4 == 14657);
	assert(out5 == 5445);
	assert(out6 == 50);
	assert(out7 == 5235); //5234??



}
