#include "menu.h"
#include <iostream>
#include <string>
#include "../board/board.cc"
#include "../player/player.cc"
using namespace std;

Menu::Menu() : player1Wins(0), player2Wins(0), 
    player1Name("Player 1"), player2Name("Player 2") {}

void Menu::displayTitle() {
    cout << "\n"
         << "====================================\n"
         << "  ____    _  _____ _____ _     _____ \n"
         << " | __ )  / \\|_   _|_   _| |   | ____|\n"
         << " |  _ \\ / _ \\ | |   | | | |   |  _|  \n"
         << " | |_) / ___ \\| |   | | | |___| |___ \n"
         << " |____/_/   \\_\\_|   |_| |_____|_____|\n"
         << " ____  _   _ ___ ____  ____  \n"
         << "/ ___|| | | |_ _|  _ \\/ ___| \n"
         << "\\___ \\| |_| || || |_) \\___ \\ \n"
         << " ___) |  _  || ||  __/ ___) |\n"
         << "|____/|_| |_|___|_|   |____/ \n"
         << "====================================\n"
         << "\n";
}

void Menu::displayMainMenu() {
    system("cls");
    displayTitle();
    cout << "1. Pojedynczy pojedynek\n";
    cout << "2. Ciagla rozgrywka\n";
    cout << "Wybierz tryb gry (1-2): ";
    
    int choice;
    cin >> choice;
    
    if (choice == 1) {
        startGame();
    } else if (choice == 2) {
        continuousGame();
    }
}

void Menu::startGame() {
    cout << "\nPodaj nazwe dla gracza 1: ";
    cin.ignore();
    getline(cin, player1Name);
    
    cout << "Podaj nazwe dla gracza 2: ";
    getline(cin, player2Name);
    
    Board board1;
    Board board2;
    Player player1(board1, 1);
    Player player2(board2, 2);
    
    player1.setPlayerName(player1Name);
    player2.setPlayerName(player2Name);
    
    cout << player1Name << ": Postaw swoje statki." << endl;
    player1.placeShips();
    cout << player2Name << ": Postaw swoje statki." << endl;
    player2.placeShips();
    
    bool gameOn = true;
    while (gameOn) {
        cout << "Tura gracza: \n" << player1Name << ".\n";
        player1.displayBoards();
        player1.attack(player2);
        if (player2.hasLost()) {
            cout << player1Name << " wygrywa!\n";
            player1Wins++;
            gameOn = false;
            displayRestartMenuSingleGame();
        }

        cout << "Tura gracza: \n" << player2Name << ".\n";
        player2.displayBoards();
        player2.attack(player1);
        if (player1.hasLost()) {
            cout << player2Name << " wygrywa!\n";
            player2Wins++;
            gameOn = false;
            displayRestartMenuSingleGame();
        }
    }
}

void Menu::displayScore() {
    cout << "\n=== WYNIKI ===\n";
    cout <<"Ilosc zwyciestw gracza "<< player1Name << ": " << player1Wins << "\n";
    cout <<"Ilosc zwyciestw gracza "<< player2Name << ": " << player2Wins << "\n";
}

void Menu::displayRestartMenu() {
    displayScore();
    cout << "\n1. Zagraj ponownie\n";
    cout << "2. Zakoncz gre\n";
    cout << "Wybierz opcje (1-2): ";
    
    int choice;
    cin >> choice;
    
    if (choice == 1) {
        continuousGame();
    }
}
void Menu::displayRestartMenuSingleGame() {
    cout << "1. Wroc do menu\n";
    cout << "2. Wyjdz z gry\n";
    
    int choice;
    cin >> choice;
    if (choice == 1) {
        displayMainMenu();
    }
    if (choice ==2){
        exit(0);
    }
}

void Menu::continuousGame() {
    do {
        startGame();
        displayRestartMenu();
    } while (false); // Loop is controlled by displayRestartMenu recursion
}
