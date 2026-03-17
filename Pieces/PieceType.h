constexpr size_t PieceTypeCount = 11;

enum class PieceType {
    NONE = 0,
    WHITE_PAWN = 1,
    WHITE_ROOK = 2,
    WHITE_KNIGHT = 3,
    WHITE_BISHOP = 4,
    WHITE_QUEEN = 5,
    WHITE_KING = 6,
    
    BLACK_PAWN = 7,
    BLACK_ROOK = 8,
    BLACK_KNIGHT = 9,
    BLACK_BISHOP = 10,
    BLACK_QUEEN = 11,
    BLACK_KING = 12
};

int getUnicode(PieceType piece) {
    switch (piece) {
        case PieceType::WHITE_PAWN:   return 0x2659;
        case PieceType::WHITE_ROOK:   return 0x2656;
        case PieceType::WHITE_KNIGHT: return 0x2658;
        case PieceType::WHITE_BISHOP: return 0x2657;
        case PieceType::WHITE_QUEEN:  return 0x2655;
        case PieceType::WHITE_KING:   return 0x2654;
        case PieceType::BLACK_PAWN:   return 0x265F;
        case PieceType::BLACK_ROOK:   return 0x265C;
        case PieceType::BLACK_KNIGHT: return 0x265E;
        case PieceType::BLACK_BISHOP: return 0x265D;
        case PieceType::BLACK_QUEEN:  return 0x265B;
        case PieceType::BLACK_KING:   return 0x265A;
        default:                      return 0;
    }
}