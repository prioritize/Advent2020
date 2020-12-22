#include <string>
#include <regex>
#include <vector>
#include <fstream>
#include <iostream>
#include <math.h>

using std::regex;
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
    int col, row, rows, cols;
    string colStr, rowStr;
    int seatID;
    explicit Seat(string seat, int rows, int cols) {
        seatInfo = seat;
        rows = rows;
        cols = cols;
        rowStr = seatInfo.substr(0, 7);
        colStr = seatInfo.substr(7, 3);
        row = findRow(0, rows, 0, rowStr);
        col = findRow(0, cols, 0, colStr);
        calcId();
    }
    int findRow(int min, int max, int iter, string& in) {
        int range = max - min;
        if (range == 1) {
            if (in[iter] == 'F') {
                return min;
            }
            return max;
        }
        if (in[iter] == 'F' | in[iter] == 'L') {
            return findRow(min, max - ceil(range * 0.5), ++iter, in);
        } else if (in[iter] == 'B' || in[iter] == 'R') {
            return findRow(min + ceil(range * 0.5), max, ++iter, in);
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
    Seat mySeat(data.input[0], 127, 7);
    for (auto& line : data.input) {
        seats.push_back(Seat(line, 127, 7));
    }
    int max = 0;
    for (auto seat : seats) {
        if (seat.seatID > max) {
            max = seat.seatID;
            cout << seat.seatInfo << endl;
            cout << seat.col << endl;
            cout << seat.row << endl;
        }
        cout << max << endl;
    }
    // cout << mySeat.seat << endl;
    string t("FBFBBFFRLR");
    Seat testSeat(t, 127, 7);
    cout << testSeat.row << endl;
}