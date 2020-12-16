// Copyright 2020: -- Jared Leach
#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>


using std::map;
using std::string;
using std::vector;
using std::cout;
using std::endl;

class Command {
 public:
    char letter;
    map<char, int> password;
    std::pair<int, int> range;
    string passString;

    explicit Command(vector<string> line) {
        range = getRange(line[0]);
        letter = line[1][0];
        password = fillMap(line[2]);
        passString = line[2];
    }
    std::pair<int, int> getRange(string range) {
        std::pair<int, int> out;
        int index = 0;
        int start = 0;
        for (auto it = range.begin(); it != range.end(); ++it, index++) {
            if (*it == '-') {
                out.first = stoi(range.substr(0, index - start));
                out.second = stoi(range.substr(index + 1));
            }
        }
        return out;
    }
    map<char, int> fillMap(string password) {
        map<char, int> passMap;
        for (auto letter : password) {
            if (passMap.contains(letter)) {
                passMap[letter] = passMap[letter] + 1;
            } else {
                passMap[letter] = 1;
            }
        }
        return passMap;
    }
    bool checkValid() {
        int count = password[letter];
        if (count >= range.first && count <= range.second) {
            return true;
        }
        return false;
    }
    bool checkValid2() {
        int left = passString[range.first - 1];
        int right = passString[range.second - 1];
        if (right == left) {
            return false;
        }
        if (left != letter && right != letter) {
            return false;
        }
        return true;
    }
};
class DayTwo {
 public:
    vector<Command> entries;
    int valid = 0;
    int valid2 = 0;
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

        char delimiter = ' ';
        vector<vector<string>> commands;
        for (auto line : passwords) {
            commands.push_back(splitString(line, delimiter));
        }
        for (auto command : commands) {
            entries.push_back(Command(command));
        }
        for (auto entry : entries) {
            if (entry.checkValid()) {
                valid++;
            }
            if (entry.checkValid2()) {
                valid2++;
            }
        }
    }
    vector<string> splitString(string input, char delimiter) {
        vector<string> out;
        int mover = 0;
        int start = 0;
        int length = 0;
        while (mover < input.size()) {
            if (input[mover] == delimiter) {
                out.push_back(input.substr(start, mover-start));
                start = mover + 1;
            }
            if (mover == (input.size() - 1)) {
                out.push_back(input.substr(start));
                return out;
            }
            mover++;
        }
        std::cout << "Theres' likely an error in here boys" << std::endl;
        return out;
    }

};

int main() {
    DayTwo d2("day2passwords.txt");
    std::cout << "valid: " << d2.valid << std::endl;
    std::cout << "valid2: " << d2.valid2 << std::endl;
}
