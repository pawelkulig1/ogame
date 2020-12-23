#include "catch.hpp"
#include "ogame.h"


TEST_CASE( "Energy" ) {
    using namespace ogame;
    PLAYER_OPTIONS player_options{PLAYER_CLASS::GENERAL, 2, true, true, false, false, false, 0, 4};
    PLANET_OPTIONS planet_options{8, 90, 0, 0.2, 0.2, 0.1, 0.8};

    SECTION( "Energy consumption" ) {
        REQUIRE(get_energy_consumption(METAL_MINE, 10, planet_options) == 259);
        REQUIRE(get_energy_consumption(CRYSTAL_MINE, 10, planet_options) == 259);
        REQUIRE(get_energy_consumption(DEUTERIUM_SYNTHESIZER, 10, planet_options) == 518);

        REQUIRE(get_energy_consumption(METAL_MINE, 33, planet_options) == 7664);
        REQUIRE(get_energy_consumption(CRYSTAL_MINE, 33, planet_options) == 7664);
        REQUIRE(get_energy_consumption(DEUTERIUM_SYNTHESIZER, 33, planet_options) == 15328);

        REQUIRE(get_energy_consumption(RESEARCH_LAB, 10, planet_options) == 0);
    }

    SECTION( "Energy production Solar Plant" ) {
        REQUIRE(get_solar_plant_production(0, planet_options, player_options) == 0); 
        REQUIRE(get_solar_plant_production(1, planet_options, player_options) == 42);
        REQUIRE(get_solar_plant_production(5, planet_options, player_options) == 306);
        REQUIRE(get_solar_plant_production(7, planet_options, player_options) == 517);
        REQUIRE(get_solar_plant_production(17, planet_options, player_options) == 3264);
        REQUIRE(get_solar_plant_production(38, planet_options, player_options) == 54012);

        planet_options.e_production_factor = 0.7;
        REQUIRE(get_solar_plant_production(7, planet_options, player_options) == 361);
        planet_options.e_production_factor = 0.4;
        REQUIRE(get_solar_plant_production(17, planet_options, player_options) == 1306);
        planet_options.e_production_factor = 0.2;
        REQUIRE(get_solar_plant_production(38, planet_options, player_options) == 10802);
        
        REQUIRE(get_fusion_reactor_production(38, planet_options, player_options) == 57261);
    }

    SECTION( "Energy production Fusion Reactor" ) {
        REQUIRE(get_fusion_reactor_production(0, planet_options, player_options) == 0); 
        REQUIRE(get_fusion_reactor_production(1, planet_options, player_options) == 61);
        REQUIRE(get_fusion_reactor_production(5, planet_options, player_options) == 437);

        planet_options.f_production_factor = 0.8;
        REQUIRE(get_fusion_reactor_production(7, planet_options, player_options) == 584);
        planet_options.f_production_factor = 0.0;
        REQUIRE(get_fusion_reactor_production(17, planet_options, player_options) == 0);
        planet_options.f_production_factor = 0.3;
        REQUIRE(get_fusion_reactor_production(38, planet_options, player_options) == 17178);
    }

    SECTION( "Energy production Solar Satellites" ) {
        REQUIRE(get_solar_satelite_production(planet_options, player_options) == 72); 
        
        planet_options.max_planet_temperature = -130;
        REQUIRE(get_solar_satelite_production(planet_options, player_options) == 2);

        planet_options.max_planet_temperature = -50;
        REQUIRE(get_solar_satelite_production(planet_options, player_options) == 29);
    }

    SECTION( "Mine production ratio changed" )
    {
        planet_options.m_production_factor = 0.9;
        planet_options.c_production_factor = 0.5;
        planet_options.d_production_factor = 0.1;

        REQUIRE(get_energy_consumption(METAL_MINE, 10, planet_options) == 233);
        REQUIRE(get_energy_consumption(CRYSTAL_MINE, 10, planet_options) == 129);
        REQUIRE(get_energy_consumption(DEUTERIUM_SYNTHESIZER, 10, planet_options) == 51);
        REQUIRE(get_energy_consumption(RESEARCH_LAB, 10, planet_options) == 0);
    }
}
