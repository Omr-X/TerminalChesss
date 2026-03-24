#include <algorithm>

#include "Piece.h"

class Rook : Piece {
public:
    const std::unordered_set<Move, MoveHash> getMoves() const override {
        uint64_t rooks = board.pieces[static_cast<int>(isWhite ? PieceType::WHITE_ROOK : PieceType::BLACK_ROOK)];
        std::unordered_set<Move, MoveHash> moves;

        for (int pos = 0; pos < 64; pos++) {
            Tile RookPos{pos};
            if ((rooks & (1ULL << pos)) == 0)
                continue;

            int stepNegativeX = 1;
            int stepPositiveX = 1;
            int stepNegativeY = 1;
            int stepPositiveY = 1;

            while (true) {
                const Tile test = {RookPos.x + stepPositiveX, RookPos.y};
                if (!canMove(test) && !hasKilled(test)) break;
                moves.emplace(RookPos, Tile{RookPos.x + stepPositiveX, RookPos.y});
                if (hasKilled(test)) break;
                stepPositiveX += 1;
            }
            while (true) {
                const Tile test = {RookPos.x - stepNegativeX, RookPos.y};
                if (!canMove(test) && !hasKilled(test)) break;
                moves.emplace(RookPos, Tile{RookPos.x - stepNegativeX, RookPos.y});
                if (hasKilled(test)) break;
                stepNegativeX += 1;
            }
            while (true) {
                const Tile test = {RookPos.x, RookPos.y + stepPositiveY};
                if (!canMove(test) && !hasKilled(test)) break;
                moves.emplace(RookPos, Tile{RookPos.x, RookPos.y + stepPositiveY});
                if (hasKilled(test)) break;
                stepPositiveY += 1;
            }
            while (true) {
                const Tile test = {RookPos.x, RookPos.y - stepNegativeY};
                if (!canMove(test) && !hasKilled(test)) break;
                moves.emplace(RookPos, Tile{RookPos.x, RookPos.y - stepNegativeY});
                if (hasKilled(test)) break;
                stepNegativeY += 1;
            }
        }
        return moves;
    }
};