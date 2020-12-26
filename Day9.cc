// Copyright 2020 -- Jared Leach
#include <set>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

using std::vector;
using std::string;
using std::set;
using std::cout;
using std::endl;

class InputParse {
 public:
    vector<int64_t> input;
    explicit InputParse(string fname) {
        std::ifstream inFile(fname);
        std::stringstream buffer;
        buffer << inFile.rdbuf();
        string line;
        while (getline(buffer, line)) {
            input.push_back(stol(line));
        }
    }
};

class Hax {
 public:
    vector<int64_t> input;
    set<int64_t> preamble;
    int currIdx;
    int preambleLen;
    set<int64_t> contiguous;
    int64_t q;
    Hax(vector<int64_t> in, int64_t p) {
        // Store input
        input = in;
        // Store the preamble length
        preambleLen = p;
        // Store iteration starting location
        currIdx = preambleLen;

        // Load up the intial set with the first preambleLen values
        for (int index = 0; index < preambleLen; index++) {
            preamble.insert(input[index]);
        }
        // Iterate through performing twoSum and iterating across input
        while (twoSum(input[currIdx])) {
            handleIteration();
        }
        findWindow();
    }
    // Standard twoSum (Two pointers)
    bool twoSum(int64_t query) {
        std::set<int64_t>::reverse_iterator rit;
        std::set<int64_t>::iterator it;
        it = preamble.begin();
        rit = preamble.rbegin();
        while (*it < *rit) {
            int64_t c = *it + *rit;
            if (c == query)
                return true;
            if (c > query) {
                rit++;
            } else {
                it++;
            }
        }
        q = query;
        return false;
    }
    // Handle removal and insert of values into the set
    void handleIteration() {
        int startIdx = currIdx - preambleLen;
        preamble.erase(input[startIdx]);
        preamble.insert(input[++currIdx]);
    }
    // Growing->sliding window looking for the value found in previous step
    void findWindow() {
        int start = 0;
        int end = 1;
        int sum = input[start] + input[end];
        contiguous.insert(input[start]);
        contiguous.insert(input[end]);
        while (sum != q) {
            if (sum < q) {
                end++;
                sum = sum + input[end];
                contiguous.insert(input[end]);
            } else if (sum > q) {
                contiguous.erase(input[start]);
                sum = sum - input[start++];
            }
        }
        std::set<int64_t>::iterator it = contiguous.begin();
        std::set<int64_t>::reverse_iterator rit = contiguous.rbegin();
        cout << *it << " " << *rit << endl;
    }
};

int main() {
    InputParse in("day9hacks.txt");
    Hax h(in.input, 25);
}
