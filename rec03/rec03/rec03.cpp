//
//  rec03.cpp
//  rec03
//
//  Created by Kevin J. Zheng on 9/20/18.
//  Copyright © 2018 Kevin J. Zheng. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
using namespace std;

struct Tile {
    int neighborBombs;
    bool bomb;
    bool visible;
};

class Minesweeper {
private:
    const int DIM = 10;
    const int BOMB_PROB = 10;
    int numBombs = 0;
    vector<vector<Tile>> Board;
public:
    Minesweeper() {
        srand (time(NULL));
        for (int i = 0; i < DIM; i++) {
            vector<Tile> Row;
            for (int j = 0; j < DIM; j++) {
                Tile newTile;
                newTile.visible = false;
                // randomized bomb placements
                if ((rand() % 100) < BOMB_PROB) {
                    newTile.bomb = true;
                    numBombs++;
                }
                else {
                    newTile.bomb = false;
                }
                Row.push_back(newTile);
            }
            Board.push_back(Row);
        }
        // counts neighbors and assigns neighboring bombs
        for (int i = 0; i < Board.size(); ++i) {
            for (int j = 0; j < Board.size(); ++j) {
                int neighbors = 0;
                if (Board[i][j].bomb == false) {
                    if (validRow(i-1) && validCol(j-1)){
                        if (Board[i-1][j-1].bomb == true) {
                            neighbors++;
                        }
                    }
                    if (validRow(i-1)) {
                        if (Board[i-1][j].bomb == true){
                            neighbors++;
                        }
                    }
                    if (validRow(i-1) && validCol(j+1)) {
                        if (Board[i-1][j+1].bomb == true){
                            neighbors++;
                        }
                    }
                    if (validRow(i+1) && validCol(j-1)) {
                        if (Board[i+1][j-1].bomb == true) {
                            neighbors++;
                        }
                    }
                    if (validRow(i+1)) {
                        if (Board[i+1][j].bomb == true) {
                            neighbors++;
                        }
                    }
                    if (validRow(i+1) && validCol(j+1)) {
                        if (Board[i+1][j+1].bomb == true) {
                            neighbors++;
                        }
                    }
                    if (validCol(j-1)) {
                        if (Board[i][j-1].bomb == true) {
                            neighbors++;
                        }
                    }
                    if (validCol(j+1)) {
                        if (Board[i][j+1].bomb == true) {
                            neighbors++;
                        }
                    }
                    Board[i][j].neighborBombs = neighbors;
                }
            }
        }
    };
    
    void display(bool dead) const {
        // * bomb
        // numbers neighbor
        // - empty
        // # not visible
        if (dead == false) {
//            adds x coordinates for easier viewing
//            cout << "    ";
//            for (int k = 0; k < DIM; k++) {
//                cout << k << ' ';
//            }
//            cout << endl;
//            cout << "    ";
//            for (int k = 0; k < DIM; k++) {
//                cout << "- ";
//            }
//            cout << endl;
            for (int i = 0; i < DIM; i++) {
//                adds y coordinates for easier viewing
//                cout << i << " | ";
                for (int j = 0; j < DIM; j++) {
                    if (isVisible(i,j) == false) {
                        cout << "# ";
                    }
                    else if (Board[i][j].bomb == true) {
                        cout << "* ";
                    }
                    else if (Board[i][j].bomb == false) {
                        if (Board[i][j].neighborBombs != 0) {
                            cout << Board[i][j].neighborBombs << ' ';
                        }
                        else {
                            cout << "- ";
                        }
                    }
                }
                cout << endl;
            }
        }
        // reveal the board
        else {
//            adds x coordinates for easier viewing
//            cout << "    ";
//            for (int k = 0; k < DIM; k++) {
//                cout << k << ' ';
//            }
//            cout << endl;
//            cout << "    ";
//            for (int k = 0; k < DIM; k++) {
//                cout << "- ";
//            }
//            cout << endl;
            for (int i = 0; i < DIM; i++) {
//                adds y coordinates for easier viewing
//                cout << i << " | ";
                for (int j = 0; j < DIM; j++) {
                    if (Board[i][j].bomb == true) {
                        cout << "* ";
                    }
                    else if (Board[i][j].bomb == false) {
                        if (Board[i][j].neighborBombs != 0) {
                            cout << Board[i][j].neighborBombs << ' ';
                        }
                        else {
                            cout << "- ";
                        }
                    }
                }
                cout << endl;
            }
        }
    };
    
