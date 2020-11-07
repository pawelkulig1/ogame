#include "catch.hpp"
#include "ogame.h"

static inline constexpr ogame::SEC d2s(int days)
{
    return days * 24 * 60 * 60;
}

static inline constexpr ogame::SEC h2s(int hours)
{
    return hours * 60 * 60;
}

static inline constexpr ogame::SEC m2s(int minutes)
{
    return minutes * 60;
} 

TEST_CASE( "Construction" ) {
    using namespace ogame;
    PLAYER_OPTIONS player_options{PLAYER_CLASS::GENERAL, 2, true, true, false, false, false, 0, 4};
    PLANET_OPTIONS planet_options{8, 90, 0, 0.2, 0.2, 0.1, 0.8};

    SECTION( "Construction cost" ) {
        REQUIRE(get_construction_cost_m(METAL_MINE, 1) == 60);
        REQUIRE(get_construction_cost_c(METAL_MINE, 1) == 15);
        REQUIRE(get_construction_cost_d(METAL_MINE, 1) == 0);
        REQUIRE(get_construction_cost_e(METAL_MINE, 1) == 0);

        REQUIRE(get_construction_cost_m(METAL_MINE, 10) == 2306);
        REQUIRE(get_construction_cost_c(METAL_MINE, 10) == 576);
        REQUIRE(get_construction_cost_d(METAL_MINE, 10) == 0);
        REQUIRE(get_construction_cost_e(METAL_MINE, 10) == 0);
    }

    SECTION( "Building construction time" ) {
        REQUIRE(get_construction_time(METAL_MINE, 1, planet_options, player_options) == 15);
        REQUIRE(get_construction_time(METAL_MINE, 2, planet_options, player_options) == 26);
        REQUIRE(get_construction_time(METAL_MINE, 3, planet_options, player_options) == 48);
        REQUIRE(get_construction_time(METAL_MINE, 4, planet_options, player_options) == m2s(1) + 30);
        REQUIRE(get_construction_time(METAL_MINE, 5, planet_options, player_options) == m2s(3) + 1);
        REQUIRE(get_construction_time(METAL_MINE, 6, planet_options, player_options) == m2s(6) + 48);
        REQUIRE(get_construction_time(METAL_MINE, 7, planet_options, player_options) == m2s(10) + 14);
        REQUIRE(get_construction_time(METAL_MINE, 8, planet_options, player_options) == m2s(15) + 22);
        REQUIRE(get_construction_time(METAL_MINE, 10, planet_options, player_options) == m2s(34) + 35);
        REQUIRE(get_construction_time(METAL_STORAGE, 10, planet_options, player_options) == d2s(4) + h2s(6) + m2s(24)); 
    }

    SECTION( "Building construction time with robotics factory" ) {
        planet_options.robot_factory_lvl = 2;
        REQUIRE(get_construction_time(METAL_MINE, 1, planet_options, player_options) == 5);
        REQUIRE(get_construction_time(METAL_MINE, 2, planet_options, player_options) == 8);
        REQUIRE(get_construction_time(METAL_MINE, 3, planet_options, player_options) == 16);
        REQUIRE(get_construction_time(METAL_MINE, 4, planet_options, player_options) == 30);
        REQUIRE(get_construction_time(METAL_MINE, 5, planet_options, player_options) == m2s(1));
        REQUIRE(get_construction_time(METAL_MINE, 6, planet_options, player_options) == m2s(2) + 16);
        REQUIRE(get_construction_time(METAL_MINE, 7, planet_options, player_options) == m2s(3) + 24);
        REQUIRE(get_construction_time(METAL_MINE, 8, planet_options, player_options) == m2s(5) + 7);
        REQUIRE(get_construction_time(METAL_MINE, 10, planet_options, player_options) == m2s(11) + 31);

        planet_options.nanite_factory_lvl = 1;
        REQUIRE(get_construction_time(METAL_MINE, 10, planet_options, player_options) == m2s(5) + 45);


    }

    SECTION( "Technologies construction time with research_lab" ) {
        planet_options.research_lab_lvl = 5;
        REQUIRE(get_construction_time(ASTROPHYSICS, 1, planet_options, player_options) == h2s(2));
        REQUIRE(get_construction_time(ASTROPHYSICS, 2, planet_options, player_options) == h2s(3) + m2s(30));
        REQUIRE(get_construction_time(ASTROPHYSICS, 10, planet_options, player_options) == d2s(12) + h2s(19) + m2s(52) + 24 );
    }


}
