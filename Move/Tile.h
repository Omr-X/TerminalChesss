class Tile {
public:
    const int x;
    const int y;

    Tile(const int x, const int y) :
        x{x},
        y{y}
    {}

    explicit Tile(const int pos) :
        x{pos % 8},
        y{pos / 8}
    {};

    int getPos() const {
        return x + y * 8;
    }
};

struct TileHash {
    int operator()(const Tile& tile) {
        return tile.x + tile.y * 8;
    }
};