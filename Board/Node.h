#include "../Pieces/PieceType.h"
#include "../Move/Move.h"
#include <array>
#include <optional>
#include <cstdint>

#include "Board.h"


//Node represents a game state. it is non-mutable; to create a subsequent game state, create a new node
class Node {
private:
    const Board board;

public:
    struct NodeInfo {
        bool isWhiteToMove;

        struct LastMove {
            PieceType pieceType;
            Move move;
            /*Move move (init and dest)*/
        };

        LastMove LastMove;

        struct CastlingRights {
            bool whiteKingSide;
            bool whiteQueenSide;
            bool blackKingSide;
            bool blackQueenSide;
        };

        CastlingRights castlingRights;

        // int fiftyMoveRule; implement later... anyways need to find a way to implement three fold repetition too
    };

private:
    const NodeInfo nodeInfo;

public:
    Node(const Board& board, const NodeInfo& nodeInfo);
    ~Node() = default;

    std::optional<Node> from(const Move move) const;

    static bool isKingInCheck(const Board& board, const bool isWhiteToMove);

    uint64_t operator[](const int pieceType);
    uint64_t operator[](const PieceType pieceType);
};