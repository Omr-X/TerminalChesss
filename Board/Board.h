#include <unordered_map>

class Board {
public:
    static enum class PieceType {
        WHITE_PAWN,
        WHITE_ROOK,
        WHITE_KNIGHT,
        WHITE_BISHOP,
        WHITE_QUEEN,
        WHITE_KING,
        
        BLACK_PAWN,
        BLACK_ROOK,
        BLACK_KNIGHT,
        BLACK_BISHOP,
        BLACK_QUEEN,
        BACK_KING
    };

private:
    const std::unordered_map<PieceType, uint64_t> pieces; //use std::bitset instead?
    //change to array and make enum have values 0 -> 11

public:    
    Board(const std::unordered_map<PieceType, uint64_t> pieces);
    Board(const Board& other);
    ~Board();


    const uint64_t operator[](const PieceType PieceType);
};