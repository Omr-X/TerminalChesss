#pragma once

#include <functional>
#include <unordered_set>
#include <cstdint>
#include "../Move/Move.h"
#include "../Move/Tile.h"
#include "PieceType.h"
#include "../Board/Board.h"
#include "../Board/Node.h"


class Piece {
protected:
    const bool isWhite;
    const Board& board;

public:
    Piece(const bool isWhiteToMove, const Board& board) :
        isWhite{isWhiteToMove},
        board{board}
    {};
    ~Piece() = default;

    virtual const std::unordered_set<Move, MoveHash> getMoves() const = 0;

    static const Piece getPiece(const PieceType pieceType, const bool isWhite, const std::array<uint64_t, PieceTypeCount>& pieces, const Node::NodeInfo& nodeInfo) {
        switch (pieceType) {

            default: return {isWhite, pieces};
        }
    }

    constexpr bool isWithinBounds(int val) const {
        return isWhitinUpperBounds(val) && isWithinLowerBounds(val);
    }

    constexpr bool canMove(const Tile& dest) const {
        return isWithinBounds(dest.x)
        && isWithinBounds(dest.y)
        && (isWhite ?
            (board.getWhitePieces() & (1 << dest.x + dest.y * 8)) == 0
            : (board.getBlackPieces() & (1 << dest.x + dest.y * 8)) == 0);
    }

    constexpr bool hasKilled(const Tile& dest) const {
        return isWhite ?
            board.getBlackPieces() & (1 << dest.x + dest.y * 8) == 0
            : board.getWhitePieces() & (1 << dest.x + dest.y * 8) == 0;
    }
};
