// Copyright 2020 - Jared Leach
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <regex>
#include <functional>

using std::vector;
using std::string;
using std::cout;
using std::endl;
using regex_iterator = std::regex_token_iterator<string::iterator>;
class InputParse {
 public:
    vector<string> rawIDs;
    vector<vector<string>> ids;
    explicit InputParse(string fname) {
        std::ifstream idFile;
        idFile.open(fname);
        string line;
        string id;
        string newLine("\n");
        if (idFile.is_open()) {
            while (getline(idFile, line)) {
                if (line.size() == 0) {
                    rawIDs.push_back(id);
                    id = "";
                } else {
                    if (id.size() == 0) {
                        id = line;
                    } else {
                        id = id + " " + line;
                    }
                }
            }
            rawIDs.push_back(id);
        }
    }
};

class Identification {
 public:
    std::map<string, bool> id;
    std::map<string, std::function<bool(string)>> validators;
    std::map<string, bool> eyeColors;
    bool isValid = false;
    string inString;
    
    explicit Identification(string vitals) {
        inString = vitals;
        id["byr"] = false;
        id["iyr"] = false;
        id["eyr"] = false;
        id["hgt"] = false;
        id["hcl"] = false;
        id["ecl"] = false;
        id["pid"] = false;
        id["cid"] = true;

        eyeColors["amb"] = true;
        eyeColors["blu"] = true;
        eyeColors["brn"] = true;
        eyeColors["gry"] = true;
        eyeColors["grn"] = true;
        eyeColors["hzl"] = true;
        eyeColors["oth"] = true;

        std::function<bool(string)> byrCheck = [&](string in) {
            int year = stoi(in);
            if ((year >= 1920) && (year <= 2002)) {
                return true;
            }
            return false;
        };
        std::function<bool(string)> iyrCheck = [&](string in) {
            int year = stoi(in);
            if (year >= 2010 && year <= 2020) {
                return true;
            }
            return false;
        };
        std::function<bool(string)> eyrCheck = [&](string in) {
            int year = stoi(in);
            if (year >= 2020 && year <= 2030) {
                return true;
            }
            return false;
        };
        std::function<bool(string)> hgtCheck = [&](string height) {
            int submatches[] = {1, 2};
            std::regex h("(\\d{2,3})(cm|in)");
            std::sregex_iterator currentMatch(height.begin(), height.end(), h);
            std::sregex_iterator lastMatch;
            while (currentMatch != lastMatch) {
                std::smatch match = *currentMatch;
                if (match.ready()) {
                    string unit = match[2];
                    int number = stoi(match[1]);
                    if (unit == "in" && number >= 59 && number <= 76) {
                        return true;
                    }
                    if (unit == "cm" && number >= 150 && number <= 193) {
                        return true;
                    }
                } else {
                    return false;
                }
                return false;
            }
        };
        std::function<bool(string)> hclCheck = [&](string hair) {
            std::regex hcl("#[0-9a-f]{6}\\b");
            std::sregex_iterator currentMatch(hair.begin(), hair.end(), hcl);
            std::sregex_iterator lastMatch;
            while (currentMatch != lastMatch) {
                std::smatch match = *currentMatch;
                return true;
            }
            return false;
        };
        std::function<bool(string)> eclCheck = [&](string eyes) {
            std::regex ecl("amb\\b|blu\\b|brn\\b|gry\\b|grn\\b|hzl\\b|oth\\b");
            std::sregex_iterator currentMatch(eyes.begin(), eyes.end(), ecl);
            std::sregex_iterator lastMatch;
            while (currentMatch != lastMatch) {
                std::smatch match = *currentMatch;      
                return match.ready();
            }
            return false;
        };
        std::function<bool(string)> pidCheck = [&](string checkThis) {
            int submatches = 1;
            std::regex pid("[0-9]{9}\\b");
            std::sregex_iterator currentMatch(checkThis.begin(), checkThis.end(), pid);
            std::sregex_iterator lastMatch;
            while (currentMatch != lastMatch) {
                std::smatch match = *currentMatch;
                return match.ready();
            }
            return false;
        };
        std::function<bool(string)> cidCheck = [&](string checkThis) {
            return true;
        };
        validators["byr"] = byrCheck;
        validators["iyr"] = iyrCheck;
        validators["eyr"] = eyrCheck;
        validators["hgt"] = hgtCheck;
        validators["hcl"] = hclCheck;
        validators["ecl"] = eclCheck;
        validators["pid"] = pidCheck;
        validators["cid"] = cidCheck;

        parseVital(vitals);
    }
    void parseVital(string vitals) {
        std::regex_token_iterator<string::iterator> rend;
        int submatches[] = {1, 2};
        std::regex e("([a-z]{3}):([\\w#]*)");
        regex_iterator a(vitals.begin(), vitals.end(), e, submatches);
        while (a != rend) {
            try {
                string key = *a;
                id[key] = validators[key](*++a);
            } catch(const std::exception& e) {
                std::cerr << e.what() << '\n';
            }
            ++a;
        }
        isValid = validateID();
    }
    bool validateID() {
        std::cout << std::boolalpha;
        for (auto it = id.begin(); it != id.end(); ++it) {
            if (it->second == false) {
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
    for (auto id : input.rawIDs) {
        Identification newID(id);
        batch.push_back(newID);
    }
    int numValid = 0;
    for (auto id : batch) {
        if (id.isValid) {
            cout << id.inString << endl;
            // for (auto it = id.id.begin(); it != id.id.end(); it++) {
            //     cout << "key: " << it->first << " value: " << it->second << endl;
            // }
            cout << endl;
            numValid++;
        }
    }
    Identification currentID = batch[0];
    for (auto it = currentID.id.begin(); it != currentID.id.end(); it++) {
        cout << "key: " << it->first << " value: " << it->second << endl;
    }
    std::cout << numValid << std::endl;
    std::cout << batch.size() << std::endl;
}
