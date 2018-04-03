#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Move.h"
#include "Piece.h"

TEST_CASE( "Piece data-type works correctly", "[piece]" ) {
}

TEST_CASE("Move data-type works correctly", "[move]") {

    SECTION("Move can be created from 4 int parameters.") {
        Move m(1, 2, 3, 4);
        REQUIRE(m.getFrom().x == 1);
        REQUIRE(m.getFrom().y == 2);
        REQUIRE(m.getTo().x == 3);
        REQUIRE(m.getTo().y == 4);
    }

    SECTION("Move can be created from 2 coord parameters.") {
        Move m(Coord(5,6), Coord(6,7));
        REQUIRE(m.getFrom().x == 5);
        REQUIRE(m.getFrom().y == 6);
        REQUIRE(m.getTo().x == 6);
        REQUIRE(m.getTo().y == 7);
    }
}