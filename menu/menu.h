#ifndef MENU_H
#define MENU_H
#include <iostream>
using namespace std;
class Menu {
public:
    Menu();
    void displayMainMenu();
    void startGame();
    void continuousGame();
    void displayRestartMenu();
    void displayRestartMenuSingleGame();
private:
    int player1Wins;
    int player2Wins;
    string player1Name;
    string player2Name;
    void displayTitle();
    void displayScore();
};

#endif
