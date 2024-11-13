#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <vector>
#include "../ship/ship.h"
#include "../board/board.h"
using namespace std;
class Player
{
    private:
    Board ownBoard;
    Board targetBoard;
    int playerNumber;
    string playerName;
    public:
    vector<Ship> ships;
    Player(Board &ownBoard, int playerNumber);
    void placeShips();
    bool attack(Player &opponent);
    bool hasLost();
    void displayBoards();
    Board& getBoard();
    void setPlayerName(const string &name);
};

#endif