    bool done() const {
        int unseen = 0;
        for (int i = 0; i < DIM; i++) {
            for (int j = 0; j < DIM; j++) {
                if (Board[i][j].visible == false) {
                    unseen++;
                }
            }
        }
        if (unseen == numBombs) {
            return true;
        }
        return false;
    };
    
    bool validRow(int row) const {
        if (row < 0 || row >= DIM) {
            return false;
        }
        return true;
    };
    
    bool validCol(int col) const {
        if (col < 0 || col >= DIM) {
            return false;
        }
        return true;
    };
    
    bool isVisible(int row, int col) const {
        if (Board[row][col].visible == true) {
            return true;
        }
        return false;
    };
    
    bool play(int row, int col) {
        // base case: if bomb found, end the game
        if (Board[row][col].bomb) {
            return false;
        }
        // if tile has bombs nearby, display
        else if (Board[row][col].neighborBombs > 0){
            Board[row][col].visible = true;
        }
        // if tile has no neighboring bombs check neighboring tiles
        else if (Board[row][col].neighborBombs == 0) {
            Board[row][col].visible = true;
            if (validCol(col) && validRow(row+1)) {
                // if the tile hasn't been visited yet call play on that tile
                if (Board[row+1][col].visible == false) {
                    play((row+1),(col));
                    // mark tile as visited so it won't check this tile again
                    Board[row+1][col].visible = true;
                }
                Board[row+1][col].visible = true;
            }
            if (validCol(col+1) && validRow(row)) {
                if (Board[row][col+1].visible == false) {
                    play((row),(col+1));
                    Board[row][col+1].visible = true;
                }
                Board[row][col+1].visible = true;
            }
            if (validCol(col) && validRow(row-1)) {
                if (Board[row-1][col].visible == false) {
                    play((row-1),(col));
                    Board[row-1][col].visible = true;
                }
                Board[row-1][col].visible = true;
            }
            if (validCol(col-1) && validRow(row)) {
                if (Board[row][col-1].visible == false) {
                    play((row),(col-1));
                    Board[row][col-1].visible = true;
                }
                Board[row][col-1].visible = true;
            }
            if (validRow(row-1) && validCol(col-1)) {
                if (Board[row-1][col-1].visible == false) {
                    play((row-1),(col-1));
                    Board[row-1][col-1].visible = true;
                }
                Board[row-1][col-1].visible = true;
            }
            if (validRow(row-1) && validCol(col+1)) {
                if (Board[row-1][col+1].visible == false) {
                    play((row-1),(col+1));
                    Board[row-1][col+1].visible = true;
                }
                Board[row-1][col+1].visible = true;
            }
            if (validRow(row+1) && validCol(col-1)) {
                if (Board[row+1][col-1].visible == false) {
                    play((row+1),(col-1));
                    Board[row+1][col-1].visible = true;
                }
                Board[row+1][col-1].visible = true;
            }
            if (validRow(row+1) && validCol(col+1)) {
                if (Board[row+1][col+1].visible == false) {
                    play((row+1),(col+1));
                    Board[row+1][col+1].visible = true;
                }
                Board[row+1][col+1].visible = true;
            }
        }
        return true;
    }
};

int main() {
    Minesweeper sweeper;
    // Continue until only invisible cells are bombs
    while (!sweeper.done()) {
        sweeper.display(false); // display board without bombs
        int row_sel = -1, col_sel = -1;
        while (row_sel == -1) {
            // Get a valid move
            int row;
            int col;
            cout << "row? ";
            cin >> row;
            if (!sweeper.validRow(row)) {
                cout << "Row out of bounds\n";
                continue;
            }
            cout << "col? ";
            cin >> col;
            if (!sweeper.validCol(col)) {
                cout << "Column out of bounds\n";
                continue;
            }
            if (sweeper.isVisible(row,col)) {
                cout << "Square already visible\n";
                continue;
            }
            row_sel = row;
            col_sel = col;
        }
        // Set selected square to be visible. May effect other cells.
        if (!sweeper.play(row_sel,col_sel)) {
            cout << "Sorry, you died..\n";
            sweeper.display(true); // Final board with bombs shown
            exit(0);
        }
    }
    // Ah! All invisible cells are bombs, so you won!
    cout << "You won!!!!\n";
    sweeper.display(true); // Final board with bombs shown
}
