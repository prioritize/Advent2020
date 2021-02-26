// Copyright: 2020 -- Jared Leach
#ifndef DAY14_HPP_
#define DAY14_HPP_
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>

using std::vector;
using std::string;
using std::cout;
using std::endl;
using reg_iter = std::sregex_iterator;

struct Command {
    string type;
    string mask;
    int address;
    int value;
};

class InputParse {
 public:
    string fname;
    string input;
    vector<Command> commands;
    explicit InputParse(string fname);
};

class DockingData {
 public:
    vector<Command> commands;
    int instruction;
    string mask;
    explicit DockingData(vector<Command> commands);
    void executeCommand();
    void applyMask();
    void setMemory();
};

#endif  // DAY14_HPP_
