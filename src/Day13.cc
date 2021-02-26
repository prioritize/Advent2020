// Copyright: Jared Leach -- 2020

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <regex>

using std::vector;
using std::string;
using std::map;
using std::cout;
using std::endl;

class InputParse {
 public:
    int departure;
    map<int, int> schedule;
    string fname;
    explicit InputParse(string fname);
};

InputParse::InputParse(string fname)
: fname(fname) {
    std::ifstream InFile(fname);
    std::stringstream buffer;
    buffer << InFile.rdbuf();
    string temp;
    getline(buffer, temp);
    departure = stoi(temp);
    temp.clear();
    std::regex c("([0-9]+)?x?,?");
    getline(buffer, temp);
    std::sregex_iterator currentMatch(temp.begin(), temp.end(), c);
    std::sregex_iterator lastMatch;
    int offset = 0;
    while (currentMatch != lastMatch) {
        std::smatch match = *currentMatch;
        if (match.ready()) {
            if (match[1] ==  "") {
            } else {
                schedule.insert({stoi(match[1]), offset});
            }
            offset++;
            // schedule.insert({stoi(match[0]), true});
            // cout << stoi(match[0]) << endl;
        }
        currentMatch++;
    }
}

int main() {
    InputParse in("day13.txt");
    int earliest = INT32_MAX;
    for (auto& [key, value] : in.schedule) {
        cout << "key: " << key << " position: " << value << endl;
        int temp = in.departure / key;
        temp++;
        int current = (temp * key) - in.departure;
        if (current < earliest) {
            cout << "earliest key is: " << key << endl;
            earliest = current;
        }
    }

    cout << earliest << endl;
    uint64_t a = 983;
    uint64_t b = 7;
    uint64_t offset = 17;
    uint64_t holder = 0;
    uint64_t counter = 0;
    while (1) {
        holder = (a * counter) - offset;
        for (auto& [key, value] : in.schedule) {
            if (!((holder - value) % key == 0)) {
                break;
            }
            if (key == 983) {
                cout << holder << endl;
            }
        }
        counter++;
    }
}
