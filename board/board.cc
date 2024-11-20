#include "board.h"
#include <iostream>
#include <vector>
#include "../ship/ship.cc"
using namespace std;

Board::Board() {
    for(int i = 1; i <= BOARD_SIZE; i++) {
        for(int j = 1; j <= BOARD_SIZE; j++) {
            board[i][j] = '~';
        }
    }
}

bool Board::isValidPosition(int y, int x) const{
    return y >= 1 && y <= BOARD_SIZE && x >= 1 && x <= BOARD_SIZE;
}

bool Board::isShip(int y, int x) const {
    return isValidPosition(y, x) && (board[y][x] == 'S' || board[y][x] == 'X');
}

void Board::markSurroundingCells(int y, int x) {
    // First, find the entire ship
    vector<pair<int, int>> shipCells;
    shipCells.push_back({y, x});
    
    // Check horizontal
    int tempX = x - 1;
    while (tempX >= 1 && isShip(y, tempX)) {
        shipCells.push_back({y, tempX});
        tempX--;
    }
    tempX = x + 1;
    while (tempX <= BOARD_SIZE && isShip(y, tempX)) {
        shipCells.push_back({y, tempX});
        tempX++;
    }
    
    // Check vertical
    int tempY = y - 1;
    while (tempY >= 1 && isShip(tempY, x)) {
        shipCells.push_back({tempY, x});
        tempY--;
    }
    tempY = y + 1;
    while (tempY <= BOARD_SIZE && isShip(tempY, x)) {
        shipCells.push_back({tempY, x});
        tempY++;
    }
    
    // Mark surrounding cells for each ship cell
    for (const auto& cell : shipCells) {
        for(int dy = -1; dy <= 1; dy++) {
            for(int dx = -1; dx <= 1; dx++) {
                if (dy == 0 && dx == 0) continue;
                
                int newY = cell.first + dy;
                int newX = cell.second + dx;
                if (isValidPosition(newY, newX) && board[newY][newX] == '~') {
                    markMiss(newY, newX);
                }
            }
        }
    }
}

bool Board::isShipSunk(int y, int x) {
    if (!isShip(y, x)) return false;
    
    // Check horizontally
    int startX = x;
    while (startX > 1 && isShip(y, startX-1)) startX--;
    
    int endX = x;
    while (endX < BOARD_SIZE && isShip(y, endX+1)) endX++;
    
    // Check if all horizontal parts are hit
    bool horizontalShip = false;
    if (startX != x || endX != x) {
        horizontalShip = true;
        for (int i = startX; i <= endX; i++) {
            if (board[y][i] == 'S') return false;
        }
        // If ship is sunk, mark surrounding cells
        for (int i = startX; i <= endX; i++) {
            markSurroundingCells(y, i);
        }
        return true;
    }
    
    // Check vertically
    int startY = y;
    while (startY > 1 && isShip(startY-1, x)) startY--;
    
    int endY = y;
    while (endY < BOARD_SIZE && isShip(endY+1, x)) endY++;
    
    // Check if all vertical parts are hit
    for (int i = startY; i <= endY; i++) {
        if (board[i][x] == 'S') return false;
    }
    // If ship is sunk, mark surrounding cells
    for (int i = startY; i <= endY; i++) {
        markSurroundingCells(i, x);
    }
    
    return true;
}

bool Board::canPlaceShip(int y, int x, int size, char direction) const {
    for(int i = 0; i < size; i++) {
        int newY = y, newX = x;
        
        if(direction == 'U') newY = y - i;
        else if(direction == 'D') newY = y + i;
        else if(direction == 'L') newX = x - i;
        else if(direction == 'R') newX = x + i;
        
        if(!isValidPosition(newY, newX)) return false;
        
        for(int dy = -1; dy <= 1; dy++) {
            for(int dx = -1; dx <= 1; dx++) {
                int checkY = newY + dy;
                int checkX = newX + dx;
                if(isValidPosition(checkY, checkX) && isShip(checkY, checkX)) {
                    return false;
                }
            }
        }
    }
    return true;
}

bool Board::placeShip(int y, int x, int size, char direction) {
    if(!canPlaceShip(y, x, size, direction)) return false;
    
    Ship newShip(size);
    for(int i = 0; i < size; i++) {
        int newY = y, newX = x;
        
        if(direction == 'U') newY = y - i;
        else if(direction == 'D') newY = y + i;
        else if(direction == 'L') newX = x - i;
        else if(direction == 'R') newX = x + i;
        
        board[newY][newX] = 'S';
        newShip.addPosition(newY, newX);
    }
    ships.push_back(newShip);
    return true;
}

void Board::displayBoard(bool hideShips) const
{
    cout << "\n     1 2 3 4 5 6 7 8 9 10\n";
    cout << "   +--------------------+\n";
    
    for(int i = 1; i <= 10; i++)
    {
        if (i < 10)
            cout << " " << i << " |";
        else
            cout << i << " |";
            
        for(int j = 1; j <= 10; j++)
        {
            if(hideShips && board[i][j] == 'S')
            {
                cout << " .";
            }
            else
            {
                switch(board[i][j]) {
                    case '~': cout << " ."; break;
                    case 'S': cout << " S"; break;
                    case 'X': cout << " X"; break;
                    case 'O': cout << " O"; break;
                    default:  cout << " " << board[i][j]; break;
                }
            }
        }
        cout << " |" << endl;
    }
    
    cout << "   +--------------------+\n\n";
}

bool Board::isHit(int y, int x) const {
    if (!isValidPosition(y, x)) return false;
    
    for (const Ship& ship : ships) {
        if (ship.isHit(y, x)) {
            return true;
        }
    }
    return false;
}

bool Board::isAttacked(int y, int x) const {
    return isValidPosition(y, x) && (board[y][x] == 'X' || board[y][x] == 'O');
}

void Board::markHit(int y, int x) {
    if(isValidPosition(y, x)) board[y][x] = 'X';
}

void Board::markMiss(int y, int x) {
    if(isValidPosition(y, x)) board[y][x] = 'O';
}

bool Board::allShipsSunk() const {
    for(int i = 1; i <= BOARD_SIZE; i++) {
        for(int j = 1; j <= BOARD_SIZE; j++) {
            if(board[i][j] == 'S') return false;
        }
    }
    return true;
}