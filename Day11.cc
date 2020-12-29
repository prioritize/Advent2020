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
void Seat::neighborSum(vector<vector<Seat>>& seats) {
    neighborCount = 0;
    for (auto& seat : neighbors) {
        if (seats[seat.first][seat.second].val == '#') {
            neighborCount++;
        }
    }
}
void Seat::modify() {
    if (this->val == '#' && neighborCount >= 4) {
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
void modifySeats(vector<vector<Seat>>& seats) {
    for (int row = 0; row < seats.size(); row++) {
        for (int col = 0; col < seats[row].size(); col++) {
            seats[row][col].modify();
        }
    }
}
void cycle(vector<vector<Seat>>& seats) {
    checkSums(seats);
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
    while (count < 100) {
        cycle(seats);
        cout << countSeats(seats) << endl;
        count++;
    }
}
