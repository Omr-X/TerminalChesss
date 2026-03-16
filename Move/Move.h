#include "Tile.h"

class Move {
public:
    const Tile init;
    const Tile dest;

    Move(const Tile init, const Tile dest) :
        init{init.x, init.y},
        dest{dest.x, dest.y}
    {
        //Nth
    };
    ~Move() {
        //Nth
    };
};