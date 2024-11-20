#include "player.h"
#include "../menu/menu.h"
#include <limits>
#include <stdlib.h>
using namespace std;

Player::Player(Board& ownBoard, int playerNumber) 
    : ownBoard(ownBoard), targetBoard(), playerNumber(playerNumber) {
}

void clearScreen() {
    system("cls");
}

void Player::placeShips() {
    int sizes[] = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};
    int x, y;
    char direction;
    
    for(int size : sizes) {
        clearScreen();
        cout << "\n=== Umieszczanie statku o dlugosci " << size << " ===" << endl << endl;
        cout << "Plansza gracza " << playerName << ":\n";
        ownBoard.displayBoard(false);
        
        while(true) {
            bool validInput = false;
            
            // Get Y coordinate
            while (!validInput) {
                cout << "\nPodaj wspolrzedne y: ";
                if (!(cin >> y)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Nieprawidlowe wspolrzedne! Podaj liczbe od 1 do 10." << endl;
                    continue;
                }
                if (y < 1 || y > 10) {
                    cout << "Wspolrzedne poza plansza! Podaj liczbe od 1 do 10." << endl;
                    continue;
                }
                validInput = true;
            }
            
            // Get X coordinate
            validInput = false;
            while (!validInput) {
                cout << "Podaj wspolrzedne x: ";
                if (!(cin >> x)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Nieprawidlowe wspolrzedne! Podaj liczbe od 1 do 10." << endl;
                    continue;
                }
                if (x < 1 || x > 10) {
                    cout << "Wspolrzedne poza plansza! Podaj liczbe od 1 do 10." << endl;
                    continue;
                }
                validInput = true;
            }
            
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            

            validInput = false;
            while (!validInput) {
                cout << "Podaj kierunek (U - w gore, D - w dol, L - w lewo, R - w prawo): ";
                if (!(cin >> direction)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Nieprawidlowy kierunek! Uzyj U, D, L lub R." << endl;
                    continue;
                }
                
                direction = toupper(direction);
                if (direction != 'U' && direction != 'D' && direction != 'L' && direction != 'R') {
                    cout << "Nieprawidlowy kierunek! Uzyj U, D, L lub R." << endl;
                    continue;
                }
                validInput = true;
            }
            
            // Clear any remaining characters
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
            if(ownBoard.placeShip(y, x, size, direction))
                break;
                
            cout << "\nNie mozna umiescic statku w tym miejscu. Sprobuj ponownie." << endl;
        }
    }
}

bool Player::attack(Player &opponent) {
    bool gameWon = false;
    bool hit = false;
    bool validAttack = false;
    
    do {
        clearScreen();
        cout << "\n=== Ruch gracza " << playerName << " ===" << endl << endl;
        displayBoards();
        
        int x, y;
        bool validInput = false;
        
        while (!validInput) {
            cout << "\nPodaj wspolrzedne ataku:\ny: ";
            if (!(cin >> y)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Nieprawidlowe wspolrzedne! Podaj liczbe od 1 do 10." << endl;
                continue;
            }
            
            cout << "x: ";
            if (!(cin >> x)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Nieprawidlowe wspolrzedne! Podaj liczbe od 1 do 10." << endl;
                continue;
            }
            
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
            if (x < 1 || x > 10 || y < 1 || y > 10) {
                cout << "Wspolrzedne poza plansza! Podaj liczby od 1 do 10." << endl;
                continue;
            }
            
            validInput = true;
        }
        
        if (targetBoard.isAttacked(y, x)) {
            cout << "\nJuz atakowales to pole! Sprobuj ponownie." << endl;
            cout << "\nNacisnij ENTER, aby kontynuowac...";
            cin.get();
            continue;
        }
        
        validAttack = true;
        hit = opponent.ownBoard.isHit(y, x);
        if(hit) {
            opponent.ownBoard.markHit(y, x);
            targetBoard.markHit(y, x);
            clearScreen();
            
            if (opponent.ownBoard.isShipSunk(y, x)) {
                cout << "\n!!! TRAFIONY ZATOPIONY !!!" << endl;
                for(int dy = -1; dy <= 1; dy++) {
                    for(int dx = -1; dx <= 1; dx++) {
                        int newY = y + dy;
                        int newX = x + dx;
                        if (opponent.ownBoard.isValidPosition(newY, newX) && 
                            !opponent.ownBoard.isShip(newY, newX)) {
                            targetBoard.markMiss(newY, newX);
                        }
                    }
                }
                opponent.ownBoard.markSurroundingCells(y, x);
                targetBoard.markSurroundingCells(y, x);
            } else {
                cout << "\n!!! TRAFIONY !!!" << endl;
            }
            
            if (opponent.hasLost()) {
                gameWon = true;
                break;
            }
            cout << "Dostajesz dodatkowy strzal!" << endl;
        } else {
            opponent.ownBoard.markMiss(y, x);
            targetBoard.markMiss(y, x);
            clearScreen();
            cout << "\n--- Pudlo ---" << endl;
        }
        
        displayBoards();
        
        cout << "\nNacisnij ENTER, aby kontynuowac...";
        cin.get();
        
    } while ((hit || !validAttack) && !gameWon);
    
    return gameWon;
}

bool Player::hasLost() {
    return ownBoard.allShipsSunk();
}

void Player::displayBoards() {
    cout << "Twoja plansza:\n";
    ownBoard.displayBoard(false);
    cout << "\nPlansza przeciwnika:\n";
    targetBoard.displayBoard(true);
}

void Player::setPlayerName(const string &name) {
    this->playerName = name;
}
