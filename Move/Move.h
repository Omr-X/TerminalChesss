#include "Tile.h"

class Move {
public:
    const Tile init;
    const Tile dest;

    Move(const Tile init, const Tile dest) :
        init{init.x, init.y},
        dest{dest.x, dest.y}
    {};

    bool operator==(const Move& other) const {
        return init.x == other.init.x && init.y == other.init.y
            && dest.x == other.dest.x && dest.y == other.dest.y;
    }
};

struct MoveHash {
    int operator() (const Move& move) {
        return TileHash{}(move.init) + 64 * (TileHash{}(move.dest));
    }
};