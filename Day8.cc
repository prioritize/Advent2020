// Copyright: 2020 -- Jared Leach
#include <fstream>
#include <iostream>
#include <vector>
#include <functional>
#include <string>
#include <regex>
#include <map>
#include <set>

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::pair;
using std::set;



class InputParse {
 public:
    vector<std::pair<string, string>> commands;
    explicit InputParse(string fname) {
        std::ifstream inFile(fname);
        std::stringstream buffer;
        buffer << inFile.rdbuf();
        string test = buffer.str();
        std::regex c("(([a-z]{3})\\s([+-]\\d{1,4})\\b)");
        std::sregex_iterator
            currentMatch(test.begin(), test.end(), c);
        std::sregex_iterator lastMatch;
        while (currentMatch != lastMatch) {
            std::smatch match = *currentMatch;
            if (match.ready()) {
                std::pair<string, string> t({match[2], match[3]});
                commands.push_back(t);
            }
            currentMatch++;
        }
    }
};
class Program {
 public:
    vector<std::pair<string, int>> instructions;
    int currentOffset = 0;
    int accumulator = 0;
    std::set<int> visited;
    vector<int> backtrack;
    std::map<string, std::function<void(int)>> commands;

    std::function<void(int)> acc = [&](int toAdd) {
        accumulator = accumulator + toAdd;
        visited.insert(currentOffset);
        currentOffset++;
    };
    std::function<void(int)> nop = [&](int offset) {
        visited.insert(currentOffset);
        currentOffset++;
    };
    std::function<void(int)> jmp = [&](int jump) {
        visited.insert(currentOffset);
        currentOffset = currentOffset + jump;
    };
    explicit Program(const vector<pair<string, string>>& inInstructions) {
        for (auto& command : inInstructions) {
            if (command.second[0] == '-') {
                instructions.push_back(
                    {command.first, 0 - stoi(command.second.substr(1))});
            } else {
                instructions.push_back(
                    {command.first, stoi(command.second.substr(1))});
            }
        }

        commands.insert({"acc", acc});
        commands.insert({"jmp", jmp});
        commands.insert({"nop", nop});
    }
    int runProgram() {
        bool changed = false;
        int changedIndex;
        int storedAccumulator;
        set<int> storedVisited;
        while (1) {
            if (visited.count(642)) {
                return accumulator;
            }
            if (instructions[currentOffset].first == "jmp" && changed == false) {
                changed = true;
                changedIndex = currentOffset;
                storedAccumulator = accumulator;
                storedVisited = visited;
                commands["nop"](instructions[currentOffset].second);
            } else if (instructions[currentOffset].first == "nop" && changed == false) {
                changed = true;
                changedIndex = currentOffset;
                storedAccumulator = accumulator;
                storedVisited = visited;
                commands["jmp"](instructions[currentOffset].second);
            }
            if (visited.count(currentOffset)) {
                visited = storedVisited;
                accumulator = storedAccumulator;
                currentOffset = changedIndex;
                changed = false;
            }
            commands[instructions[currentOffset].first](instructions[currentOffset].second);
        }
    }
};
int main() {
    InputParse in("day8instructions.txt");
    Program p(in.commands);
    cout << p.runProgram() << endl;
}
