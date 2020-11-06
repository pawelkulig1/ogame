#include "catch.hpp"
#include "ogame.h"

TEST_CASE( "Crystal Mine" ) {
    using namespace ogame;
    PLAYER_OPTIONS player_options{PLAYER_CLASS::DISCOVERER, 8, true, true, true, true, false, 2, 4};
    PLANET_OPTIONS planet_options{12, 95, 0, 0.2, 0.4, 0.2, 0.0};

    SECTION( "extraction" ) {
        REQUIRE(get_crystal_extraction(0, planet_options, player_options) == 120);
        REQUIRE(get_crystal_extraction(1, planet_options, player_options) == 384);
        REQUIRE(get_crystal_extraction(5, planet_options, player_options) == 2052);
        REQUIRE(get_crystal_extraction(10, planet_options, player_options) == 6344);
        REQUIRE(get_crystal_extraction(17, planet_options, player_options) == 20742);
        REQUIRE(get_crystal_extraction(39, planet_options, player_options) == 385234);
    }

    //SECTION( "extraction_no_boosters" ) {
    //    planet_options.m_enchancement = 0.0;
    //    REQUIRE(get_metal_extraction(0, planet_options, player_options) == 30 + 10);
    //    REQUIRE(get_metal_extraction(7, planet_options, player_options) == 785);
    //    REQUIRE(get_metal_extraction(9, planet_options, player_options) == 1200);
    //}

    //SECTION( "extraction speed 2" ) {
    //    player_options.universe_speed = 2;
    //    REQUIRE(get_metal_extraction(0, planet_options, player_options) == 81); 
    //    REQUIRE(get_metal_extraction(1, planet_options, player_options) == 219);
    //    REQUIRE(get_metal_extraction(5, planet_options, player_options) == 1091);
    //    REQUIRE(get_metal_extraction(10, planet_options, player_options) == 3336);
    //    REQUIRE(get_metal_extraction(17, planet_options, player_options) == 10869);
    //    REQUIRE(get_metal_extraction(39, planet_options, player_options) == 201544);
    //}

    //SECTION( "extraction_no_geologist" ) {
    //    player_options.has_geologist = false;
    //    REQUIRE(get_metal_extraction(0, planet_options, player_options) == 40);
    //    REQUIRE(get_metal_extraction(6, planet_options, player_options) == 664);
    //    REQUIRE(get_metal_extraction(11, planet_options, player_options) == 1883);
    //}

    //SECTION( "extraction_full_staff" ) {
    //    player_options.has_geologist = true;
    //    player_options.has_engineer = true;
    //    player_options.has_admiral  = true;
    //    player_options.has_commander = true;
    //    player_options.has_technocrat = true;

    //    REQUIRE(get_metal_extraction(0, planet_options, player_options) == 40);
    //    REQUIRE(get_metal_extraction(14, planet_options, player_options) == 3420);
    //    REQUIRE(get_metal_extraction(19, planet_options, player_options) == 7429);
    //}

    //SECTION( "extraction_planet_position" ) {
    //    planet_options.position = 1;
    //    REQUIRE(get_metal_extraction(0, planet_options, player_options) == 30);
    //    REQUIRE(get_metal_extraction(12, planet_options, player_options) == 1780);
    //    REQUIRE(get_metal_extraction(8, planet_options, player_options) == 827);

    //    planet_options.position = 7;
    //    REQUIRE(get_metal_extraction(12, planet_options, player_options) == 2189);

    //    planet_options.position = 9;
    //    REQUIRE(get_metal_extraction(12, planet_options, player_options) == 2189);

    //    planet_options.position = 6;
    //    REQUIRE(get_metal_extraction(12, planet_options, player_options) == 2082);

    //    planet_options.position = 10;
    //    REQUIRE(get_metal_extraction(12, planet_options, player_options) == 2082);
    //}
}
