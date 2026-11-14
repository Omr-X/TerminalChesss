#include <iostream>
#include <fcntl.h>
#include <io.h>
#include <cmath>
#include <functional>
#include <unordered_map>
#include <windows.h>
#include "ChessMoves.h"

const int width = 20;
const int height = 20;

const wchar_t* ORANGE = L"\033[92m";
const wchar_t* WHITE   = L"\033[97m";
const wchar_t* RESET = L"\033[0m";

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

constexpr wchar_t sep = L'\u2502';
constexpr wchar_t empty = L'\uFF0D';

void drawBoardHighlight(std::pair<int, int> highlight){
    std::wcout << "\033[H\033[J"; // Clear the console screen

    for (int i = 0; i < 17; i++) {

           if(i % 2 == 1) std::wcout << 8 - (i / 2) << L" ";
            int row = i / 2;

        for (int j = 0; j < 8; j++) {

           if (i % 2 == 0) {
                if (j == 0) {
                    bool lineHl = (i == 2 * highlight.first || i == 2 * highlight.first + 2);
                    std::wcout << L"   ";
                    for (int x = 0; x <= 40; x++) {
                        bool hl = lineHl && x >= 5 * highlight.second && x <= 5 * (highlight.second + 1);
                        std::wcout << (hl ? ORANGE : WHITE) << L"\u2500";
                    }
                    std::wcout << RESET;
                }
                continue;                                
            }

            bool hl = (row == highlight.first) && (j >= highlight.second && j <= highlight.second + 1);
            std::wcout << L" "  << (hl ? ORANGE : WHITE) << sep << RESET << L" ";
            if (board[row][j] != None)
                std::wcout << static_cast<wchar_t>(board[row][j]) << L" ";
            else
                std::wcout << empty;
        }

        if(i % 2 == 1) std::wcout << L" " << (highlight.first == row ? ORANGE : WHITE) << sep << RESET;
        std::wcout << L"\n";
    }

    std::wcout << L"     A    B    C    D    E    F    G    H\n";

/**
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
    */
}

void drawBoard() {
  drawBoardHighlight(std::pair<int, int>(-1, -1)); 
}

/**
 * Translates a chess coordinate (e.g., "A5") to a pair of indices (row, column) for the board array.
 * the row start from 0 to 7 where 0 is the top row (8 in chess notation) and 7 is the bottom row (1 in chess notation).
 * the column start from 0 to 7 where 0 is the leftmost column (A in chess notation) and 7 is the rightmost column (H in chess notation).
 * If the coordinate is invalid, it returns (-1, -1).
 * 
 * @param coor The chess coordinate as a string (e.g., "A5").
 */
std::pair<int, int> translateToIndex(const std::string& coor) {
    if (coor.length() != 2) return std::pair<int, int>(-1, -1);
    char col = std::toupper(coor.at(0));
    if (!(col >= 'A' && col <= 'H')) return std::pair<int, int>(-1, -1);
    if (!(coor.at(1) >= '1' && coor.at(1) <= '8')) return std::pair<int, int>(-1, -1);

    return std::pair<int, int>(std::abs(coor.at(1) - 56), col - 65);
}

/**
 * Returns the piece at the given row and column on the board.
 * If the coordinates are out of bounds, it returns None.
 * 
 * @param row The row index (0-7) of the board.
 * @param col The column index (0-7) of the board.
 */
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

    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(h, &mode);
    SetConsoleMode(h, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

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
            if (!isValidCoordinate(final)) {
              std::wcout << L"Invalid coordinate. Please enter a valid square (ex: A5).\n"; 
              continue;
            }
            
            end = translateToIndex(final);
            if (checkBoard(end.first, end.second) != None && isBlack(checkBoard(end.first, end.second)) == blackPlaying) {
                std::wcout << L"You cannot move to a square occupied by your own piece. Please try again. \n";
                continue;
            }
            if (start == end) {
                std::wcout << L"You haven't move your piece. Please try again. \n";
                continue;
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
                continue;
            }

            break;
        }
    } while (!endgame);

    if (blackPlaying) std::wcout << L"White wins!\n";
    else std::wcout << L"Black wins!\n";
    return 0;
}