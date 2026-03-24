#include "Piece.h"

class King : Piece {
private:
    const Node::NodeInfo& nodeInfo;

public:
    King(const bool isWhiteToMove, const Board& board, const Node::NodeInfo& nodeInfo) :
        nodeInfo{nodeInfo},
        Piece{isWhiteToMove, board}
    {};

    const std::unordered_set<Move, MoveHash> getMoves() const override {
        uint64_t kings = board.pieces[static_cast<int>(isWhite ? PieceType::WHITE_KING : PieceType::BLACK_KING)];
        std::unordered_set<Move, MoveHash> moves;

        for (int pos; pos < 64; pos++) {
            if ((kings & (1 << pos)) != 0)
                continue;

            Tile kingPos{pos};

            if (canMove({kingPos.x + 1, kingPos.y + 1}))
                moves.emplace({kingPos, Tile{kingPos.x + 1, kingPos.y + 1}});
            if (canMove({kingPos.x + 1, kingPos.y}))
                moves.emplace({kingPos, Tile{kingPos.x + 1, kingPos.y}});
            if (canMove({kingPos.x + 1,kingPos.y - 1}))
                moves.emplace({kingPos, Tile{kingPos.x + 1, kingPos.y - 1}});
            if (canMove({kingPos.x, kingPos.y + 1}))
                moves.emplace({kingPos, Tile{kingPos.x, kingPos.y + 1}});
            if (canMove({kingPos.x, kingPos.y - 1}))
                moves.emplace({kingPos, Tile{kingPos.x, kingPos.y - 1}});
            if (canMove({kingPos.x - 1, kingPos.y + 1}))
                moves.emplace({kingPos, Tile{kingPos.x - 1, kingPos.y + 1}});
            if (canMove({kingPos.x - 1, kingPos.y}))
                moves.emplace({kingPos, Tile{kingPos.x - 1, kingPos.y}});
            if (canMove({kingPos.x - 1, kingPos.y - 1}))
                moves.emplace({kingPos, Tile{kingPos.x - 1, kingPos.y - 1}});


            //TODO -> castling logic
            // if (nodeInfo.castlingRights.whiteKingSide && isWhite) {
            //     Node::isKingInCheck(board, isWhite);
            // }
            // if (nodeInfo.castlingRights.whiteQueenSide && isWhite) {
            // }

            }
        }

        return moves;
    }
};
