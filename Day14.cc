// Copyright: 2020 -- Jared Leach
#include "Day14.hpp"

InputParse::InputParse(string fname)
    : fname(fname) {
    std::ifstream inFile(fname);
    std::stringstream buffer;
    buffer << inFile.rdbuf();
    string temp;
    while (getline(buffer, temp)) {
        input = input + "\n" + temp;
    }
    std::regex reg("((mask|mem[[](\\d*)[\\]]))\\s=\\s(\\w*)\\b");
    std::sregex_iterator currentMatch(input.begin(), input.end(), reg);
    std::sregex_iterator lastMatch;
    while (currentMatch != lastMatch) {
        std::smatch match = *currentMatch;
        if (match.ready()) {
            if (match[2] == "mask") {
                Command c;
                c.type = "mask";
                c.mask = match[4];
                commands.push_back(c);
            } else {
                Command c;
                c.type = "mem";
                c.address = stoi(match[3].str());
                c.value = stoi(match[4].str());
                commands.push_back(c);
            }
        }
        currentMatch++;
    }
}
DockingData::DockingData(vector<Command> commands)
    : commands(commands), instruction(0),
    mask("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX") {}

void DockingData::executeCommand() {
    Command current = commands[instruction];
    if (current.type == "mask") {
        applyMask();
    } else {
        setMemory();
    }
}
void DockingData::applyMask() {
    for (int i = 0; i < commands[instruction].mask.size(); ++i) {
        if (commands[instruction].mask == "X") {
            continue;
        } else {
            mask[i] = commands[instruction].mask[i];
        }
    }
}
void DockingData::setMemory() {

}
