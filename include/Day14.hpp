// Copyright: 2020 -- Jared Leach
#ifndef DAY14_HPP_
#define DAY14_HPP_
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>
#include <map>

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
 private:
    void increment();
 public:
    vector<Command> commands;
    int instruction;
    string mask;
    std::map<int, int> memory;
    explicit DockingData(vector<Command> commands);
    void executeCommand();
    int applyMask(int value);
    void setMemory(int location, int value);
    void setMask(string mask);
};

#endif  // DAY14_HPP_
