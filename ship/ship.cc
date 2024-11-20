#pragma once
#include "ship.h"

Ship::Ship(int length) : length(length) {
    hitStatus.resize(length, false);
}

void Ship::addPosition(int y, int x) {
    positions.push_back({y, x});
}

bool Ship::isHit(int y, int x) const {
    for (size_t i = 0; i < positions.size(); i++) {
        if (positions[i].first == y && positions[i].second == x) {
            return true;
        }
    }
    return false;
}

bool Ship::isSunk() const {
    for (bool hit : hitStatus) {
        if (!hit) return false;
    }
    return true;
}

int Ship::getLength() const {
    return length;
}

const std::vector<std::pair<int, int>>& Ship::getPositions() const {
    return positions;
}