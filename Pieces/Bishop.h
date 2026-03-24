#include <algorithm>

#include "Piece.h"

class Bishop : Piece {
public:
    const std::unordered_set<Move, MoveHash> getMoves() const override {
        uint64_t Bishops = board.pieces[static_cast<int>(isWhite ? PieceType::WHITE_BISHOP : PieceType::BLACK_BISHOP)];
        std::unordered_set<Move, MoveHash> moves;

        for (int pos = 0; pos < 64; pos++) {
            Tile BishopPos{pos};
            if ((Bishops & (1ULL << pos)) == 0)
                continue;

            int stepQuadrantI = 1;
            int stepQuadrantII = 1;
            int stepQuadrantIII = 1;
            int stepQuadrantIV = 1;

            while (true) {
                const Tile test = {BishopPos.x + stepQuadrantI, BishopPos.y + stepQuadrantI};
                if (!canMove(test) && !hasKilled(test)) break;
                moves.emplace(BishopPos, Tile{BishopPos.x + stepQuadrantI, BishopPos.y + stepQuadrantI});
                if (hasKilled(test)) break;
                stepQuadrantI += 1;
            }
            while (true) {
                const Tile test = {BishopPos.x - stepQuadrantII, BishopPos.y + stepQuadrantII};
                if (!canMove(test) && !hasKilled(test)) break;
                moves.emplace(BishopPos, Tile{BishopPos.x - stepQuadrantII, BishopPos.y + stepQuadrantII});
                if (hasKilled(test)) break;
                stepQuadrantII += 1;
            }
            while (true) {
                const Tile test = {BishopPos.x + stepQuadrantIV, BishopPos.y - stepQuadrantIV};
                if (!canMove(test) && !hasKilled(test)) break;
                moves.emplace(BishopPos, Tile{BishopPos.x + stepQuadrantIV, BishopPos.y - stepQuadrantIV});
                if (hasKilled(test)) break;
                stepQuadrantIV += 1;
            }
            while (true) {
                const Tile test = {BishopPos.x - stepQuadrantIII, BishopPos.y - stepQuadrantIII};
                if (!canMove(test) && !hasKilled(test)) break;
                moves.emplace(BishopPos, Tile{BishopPos.x - stepQuadrantIII, BishopPos.y - stepQuadrantIII});
                if (hasKilled(test)) break;
                stepQuadrantIII += 1;
            }
        }

        return moves;
    }
};