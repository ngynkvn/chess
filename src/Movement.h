#if !defined(MOVEMENT_H)
#define MOVEMENT_H
namespace Movement
{
struct MoveSet
{
    ePieceCode piece;
    std::vector<coordinate> directions;
    bool ray;
    MoveSet(ePieceCode piece, std::vector<coordinate> directions, bool ray) : piece(piece), directions(std::move(directions)), ray(ray) {}
    MoveSet(ePieceCode piece) : piece(piece) {}
};

struct _MoveSet
{
    pieceCode piece;
    std::vector<coordinate> directions;
    bool ray;
    _MoveSet(pieceCode piece, std::vector<coordinate> directions, bool ray) : piece(piece), directions(std::move(directions)), ray(ray) {}
    _MoveSet(pieceCode piece) : piece(piece) {}
};

const std::vector<coordinate> dirRook = {coordinate(0, 1),
                                    coordinate(0, -1),
                                    coordinate(1, 0),
                                    coordinate(-1, 0)};
const std::vector<coordinate> dirBishop = {coordinate(1, 1),
                                      coordinate(1, -1),
                                      coordinate(-1, -1),
                                      coordinate(-1, 1)};
const std::vector<coordinate> dirQueen = {coordinate(1, 1),
                                     coordinate(1, -1),
                                     coordinate(-1, -1),
                                     coordinate(-1, 1),
                                     coordinate(0, 1),
                                     coordinate(0, -1),
                                     coordinate(1, 0),
                                     coordinate(-1, 0)};
;
const std::vector<coordinate> dirKnight = {coordinate(1, 2),
                                      coordinate(2, 1),
                                      coordinate(2, -1),
                                      coordinate(1, -2),
                                      coordinate(-1, 2),
                                      coordinate(-2, 1),
                                      coordinate(-2, -1),
                                      coordinate(-1, -2)};
const std::vector<coordinate> dirKing = dirQueen;
MoveSet Rook = MoveSet(ePieceCode::Rook, dirRook, true);
MoveSet Bishop = MoveSet(ePieceCode::Bishop, dirBishop, true);
MoveSet Queen = MoveSet(ePieceCode::Queen, dirQueen, true);
MoveSet Knight = MoveSet(ePieceCode::Knight, dirKnight, false);
MoveSet King = MoveSet(ePieceCode::King, dirKing, false);
MoveSet Pawn = MoveSet(ePieceCode::Pawn);

_MoveSet _Rook = _MoveSet(pieceCode::rook, dirRook, true);
_MoveSet _Bishop = _MoveSet(pieceCode::bishop, dirBishop, true);
_MoveSet _Queen = _MoveSet(pieceCode::queen, dirQueen, true);
_MoveSet _Knight = _MoveSet(pieceCode::knight, dirKnight, false);
_MoveSet _King = _MoveSet(pieceCode::king, dirKing, false);
_MoveSet _Pawn = _MoveSet(pieceCode::pawn);
const std::vector<MoveSet> movements = {Rook, Bishop, Queen, Knight, Pawn, King};
const std::vector<_MoveSet> _movements = {_Rook, _Bishop, _Queen, _Knight, _Pawn, _King};
} // namespace Movement
#endif // MOVEMENT_H
