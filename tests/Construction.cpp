#include "catch.hpp"
#include "ogame.h"


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
}
