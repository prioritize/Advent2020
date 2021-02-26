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

int look(std::pair<int, int> l, std::pair<int, int> d, vector<vector<char>>* seats);

InputParse::InputParse(string fname) {
    std::ifstream inFile(fname);
    std::stringstream buffer;
    buffer << inFile.rdbuf();

    string line;
    while (getline(buffer, line)) {
        vector<char> temp;
        for (auto& c : line) {
            temp.push_back(c);
        }
        input.push_back(temp);
        temp.clear();
    }
}

int neighbors(int row, int col, vector<vector<char>>* seats,
            vector<std::pair<int, int>> directions) {
    int n = 0;
    vector<vector<char>>&s = *seats;
    for (auto& d : directions) {
        n += look({row+d.first, col+d.second}, d, seats);
    }
// for (auto l : seats) {
    //     for (auto c  : l) {

    //     }
    // }
    return n;
}
int look(std::pair<int, int> l, std::pair<int, int> d, vector<vector<char>>* seats) {
    vector<vector<char>> &s = *seats;
    // cout << l.first << " : " << l.second << d.first << " : " << d.second << endl;
    if (l.first < 0 || l.first >= s.size()) {
        return 0;
    }
    if (l.second < 0 || l.second >= s[l.first].size()) {
        return 0;
    }
    if (s[l.first][l.second] == '#') {
        return 1;
    }
    if (s[l.first][l.second] == 'L') {
        return 0;
    }
    return look({l.first + d.first, l.second + d.second}, d, seats);
}
void lookAll(vector<vector<char>>* seats) {
    vector<vector<char>>&s = *seats;
    vector<std::pair<int, int>> directions;
    directions.push_back({-1, 0});
    directions.push_back({1, 0});
    directions.push_back({0, -1});
    directions.push_back({0, 1});
    directions.push_back({-1, -1});
    directions.push_back({-1, 1});
    directions.push_back({1, 1});
    directions.push_back({1, -1});
    vector<vector<int>> nVector;
    for (int r = 0; r < s.size(); r++) {
        vector<int> temp;
        for (int c = 0; c < s[r].size(); c++) {
            temp.push_back(neighbors(r, c, seats, directions));
        }
        nVector.push_back(temp);
        temp.clear();
    }
    for (int r = 0; r < s.size(); r++) {
        for (int c = 0; c < s[r].size(); c++) {
            if (nVector[r][c] >= 5 && s[r][c] == '#') {
                s[r][c] = 'L';
            }
            if (nVector[r][c] == 0 && s[r][c] == 'L') {
                s[r][c] = '#';
            }
        }
    }
    int count = 0;
    for (auto& r : s) {
        for (auto c : r) {
            if (c == '#')
                count++;
        }
    }
    cout << count << endl;
}

int main() {
    InputParse in("day11seats.txt");
    int i = 0;
    while (i < 100) {
        lookAll(&in.input);
        i++;
    }
}
