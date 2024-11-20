#ifndef BOARD_H
#define BOARD_H
#include "../ship/ship.cc"
#include <vector>

class Board {
public:
    Board();
    void displayBoard(bool hideShips) const;
    bool placeShip(int y, int x, int size, char direction);
    bool isHit(int y, int x) const;
    bool isAttacked(int y, int x) const;
    void markHit(int y, int x);
    void markMiss(int y, int x);
    bool allShipsSunk() const;
    bool isShipSunk(int y, int x);
    bool isShip(int y, int x) const;
    bool isValidPosition(int y, int x) const;
    void markSurroundingCells(int y, int x);

private:
    static const int BOARD_SIZE = 10;
    char board[BOARD_SIZE + 1][BOARD_SIZE + 1];
    std::vector<Ship> ships;
    bool canPlaceShip(int y, int x, int size, char direction) const;
};

#endif
