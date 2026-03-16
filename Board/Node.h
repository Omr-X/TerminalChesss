#include "../Pieces/PieceType.h"
#include "../Move/Move.h"
#include <array>
#include <optional>
#include <cstdint>


//Node represents a game state. it is meant to be const; to create a subsequent game state, create a new node
class Node {
private:
    const std::array<uint64_t, PieceTypeCount> pieces;

    static struct NodeInfo { bool isWhiteToMove;

        static struct LastMove {
            PieceType pieceType;
            /*Move move (init and dest)*/
        };

        LastMove LastMove;

        static struct CastlingRights {
            bool whiteKingSide;
            bool whiteQueenSide;
            bool blackKingSide;
            bool blackQueenSide;
        };

        CastlingRights castlingRights;

        // int fiftyMoveRule; implement later... anyways need to find a way to implement three fold repetition too
    };

    const NodeInfo nodeInfo;

public:    
    Node(const std::array<uint64_t, PieceTypeCount>& pieces, const NodeInfo& nodeInfo);
    ~Node();

    std::optional<Node> from(const Move move) const;

    static bool isKingInCheck(const std::array<uint64_t, PieceTypeCount>& pieces, const bool isWhiteToMove);

    uint64_t operator[](const int pieceType);
    uint64_t operator[](const PieceType pieceType);
};