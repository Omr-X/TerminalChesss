#pragma once

#include <cstdint>
#include <array>

#include "../Pieces/PieceType.h"

//non mutable
class Board {
public:
    const std::array<uint64_t, PieceTypeCount> pieces;

    Board(const std::array<uint64_t, PieceTypeCount>& pieces) :
        pieces{pieces}
    {};
    ~Board();

    const uint64_t getWhitePieces() const {
        return pieces[static_cast<int>(PieceType::WHITE_BISHOP)]
        | pieces[static_cast<int>(PieceType::WHITE_KNIGHT)]
        | pieces[static_cast<int>(PieceType::WHITE_KING)]
        | pieces[static_cast<int>(PieceType::WHITE_PAWN)]
        | pieces[static_cast<int>(PieceType::WHITE_QUEEN)]
        | pieces[static_cast<int>(PieceType::WHITE_ROOK)];
    }

    const uint64_t getBlackPieces() const {
        return pieces[static_cast<int>(PieceType::BLACK_BISHOP)]
        | pieces[static_cast<int>(PieceType::BLACK_KNIGHT)]
        | pieces[static_cast<int>(PieceType::BLACK_KING)]
        | pieces[static_cast<int>(PieceType::BLACK_PAWN)]
        | pieces[static_cast<int>(PieceType::BLACK_QUEEN)]
        | pieces[static_cast<int>(PieceType::BLACK_ROOK)];
    }

    const uint64_t getAllPieces() const {
        return getWhitePieces() | getBlackPieces();
    }
};
