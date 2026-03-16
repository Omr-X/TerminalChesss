#include "Node.h"

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

    if(!assertValidPieceToMove(newPieces, move.init))
        return std::nullopt;



    if(Node::isKingInCheck(newPieces, newNodeInfo.isWhiteToMove))
        return std::nullopt;

    return std::make_optional<Node>({
        newPieces,
        newNodeInfo
    });
}

bool assertValidPieceToMove(const std::array<uint64_t, PieceTypeCount>& pieces, Tile init) {
    for(uint64_t pieceType : pieces) {
        if(pieceType & 0b1 << init.x * 8 + init.y != 0) { //validate x/y and operator precedence
            // set pieceType of pos to idk...
            return true;
        }
    }

    return false;
};

bool Node::isKingInCheck(const std::array<uint64_t, PieceTypeCount>& pieces, const bool isWhiteToMove) {
   return false;
}