#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>

using std::vector;
using std::string;
using std::cout;
using std::endl;

class InputParse {
 public:
    vector<vector<string>> groups;
    explicit InputParse(string fname) {
        std::ifstream inFile(fname);
        std::stringstream buffer;
        buffer << inFile.rdbuf();

        string line;
        vector<string> temp;
        while (getline(buffer, line)) {
            if (line.size() == 0) {
                groups.push_back(temp);
                temp.clear();
            } else {
                temp.push_back(line);
            }
        }
        groups.push_back(temp);
    }
};

class Group {
 public:
    vector<string> in;
    std::map<char, uint32_t> answers;
    int groupsize;
    int questions = 0;;
    int common = 0;
    explicit Group(vector<string> input) {
        in = input;
        for (auto& line : in) {
            for (auto& q : line) {
                if (answers.contains(q)) {
                    answers[q] = answers[q] + 1;
                    continue;
                }
                answers[q] = 1;
            }
        }
        questions = answers.size();
        groupsize = in.size();
        checkCommon();
    }
    void checkCommon() {
        for (auto& [key, value] : answers) {
            if (value == groupsize) {
                common++;
            }
        }
    }
};

int main() {
    InputParse in("day6questions.txt");
    vector<Group> groups;
    for (auto& group : in.groups) {
        groups.push_back(Group(group));
    }
    int questions = 0;
    int common = 0;
    for (auto& group : groups) {
        questions = questions + group.questions;
        common = common + group.common;
    }
    cout << questions << endl;
    cout << common << endl;
    
}