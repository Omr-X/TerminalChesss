#include <cstdint>
#include <unordered_set>

#include "Piece.h"
#include "PieceType.h"

class Queen : Piece {
public:
    const std::unordered_set<Move, MoveHash> getMoves() const override {
        uint64_t queens = board.pieces[static_cast<int>(isWhite ? PieceType::WHITE_QUEEN : PieceType::BLACK_QUEEN)];
        std::unordered_set<Move, MoveHash> moves;

        for (int pos = 0; pos < 64; pos++) {
            Tile RookPos{pos};
            if ((queens & (1ULL << pos)) == 0)
                continue;

            int step = 1;

            while (true) {
                const Tile test = {RookPos.x + step, RookPos.y};
                if (!canMove(test) && !hasKilled(test)) break;
                moves.emplace(RookPos, Tile{RookPos.x + step, RookPos.y});
                if (hasKilled(test)) break;
                step += 1;
            }

            step = 1;
            while (true) {
                const Tile test = {RookPos.x - step, RookPos.y};
                if (!canMove(test) && !hasKilled(test)) break;
                moves.emplace(RookPos, Tile{RookPos.x - step, RookPos.y});
                if (hasKilled(test)) break;
                step += 1;
            }

            step = 1;
            while (true) {
                const Tile test = {RookPos.x, RookPos.y + step};
                if (!canMove(test) && !hasKilled(test)) break;
                moves.emplace(RookPos, Tile{RookPos.x, RookPos.y + step});
                if (hasKilled(test)) break;
                step += 1;
            }

            step = 1;
            while (true) {
                const Tile test = {RookPos.x, RookPos.y - step};
                if (!canMove(test) && !hasKilled(test)) break;
                moves.emplace(RookPos, Tile{RookPos.x, RookPos.y - step});
                if (hasKilled(test)) break;
                step += 1;
            }

            step = 1;
            while (true) {
                const Tile test = {RookPos.x + step, RookPos.y + step};
                if (!canMove(test) && !hasKilled(test)) break;
                moves.emplace(RookPos, Tile{RookPos.x + step, RookPos.y + step});
                if (hasKilled(test)) break;
                step += 1;
            }

            step = 1;
            while (true) {
                const Tile test = {RookPos.x - step, RookPos.y + step};
                if (!canMove(test) && !hasKilled(test)) break;
                moves.emplace(RookPos, Tile{RookPos.x - step, RookPos.y + step});
                if (hasKilled(test)) break;
                step += 1;
            }

            step = 1;
            while (true) {
                const Tile test = {RookPos.x + step, RookPos.y - step};
                if (!canMove(test) && !hasKilled(test)) break;
                moves.emplace(RookPos, Tile{RookPos.x + step, RookPos.y - step});
                if (hasKilled(test)) break;
                step += 1;
            }

            step = 1;
            while (true) {
                const Tile test = {RookPos.x - step, RookPos.y - step};
                if (!canMove(test) && !hasKilled(test)) break;
                moves.emplace(RookPos, Tile{RookPos.x - step, RookPos.y - step});
                if (hasKilled(test)) break;
                step += 1;
            }
        }
        return moves;
    }
};