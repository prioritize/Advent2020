// Copyright 2020 - Jared Leach
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <regex>

using std::vector;
using std::string;
class InputParse {
 public:
    vector<vector<string>> rawIDs;
    vector<vector<string>> ids;
    explicit InputParse(string fname) {
        std::ifstream idFile;
        idFile.open(fname);
        string line;
        vector<string> id;
        string newLine("\n");
        if (idFile.is_open()) {
            while (getline(idFile, line)) {
                if (line.size() == 0) {
                    rawIDs.push_back(id);
                    id.clear();
                } else {
                    id.push_back(line);
                }
            }
            rawIDs.push_back(id);
        }
        vector<string> newID;
        for (auto id : rawIDs) {
            for (auto line : id) {
                vector<string> temp = split(line, ' ');
                for (auto entry : temp) {
                    newID.push_back(entry);
                }
            }
            ids.push_back(newID);
            newID.clear();
        }
    }
    vector<string> split(string line, char delimiter) {
        int index = 0;
        int subStart = 0;
        vector<string> substrings;
        for (string::iterator it = line.begin(); it <= line.end(); ++it, ++index) {
            if (*it == ' ') {
                substrings.push_back(line.substr(subStart, index - subStart));
                subStart = index + 1;
            } else if (it == line.end()) {
                substrings.push_back(line.substr(subStart));
            }
        }
        return substrings;
    }
};

class Identification {
 public:
    std::map<string, string> id;
    explicit Identification(vector<string> vitals) {
        id["byr"] = "dis bad";
        id["iyr"] = "dis bad";
        id["eyr"] = "dis bad";
        id["hgt"] = "dis bad";
        id["hcl"] = "dis bad";
        id["ecl"] = "dis bad";
        id["pid"] = "dis bad";
        id["cid"] = "dis bad";
        parseVital(vitals);
    }
    void parseVital(vector<string> vitals) {
        for (auto vital : vitals) {
            int index = 0;
            string key, value;
            for (string::iterator it = vital.begin(); it != vital.end(); ++it, ++index) {
                if (*it == ':') {
                    key = vital.substr(0, index);
                    value = vital.substr(index + 1);
                    if (id.contains(key)) {
                        std::cout << id[key] << std::endl;
                        id[key] = value;
                    } else {
                        std::cout << "key not in map" << std::endl;
                    }
                }
            }
        }
    }
    bool validateID() {
        for (auto it = id.begin(); it != id.end(); ++it) {
            if (it->second == "dis bad") {
                if (it->first == "cid") {
                    continue;
                } else {
                    return false;
                }
            }
        }
        return true;
    }
};

int main() {
    vector<Identification> batch;
    InputParse input("day4ids.txt");
    for (auto id : input.ids) {
        Identification newID(id);
        batch.push_back(newID);
    }
    int numValid = 0;
    for (auto id : batch) {
        if(id.validateID()) {
            numValid++;
        }
    }
    std::cout << numValid << std::endl;
    std::cout << batch.size() << std::endl;
}
