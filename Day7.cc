#include <fstream>
#include <iostream>
#include <vector>
#include <regex>
#include <queue>

using std::cout;
using std::endl;
using std::string;
using std::vector;

class InputParse {
 public:
    std::map<string, int> bagTypes;
    std::vector<string> input;
    explicit InputParse(string fname) {
        std::ifstream inFile(fname);
        std::stringstream buffer;
        buffer << inFile.rdbuf();
        string line;
        while (getline(buffer, line)) {
            input.push_back(line);
        }
    }
};

class Bag {
 public:
    string descriptor;
    std::map<string, int> bags;
    explicit Bag(string bagDef) {
        std::regex bagMatch("(([0-9])\\s)?(\\w+\\s\\w+)\\sbags?");
        std::sregex_iterator currentMatch(bagDef.begin(), bagDef.end(), bagMatch);
        std::sregex_iterator lastMatch;
        while (currentMatch != lastMatch) {
            std::smatch match = *currentMatch;
            if (match.ready()) {
                if (match[1].str().size() == 0) {
                    if (match[3] == "no other") {
                        bags[match[3].str()] = 0;
                    } else {
                        descriptor = match[3].str();
                    }
                } else {
                    bags[match[3].str()] = stoi(match[2].str());
                }
            }
            currentMatch++;
        }
    }

    bool contains(string bag) {
        return bags.contains(bag);
    }
};
int findCombos(string target, std::map<string, std::map<string, int>> allBags) {
    cout << std::boolalpha;
    std::queue<string> bags;
    for (auto &[key, value] : allBags[target]) {
        bags.push(key);
    }
    while (bags.size() > 0) {
        for (auto &[key, value] : allBags[bags.front()]) {
            if (!allBags[target].contains(key)) {
                allBags[target][key] = 1;
                bags.push(key);
                continue;
            }
        }
        bags.pop();
    }
    return allBags[target].size();
}
// TODO: Satchel class that holds collection of bags and then recurses through them to find the number of bags of each
class Satchel {
 public:
    std::map<string,  Bag> inside;
    explicit Satchel(InputParse in) {
        for (auto entry : in.input) {
            Bag b(entry);
            // Insert does not call the default constructor, operator[] does!
            inside.insert({b.descriptor, b});
        }
    }
    int recurse(string target) {
        int bags = 0;
        Bag currentBag = inside.at(target);
        for (auto& [key, value] : currentBag.bags) {
            if (key == "no other")
                return 0;
            bags = bags + value + value * recurse(key);
        }
        return bags;
    }
};

std::map<string, std::map<string, int>> buildGazinta(vector<string> in) {
    std::map<string, std::map<string, int>> allBags;
    std::regex bagMatch("(\\w+\\s\\w+)\\sbags?");
    for (auto &entry : in) {
        std::sregex_iterator currentMatch(entry.begin(), entry.end(), bagMatch);
        std::sregex_iterator lastMatch;
        string outer;
        int first = true;
        while (currentMatch != lastMatch) {
            std::smatch match = *currentMatch;
            if (!match.ready())
                continue;
            string bag = match[1].str();
            // if (!allBags.contains(bag))
            //     allBags[bag] = {};
            if (first == true) {
                outer = bag;
                first = false;
            } else {
                allBags[bag][outer] = 1;
            }
            currentMatch++;
        }
    }
    return allBags;
}

int main() {
    InputParse in("day7bags.txt");
    std::map<string, std::map<string, int>> allBags = buildGazinta(in.input);
    cout << findCombos("shiny gold" , allBags) << endl;
    Satchel satchel(in);
    cout << satchel.recurse("shiny gold") << endl;
}
