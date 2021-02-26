// Copyright: Jared Leach - 2020
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <map>

using std::vector;
using std::string;
using std::cout;
using std::endl;

class InputParse {
 public:
    vector<int> input;
    std::map<int, uint64_t> dynamic;
    explicit InputParse(string fname) {
        std::ifstream inFile(fname);
        std::stringstream buffer;
        buffer << inFile.rdbuf();

        string line;
        while (getline(buffer, line)) {
            input.push_back(stoi(line));
        }
        input.push_back(0);
        std::sort(input.begin(), input.end());
        input.push_back(input[input.size()-1]+3);
    }
    // Write a recursive brute force function to evaluate all the 
    uint64_t iterate(int index) {
        // Ending case for recursive function
        if (index == input.size() - 1) {
            return 1;
        }
        if (dynamic.contains(index)) {
            return dynamic[index];
        }
        uint64_t answer = 0;
        for (int j = index + 1; j < input.size(); j++) {
            if ((input[j]) - input[index] <= 3) {
                answer += iterate(j);
            }
        }
        dynamic.insert({index, answer});
        return answer;
    }
};

class Adapter {
 public:
    int joltage;
    explicit Adapter(int j) {
        joltage = j;
    }
};

int main() {
    InputParse in("day10adapters.txt");
    vector<Adapter> adapters;
    for (auto& a : in.input) {
        adapters.push_back(Adapter(a));
    }
    vector<int> differences(4, 0);
    for (int index = 0; index < adapters.size() - 1; index++) {
        differences[adapters[index + 1].joltage - adapters[index].joltage]++;
    }
    for (auto& difference : differences) {
        cout << difference << endl;
    }
    cout << in.iterate(0) << endl;
}

