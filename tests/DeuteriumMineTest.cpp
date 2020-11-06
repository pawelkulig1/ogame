#include "catch.hpp"
#include "ogame.h"


TEST_CASE( "Deuterium Mine" ) {
    using namespace ogame;
    PLAYER_OPTIONS player_options{PLAYER_CLASS::GENERAL, 1, true, true, false, false, false, 0, 0};
    PLANET_OPTIONS planet_options{8, 15, 0, 0.2, 0.2, 0.1, 0.2};

    SECTION( "extraction" ) {
        REQUIRE(get_deuterium_extraction(0, planet_options, player_options) == 0);
        REQUIRE(get_deuterium_extraction(1, planet_options, player_options) == 19);
        REQUIRE(get_deuterium_extraction(5, planet_options, player_options) == 133);
        REQUIRE(get_deuterium_extraction(10, planet_options, player_options) == 429);
        REQUIRE(get_deuterium_extraction(17, planet_options, player_options) == 1423);
        REQUIRE(get_deuterium_extraction(39, planet_options, player_options) == 26572);
    }

    SECTION( "extraction_no_geologist" ) {
        player_options.has_geologist = false;
        REQUIRE(get_deuterium_extraction(6, planet_options, player_options) == 161); 
        REQUIRE(get_deuterium_extraction(11, planet_options, player_options) == 476);
    }

    SECTION( "extraction_planet_temperature" ) {
        planet_options.max_planet_temperature = -130;
        REQUIRE(get_deuterium_extraction(0, planet_options, player_options) == 0);
        REQUIRE(get_deuterium_extraction(12, planet_options, player_options) == 886);
        REQUIRE(get_deuterium_extraction(8, planet_options, player_options) == 404);

        planet_options.max_planet_temperature = -30;
        REQUIRE(get_deuterium_extraction(12, planet_options, player_options) == 705);

        planet_options.max_planet_temperature = 0;
        REQUIRE(get_deuterium_extraction(12, planet_options, player_options) == 650);

        planet_options.max_planet_temperature = 50;
        REQUIRE(get_deuterium_extraction(12, planet_options, player_options) == 560);

        planet_options.max_planet_temperature = 260;
        REQUIRE(get_deuterium_extraction(12, planet_options, player_options) == 180);
    }
    //TODO energetic_technology_lvl
}
