#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <math.h>
#include <sstream>

using std::vector;
using std::string;
using std::cout;
using std::endl;

class InputParse {
 public:
    vector<string> input;
    explicit InputParse(string fname) {
        std::ifstream inFile(fname);
        std::stringstream buffer;
        buffer << inFile.rdbuf();
        string line;
        while(getline(buffer, line)) {
            input.push_back(line);
        }
    }
};

class Seat {
 public:
    string seatInfo;
    uint32_t col, row;
    string colStr, rowStr;
    int seatID;
    explicit Seat(string seat) {
        row = 0;
        col = 0;
        seatInfo = seat;
        rowStr = seatInfo.substr(0, 7);
        colStr = seatInfo.substr(7, 3);
        findRow(rowStr);
        findCol(colStr);
        calcId();
    }
    int findRow(string& in) {
        int len = in.size() - 1;
        for (auto bit : in) {
            if (bit == 'B') {
                row |= 1UL << len;
            }
            len--;
        }
    }
    int findCol(string& in) {
        int len = in.size() - 1;
        for (auto bit : in) {
            if (bit == 'R') {
                col |= 1UL << len;
            }
            len--;
        }
    }
    void calcId() {
        seatID = row * 8 + col;
    }
};

int main() {
    int maxRow = 127;
    vector<Seat> seats;
    InputParse data("day5seats.txt");
    for (auto& line : data.input) {
        seats.push_back(Seat(line));
    }
    std::map<int, bool> elimMap;
    for (int i = 0; i < 1024; ++i) {
        elimMap[i] = true;
    }

    for (auto& seat : seats) {
        elimMap.erase(seat.seatID);
    }
    for (auto [key, value] : elimMap) {
        cout << key << endl;
    }
}