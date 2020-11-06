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

    RES out8 = get_construction_cost_m(METAL_MINE, 1); 
    RES out9 = get_construction_cost_m(METAL_MINE, 10); 
    RES out10 = get_construction_cost_c(METAL_MINE, 1); 
    SEC out11 = get_building_construction_time(METAL_MINE, 1, 0, 0);
    SEC out12 = get_building_construction_time(METAL_MINE, 29, 10, 2);
    SEC out13 = get_technology_construction_time(ESPIONAGE_TECHNOLOGY, 1, 3);
    SEC out14 = get_ship_construction_time(SOLAR_SATELITE, 1, 0);

    auto end = std::chrono::steady_clock::now();
    std::cout << "time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << '\n';
	
    std::cout << out11 << '\n';
    std::cout << out12 << '\n';
    std::cout << out13 << '\n';
    std::cout << out14 << '\n';
	assert(out1 == 32901);
	assert(out2 == 16242);
	assert(out3 == 9249); //9250 enchancement_bonus option rounding error?
	assert(out4 == 14657);
	assert(out5 == 5445);
	assert(out6 == 50);
	assert(out7 == 5235); //5234??
    assert(out8 == 60);
    assert(out9 == 2306);
    assert(out10 == 15); 
    assert(out11 == 30); 



}
