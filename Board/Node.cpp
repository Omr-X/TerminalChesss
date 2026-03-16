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

std::optional<Node> Node::from(/*Move move*/) const {
    //do move ...

    if(Node::isKingInCheck(pieces, nodeInfo.isWhiteToMove))
        return std::nullopt;
    
    // return std::make_optional(pieces); // wtf is that error? lol
    return std::nullopt;
}

bool Node::isKingInCheck(const std::array<uint64_t, PieceTypeCount>& pieces, const bool isWhiteToMove) {
    return false;
}