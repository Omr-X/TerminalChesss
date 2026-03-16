#include "Node.h"

namespace nodeUtils {
    bool assertValidPieceToMove(const std::array<uint64_t, PieceTypeCount>& pieces, Tile init) {
        for(uint64_t pieceType : pieces) {
            if((pieceType & 0b1 << init.x + init.y * 8) != 0) {
                pieceType &= ~(pieceType & 0b1 << init.x + init.y * 8);
                return true;
            }
        }

        return false;
    };
};


Node::Node(const std::array<uint64_t, PieceTypeCount>& pieces, const Node::NodeInfo& nodeInfo) :
    pieces{pieces},
    nodeInfo{nodeInfo}
{
    //Nth
}

Node::~Node() {
    //Nth
}
std::optional<Node> Node::from(const Move move) const {
    std::array<uint64_t, PieceTypeCount> newPieces = pieces; // will modif original?
    Node::NodeInfo newNodeInfo = nodeInfo; // will modif original?

    if(!nodeUtils::assertValidPieceToMove(newPieces, move.init))
        return std::nullopt;

    

    if(Node::isKingInCheck(newPieces, newNodeInfo.isWhiteToMove))
        return std::nullopt;

    return std::make_optional<Node>({
        newPieces,
        newNodeInfo
    });
}

bool Node::isKingInCheck(const std::array<uint64_t, PieceTypeCount>& pieces, const bool isWhiteToMove) {
   return false;
}

