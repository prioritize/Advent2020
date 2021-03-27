// Copyright: 2020 -- Jared Leach
#include "../include/Day14.hpp"

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

void DockingData::applyMask() {
    for (uint i = 0; i < commands[instruction].mask.size(); ++i) {
        if (commands[instruction].mask == "X") {
            continue;
        } else {
            mask[i] = commands[instruction].mask[i];
        }
    }
}

void DockingData::setMemoryLocation(int address, int value) {
    // For this function...iterate through the mask,
    // if there's an x do nothing, if there's a 1 bitshift a 1,
    // if there's a zero bitshift the zero
    uint64_t temp = value;
    for (uint i = 0; i < mask.size(); ++i) {
        if (mask[i] == 'X') {
            continue;
        } else if (mask[i] == '0') {
            temp &= ~(1 << i);
        } else if (mask[i] == '1') {
            temp |= (1 << i);
        }
    }
}

void DockingData::setMask(string inMask) {
    mask = inMask;
}

void DockingData::parseInstruction() {
    if (commands[instruction].type == "mask") {
        cout << "stuff" << endl;
    }
}
