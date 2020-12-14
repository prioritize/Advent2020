// Copyright 2020: -- Jared Leach
#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

using std::map;
using std::string;
using std::vector;

class DayTwo {
 public:
    map<char, int> passwords;

    explicit DayTwo(string fname) {
        std::ifstream instructions;
        instructions.open(fname);
        vector<string> passwords;
        if (instructions.is_open()) {
            string line;
            while (getline(instructions, line)) {
                passwords.push_back(line);
            }
        } else {
            std::cout << "Unable to open passwords file" << std::endl;
            exit(EXIT_FAILURE);
        }

    }
    vector<string> splitString(string input, char delimiter) {

    }
};

int main() {
    DayTwo d2("day2passwords.txt");
}