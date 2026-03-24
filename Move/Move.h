#include "Tile.h"

class Move {
public:
    const Tile init;
    const Tile dest;

    Move(const Tile init, const Tile dest) :
        init{init.x, init.y},
        dest{dest.x, dest.y}
    {};


};

struct MoveHash {
    int operator() (const Move& move) {
        return TileHash{}(move.init) + 64 * (TileHash{}(move.dest));
    }
};