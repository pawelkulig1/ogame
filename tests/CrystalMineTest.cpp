#include "catch.hpp"
#include "ogame.h"

TEST_CASE( "Crystal Mine" ) {
    using namespace ogame;
    PLAYER_OPTIONS player_options{PLAYER_CLASS::DISCOVERER, 8, true, true, true, true, false, 2, 4};
    PLANET_OPTIONS planet_options{12, 95, 0, 0.2, 0.4, 0.2, 0.0};

    SECTION( "extraction" ) {
        REQUIRE(get_crystal_extraction(0, planet_options, player_options) == 120);
        REQUIRE(get_crystal_extraction(1, planet_options, player_options) == 386);
        REQUIRE(get_crystal_extraction(5, planet_options, player_options) == 2069);
        REQUIRE(get_crystal_extraction(10, planet_options, player_options) == 6399);
        REQUIRE(get_crystal_extraction(17, planet_options, player_options) == 20923);
        REQUIRE(get_crystal_extraction(39, planet_options, player_options) == 388623);
    }

    SECTION( "extraction_no_boosters" ) {
        planet_options.c_enchancement = 0.0;
        REQUIRE(get_crystal_extraction(0, planet_options, player_options) == 120);
        REQUIRE(get_crystal_extraction(7, planet_options, player_options) == 2549);
        REQUIRE(get_crystal_extraction(9, planet_options, player_options) == 3900);
    }

    SECTION( "extraction_no_geologist" ) {
        player_options.has_geologist = false;
        REQUIRE(get_crystal_extraction(6, planet_options, player_options) == 2522);
        REQUIRE(get_crystal_extraction(11, planet_options, player_options) == 7215); 
    }

    SECTION( "extraction_full_staff" ) {
        player_options.has_geologist = true;
        player_options.has_engineer = true;
        player_options.has_admiral  = true;
        player_options.has_commander = true;
        player_options.has_technocrat = true;

        REQUIRE(get_crystal_extraction(14, planet_options, player_options) == 13161); 
        REQUIRE(get_crystal_extraction(19, planet_options, player_options) == 28625); 
    }

    SECTION( "extraction_planet_position" ) {
        planet_options.position = 1;
        REQUIRE(get_crystal_extraction(12, planet_options, player_options) == 12933);

        planet_options.position = 2;
        REQUIRE(get_crystal_extraction(12, planet_options, player_options) == 12008); //there is bug on website here 1.296, should be 1.3

        planet_options.position = 3;
        REQUIRE(get_crystal_extraction(12, planet_options, player_options) == 11084);

        planet_options.position = 4;
        REQUIRE(get_crystal_extraction(12, planet_options, player_options) == 9238);
    }
}
