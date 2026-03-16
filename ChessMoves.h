#ifndef CHESSMOVES_H
#define CHESSMOVES_H

#include <utility> // For std::pair
#include <cmath>   // For std::abs

template <typename T>
class ChessMoves {
private:
    const std::pair<int, int>& start;
    const std::pair<int, int>& end;
    T (&board)[8][8];

public:
    ChessMoves(const std::pair<int, int>& initPos, const std::pair<int, int>& finalPos, T(&boardRef)[8][8])
    : start(initPos), end(finalPos), board(boardRef) {}

    int deltaRow() { return start.first - end.first; }
    int deltaCol() { return start.second - end.second; }

    bool Rook() {
        if (deltaRow() != 0 && deltaCol() != 0) return false;

        int stepR = (deltaRow() == 0) ? 0 : (end.first > start.first ? 1 : -1);
        int stepC = (deltaCol() == 0) ? 0 : (end.second > start.second ? 1 : -1);
        int currR = start.first + stepR;
        int currC = start.second + stepC;

        while (currR != end.first || currC != end.second) {
            if (static_cast<int>(board[currR][currC]) != 0) return false;
            currR += stepR;
            currC += stepC;
        }
        return true;
    }

    bool Bishop() {
        if (std::abs(deltaCol()) != std::abs(deltaRow())) return false;

        int stepR = (end.first > start.first ? 1 : -1);
        int stepC = (end.second > start.second ? 1 : -1);
        int currR = start.first + stepR;
        int currC = start.second + stepC;

        while (currR != end.first || currC != end.second) {
            if (static_cast<int>(board[currR][currC]) != 0) return false;
            currR += stepR;
            currC += stepC;
        }
        return true;
    }

    bool Queen() {
        return Rook() || Bishop();
    }
};

#endif