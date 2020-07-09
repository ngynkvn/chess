#include "catch.hpp"
#include "Board.h"

TEST_CASE("FEN parser works")
{
    auto b = _Board::init();
    auto fen = _Board::from_fen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    CHECK(b.state == fen.state);
}