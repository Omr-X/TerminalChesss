#include <iostream>
#include <fcntl.h>
#include <io.h>
#include <cmath>
#include <functional>
#include <unordered_map>
#include "ChessMoves.h"
#include "Pieces/PieceType.h"


PieceType board[8][8] = {
    {PieceType::BLACK_ROOK, PieceType::BLACK_KNIGHT, PieceType::BLACK_BISHOP, PieceType::BLACK_QUEEN, PieceType::BLACK_KING, PieceType::BLACK_BISHOP, PieceType::BLACK_KNIGHT, PieceType::BLACK_ROOK},
    {PieceType::BLACK_PAWN, PieceType::BLACK_PAWN, PieceType::BLACK_PAWN, PieceType::BLACK_PAWN, PieceType::BLACK_PAWN, PieceType::BLACK_PAWN, PieceType::BLACK_PAWN, PieceType::BLACK_PAWN},
    {PieceType::NONE, PieceType::NONE, PieceType::NONE, PieceType::NONE, PieceType::NONE, PieceType::NONE, PieceType::NONE, PieceType::NONE},
    {PieceType::NONE, PieceType::NONE, PieceType::NONE, PieceType::NONE, PieceType::NONE, PieceType::NONE, PieceType::NONE, PieceType::NONE},
    {PieceType::NONE, PieceType::NONE, PieceType::NONE, PieceType::NONE, PieceType::NONE, PieceType::NONE, PieceType::NONE, PieceType::NONE},
    {PieceType::NONE, PieceType::NONE, PieceType::NONE, PieceType::NONE, PieceType::NONE, PieceType::NONE, PieceType::NONE, PieceType::NONE},
    {PieceType::WHITE_PAWN, PieceType::WHITE_PAWN, PieceType::WHITE_PAWN, PieceType::WHITE_PAWN, PieceType::WHITE_PAWN, PieceType::WHITE_PAWN, PieceType::WHITE_PAWN, PieceType::WHITE_PAWN},
    {PieceType::WHITE_ROOK, PieceType::WHITE_KNIGHT, PieceType::WHITE_BISHOP, PieceType::WHITE_QUEEN, PieceType::WHITE_KING, PieceType::WHITE_BISHOP, PieceType::WHITE_KNIGHT, PieceType::WHITE_ROOK}
};

static auto sep = L'\u2502';
static auto empty = L'\uFF0D';

void drawBoard() {
    std::wcout << '\n';
    for(const auto &i : board){
        std::wcout << sep;
        for(const auto y : i) {
            if (y != PieceType::NONE)
                std::wcout << static_cast<wchar_t>(getUnicode(y));
            else
                std::wcout << empty;
            std::wcout << sep;
        }
        std::wcout << L"\n";
    }
    std::wcout << std::endl;
}

std::pair<int, int> translateToIndex(const std::string& coor) {
    if (coor.length() != 2) return std::pair<int, int>(-1, -1);
    char col = std::toupper(coor.at(0));
    if (!(col >= 'A' && col <= 'H')) return std::pair<int, int>(-1, -1);
    if (!(coor.at(1) >= '1' && coor.at(1) <= '8')) return std::pair<int, int>(-1, -1);

    return std::pair<int, int>(std::abs(coor.at(1) - 56), col - 65);
}

PieceType checkBoard(const int row, const int col) {
    if (row < 0 || row > 7 || col < 0 || col > 7) return PieceType::NONE;
    return board[row][col];
}

void movePiece(const std::string& actual, const std::string& move) {
    std::pair<int, int> from = translateToIndex(actual);
    std::pair<int, int> to = translateToIndex(move);

    board[to.first][to.second] = board[from.first][from.second];
    board[from.first][from.second] = PieceType::NONE;
}

bool isValidCoordinate(const std::string& coor) {
    std::pair<int, int> index = translateToIndex(coor);
    return index.first != -1 && index.second != -1;
}

