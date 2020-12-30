// Copyright: Jared Leach -- 2020

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>
#include <sstream>
#include <map>

using std::vector;
using std::string;
using std::pair;
using std::cout;
using std::endl;

class InputParse {
 public:
    vector<pair<char, int>> helmCommands;
    explicit InputParse(string fname);
};

InputParse::InputParse(string fname) {
    std::ifstream inFile(fname);
    std::stringstream buffer;
    buffer << inFile.rdbuf();
    string temp;
    while (getline(buffer, temp)) {
        pair<char, int> command(temp.substr(0, 1)[0], stoi(temp.substr(1)));
        helmCommands.push_back(command);
    }
}
class Vessel {
 public:
    int h, v, d;
    char f;
    vector<pair<char, int>> commands;
    std::map<char, std::map<char, std::map<int, char>>> luTable;
    explicit Vessel(vector<pair<char, int>> in)
        : h(0), v(0), d(0), f('E'), commands(in), luTable() {}
    void rotate(char dir, int degrees);
    void move(char direction, int offset);
    void fillTable();
    void transit();
};
void Vessel::fillTable() {
    luTable['E']['L'][90] = 'N';
    luTable['E']['L'][180] = 'W';
    luTable['E']['L'][270] = 'S';
    luTable['E']['R'][90] = 'S';
    luTable['E']['R'][180] = 'W';
    luTable['E']['R'][270] = 'N';

    luTable['W']['L'][90] = 'S';
    luTable['W']['L'][180] = 'E';
    luTable['W']['L'][270] = 'N';
    luTable['W']['R'][90] = 'N';
    luTable['W']['R'][180] = 'E';
    luTable['W']['R'][270] = 'S';

    luTable['S']['L'][90] = 'E';
    luTable['S']['L'][180] = 'N';
    luTable['S']['L'][270] = 'W';
    luTable['S']['R'][90] = 'W';
    luTable['S']['R'][180] = 'N';
    luTable['S']['R'][270] = 'E';

    luTable['N']['L'][90] = 'W';
    luTable['N']['L'][180] = 'S';
    luTable['N']['L'][270] = 'E';
    luTable['N']['R'][90] = 'E';
    luTable['N']['R'][180] = 'S';
    luTable['N']['R'][270] = 'W';
}

void Vessel::rotate(char dir, int degrees) {
    cout << luTable[f][dir][degrees];
    f = luTable[f][dir][degrees];
    cout << "forward is: " << f << endl;
}

void Vessel::move(char direction, int offset) {
    if (direction == 'E') {
        h += offset;
        return;
    }
    if (direction == 'W') {
        h -= offset;
        return;
    }
    if (direction == 'N') {
        v += offset;
        return;
    }
    if (direction == 'S') {
        v -= offset;
        return;
    }
    if (direction == 'F') {
        move(f, offset);
    }
    if (direction == 'R' || direction == 'L') {
        rotate(direction, offset);
    }
}
void Vessel::transit() {
    for (auto& c : commands) {
        move(c.first, c.second);
    }
    cout << h << " : " << v << endl;
}
int main() {
    InputParse in("day12directions.txt");
    Vessel v(in.helmCommands);
    v.fillTable();
    cout << v.luTable['E']['L'][270];
    v.transit();
}
