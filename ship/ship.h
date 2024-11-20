#ifndef SHIP_H
#define SHIP_H
#include <vector>
#include <utility>

class Ship {
public:
    Ship(int length);
    void addPosition(int y, int x);
    bool isHit(int y, int x) const;
    bool isSunk() const;
    int getLength() const;
    const std::vector<std::pair<int, int>>& getPositions() const;

private:
    int length;
    std::vector<std::pair<int, int>> positions;
    std::vector<bool> hitStatus;
};
#endif