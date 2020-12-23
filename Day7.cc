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
    bool hasGold = false;
	explicit Bag(string bagDef) {
		std::regex bagMatch("(\\w+\\s\\w+)\\sbags?");
		std::sregex_iterator currentMatch(bagDef.begin(), bagDef.end(), bagMatch);
		std::sregex_iterator lastMatch;
        bool first = true;
		while (currentMatch != lastMatch) {
			std::smatch match;
			match = *currentMatch;
			if (match.ready()) {
                if (first) {
                    descriptor = match[1];
                    first = false;
                } else {
                    bags[match[1]] = 1;
                }
			}
            bagDef = match.suffix();
            currentMatch++;
		}
	}
    bool contains(string bag) {
        return bags.contains(bag);
    }
};



int main() {
	InputParse in("day7bags.txt");
	vector<Bag> rules;
    std::map<string, std::map<string, int>> allBags;
	std::regex bagMatch("(\\w+\\s\\w+)\\sbags?");
	for (auto& entry : in.input) {
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
    cout << std::boolalpha;
    std::queue<string> bags;
    string target = "shiny gold";
    for (auto& [key, value] : allBags[target]) {
        bags.push(key);
    }
    while (bags.size() > 0) {
        for (auto& [key, value] : allBags[bags.front()]) {
            if (!allBags[target].contains(key)) {
                allBags[target][key] = 1;
                bags.push(key);
                continue;
            }
        }
        bags.pop();
    }
    cout << allBags["shiny gold"].size() << endl;
    cout << endl;
}
