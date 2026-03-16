#include <iostream>
#include <fcntl.h>
#include <io.h>
#include <cmath>
#include <functional>
#include <unordered_map>
#include "ChessMoves.h"


enum Pieces {
    None = 0,
    B_Pawn = L'\u2659',
    B_Rook = L'\u2656',
    B_Knight = L'\u2658',
    B_Bishop = L'\u2657',
    B_Queen = L'\u2655',
    B_King = L'\u2654',
    W_Pawn = B_Pawn + 6,
    W_Rook = B_Rook + 6,
    W_Knight = B_Knight + 6,
    W_Bishop = B_Bishop + 6,
    W_Queen = B_Queen + 6,
    W_King = B_King + 6
};

Pieces board[8][8] = {
    {B_Rook, B_Knight, B_Bishop, B_Queen, B_King, B_Bishop, B_Knight, B_Rook},
    {B_Pawn, B_Pawn, B_Pawn, B_Pawn, B_Pawn, B_Pawn, B_Pawn, B_Pawn},
    {None, None, None, None, None, None, None, None},
    {None, None, None, None, None, None, None, None},
    {None, None, None, None, None, None, None, None},
    {None, None, None, None, None, None, None, None},
    {W_Pawn, W_Pawn, W_Pawn, W_Pawn, W_Pawn, W_Pawn, W_Pawn, W_Pawn},
    {W_Rook, W_Knight, W_Bishop, W_Queen, W_King, W_Bishop, W_Knight, W_Rook}
};

static auto sep = L'\u2502';
static auto empty = L'\uFF0D';

void drawBoard() {
    std::wcout << '\n';
    for(const auto &i : board){
        std::wcout << sep;
        for(const auto y : i) {
            if (y != None)
                std::wcout << static_cast<wchar_t>(y);
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

Pieces checkBoard(const int row, const int col) {
    if (row < 0 || row > 7 || col < 0 || col > 7) return None;
    return board[row][col];
}

void movePiece(const std::string& actual, const std::string& move) {
    std::pair<int, int> from = translateToIndex(actual);
    std::pair<int, int> to = translateToIndex(move);

    board[to.first][to.second] = board[from.first][from.second];
    board[from.first][from.second] = None;
}

bool isValidCoordinate(const std::string& coor) {
    std::pair<int, int> index = translateToIndex(coor);
    return index.first != -1 && index.second != -1;
}

bool isBlack(Pieces piece) {
    return piece != None && piece < 9818;
}

int main() {
    _setmode(_fileno(stdout), _O_U16TEXT);
    bool blackPlaying = false;
    bool endgame = false;
    std::pair<int,int> start;
    std::pair<int, int> end;
    ChessMoves<Pieces> chessMoves(start, end, board);

    std::unordered_map<int, std::function<bool()>> moveValidators = {
        {B_Rook,   [&]() { return chessMoves.Rook();   }},
        {W_Rook,   [&]() { return chessMoves.Rook();   }},
        {B_Bishop, [&]() { return chessMoves.Bishop(); }},
        {W_Bishop, [&]() { return chessMoves.Bishop(); }},
        {B_Queen,  [&]() { return chessMoves.Queen();  }},
        {W_Queen,  [&]() { return chessMoves.Queen();  }},
       {B_Knight, [&]() { return chessMoves.Knight(); }},
        {W_Knight, [&]() { return chessMoves.Knight(); }},
        {B_King,   [&]() { return chessMoves.King();   }},
        {W_King,   [&]() { return chessMoves.King();   }},
        {B_Pawn,   [&]() { return chessMoves.Pawn(true);}},
        {W_Pawn,   [&]() { return chessMoves.Pawn(false);}},
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
                if (checkBoard(start.first, start.second) == None) {
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
                if (checkBoard(end.first, end.second) != None && isBlack(checkBoard(end.first, end.second)) == blackPlaying) {
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

        Pieces moving = checkBoard(start.first, start.second);
        auto it = moveValidators.find(static_cast<int>(moving));
        if (it != moveValidators.end() && it->second()) {
            if (checkBoard(end.first, end.second) == B_King || checkBoard(end.first, end.second) == W_King) endgame = true;
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