bool isBlack(PieceType piece) {
    return piece != PieceType::NONE && piece > PieceType::WHITE_KING;
}

int main() {
    _setmode(_fileno(stdout), _O_U16TEXT);
    bool blackPlaying = false;
    bool endgame = false;
    std::pair<int,int> start;
    std::pair<int, int> end;
    ChessMoves<PieceType> chessMoves(start, end, board);

    std::unordered_map<int, std::function<bool()>> moveValidators = {
        {static_cast<int>(PieceType::BLACK_ROOK),   [&]() { return chessMoves.Rook();        }},
        {static_cast<int>(PieceType::WHITE_ROOK),   [&]() { return chessMoves.Rook();        }},
        {static_cast<int>(PieceType::BLACK_BISHOP), [&]() { return chessMoves.Bishop();      }},
        {static_cast<int>(PieceType::WHITE_BISHOP), [&]() { return chessMoves.Bishop();      }},
        {static_cast<int>(PieceType::BLACK_QUEEN),  [&]() { return chessMoves.Queen();       }},
        {static_cast<int>(PieceType::WHITE_QUEEN),  [&]() { return chessMoves.Queen();       }},
        {static_cast<int>(PieceType::BLACK_KNIGHT), [&]() { return chessMoves.Knight();      }},
        {static_cast<int>(PieceType::WHITE_KNIGHT), [&]() { return chessMoves.Knight();      }},
        {static_cast<int>(PieceType::BLACK_KING),   [&]() { return chessMoves.King();        }},
        {static_cast<int>(PieceType::WHITE_KING),   [&]() { return chessMoves.King();        }},
        {static_cast<int>(PieceType::BLACK_PAWN),   [&]() { return chessMoves.Pawn(true);}},
        {static_cast<int>(PieceType::WHITE_PAWN),   [&]() { return chessMoves.Pawn(false);}},
    };

    do {
        drawBoard();
        std::string init;
        std::string final;

        if (blackPlaying) std::wcout << L"Black move" << L"\n";
        else std::wcout << L"White move \n";

        while (true) {
            std::wcout << L"Piece you want to move : ";
            std::cin >> init;

            if (isValidCoordinate(init)) {
                start = translateToIndex(init);
                if (checkBoard(start.first, start.second) == PieceType::NONE) {
                    std::wcout << L"There is no piece at that coordinate. Please try again.\n";
                    continue;
                }
                if (isBlack(checkBoard(start.first, start.second)) != blackPlaying) {
                    std::wcout << L"This isn't your piece. Please enter a valid square. \n";
                    continue;
                }
                break;
            }
            std::wcout << L"Invalid coordinate. Please enter a valid square (ex: A5).\n";
        }

        while (true) {
            std::wcout << L"Where do you want to move it : ";
            std::cin >> final;
            if (isValidCoordinate(final)) {
                end = translateToIndex(final);
                if (checkBoard(end.first, end.second) != PieceType::NONE && isBlack(checkBoard(end.first, end.second)) == blackPlaying) {
                    std::wcout << L"You cannot move to a square occupied by your own piece. Please try again. \n";
                    continue;
                }
                if (start == end) {
                    std::wcout << L"You haven't move your piece. Please try again. \n";
                    continue;
                }
                break;
            }
            std::wcout << L"Invalid coordinate. Please enter a valid square (ex: A5).\n";
        }

        PieceType moving = checkBoard(start.first, start.second);
        auto it = moveValidators.find(static_cast<int>(moving));
        if (it != moveValidators.end() && it->second()) {
            if (checkBoard(end.first, end.second) == PieceType::BLACK_KING || checkBoard(end.first, end.second) == PieceType::WHITE_KING) endgame = true;
            movePiece(init, final);
            blackPlaying = !blackPlaying;
        }
        else {
            std::wcout << "Your move is illegal. Please try again. \n";
        }
    } while (!endgame);

    if (blackPlaying) std::wcout << L"White wins!\n";
    else std::wcout << L"Black wins!\n";
    return 0;
}