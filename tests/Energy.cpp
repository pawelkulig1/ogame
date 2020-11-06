
#include "catch.hpp"
#include "ogame.h"


TEST_CASE( "Energy" ) {
    using namespace ogame;
    PLAYER_OPTIONS player_options{PLAYER_CLASS::GENERAL, 2, true, true, false, false, false, 0, 4};
    PLANET_OPTIONS planet_options{8, 90, 0, 0.2, 0.2, 0.1, 0.8};

    SECTION( "Energy consumption" ) {
        REQUIRE(get_energy_consumption(METAL_MINE, 10) == 259);
        REQUIRE(get_energy_consumption(CRYSTAL_MINE, 10) == 259);
        REQUIRE(get_energy_consumption(DEUTERIUM_SYNTHESIZER, 10) == 518);

        REQUIRE(get_energy_consumption(METAL_MINE, 33) == 7664);
        REQUIRE(get_energy_consumption(CRYSTAL_MINE, 33) == 7664);
        REQUIRE(get_energy_consumption(DEUTERIUM_SYNTHESIZER, 33) == 15328);

        REQUIRE(get_energy_consumption(RESEARCH_LAB, 10) == 0);
    }

    SECTION( "Energy production Solar Plant" ) {
        REQUIRE(get_solar_plant_production(0, planet_options, player_options) == 0); 
        REQUIRE(get_solar_plant_production(1, planet_options, player_options) == 42);
        REQUIRE(get_solar_plant_production(5, planet_options, player_options) == 306);
        REQUIRE(get_solar_plant_production(7, planet_options, player_options) == 517);
        REQUIRE(get_solar_plant_production(17, planet_options, player_options) == 3264);
        REQUIRE(get_solar_plant_production(38, planet_options, player_options) == 54012);
    }

    SECTION( "Energy production Fusion Reactor" ) {
        REQUIRE(get_fusion_reactor_production(0, planet_options, player_options) == 0); 
        REQUIRE(get_fusion_reactor_production(1, planet_options, player_options) == 61);
        REQUIRE(get_fusion_reactor_production(5, planet_options, player_options) == 437);
        REQUIRE(get_fusion_reactor_production(7, planet_options, player_options) == 727);
        REQUIRE(get_fusion_reactor_production(17, planet_options, player_options) == 4194);
        REQUIRE(get_fusion_reactor_production(38, planet_options, player_options) == 57261);
    }

    SECTION( "Energy production Solar Satellites" ) {
        REQUIRE(get_solar_satelite_production(planet_options, player_options) == 72); 
        
        planet_options.max_planet_temperature = -130;
        REQUIRE(get_solar_satelite_production(planet_options, player_options) == 2);

        planet_options.max_planet_temperature = -50;
        REQUIRE(get_solar_satelite_production(planet_options, player_options) == 29);
    }
    //SECTION( "extraction_planet_temperature" ) {
    //    planet_options.max_planet_temperature = -130;
    //    REQUIRE(get_deuterium_extraction(0, planet_options, player_options) == 0);
    //    REQUIRE(get_deuterium_extraction(12, planet_options, player_options) == 886);
    //    REQUIRE(get_deuterium_extraction(8, planet_options, player_options) == 404);

    //    planet_options.max_planet_temperature = -30;
    //    REQUIRE(get_deuterium_extraction(12, planet_options, player_options) == 705);

    //    planet_options.max_planet_temperature = 0;
    //    REQUIRE(get_deuterium_extraction(12, planet_options, player_options) == 650);

    //    planet_options.max_planet_temperature = 50;
    //    REQUIRE(get_deuterium_extraction(12, planet_options, player_options) == 560);

    //    planet_options.max_planet_temperature = 260;
    //    REQUIRE(get_deuterium_extraction(12, planet_options, player_options) == 180);
    //}
}
