#include "Node.h"

#include <iostream>

namespace nodeUtils {
    bool isPieceAtPos(const int pos, const uint64_t piece) {
        return (piece & (1ULL << pos)) != 0;
    }

    bool isPieceAtPos(const Tile pos, const uint64_t piece) {
        return (piece & (1ULL << pos.getPos())) != 0;
    }
};


Node::Node(const Board& board, const Node::NodeInfo& nodeInfo) :
    board{board},
    nodeInfo{nodeInfo}
{
}

std::optional<Node> Node::from(const Move move) const {
    Board newBoard = board;
    Node::NodeInfo newNodeInfo = nodeInfo;

    //TODO, reverify logic

    if(Node::isKingInCheck(newBoard, newNodeInfo.isWhiteToMove))
        return std::nullopt;

    return std::make_optional<Node>({
        newBoard,
        newNodeInfo
    });
}

uint64_t Node::operator[](const int pieceType) {
    return board.pieces[pieceType];
}

uint64_t Node::operator[](const PieceType pieceType) {
    return board.pieces[static_cast<int>(pieceType)];
}

bool Node::isKingInCheck(const Board& board, const bool isWhiteToMove) {
#ifdef __debug
    if (board[static_cast<int>(isWhiteToMove ? PieceType::BLACK_KING : PieceType::WHITE_KING)])
        throw std::runtime_error("skill issue");
#endif

    uint64_t king = board.pieces[static_cast<int>(isWhiteToMove ? PieceType::BLACK_KING : PieceType::WHITE_KING)];

    for (int pos = 0; pos < 64; pos++) {
        if (nodeUtils::isPieceAtPos(pos, king)) {
            Tile kingPos{pos};

            uint64_t knights = board.pieces[static_cast<int>(isWhiteToMove ? PieceType::WHITE_KNIGHT : PieceType::BLACK_KNIGHT)];
            //verify that no knights can capture the king

            //TODO...

            return false;
        }
    }

    throw std::runtime_error("skill issue @Node::isKingInCheck n2");
}