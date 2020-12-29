// Copyright: Jared Leach - 2020
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include "seat.h"
#include "inputparse.h"

using std::string;
using std::vector;
using std::cout;
using std::endl;

InputParse::InputParse(string fname) {
    std::ifstream inFile(fname);
    std::stringstream buffer;
    buffer << inFile.rdbuf();

    string line;
    while (getline(buffer, line)) {
        input.push_back(line);
    }
}

Seat::Seat(int r, int c, char v)
    : row(r), col(c), neighborCount(0), val(v) {
}
void Seat::genNeighbors(vector<vector<Seat>>& seats) {
    for (int r = row - 1; r <= row + 1; r++) {
        for (int c = col - 1; c <= col + 1; c++) {
            if (r == row && c == col)
                continue;
            if (r < 0 || r >= seats.size())
                continue;
            if (c < 0 || c >= seats[r].size())
                continue;
            neighbors.push_back({r, c});
        }
    }
}
void Seat::sightNeighbors(vector<vector<Seat>>& seats) {
    neighborCount = 0;
    cout << row - 1 << " : " << col << endl;
    neighborCount += seats[row-1][col].look(-1, 0, seats);
    // neighborCount += seats[row+1][col].look(1, 0, seats);
    // neighborCount += seats[row][col-1].look(0, -1, seats);
    // neighborCount += seats[row][col+1].look(0, 1, seats);
    // neighborCount += seats[row-1][col-1].look(-1, -1, seats);
    // neighborCount += seats[row-1][col+1].look(-1, 1, seats);
    // neighborCount += seats[row+1][col+1].look(1, 1, seats);
    // neighborCount += seats[row+1][col-1].look(1, -1, seats);
    // !! The error is occuring because Seat::look is checking it's own value
    // !! It should not care about it's own value when evaluating neighbors.
}
int Seat::look(int r_dir, int c_dir, vector<vector<Seat>>& seats) {
    cout << "look: " << row << " : " << col << endl;
    cout << r_dir << " : "  << c_dir << endl;
    if (val == '#') {
        cout << "found full" << endl;
        return 1;
    }
    if (val == 'L') {
        cout << "found empty" << endl;
        return 0;
    }
    if (row <= 0 || row >= seats.size() - 1) {
        cout << "row oob" << endl;
        return 0;
    }
    if (col <= 0 || row >= seats[0].size() - 1) {
        cout << "col oob" << endl;
        return 0;
    }
    cout << "recursing" << endl;
    return seats[row + r_dir][col + c_dir].look(r_dir, c_dir, seats);
}
void Seat::neighborSum(vector<vector<Seat>>& seats) {
    neighborCount = 0;
    for (auto& seat : neighbors) {
        if (seats[seat.first][seat.second].val == '#') {
            neighborCount++;
        }
    }
}
void Seat::modify() {
    if (this->val == '#' && neighborCount >= 5) {
        this->val = 'L';
        return;
    }
    if (this->val == 'L'  && neighborCount == 0) {
        this->val = '#';
    }
}
void genAllNeighbors(vector<vector<Seat>>& seats) {
    for (int row = 0; row < seats.size(); row++) {
        for (int col = 0; col < seats[row].size(); col++) {
            seats[row][col].genNeighbors(seats);
        }
    }
}

void checkSums(vector<vector<Seat>>& seats) {
    for (int row = 0; row < seats.size(); row++) {
        for (int col = 0; col < seats[row].size(); col++) {
            seats[row][col].neighborSum(seats);
        }
    }
}
void checkRecursive(vector<vector<Seat>>& seats) {
    for (int row = 0; row < seats.size(); row++) {
        for (int col = 0; col < seats[row].size(); col++) {
            cout << "checkRecurse -> " << row << " : " << col << endl;
            seats[row][col].sightNeighbors(seats);
            cout << "next seat" << endl;
        }
    }
}

void modifySeats(vector<vector<Seat>>& seats) {
    for (int row = 0; row < seats.size(); row++) {
        for (int col = 0; col < seats[row].size(); col++) {
            seats[row][col].modify();
        }
    }
}
void cycle(vector<vector<Seat>>& seats) {
    checkRecursive(seats);
    modifySeats(seats);
}
int countSeats(vector<vector<Seat>> seats) {
    int count = 0;
    for (int row = 0; row < seats.size(); row++) {
        for (int col = 0; col < seats[row].size(); col++) {
            if (seats[row][col].val == '#') {
                count++;
            }
        }
    }
    return count;
}

int main() {
    InputParse in("day11seats.txt");
    vector<vector<Seat>> seats;
    for (int row = 0; row < in.input.size(); row++) {
        vector<Seat> temp;
        for (int col = 0; col < in.input[row].size(); col++) {
            temp.push_back(Seat(row, col, in.input[row][col]));
        }
        seats.push_back(temp);
    }
    genAllNeighbors(seats);
    int count = 0;
    // while (count < 1000) {
    //     cycle(seats);
    //     cout << countSeats(seats) << endl;
    //     count++;
    // }
    cycle(seats);
    for (auto& row : seats) {
        for (auto& col : row) {
            cout << col.val;
        }
        cout << endl;
    }
    cycle(seats);
    for (auto& row : seats) {
        for (auto& col : row) {
            cout << col.val;
        }
        cout << endl;
    }

}
