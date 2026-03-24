#pragma once
#include <cstdint>
#include <stdexcept>
constexpr size_t PieceTypeCount = 12;



enum class PieceType {
    WHITE_PAWN = 0,
    WHITE_ROOK = 1,
    WHITE_KNIGHT = 2,
    WHITE_BISHOP = 3,
    WHITE_QUEEN = 4,
    WHITE_KING = 5,
    
    BLACK_PAWN = 6,
    BLACK_ROOK = 7,
    BLACK_KNIGHT = 8,
    BLACK_BISHOP = 9,
    BLACK_QUEEN = 10,
    BLACK_KING = 11
};

constexpr wchar_t getUnicode(const PieceType piece) {
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

        default:                        throw std::runtime_error("skill issue @PieceType::getUnicode");
    }
}