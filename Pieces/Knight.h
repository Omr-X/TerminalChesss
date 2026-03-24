#include "Piece.h"

class Knight : Piece {
public:
    const std::unordered_set<Move, MoveHash> getMoves() const override {
        uint64_t knights = board.pieces[static_cast<int>(isWhite ? PieceType::WHITE_KNIGHT : PieceType::BLACK_KNIGHT)];
        std::unordered_set<Move, MoveHash> moves;

        for (int pos = 0; pos < 64; pos++) {
            if ((knights & (1ULL << pos)) == 0)
                continue;

            Tile knightPos{pos};

            if (canMove({knightPos.x + 2, knightPos.y + 1}) || hasKilled({knightPos.x + 2, knightPos.y + 1}))
                moves.emplace(knightPos, Tile{knightPos.x + 2, knightPos.y + 1});
            if (canMove({knightPos.x + 2, knightPos.y - 1}) || hasKilled({knightPos.x + 2, knightPos.y - 1}))
                moves.emplace(knightPos, Tile{knightPos.x + 2, knightPos.y - 1});
            if (canMove({knightPos.x - 2, knightPos.y + 1}) || hasKilled({knightPos.x - 2, knightPos.y + 1}))
                moves.emplace(knightPos, Tile{knightPos.x - 2, knightPos.y + 1});
            if (canMove({knightPos.x - 2, knightPos.y - 1}) || hasKilled({knightPos.x - 2, knightPos.y - 1}))
                moves.emplace(knightPos, Tile{knightPos.x - 2, knightPos.y - 1});
            if (canMove({knightPos.x + 1, knightPos.y + 2}) || hasKilled({knightPos.x + 1, knightPos.y + 2}))
                moves.emplace(knightPos, Tile{knightPos.x + 1, knightPos.y + 2});
            if (canMove({knightPos.x - 1, knightPos.y + 2}) || hasKilled({knightPos.x - 1, knightPos.y + 2}))
                moves.emplace(knightPos, Tile{knightPos.x - 1, knightPos.y + 2});
            if (canMove({knightPos.x + 1, knightPos.y - 2}) || hasKilled({knightPos.x + 1, knightPos.y - 2}))
                moves.emplace(knightPos, Tile{knightPos.x + 1, knightPos.y - 2});
            if (canMove({knightPos.x - 1, knightPos.y - 2}) || hasKilled({knightPos.x - 1, knightPos.y - 2}))
                moves.emplace(knightPos, Tile{knightPos.x - 1, knightPos.y - 2});
        }

        return moves;
    }
};