#include <algorithm>

#include "Piece.h"

class Bishop : Piece {
public:
    const std::unordered_set<Move, MoveHash> getMoves() const override {
        uint64_t Bishops = board.pieces[static_cast<int>(isWhite ? PieceType::WHITE_BISHOP : PieceType::BLACK_BISHOP)];
        std::unordered_set<Move, MoveHash> moves;

        for (int pos; pos < 64; pos++) {
            Tile BishopPos{pos};
            if ((Bishops & (1 << pos)) != 0)
                continue;

            int stepQuadrantI = 1;
            int stepQuadrantII = 1;
            int stepQuadrantIII = 1;
            int stepQuadrantIV = 1;

            while (true) {const Tile test = {
                BishopPos.x + stepQuadrantI, BishopPos.y + stepQuadrantI};
                if (canMove(test) || hasKilled(test)) break;
                moves.emplace(BishopPos, Tile{BishopPos.x + stepQuadrantI, BishopPos.y});
                stepQuadrantI += 1;
            }
            while (true) {const Tile test = {
                BishopPos.x - stepQuadrantII, BishopPos.y + stepQuadrantII};
                if (canMove(test) || hasKilled(test)) break;
                moves.emplace(BishopPos, Tile{BishopPos.x - stepQuadrantII, BishopPos.y});
                stepQuadrantII += 1;
            }
            while (true) {const Tile test = {
                BishopPos.x + stepQuadrantIV, BishopPos.y - stepQuadrantIV};
                if (canMove(test) || hasKilled(test)) break;
                move.emplace(BishopPos, Tile{BishopPos.x, BishopPos.y + stepQuadrantIV});
                stepQuadrantIV += 1;
            }
            while (true) {
                const Tile test = {BishopPos.x - stepQuadrantIII, BishopPos.y - stepQuadrantIII};
                if (canMove(test) || hasKilled(test)) break;
                move.emplace(BishopPos, Tile{BishopPos.x, BishopPos.y - stepQuadrantIII});
                stepQuadrantIII += 1;
            }
        }

        return moves;
    }
};